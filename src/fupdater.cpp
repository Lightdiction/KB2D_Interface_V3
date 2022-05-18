
#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/comhw.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QProcess>

#define SIZE_CY_FILE_BYTEMAX    100000
#define BYTE_SHIFT              11
#define PAGEDATA_MULTIPLE       (1 << BYTE_SHIFT)

#define DIST_RESSOURCES         "http://lightdiction.com/Ressources/"


/*
 * ======================================
 * Connect to Lightdiction Website
 * Detects if a new version is available
 * ======================================
 */
bool MainWindow::checkNewVersions()
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req((QUrl)(DIST_RESSOURCES + tr("VersionNotes.txt")));
    QNetworkReply *reply = nam.get(req);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer = reply->readAll();

    // Localize Version number
    int ind = buffer.indexOf("===========================================");
    if (ind == -1)
    {
        SendLog("Cannot connect to Website");
        return false;
    }
    int indEnd = buffer.indexOf("===========================================", ind + 1);
    int indFirm = buffer.indexOf("< FIRMWARE V") + QString("< FIRMWARE V").length();
    QString parsedFirmInt = "";
    QString parsedFirmDec = "";
    while ((buffer.at(indFirm) != '.') && (ind < buffer.length()))
    {
        parsedFirmInt.append(buffer.at(indFirm));
        indFirm++;
    }
    indFirm++;
    while ((buffer.at(indFirm) != ' ') && (ind < buffer.length()))
    {
        parsedFirmDec.append(buffer.at(indFirm));
        indFirm++;
    }
    lastParsedFirmware = parsedFirmInt.toInt() * 100 + parsedFirmDec.toInt();
    qDebug() << lastParsedFirmware;

    // Check parsing errors
    if (indEnd <= ind)
    {
        SendLog("Cannot parse Version file");
        return false;
    }

    // Find last version
    while (((buffer.at(ind) == '\n') || (buffer.at(ind) == '\r') || (buffer.at(ind) == 'V') || (buffer.at(ind) == '=')) && (ind < buffer.length()))
        ind++;
    QString resVersion = "";
    while ((buffer.at(ind) != ' ') && (ind < buffer.length()))
    {
        resVersion.append(buffer.at(ind));
        ind++;
    }

    // Check parsing errors
    if (ind >= indEnd)
    {
        SendLog("Cannot parse Version file");
        return false;
    }

    // Compare Versions
    if (qRound(resVersion.toFloat() * 100) == LAST_VERSION)
    {
        qDebug() << "Software up to date";
        return false;
    }
    else if (qRound(resVersion.toFloat() * 100) < LAST_VERSION)
    {
        SendLog("Living in the future?");
        return false;
    }
    else if (qRound(resVersion.toFloat() * 100) > LAST_VERSION)
    {
        // Find description
        while ((buffer.at(ind) != '\n') && (buffer.at(ind) != '\r') && (ind < buffer.length()))
            ind++;
        while (((buffer.at(ind) == '\n') || (buffer.at(ind) == '\r')) && (ind < buffer.length()))
            ind++;
        while ((buffer.at(ind) != '=') && (ind < buffer.length()))
        {
            newVersionDesc.append(buffer.at(ind));
            ind++;
        }
        SendLog("Update Requested - Actual Version = " + QString::number(LAST_VERSION));

        if (QMessageBox::question(this, tr("New version available"), tr("Version ") + resVersion + tr(" is available.\n\nDo you want to update and restart now?\n\n"
                                                                                                      "Content of this new version:\n") + newVersionDesc) == QMessageBox::Yes)
        {
            QEventLoop loopExe;
            QNetworkAccessManager namExe;
#ifdef WIN_PLATFORM
            QNetworkRequest reqExe((QUrl)(DIST_RESSOURCES "KB2D_v" + resVersion + "_setup.exe"));
#endif
#ifdef LIN_PLATFORM
            QNetworkRequest reqExe((QUrl)(DIST_RESSOURCES "KB2D_v" + resVersion + "_setup.deb"));
#endif
#ifdef MAC_PLATFORM
            QNetworkRequest reqExe((QUrl)(DIST_RESSOURCES "KB2D_v" + resVersion + "_setup.dmg"));
#endif
            QNetworkReply *replyExe = namExe.get(reqExe);
            connect(replyExe, &QNetworkReply::finished, &loopExe, &QEventLoop::quit);
            loopExe.exec();

            QByteArray exeContent = replyExe->readAll();
            if (exeContent.length() > 0)
            {
                // Check and create setups directory
                QDir dir("sw_fw");
                if (!dir.exists())
                    dir.mkpath(".");
                QFile output("sw_fw/KB2D_v" + resVersion + "_setup.exe");
                if (!output.open(QIODevice::WriteOnly))
                {
                    qDebug() << "Cannot write file";
                    return false;
                }
                output.write(exeContent);
                output.close();

                if (!QProcess::startDetached(QDir::currentPath() + "/sw_fw/KB2D_v" + resVersion + "_setup.exe"))
                {
                    SendError(this, tr("Setup program cannot be executed at following path: ") + QDir::currentPath() + "/sw_fw/KB2D_v" + resVersion + "_setup.exe", \
                              FUpdater_CheckNewVersion, tr("Setup program cannot be executed"));
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

/*
 * ======================================
 * Read Crypt File and load in Flash
 * Returns 0 if this is a SUCCESS
 * ======================================
 */
int MainWindow::readCyFile(FILE *cyFile)
{
    qDebug() << "Read Cy File...";
    SendLog("Starting firmware Update");
    unsigned long countChar = 0;
    int thCountPage;
    int countPage;
    int dataCy[SIZE_CY_FILE_BYTEMAX] = {0};
    int err = 0, err2 = 0;
    int failLoadPage = 0;

    // Read All file and stock it
    do
    {
        dataCy[countChar] = fgetc(cyFile);
        countChar += 1;
    }
    while ((dataCy[countChar - 1] >= 0) && (dataCy[countChar - 1] != EOF));
    //return dataCy[121];

    qDebug() << "File read" << countChar;
    // Wrong Data Number
    if (countChar < 2)
        return -1;
    countChar -= 2;     // Remove EOF and page Count
    if ((countChar & (PAGEDATA_MULTIPLE - 1)) != 0)
        return countChar;

    countPage = countChar >> 11;
    thCountPage = dataCy[countChar];


    // Wrong symbol, or can't read
    if (dataCy[countChar + 1] != EOF)
        return -4;

    // No correspondance between theoretical page Number and read page Number
    if (countPage != thCountPage)
        return -2;

    updateProgressBar(0, countPage * 2);

    // Send all Data Page by Page
    for (int _ii = 0; _ii < countPage; _ii++)
    {
        // Send all Data in 1 page
        for (int _jj = 0; _jj < PAGEDATA_MULTIPLE; _jj++)
        {
            dfuDev.sendAndCheck(MIDI_PROGMEM, ((dataCy[(_ii * PAGEDATA_MULTIPLE) + _jj] & 0xF0) >> 4), (dataCy[(_ii * PAGEDATA_MULTIPLE) + _jj] & 0xF));
            if (failLoadPage == 2)  // If data were saturated twice on reception, add Sleep(1) to prevent saturation.
                qSleep(1);
        }

        // Program page
        dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
        err = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
        // B6 01 03 = Saturation (Wrong Data Number) = -1103
        // B6 02 03 = Saturation + No Page = -2103
        // B6 01 02 = Wrong Page (Saturation always have priority on Wrong Page) = -1102
        // C6 00 00 = OK
        // -10 = timeout
        if (err != 0)
        {
            SendLog("DFU SendAndCheck err: failLoadPage=" + QString::number(failLoadPage));
            if (failLoadPage < 2)
            {
                switch (err)
                {
                case -1103:     // Saturation on data reception
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;

                case -2103:
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;

                case -1102:
                    dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
                    err2 = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
                    if (err2 != 0)
                    {
                        failLoadPage++;
                        _ii--;  // Reload current page
                    }
                    else
                        failLoadPage = 0;
                    break;

                case -10:
                    dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
                    err2 = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
                    if (err2 != 0)
                    {
                        failLoadPage++;
                        _ii--;  // Reload current page
                    }
                    else
                        failLoadPage = 0;
                    break;

                default:
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;
                }
            }
            else
                return err;
        }
        else
            failLoadPage = 0;   // Reset error when a page is correctly programmed

        // Update Status
        updateProgressBar(2 * (_ii + 1));
    }

    // Send message for End Of Prog
    err = dfuDev.sendAndCheck(MIDI_ENDOFPROG);                                              // Send End Of File here
    if (err != 0)
    {
        err2 = dfuDev.sendAndCheck(MIDI_ENDOFPROG);     // 2nd try
        if (err2 != 0)
            return (100 * err) + err2;
    }

    SendLog("Firmware Update Successful");
    return 0;   // SUCCESS
}

/*
 * ==============================
 * Flash program
 * ==============================
 */
bool MainWindow::flashProg(QString fileName)
{
    int res = -1;
    FILE *pData;
    QString wText = fileName;

    int  ver = 0, subVer = 0;

    ver = dfuDev.checkDfuFeedback(Check_Dfu_Version);
    subVer = dfuDev.checkDfuFeedback(Check_Dfu_SubVersion);

    // Get the previous path used for DFU
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.beginGroup("DFU_Settings");
    QString savedPath = globQSettings.value("LastPath", "").toString();
    if ((savedPath == "") || !QFileInfo::exists(savedPath))
        savedPath = QDir::currentPath();
    globQSettings.endGroup();


    if ((ver == -2) && (subVer == -2))
    {
        // Legacy Firmware detected
        QMessageBox::information(this, tr("Legacy Bootloader Detected"), tr("Legacy Bootloader Version: 1.0"
                             "\n\nTo obtain your firmware update (.kb2d file), please contact Lightdiction:"
                             "\n\ncontact@lightdiction.com"));
#ifndef GITX
        if (wText == "")
            wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: 1.0 | Enter firmware KB file .kb2d"), savedPath, "*.kb2d");
        if (wText != QString())
        {
            // Save the actual path for future loadings
            QSettings globQSettings(".kbsession", QSettings::IniFormat);
            globQSettings.beginGroup("DFU_Settings");
            globQSettings.setValue("LastPath", QFileInfo(wText).absolutePath());
            globQSettings.endGroup();

            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
                ui->actionLoad_now->setEnabled(0);
                ui->exitUpdaterButton->setEnabled(0);
                ui->actionLoad_Firmware_2_0->setEnabled(0);
                res = readLegacyFile(pData);
                if (res != 0)
                {
                    SendError(this, tr("Flash Error Code: ") + QString::number(res), MainWindow_FlashProg_2_C);
                }
                else
                {
                    //ui->statusBar->showMessage("Firmware Upgrade complete", 0);
                    setStatus(tr("Firmware Upgrade complete"));
                    QMessageBox::information(this, tr("SUCCESS"), tr("Memory correctly Flashed"));
                }
                fclose(pData);
                ui->flashProgButton->hide();
                ui->actionLoad_now->setVisible(0);
                ui->exitUpdaterButton->setEnabled(1);
                ui->actionLoad_Firmware_2_0->setEnabled(1);
                setFlashText(tr("Load Firmware file"));
            }
        }
#endif
    }
    else if (ver < 2)
    {
        // Legacy Firmware detected
        QMessageBox::information(this, tr("Legacy Bootloader Detected"), tr("Bootloader Version: ") + QString::number(ver) + "." + QString::number(subVer) + \
                                 tr("\n\nTo obtain your firmware update (.kb2d file), please contact Lightdiction:"
                                 "\n\ncontact@lightdiction.com"));
#ifndef GITX
        if (wText == "")
            wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: ") + QString::number(ver) + "." + QString::number(subVer) + \
                                             tr(" | Enter firmware KB file .kb2d"), savedPath, "*.kb2d");
        if (wText != QString())
        {
            // Save the actual path for future loadings
            QSettings globQSettings(".kbsession", QSettings::IniFormat);
            globQSettings.beginGroup("DFU_Settings");
            globQSettings.setValue("LastPath", QFileInfo(wText).absolutePath());
            globQSettings.endGroup();

            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
                ui->actionLoad_now->setEnabled(0);
                ui->exitUpdaterButton->setEnabled(0);
                ui->actionLoad_Firmware_2_0->setEnabled(0);
                res = readLegacyFile(pData);
                if (res != 0)
                {
                    SendError(this, tr("Flash Error Code: ") + QString::number(res), MainWindow_FlashProg_2_C);
                }
                else
                {
                    //ui->statusBar->showMessage("Firmware Upgrade complete", 0);
                    setStatus(tr("Firmware Upgrade complete"));
                    QMessageBox::information(this, tr("SUCCESS"), tr("Memory correctly Flashed"));
                }
                fclose(pData);
                ui->flashProgButton->hide();
                ui->actionLoad_now->setVisible(0);
                ui->exitUpdaterButton->setEnabled(1);
                ui->actionLoad_Firmware_2_0->setEnabled(1);
                setFlashText(tr("Load Firmware file"));
            }
        }
#endif
    }
    else
    {
        //////////////
        QString uniqueID = "";
        int id[12] = {0};
        for (int _i = 11; _i >= 0; _i--)
        {
            id[_i] = dfuDev.checkDfuFeedback(Check_Dfu_ID0 + 2 * _i);
            id[_i] += dfuDev.checkDfuFeedback(Check_Dfu_ID0 + 1 + (2 * _i));
            uniqueID += QString::number(id[_i], 16).toUpper();
        }
        //QMessageBox::information(this, "Unique ID", uniqueID);
        //////////////

        if (wText == "")
            wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: ") + QString::number(ver) + "." + QString::number(subVer) + " | Unique ID: " + uniqueID + \
                                             tr(" | Enter firmware KB file .kbf"), savedPath, "*.kbf");
        if (wText != QString())
        {
            // Save the actual path for future loadings
            QSettings globQSettings(".kbsession", QSettings::IniFormat);
            globQSettings.beginGroup("DFU_Settings");
            globQSettings.setValue("LastPath", QFileInfo(wText).absolutePath());
            globQSettings.endGroup();

            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
                ui->actionLoad_now->setEnabled(0);
                ui->exitUpdaterButton->setEnabled(0);
                ui->actionLoad_Firmware_2_0->setEnabled(0);
                res = readCyFile(pData);
                if (res != 0)
                {
                    SendError(this, tr("Flash Error Code: ") + QString::number(res), MainWindow_FlashProg_2_C);
                }
                else
                {
                    //ui->statusBar->showMessage("Firmware Upgrade complete", 0);
                    setStatus(tr("Firmware Upgrade complete"));
                    QMessageBox::information(this, tr("SUCCESS"), tr("Memory correctly Flashed"));
                }
                fclose(pData);
                ui->flashProgButton->hide();
                ui->actionLoad_now->setVisible(0);
                ui->exitUpdaterButton->setEnabled(1);
                ui->actionLoad_Firmware_2_0->setEnabled(1);
                setFlashText(tr("Load Firmware file"));
            }
        }
    }
    if (res != 0)
        return false;
    return true;
}

/*
 * ==========================
 * Exit the Firmware Updater
 * ==========================
 */
void MainWindow::exitFUpdater()
{
    dfuDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
    harpOut.close();
    dfuDev.setConnected(0);
    setStatus(tr("Wait a few seconds for initialization..."));
    ui->flashProgButton->setEnabled(0);
    ui->actionLoad_now->setEnabled(0);
    ui->actionLoad_Firmware_2_0->setEnabled(0);
    ui->exitUpdaterButton->setEnabled(0);
    ui->menuOutils->setEnabled(0);

    QCoreApplication::processEvents();
    setFlashText(tr("Please wait..."));
    QCoreApplication::processEvents();
    qSleep(1500);
    setFlashText(tr("Load Firmware file"));

    updateMidiPortsList();

    if ((dfuDev.isConnected() == 0) && (kbDev.isConnected() == 0))
    {
        SendError(this, tr("Cannot connect to KB2D, please select the ports manually.\n\n"
                             "Please ensure KB2D Ports are available.\n\n"
                             "/!\\ If you just updated the firmware and the KB2D is not working anymore, do not panic:\n"
                             "- Close this interface, and unplug the KB2D.\n"
                             "- Then press the start button on the KB2D hardware device while plugging the USB. This will force the KB2D to start in Firmware Updater mode.\n"
                             "- Load your Firmware file again."), FUpdater_Exit, tr("Cannot connect to LD Firmware Updater"));
    }
}

/*
 * =================================
 * Initialize the Firmware Updater
 * =================================
 */
bool MainWindow::initializeFU()
{
    setFlashText(tr("Load Firmware file"));
    ui->flashProgressBar->setValue(0);
    ui->firmwareVersionValue->setText("NA");
    ui->uniqueIDValue->setText("NA");

    ui->flashProgButton->show();
    ui->actionLoad_now->setVisible(1);
    ui->flashProgButton->setEnabled(1);
    ui->actionLoad_now->setEnabled(1);
    ui->exitUpdaterButton->setEnabled(1);
    ui->actionLoad_Firmware_2_0->setEnabled(1);

    if (dfuDev.isConnected())
    {
        ui->firmwareStatusValue->setText(tr("DFU Connected"));
        setStatus(tr("DFU Connected"));

        int  ver = 0, subVer = 0;
        ver = dfuDev.checkDfuFeedback(Check_Dfu_Version);
        subVer = dfuDev.checkDfuFeedback(Check_Dfu_SubVersion);

        // Version known, but cannot read Unique ID
        if ((ver > 0) && (ver < 2))
        {
            ui->firmwareVersionValue->setText(QString::number(ver) + "." + QString::number(subVer));
            SendLog("DFU Connected - Version: " + QString::number(ver) + "." + QString::number(subVer));
        }
        else if (ver >= 2)
        {

            QString uniqueID = "";
            int id[12] = {0};
            for (int _i = 11; _i >= 0; _i--)
            {
                id[_i] = dfuDev.checkDfuFeedback(Check_Dfu_ID0 + 2 * _i);
                id[_i] += dfuDev.checkDfuFeedback(Check_Dfu_ID0 + 1 + (2 * _i));
                uniqueID += QString::number(id[_i], 16).toUpper();
            }

            ui->firmwareVersionValue->setText(QString::number(ver) + "." + QString::number(subVer));
            ui->uniqueIDValue->setText(uniqueID);
            SendLog("DFU Connected - Version: " + QString::number(ver) + "." + QString::number(subVer) + " | Unique ID: " + uniqueID);

            if (fuUpdateRequested)
            {
                if (autoStartFUAndParse())
                {
                    // Update Successful
                    return true;
                }
                else
                {
                    QMessageBox::warning(this, tr("Error on automatic update"), tr("The firmware cannot be updated automatically"
                                         "\n\nPlease retry later or download the last firmware update on https://lightdiction.com/Ressources"
                                         "\n\nOr contact us at:\ncontact@lightdiction.com"));
                }
            }
        }
        if (ver < 2)
        {
            QMessageBox::warning(this, tr("Legacy Bootloader Detected"), tr("Legacy Bootloader Version: 1.0"
                                 "\n\nA firmware update has been requested. To obtain your firmware update (.kb2d file), please contact Lightdiction:"
                                 "\n\ncontact@lightdiction.com"));
        }
        QCoreApplication::processEvents();

        if (!fuUpdateRequested)
            QMessageBox::information(this, tr("Device connected"), tr("LD Firmware Updater connected\n\nClick on 'Load Firmware file' to update\n"
                                 "Or click on 'Exit Firmware Updater' to Exit and return to the KB2D Interface"));
    }
    QCoreApplication::processEvents();
    return false;
}

bool MainWindow::autoStartFUAndParse()
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req((QUrl)(DIST_RESSOURCES "FWKB_V" + QString::number(lastParsedFirmware) + ".kbf"));
    QNetworkReply *reply = nam.get(req);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer = reply->readAll();

    if (buffer.length() > 0)
    {
        // Check and create setups directory
        QDir dir("sw_fw");
        if (!dir.exists())
            dir.mkpath(".");
        QFile output("sw_fw/FWKB_V" + QString::number(lastParsedFirmware) + ".kbf");
        if (!output.open(QIODevice::WriteOnly))
        {
            qDebug() << "Cannot write file";
            return false;
        }
        output.write(buffer);
        output.close();
        if (flashProg("sw_fw/FWKB_V" + QString::number(lastParsedFirmware) + ".kbf"))
            return true;
    }

    return false;
}

void MainWindow::updateProgressBar(int currentValue, int valMax)
{
    if (valMax > 0)
        ui->flashProgressBar->setMaximum(valMax);
    ui->flashProgressBar->setValue(currentValue);

    setStatus(tr("Upgrading Firmware... ") + QString::number(currentValue) + tr("KB"));
    setFlashText(tr("Upgrading Firmware... "));
    QCoreApplication::processEvents();
}



/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Main Window **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All Main functions regarding:
 * - UI
 * - MIDI Callbacks
 * - Generic Buttons
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/versiondialog.h"

//#include "comhw.h"

//#define Z_DIMENSION

//int mappingCommand[NUM_EXTERNAL_COMMANDS][3] = {{-1}};

//unsigned long timeRec = 0;

bool configDone = 0;

bool cancelValue = 0;

QString saveNameMidi;
QString saveNameMidiIn;
int saveIndexMidiOut = 0;
int saveIndexMidiIn = 0;

int extMidiIndexToLearn;

void qSleep(int timeToSleep)
{
    QElapsedTimer tim;
    tim.start();
    while(tim.elapsed() < timeToSleep)
        QApplication::processEvents();
}

/*
 * ==============================
 * Send Error to User and
 * Write error in log file
 * ==============================
 */
void SendError(QWidget *parent, const QString &errMessage, int errorIndex, const QString &compMessage, bool disp)
{
    if (errorIndex > 10000)
    {
        if (disp)
            QMessageBox::critical(parent, QObject::tr("Error"), errMessage + QObject::tr("\nError code: ") + QString::number(errorIndex));
    }
    else
    {
        if (disp)
            QMessageBox::warning(parent, "Warning", errMessage + "\nWarning code: " + QString::number(errorIndex));
    }

    // Check and create logs directory
    QDir dir("logs");
    if (!dir.exists())
        dir.mkpath(".");
    // Log File
    QFile logFile("logs/" + QDateTime::currentDateTime().toString("yyMM") + "_kb" + QString::number(LAST_VERSION) + ".log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (logFile.isOpen())
    {
        if (compMessage == "xxx")
        {
            QTextStream outStream(&logFile);
            outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << errMessage << "\n";
        }
        else
        {
            QTextStream outStream(&logFile);
            outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " \
                      << "Err " << QString::number(errorIndex) << " _ " << compMessage << "\n";
        }
        logFile.close();
    }
    else
        qDebug() << "Can't open log file";
}

/*
 * ==============================
 * Write information in log file
 * ==============================
 */
void SendLog(const QString &logMessage)
{
    // Check and create logs directory
    QDir dir("logs");
    if (!dir.exists())
        dir.mkpath(".");
    // Log File
    QFile logFile("logs/" + QDateTime::currentDateTime().toString("yyMM") + "_kb" + QString::number(LAST_VERSION) + ".log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (logFile.isOpen())
    {
        QTextStream outStream(&logFile);
        outStream << QDateTime::currentDateTime().toString("yy/MM/dd") << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " > " << logMessage << "\n";
        logFile.close();
    }
    else
        qDebug() << "Can't open log file";
}

/*
 * =============================================
 * Event Filter for Wheel events
 * Spin Box, Double Spin Box, Slider, Combo Box
 * =============================================
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Wheel)
    {
        QSpinBox* spin = qobject_cast<QSpinBox*>(obj);
        if(spin && !spin->hasFocus())
        {
            event->ignore();
            return true;
        }
        QDoubleSpinBox* dSpin = qobject_cast<QDoubleSpinBox*>(obj);
        if(dSpin && !dSpin->hasFocus())
        {
            event->ignore();
            return true;
        }
        QSlider* slider = qobject_cast<QSlider*>(obj);
        if(slider && !slider->hasFocus())
        {
            event->ignore();
            return true;
        }
        QComboBox* combo = qobject_cast<QComboBox*>(obj);
        if(combo && !combo->hasFocus())
        {
            event->ignore();
            return true;
        }
    }

    event->accept();
    return false;
}

void MainWindow::updateWidgetsDisplay()
{
}

/*
 * ======================================
 * All ports are initialized in main.cpp
 * Just after this MainWindow is created
 * ======================================
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    SendLog("Program starting...");

    /////// Filter for Wheel Events ///////
    QList <QSpinBox *> listSpin = this->findChildren<QSpinBox *>();
    foreach (QSpinBox *qs, listSpin)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QDoubleSpinBox *> listDSpin = this->findChildren<QDoubleSpinBox *>();
    foreach (QDoubleSpinBox *qs, listDSpin)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QSlider *> listSlider = this->findChildren<QSlider *>();
    foreach (QSlider *qs, listSlider)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }

    QList <QComboBox *> listCombo = this->findChildren<QComboBox *>();
    foreach (QComboBox *qs, listCombo)
    {
        qs->setFocusPolicy(Qt::StrongFocus);
        qs->installEventFilter(this);
    }
    ///////

    ui->thresholdWidget->setHidden(1);

    updateInProgress = false;
    extMidiIndexToLearn = -1;

    ui->statusBar->addPermanentWidget(ui->statusLabel, 0);

#ifdef NO_MORE_BUTTONS
    ui->startButton->setHidden(1);
    ui->startButton->setEnabled(0);
    ui->pauseButton->setHidden(1);
    ui->pauseButton->setEnabled(0);
    ui->stopCalButton->setHidden(1);
    ui->stopCalButton->setEnabled(0);
    ui->SaveParamButton->setHidden(1);
    ui->SaveParamButton->setEnabled(0);

    ui->widgetStartStop->setHidden(1);

    //ui->detAssistantWidget->setHidden(0);
#ifndef TEST_MODE
    ui->widget_SNFlash->setHidden(1);
#endif
#endif
/*
    QFont swFont = QFont();
    swFont.setPointSize(6);
    ui->ThreLabel->setFont(swFont);
*/
    ui->XMin_Label->setVisible(0);
    ui->XMax_Label->setVisible(0);
    ui->angleMinDoubleSpinBox->setVisible(0);
    ui->angleMaxDoubleSpinBox->setVisible(0);

    groupList[Group_DetXParam] = ui->detXGroup;
    groupList[Group_DetZParam] = ui->detZGroup;
    groupList[Group_AnglesParam] = ui->anglesParamGroup;
    groupList[Group_MidiParam] = ui->midiParamGroup;
    groupList[Group_NotesParam] = ui->notesParamGroup;
    groupList[Group_MainPresets] = ui->mainPresetsGroup;
    groupList[Group_MidiPresets] = ui->midiPresetsGroup;
    groupList[Group_MainMapping] = ui->mainScrollArea;
    groupList[Group_MidiMapping] = ui->midiScrollArea;
    groupList[Group_DetXMapping] = ui->detXScrollArea;
    groupList[Group_DetZMapping] = ui->detZScrollArea;
    groupList[Group_MainPresetsMapping] = ui->mainPresetsScrollArea;
    groupList[Group_MidiPresetsMapping] = ui->midiPresetsScrollArea;

    resetMidiPorts();

    ///// TAB 1 /////
    angleLabel[0] = ui->X1_Label;
    angleLabel[1] = ui->X2_Label;
    angleLabel[2] = ui->X3_Label;
    angleLabel[3] = ui->X4_Label;
    angleLabel[4] = ui->X5_Label;
    angleLabel[5] = ui->X6_Label;
    angleLabel[6] = ui->X7_Label;
    angleLabel[7] = ui->X8_Label;
    angleLabel[8] = ui->X9_Label;
    angleLabel[9] = ui->X10_Label;
    angleLabel[10] = ui->X11_Label;
    angleLabel[11] = ui->X12_Label;
    angleLabel[12] = ui->X13_Label;
    angleLabel[13] = ui->X14_Label;
    angleLabel[14] = ui->X15_Label;
    angleLabel[15] = ui->X16_Label;

    angleDoubleSpinBox[0] = ui->angleDoubleSpinBox_1;
    angleDoubleSpinBox[1] = ui->angleDoubleSpinBox_2;
    angleDoubleSpinBox[2] = ui->angleDoubleSpinBox_3;
    angleDoubleSpinBox[3] = ui->angleDoubleSpinBox_4;
    angleDoubleSpinBox[4] = ui->angleDoubleSpinBox_5;
    angleDoubleSpinBox[5] = ui->angleDoubleSpinBox_6;
    angleDoubleSpinBox[6] = ui->angleDoubleSpinBox_7;
    angleDoubleSpinBox[7] = ui->angleDoubleSpinBox_8;
    angleDoubleSpinBox[8] = ui->angleDoubleSpinBox_9;
    angleDoubleSpinBox[9] = ui->angleDoubleSpinBox_10;
    angleDoubleSpinBox[10] = ui->angleDoubleSpinBox_11;
    angleDoubleSpinBox[11] = ui->angleDoubleSpinBox_12;
    angleDoubleSpinBox[12] = ui->angleDoubleSpinBox_13;
    angleDoubleSpinBox[13] = ui->angleDoubleSpinBox_14;
    angleDoubleSpinBox[14] = ui->angleDoubleSpinBox_15;
    angleDoubleSpinBox[15] = ui->angleDoubleSpinBox_16;

    ///// TAB 2 /////
    Z0_ComboBox[0] = ui->X0Z0_ComboBox;
    Z0_ComboBox[1] = ui->X1Z0_ComboBox;
    Z0_ComboBox[2] = ui->X2Z0_ComboBox;
    Z0_ComboBox[3] = ui->X3Z0_ComboBox;
    Z0_ComboBox[4] = ui->X4Z0_ComboBox;
    Z0_ComboBox[5] = ui->X5Z0_ComboBox;
    Z0_ComboBox[6] = ui->X6Z0_ComboBox;
    Z0_ComboBox[7] = ui->X7Z0_ComboBox;
    Z0_ComboBox[8] = ui->X8Z0_ComboBox;
    Z0_ComboBox[9] = ui->X9Z0_ComboBox;
    Z0_ComboBox[10] = ui->X10Z0_ComboBox;
    Z0_ComboBox[11] = ui->X11Z0_ComboBox;
    Z0_ComboBox[12] = ui->X12Z0_ComboBox;
    Z0_ComboBox[13] = ui->X13Z0_ComboBox;
    Z0_ComboBox[14] = ui->X14Z0_ComboBox;
    Z0_ComboBox[15] = ui->X15Z0_ComboBox;
/*
    for (int _i = 0; _i < MAX_NBEAMS; _i++)
    {
        Z0_ComboBox[_i]->setEditable(true);
        Z0_ComboBox[_i]->lineEdit()->setAlignment(Qt::AlignCenter);
        Z0_ComboBox[_i]->lineEdit()->setReadOnly(true);
    }
*/

    ///// QSettings MIDI /////
    InitializeMidiConfig();

    ///// QSettings MAIN /////
    InitializeMainConfig();

    ///// TAB 3 & QSettings Mapping /////
    InitializeMapping();

    // Restore Window Properties
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    if (globQSettings.childGroups().contains("Global Settings", Qt::CaseInsensitive))
    {
        globQSettings.beginGroup("Global Settings");

        this->setGeometry(0,0,globQSettings.value("Width", 1150).toInt(),globQSettings.value("Height", 718).toInt());
        QSize screenSize = qApp->primaryScreen()->availableSize();
        this->move((screenSize.width() / 2) - (this->width() / 2), (screenSize.height() / 2) - (this->height() / 2));

        if (globQSettings.value("MaxWin", 0).toInt() == 1)
            this->showMaximized();

        globQSettings.endGroup();
    }
    else
        this->showMaximized();

    // Show last version informations
    globQSettings.beginGroup("Last_Version");
    if (globQSettings.value("Version", 0).toInt() != LAST_VERSION)
    {
        globQSettings.setValue("Version", LAST_VERSION);
        VersionDialog verDialog;
        verDialog.setModal(true);
        verDialog.exec();
    }
    globQSettings.endGroup();

    // Timer not used
    modifTimer.setInterval(3000);
    modifTimer.setSingleShot(false);
    connect(&modifTimer, &QTimer::timeout, this, &MainWindow::checkModifications);

    configDone = 1;
    SendLog("Initialization done");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * ================================
 * Close everything before leaving
 * ================================
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    modifTimer.stop();
    disconnect(&modifTimer, &QTimer::timeout, this, &MainWindow::checkModifications);
    kbDev.setConnected(0);
    dfuDev.setConnected(0);
    harpOut.close();
    harpIn.close();
    extIn.close();
    extOut.close();

    // Save global session settings
    WriteTempMapping();

    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.beginGroup("Global Settings");

    if (this->isMaximized())
        globQSettings.setValue("MaxWin", 1);
    else
    {
        globQSettings.setValue("MaxWin", 0);
        globQSettings.setValue("Width", this->width());
        globQSettings.setValue("Height", this->height());
    }
    globQSettings.setValue("Ext MIDI In", ui->extMidiInComboBox->currentText());
    globQSettings.setValue("Ext MIDI Out", ui->extMidiOutComboBox->currentText());

    globQSettings.endGroup();

    SendLog("Program exited correctly");
    QApplication::processEvents();

    event->accept();
}

/*
 * ==============================
 * Close MainWindow
 * ==============================
 */
void MainWindow::quitProg()
{
    //QApplication::quit();
    close();
}

void MainWindow::setDetActionsVisibility(bool enab, bool vis)
{
    ui->actionDetection_Assistant->setEnabled(enab);
    ui->actionAuto_Calibration->setEnabled(enab);
    ui->actionLearn_One_Angle->setEnabled(enab);
    ui->actionInvert_X_Notes->setEnabled(enab);

    ui->actionDetection_Assistant->setVisible(vis);
    ui->actionAuto_Calibration->setVisible(vis);
    ui->actionLearn_One_Angle->setVisible(vis);
    ui->actionInvert_X_Notes->setVisible(vis);
}

/*
 * ==================
 * Update Status
 * ==================
 */
void MainWindow::setStatus(QString const& status)
{
    ui->statusLabel->setText(status);
}

/*
 * =========================
 * DFU Only
 * Set text on Flash Button
 * =========================
 */
void MainWindow::setFlashText(const QString &text)
{
    ui->flashProgButton->setText(text);
}

/*
 * =======================
 * Set Serial Number
 * Can be set only once
 * (Lightdiction Only)
 * =======================
 */
void MainWindow::on_SNButton_clicked()
{
    bool ok = 0;
    int SNToLoad = 0;
    SNToLoad = QInputDialog::getInt(this, "S/N ?", "S/N = ", 0, 0, 16383, 1, &ok);
    if (ok)
    {
        //QMessageBox::information(this, "Data sent", "\nS/N: " + (QString::number(((SNToLoad >> 7) & 0x7F)))+ " " + (QString::number((SNToLoad & 0x7F))));
        kbDev.sendCom(MIDI_SN + ((SNToLoad >> 7) & 0x7F));      // Set High bits value here (x127)
        kbDev.sendCom(MIDI_SUBSN + (SNToLoad & 0x7F));             // Set Low bits value here
    }
}

/*
 * ======================
 * DFU Only
 * ======================
 */
void MainWindow::on_flashProgButton_clicked()
{
    flashProg();
}
//////////////////////////////////
///////////// BUTTON /////////////
//////////////////////////////////

void MainWindow::on_SaveParamButton_clicked()
{
    saveInFlashFunc();
}

void MainWindow::on_startButton_clicked()
{
    startFunc();
}

void MainWindow::on_pauseButton_clicked()
{
    pauseFunc();
}

/*
 * =============================================
 * Harp In function linked to CALLBACK
 * =============================================
 */
void MainWindow::harpInProc()
{
    ////////////////////// Firmware Tests /////////////////////
    /// Firmware tests are directly done in ComHw function

    ////////////////// Start and Pause Tests //////////////////
    if (kbDev.isWaitingFb() == 0)
    {
        if ((harpIn.getParam(0) == 0xB7) && (harpIn.getParam(1) == 0x2C) && (harpIn.getParam(2) == 0))
        {
            //ui->startButton->click();
            ui->actionStart->trigger();
        }
        else if ((harpIn.getParam(0) == 0xB7) && (harpIn.getParam(1) == 0x2C) && (harpIn.getParam(2) == 1))
        {
            //ui->pauseButton->click();
            ui->actionPause->trigger();
        }
    }
    ///////////////////////////////////////////////////////////
    kbDev.waitForFeedback(0);
    dfuDev.waitForFeedback(0);
}

/*
 * ========================
 * MIDI Callback for users
 * ========================
 */
void MidiDevIn::midiInCallback(HMIDIIN hMidiIn, DWORD_PTR dwInstance, unsigned char data1, unsigned char data2, unsigned char data3, DWORD_PTR mdTimestamp)
{
    (void)mdTimestamp; // Does nothing. Just avoid to get a warning because that var is unused.
    if (hMidiIn == harpIn.getDev())
    {
        harpIn.setParam(0, data1);
        harpIn.setParam(1, data2);
        harpIn.setParam(2, data3);
        reinterpret_cast<MainWindow*> (dwInstance)->harpInProc();
    }
    else if (hMidiIn == extIn.getDev())
    {
        if (((kbDev.isConnected() == 1) || (extMidiIndexToLearn >= 0)) && (kbDev.isWaitingFb() == 0))    // Check we are not already waiting for a signal from the KB2D (no saturation).
            reinterpret_cast<MainWindow*> (dwInstance)->extInProc(data1, data2, data3);
    }
}



// Functions

/*
 * ==============================
 * Flash program
 * ==============================
 */
void MainWindow::flashProg()
{
    int res = 0;
    FILE *pData;
    QString wText;

    int  ver = 0, subVer = 0;

    ver = dfuDev.checkDfuFeedback(Check_Dfu_Version);
    subVer = dfuDev.checkDfuFeedback(Check_Dfu_SubVersion);

    if ((ver == -2) && (subVer == -2))
    {
        // Legacy Firmware detected
        QMessageBox::information(this, tr("Legacy Bootloader Detected"), tr("Legacy Bootloader Version: 1.0"
                             "\n\nTo obtain your firmware update (.kb2d file), please contact Lightdiction:"
                             "\n\ncontact@lightdiction.com"));
#ifndef GITX
        wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: 1.0 | Enter firmware KB file .kb2d"), QDir::currentPath(), "*.kb2d");
        if (wText != NULL)
        {
            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
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
                ui->flashProgButton->setEnabled(1);
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
        wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: ") + QString::number(ver) + "." + QString::number(subVer) + \
                                             tr(" | Enter firmware KB file .kb2d"), QDir::currentPath(), "*.kb2d");
        if (wText != NULL)
        {
            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
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
                ui->flashProgButton->setEnabled(1);
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

        wText = QFileDialog::getOpenFileName(this, tr("Bootloader Version: ") + QString::number(ver) + "." + QString::number(subVer) + tr(" | Unique ID: ") + uniqueID + \
                                             tr(" | Enter firmware KB file .kbf"), QDir::currentPath(), "*.kbf");
        if (wText != NULL)
        {
            pData = fopen(wText.toStdString().c_str(), "rb");					// Creates an empty file for Data
            if (pData == NULL)
                SendError(this, tr("Cannot open ") + wText, MainWindow_FlashProg_1_C);
            else
            {
                ui->flashProgButton->setEnabled(0);
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
                ui->flashProgButton->setEnabled(1);
                setFlashText(tr("Load Firmware file"));
            }
        }
    }
}

/*
 * ==============================
 * Save params
 * ==============================
 */
void MainWindow::saveInFlashFunc()
{
    if (kbDev.isConnected())
    {
        if (kbDev.getID(VERSION) >= 7)
        {
            if (kbDev.checkFeedback(Check_SaveInFlash) == 0x7F)
                ui->statusBar->showMessage(tr("Parameters saved in Flash memory"), 3000);
        }
        else
        {
            kbDev.sendCom(MIDI_SAVEALL);
            ui->statusBar->showMessage(tr("Parameters saved in Flash memory"), 3000);
        }
    }
}

/*
 * ==============================
 * Start
 * ==============================
 */
void MainWindow::startFunc()
{
    kbDev.sendCom(MIDI_START);
    if (kbDev.checkFeedback(Check_PauseOn) == 0)
    {
#ifndef NO_MORE_BUTTONS
        ui->startButton->setEnabled(0);
        ui->pauseButton->setEnabled(1);
        ui->startButton->setHidden(1);
        ui->pauseButton->setHidden(0);
#endif

        ui->actionStart->setEnabled(0);
        ui->actionPause->setEnabled(1);
        ui->actionStart->setVisible(0);
        ui->actionPause->setVisible(1);
    }
}

/*
 * ==============================
 * Pause - Stop Laser
 * ==============================
 */
void MainWindow::pauseFunc()
{
    kbDev.sendCom(MIDI_PAUSE);
    if (kbDev.checkFeedback(Check_PauseOn) == 1)
    {
#ifndef NO_MORE_BUTTONS
        ui->startButton->setEnabled(1);
        ui->pauseButton->setEnabled(0);
        ui->startButton->setHidden(0);
        ui->pauseButton->setHidden(1);
#endif

        ui->actionStart->setEnabled(1);
        ui->actionPause->setEnabled(0);
        ui->actionStart->setVisible(1);
        ui->actionPause->setVisible(0);
    }
}

/*
 * ==============================
 * Restart
 * ==============================
 */
void MainWindow::restartFunc()
{
    kbDev.sendCom(MIDI_RESTART);
    ui->statusBar->showMessage(tr("Wait while restarting..."), 500);
    setStatus(tr("Wait while restarting..."));
    QApplication::processEvents();
    qSleep(500);
    ui->statusBar->showMessage(tr("Ready"), 3000);
    updateAll(1);
}

/*
 * ==============================
 * Update All Values
 * ==============================
 */
void MainWindow::updateAll(bool optionWin)
{
    int retErr = 0;
    int saveContX = 0;
    //kbDev.setID(VERSION, 0);
    modifTimer.stop();
    QApplication::processEvents();

    if ((kbDev.checkFeedback(Check_NoteToPlay0) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay1) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay2) >= 0) && \
        (kbDev.checkFeedback(Check_NoteToPlay3) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay4) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay5) >= 0) && \
        (kbDev.checkFeedback(Check_NoteToPlay6) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay7) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay8) >= 0) && \
        (kbDev.checkFeedback(Check_NoteToPlay9) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay10) >= 0) && (kbDev.checkFeedback(Check_NoteToPlay11) >= 0) && \
        (kbDev.checkFeedback(Check_nBeamsX) >= 0) && (kbDev.checkFeedback(Check_DetLevel) >= 0) && (kbDev.checkFeedback(Check_MinPos) >= 0) && \
        (kbDev.checkFeedback(Check_MultPos) >= 0) && (kbDev.checkFeedback(Check_FPS) >= 0) && (kbDev.checkFeedback(Check_HalfDelta) >= 0) && \
        (kbDev.checkFeedback(Check_PauseOn) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListX0) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH0) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX1) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListXH1) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX2) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH2) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListX3) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH3) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX4) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListXH4) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX5) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH5) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListX6) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH6) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX7) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListXH7) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX8) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH8) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListX9) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH9) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX10) >= 0) && \
        (kbDev.checkFeedback(Check_BeamAngleListXH10) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListX11) >= 0) && (kbDev.checkFeedback(Check_BeamAngleListXH11) >= 0) && \
        (kbDev.checkFeedback(Check_SN) >= 0) && (kbDev.checkFeedback(Check_SubSN) >= 0) && (kbDev.checkFeedback(Check_Version) >= 0) && (kbDev.checkFeedback(Check_SubVersion) >= 0))
    {
        for (int _loci = 0; _loci < Group_NumTotal; _loci++)
            groupList[_loci]->setHidden(0);
        setDetActionsVisibility(1);
#ifndef TEST_MODE
        groupList[Group_MidiParam]->setEnabled(0);
        groupList[Group_DetZParam]->setEnabled(0);
#endif

        ui->actionLoad_now->setEnabled(0);
        ui->actionLoad_now->setVisible(0);

        ui->actionLoad_Firmware_2_0->setEnabled(1);

        ui->menuCommands->setEnabled(1);
        ui->menuMIDI->setEnabled(1);
        //ui->menuSequence->setEnabled(1);
        ui->menuOutils->setEnabled(1);


        ui->readButton->setHidden(0);
#ifndef NO_MORE_BUTTONS
        ui->SaveParamButton->setEnabled(1);
#endif
        ui->actionSave_in_Memory->setEnabled(1);
        if (kbDev.checkFeedback(Check_PauseOn) == 0)
        {
#ifndef NO_MORE_BUTTONS
            ui->startButton->setEnabled(0);
            ui->pauseButton->setEnabled(1);
            ui->startButton->setHidden(1);
            ui->pauseButton->setHidden(0);
#endif

            ui->actionStart->setEnabled(0);
            ui->actionPause->setEnabled(1);
            ui->actionStart->setVisible(0);
            ui->actionPause->setVisible(1);
        }
        else if (kbDev.checkFeedback(Check_PauseOn) == 1)
        {
#ifndef NO_MORE_BUTTONS
            ui->startButton->setEnabled(1);
            ui->pauseButton->setEnabled(0);
            ui->startButton->setHidden(0);
            ui->pauseButton->setHidden(1);
#endif

            ui->actionStart->setEnabled(1);
            ui->actionPause->setEnabled(0);
            ui->actionStart->setVisible(1);
            ui->actionPause->setVisible(0);
        }
        else
        {
#ifndef NO_MORE_BUTTONS
            ui->startButton->setEnabled(0);
            ui->pauseButton->setEnabled(0);
            ui->startButton->setHidden(0);
            ui->pauseButton->setHidden(0);
#endif

            ui->actionStart->setEnabled(0);
            ui->actionPause->setEnabled(0);
            ui->actionStart->setVisible(1);
            ui->actionPause->setVisible(1);
        }

        //////////////////////////////

        kbDev.setID(VERSION, kbDev.checkFeedback(Check_Version));
        kbDev.setID(SUBVERSION, kbDev.checkFeedback(Check_SubVersion));
        kbDev.setID(SERIAL, (kbDev.checkFeedback(Check_SN) << 7) + kbDev.checkFeedback(Check_SubSN));

        for (int _ii = 0 ; _ii < MAX_NBEAMS ; _ii++)
            Z0_ComboBox[_ii]->setCurrentIndex(kbDev.checkFeedback(Check_NoteToPlay0 + _ii));

        if ((kbDev.getID(VERSION) > 6) || ((kbDev.getID(VERSION) == 6) && (kbDev.getID(SUBVERSION) >= 41)))
        {
            saveContX = kbDev.checkFeedback(Check_ContX);
        }
        int saveNBeamsIndex = kbDev.checkFeedback(Check_nBeamsX) - 1;   // Because clear will reset the ComboBox and call the indexChanged function
        ui->nBeamsXComboBox->clear();
        for (int iii = 0 ; iii < MAX_NBEAMS ; iii++)
            ui->nBeamsXComboBox->addItem(QString::number(iii + 1));
        ui->nBeamsXComboBox->setCurrentIndex(saveNBeamsIndex);


        if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23))) {}
        else
        {
            ui->detLevelSlider->setValue(kbDev.checkFeedback(Check_DetLevel) + 1);
        }

        ui->detSpeedSlider->setValue(128 - kbDev.checkFeedback(Check_MinPos));
        ui->detSelectivitySlider->setValue(128 - kbDev.checkFeedback(Check_MultPos));
        ui->FPSSlider->setValue(kbDev.checkFeedback(Check_FPS) + 50);
        ui->accuracySlider->setValue(kbDev.checkFeedback(Check_HalfDelta));

        for (int _ii = 0 ; _ii < MAX_NBEAMS ; _ii++)
        {
            angleSaveValue[_ii] = (double)(kbDev.checkFeedback(Check_BeamAngleListX0 + _ii) + ((kbDev.checkFeedback(Check_BeamAngleListXH0 + _ii) - 63) * 128)) / 10;
            angleDoubleSpinBox[_ii]->setValue(angleSaveValue[_ii]);
        }
    }
    else
        retErr = 1;

    ////////////////////////////
    //////////// V6.37 /////////
    ////////////////////////////

    if ((kbDev.getID(VERSION) > 6) || ((kbDev.getID(VERSION) == 6) && (kbDev.getID(SUBVERSION) >= 37)))
    {
        if ((kbDev.checkFeedback(Check_EnabMidiMode) >= 0) && (kbDev.checkFeedback(Check_NoteChan) >= 0) && (kbDev.checkFeedback(Check_CC1Chan) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Chan) >= 0) && (kbDev.checkFeedback(Check_NoteNote) >= 0) && (kbDev.checkFeedback(Check_CC1Ctrl) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Ctrl) >= 0) && (kbDev.checkFeedback(Check_NoteVel) >= 0) && (kbDev.checkFeedback(Check_CC1Val) >= 0) && \
            (kbDev.checkFeedback(Check_CC2Val) >= 0) && (kbDev.checkFeedback(Check_CheckVarUse) >= 0))
        {
            groupList[Group_MidiParam]->setEnabled(1);

            kbDev.setMidiMode((unsigned int)kbDev.checkFeedback(Check_EnabMidiMode));
            if ((kbDev.getMidiMode() & NOTES_ONOFF) == NOTES_ONOFF)
                ui->DescNoteComboBox->setCurrentIndex(1);
            else
                ui->DescNoteComboBox->setCurrentIndex(0);

            if ((kbDev.getMidiMode() & PITCH) == PITCH)
                ui->DescCC1ComboBox->setCurrentIndex(1);
            else
                ui->DescCC1ComboBox->setCurrentIndex(0);

            if ((kbDev.getMidiMode() & CONTROL_CHANGE) == CONTROL_CHANGE)
                ui->DescCC2ComboBox->setCurrentIndex(1);
            else
                ui->DescCC2ComboBox->setCurrentIndex(0);

            ui->ChanNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteChan));
            ui->ChanCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Chan));
            ui->ChanCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Chan));

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1) != 0)
                ui->NoteNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteNote));
            else
                ui->NoteNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteNote) + 2);

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10) != 0)
                ui->ControlCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Ctrl));
            else
                ui->ControlCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Ctrl) + 2);

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100) != 0)
                ui->ControlCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Ctrl));
            else
                ui->ControlCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Ctrl) + 2);

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1000) != 0)
                ui->VelNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteVel));
            else
                ui->VelNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteVel) + 2);

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10000) != 0)
                ui->ValCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Val));
            else
                ui->ValCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Val) + 2);

            if ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100000) != 0)
                ui->ValCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Val));
            else
                ui->ValCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Val) + 2);
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V6.38 /////////
    ////////////////////////////

    if ((kbDev.getID(VERSION) > 6) || ((kbDev.getID(VERSION) == 6) && (kbDev.getID(SUBVERSION) >= 38)))
    {
        if ((kbDev.checkFeedback(Check_RelativeH) >= 0) && (kbDev.checkFeedback(Check_SmoothZ) >= 0))
        {
            groupList[Group_DetZParam]->setEnabled(1);

            if (kbDev.checkFeedback(Check_RelativeH) == 1)
            {
                ui->modulationZComboBox->setCurrentIndex(0);
                ui->nbAbsoluteLabel->setVisible(0);
            }
            else
            {
                ui->modulationZComboBox->setCurrentIndex(1);
                ui->nbAbsoluteLabel->setVisible(1);
            }

            ui->smoothZSpinBox->setValue(127 - kbDev.checkFeedback(Check_SmoothZ));
            ui->smoothZSlider->setValue(ui->smoothZSpinBox->value());
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V6.40 /////////
    ////////////////////////////

    if ((kbDev.getID(VERSION) > 6) || ((kbDev.getID(VERSION) == 6) && (kbDev.getID(SUBVERSION) >= 40)))
    {
        if ((kbDev.checkFeedback(Check_StabZ) >= 0) && (kbDev.checkFeedback(Check_AmpZ) >= 0) && (kbDev.checkFeedback(Check_FiltZ) >= 0) && (kbDev.checkFeedback(Check_InvertZ) >= 0))
        {
            ui->stabZSpinBox->setEnabled(1);
            ui->ampZSpinBox->setEnabled(1);
            ui->filterZSpinBox->setEnabled(1);
            ui->invertZCheckBox->setEnabled(1);

            ui->stabZSpinBox->setValue(kbDev.checkFeedback(Check_StabZ));
            ui->stabZSlider->setValue(ui->stabZSpinBox->value());
            ui->ampZSpinBox->setValue(128 - (kbDev.checkFeedback(Check_AmpZ)));
            ui->ampZSlider->setValue(ui->ampZSpinBox->value());
            ui->filterZSpinBox->setValue(kbDev.checkFeedback(Check_FiltZ));
            ui->filterZSlider->setValue(ui->filterZSpinBox->value());
            if (kbDev.checkFeedback(Check_InvertZ) == 1)
                ui->invertZCheckBox->setChecked(1);
            else
                ui->invertZCheckBox->setChecked(0);
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V6.41 /////////
    ////////////////////////////

    updateAngleBoxVisibility();

    if ((kbDev.getID(VERSION) > 6) || ((kbDev.getID(VERSION) == 6) && (kbDev.getID(SUBVERSION) >= 41)))
    {
        if (saveContX >= 0)
        {
            ui->nBeamsXComboBox->addItem(tr("Continuous (128)"));
            if (saveContX == 1)
                ui->nBeamsXComboBox->setCurrentIndex(MAX_NBEAMS);

            angleSaveMin = (double)(kbDev.checkFeedback(Check_AngleMinX) + ((kbDev.checkFeedback(Check_AngleMinXH) - 63) * 128)) / 10;
            angleSaveMax = (double)(kbDev.checkFeedback(Check_AngleMaxX) + ((kbDev.checkFeedback(Check_AngleMaxXH) - 63) * 128)) / 10;
            ui->angleMinDoubleSpinBox->setValue(angleSaveMin);
            ui->angleMaxDoubleSpinBox->setValue(angleSaveMax);
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V7.21 /////////
    ////////////////////////////

    //updateAngleBoxVisibility();
    ui->hardAmpComboBox->setDisabled(1);

    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 21)))
    {
        if (kbDev.checkFeedback(Check_Gain) >= 0)
        {
            ui->hardAmpComboBox->setCurrentIndex(kbDev.checkFeedback(Check_Gain));
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V7.22 /////////
    ////////////////////////////

    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 22)))
    {
        if (kbDev.checkFeedback(Check_Gain) >= 0)
        {
            ui->hardAmpComboBox->setCurrentIndex(kbDev.checkFeedback(Check_Gain));
            ui->hardAmpComboBox->setEnabled(1);
        }
        else
            retErr = 1;
    }

    ////////////////////////////
    //////////// V7.23 /////////
    ////////////////////////////

    ui->releaseSlider->hide();
    ui->releaseSpinBox->hide();
    ui->releaseLabel->hide();
    if ((kbDev.getID(VERSION) > 7) || ((kbDev.getID(VERSION) == 7) && (kbDev.getID(SUBVERSION) >= 23)))
    {
        ui->releaseSlider->show();
        ui->releaseSpinBox->show();
        ui->releaseLabel->show();

        if ((kbDev.checkFeedback(Check_Release) >= 0) && (kbDev.checkFeedback(Check_DetLevelH) >= 0))
        {
            ui->releaseSlider->setValue(kbDev.checkFeedback(Check_Release));

            ui->detLevelspinBox->setMaximum(3000);
            ui->detLevelspinBox->setMinimum(5);
            ui->detLevelSlider->setMaximum(3000);
            ui->detLevelSlider->setMinimum(5);
            int valueFb = (kbDev.checkFeedback(Check_DetLevelH) << 7) + kbDev.checkFeedback(Check_DetLevel);
            if (valueFb <= 3000)
                ui->detLevelSlider->setValue(valueFb);
            else
                ui->detLevelSlider->setValue(3000);
        }
        else
            retErr = 1;
    }
    else if ((retErr == 0) && (optionWin == 1)) //
        SendError(this, tr("Please, update your firmware to the last version (7.23 or above) to get all functionnalities:"
                                                        "\n> The firmware can be downloaded here: https://lightdiction.com/Ressources"
                                                        "\n> Or contact us at contact@lightdiction.com"), MainWindow_UpdateAll_FWUP, tr("Firmware outdated"));

////////////////////////

    if (retErr == 0)
    {
        SendLog("KB2D Connected - SN: " + QString::number(kbDev.getID(SERIAL)));


        setStatus(tr("KB2D connected: Firmware version: ") + (QString::number(kbDev.getID(VERSION))) + "."+ (QString::number(kbDev.getID(SUBVERSION))) + \
                  " - S/N: " + (QString::number(kbDev.getID(SERIAL))));

        if (optionWin == 1)
            QMessageBox::information(this, tr("KB2D connected - Device information"), tr("Firmware version: ") + (QString::number(kbDev.getID(VERSION))) + \
                                     "."+ (QString::number(kbDev.getID(SUBVERSION))) + \
                                 "\nS/N: " + (QString::number(kbDev.getID(SERIAL))) + tr("\n\nFind the version notes and manual at:\nhttps://lightdiction.com/Ressources/"));

#ifdef ENABLE_AUTOSAVE
        loadPresetMain(0);  // Load live config (last session)
        loadPresetMidi(0);  // Load live config (last session)
        modifTimer.start();
#endif
    }
    else
        SendError(this, tr("KB2D Parameters cannot be read."), MainWindow_UpdateAll_1_C);
}

/*
void MainWindow::on_openMapButton_clicked()
{
    AngleMidiDialog angleMIDIDialog;
    angleMIDIDialog.setModal(true);
    angleMIDIDialog.exec();
}
*/

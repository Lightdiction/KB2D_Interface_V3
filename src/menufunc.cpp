
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Menu Func **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions and calls that you can find in the
 * Toolbar
 * Generally, these commands call functions that you
 * can find in Main Window
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/aboutdialog.h"
#include "../inc/versiondialog.h"

#include "../inc/comhw.h"


////////////// SLOTS ////////////

////////////// ACTIONS ////////////

void MainWindow::on_actionQuit_triggered()
{
    quitProg();
}

void MainWindow::on_actionStart_triggered()
{
    startFunc();
}

void MainWindow::on_actionPause_triggered()
{
    pauseFunc();
}

void MainWindow::on_actionStopCal_triggered()
{
    cancelValue = 1;
    kbDev.waitForFeedback(0);
}

void MainWindow::on_actionSave_in_Memory_triggered()
{
    saveInFlashFunc();
}

void MainWindow::on_actionRestore_Defaults_triggered()
{
    kbDev.sendCom(MIDI_DEFAULT);
    qSleep(200);
    updateAll(0);
}

void MainWindow::on_actionLoad_Firmware_triggered()
{
    kbDev.sendCom(MIDI_BOOTMODE);
}

void MainWindow::on_actionLoad_Firmware_2_0_triggered()
{

    if (dfuDev.isConnected() == 1) // If it is currently connected, disconnect it
    {
        exitFUpdater();
    }
    else // Else, if is currently running in normal mode, disconnect KB2D
    {
        disableAllGroups();
        kbDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
        harpOut.close();
        kbDev.setConnected(0);
        qSleep(1500);

        //updateMidiPortsList();  // Update ports so the KB2D or DFU reconnects
        retryConnection(5);
    }
}

void MainWindow::on_actionLoad_now_triggered()
{
    flashProg();
}

void MainWindow::on_actionDetection_Assistant_triggered()
{
    autoSetDet();
}

void MainWindow::on_actionAuto_Calibration_triggered()
{
    calibrateAngles();
}

void MainWindow::on_actionInvert_X_Notes_triggered()
{
    invertX();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog;
    aboutDialog.setModal(true);
    aboutDialog.exec();
}

void MainWindow::on_actionShow_Version_Notes_triggered()
{
    VersionDialog verDialog;
    verDialog.setModal(true);
    verDialog.exec();
}

void MainWindow::on_actionUpdate_All_triggered()
{
    //updateAll(1);
    if (dfuDev.isConnected() == 0)
    {
        updateMidiPortsList();  // updateAll is automatically used when ports are updated.
    }
}

void MainWindow::on_actionRestart_triggered()
{
    restartFunc();
}

void MainWindow::on_actionSave_mapping_triggered()
{
    saveMappingFunction();
}

void MainWindow::on_actionLoad_mapping_triggered()
{
    loadMappingFunction();
}

void MainWindow::on_actionRestore_default_mapping_triggered()
{
    defaultMappingFunction();
}

void MainWindow::on_actionGo_to_mapping_settings_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_actionEnglish_triggered()
{
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.setValue("lang", "en");
    //QMessageBox::information(this, tr("KB2D Interface will restart"), tr("The interface will automatically restart to update the language"));
    if (QMessageBox::question(this, tr("Restart to apply changes"), tr("The program needs to restart to apply changes.\n\nDo you want to restart now?")) == QMessageBox::Yes)
    {
        changeLanguage = true;
        QTimer::singleShot(0, this, &MainWindow::quitProg);
    }
}

void MainWindow::on_actionFrench_triggered()
{
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.setValue("lang", "fr");
    //QMessageBox::information(this, tr("KB2D Interface will restart"), tr("The interface will automatically restart to update the language"));
    if (QMessageBox::question(this, tr("Restart to apply changes"), tr("The program needs to restart to apply changes.\n\nDo you want to restart now?")) == QMessageBox::Yes)
    {
        changeLanguage = true;
        QTimer::singleShot(0, this, &MainWindow::quitProg);
    }
}

void MainWindow::setDetActionsVisibility(bool enab, bool vis)
{
    ui->actionDetection_Assistant->setEnabled(enab);
    ui->actionAuto_Calibration->setEnabled(enab);
    ui->actionLearn_One_Angle->setEnabled(enab);
    ui->actionLearn_All_One_by_One->setEnabled(enab);
    ui->actionInvert_X_Notes->setEnabled(enab);

    ui->actionDetection_Assistant->setVisible(vis);
    ui->actionAuto_Calibration->setVisible(vis);
    ui->actionLearn_One_Angle->setVisible(vis);
    ui->actionLearn_All_One_by_One->setVisible(vis);
    ui->actionInvert_X_Notes->setVisible(vis);
}

void MainWindow::on_actionLearn_One_Angle_triggered()
{
    bool ok;
    int nBeamToRead = QInputDialog::getInt(this, tr("Enter Beam Number"), tr("Enter Beam Number") + ": 1-" + QString::number(ui->nBeamsXComboBox->currentIndex() + 1), \
                         1, 1, ui->nBeamsXComboBox->currentIndex() + 1, 1, &ok);
    if (ok)
        learnOneAngle(nBeamToRead - 1);
}


void MainWindow::on_actionLearn_All_One_by_One_triggered()
{
    connect(this, &MainWindow::oneAngleCalibrated, this, [this] (int indexBeam) { this->learnOneAngle(indexBeam + 1); });
    learnOneAngle(0);
}

void MainWindow::on_actionMidi_configuration_triggered()
{
    MidiDevices midiDevDialog(this);
    midiDevDialog.setModal(true);
    connect(&midiDevDialog, &MidiDevices::midiDevicesUpdated, this, &MainWindow::updateMidiPortsList);
    midiDevDialog.exec();
}


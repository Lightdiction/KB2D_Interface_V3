
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
        dfuDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
        harpOut.close();
        dfuDev.setConnected(0);
        setStatus(tr("Wait a few seconds for initialization..."));
        ui->flashProgButton->setEnabled(0);
        ui->menuOutils->setEnabled(0);
        setFlashText(tr("Please wait..."));
        QCoreApplication::processEvents();
        qSleep(500);
        setFlashText(tr("Please wait 4 s..."));
        QCoreApplication::processEvents();
        qSleep(1000);
        setFlashText(tr("Please wait 3 s..."));
        QCoreApplication::processEvents();
        qSleep(1000);
        setFlashText(tr("Please wait 2 s..."));
        QCoreApplication::processEvents();
        qSleep(1000);
        setFlashText(tr("Please wait 1 s..."));
        QCoreApplication::processEvents();
        qSleep(1000);
        setFlashText(tr("Load Firmware file"));
    }
    else // Else, if is currently running in normal mode, disconnect KB2D
    {
        kbDev.sendCom(MIDI_INAPPBOOT);  // Sends a message to KB2D / DFU so it disconnects and restarts in the other mode.
        harpOut.close();
        kbDev.setConnected(0);
        qSleep(500);
    }
    updateMidiPortsList();  // Update ports so the KB2D or DFU reconnects
    if (dfuDev.isConnected() == 1)
    {
        QMessageBox::information(this, tr("Device connected"), tr("LD Firmware Updater connected\n\nGo to  'Tools > Load Firmware file' to update\n"
                                 "Or go to 'Tools > Exit Firmware Updater' to Exit and return to KB2D Interface"));
        //ui->statusBar->showMessage("DFU Connected", 0);
        setStatus("DFU Connected");
    }
    else if (kbDev.isConnected() == 0)
    {
        SendError(this, tr("Cannot connect to the device, please select the ports manually.\n\n"
                             "If this is the first time you start the Fimware Updater on this computer, it is normal. Do not panic.\n"
                             "Please wait for the driver to be installed (it should take less than 1 minute). Please do not disconnect your KB2D device.\n\n"
                             "Then press F5 to update the ports (after closing this warning) or restart this User interface. Your LD firmware Updater should now automatically connect "
                             "to your KB2D Laser Harp interface.\nOr select ports manually."), MenuFunc_LoadFW, tr("Cannot connect to LD Firmware Updater"));
    }
}

void MainWindow::on_actionLoad_now_triggered()
{
    flashProg();
}

void MainWindow::on_actionRead_All_triggered()
{
    sendTestNote();
}

void MainWindow::on_actionDetection_Assistant_triggered()
{
    autoSetDet();
}

void MainWindow::on_actionAuto_Calibration_triggered()
{
    calibrateAngles();
}

void MainWindow::on_actionLearn_One_Angle_triggered()
{
    learnOneAngle();
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
    QMessageBox::information(this, tr("KB2D Interface will restart"), tr("The interface will automatically restart to update the language"));
    changeLanguage = true;
    quitProg();
}

void MainWindow::on_actionFrench_triggered()
{
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.setValue("lang", "fr");
    QMessageBox::information(this, tr("KB2D Interface will restart"), tr("The interface will automatically restart to update the language"));
    changeLanguage = true;
    quitProg();
}


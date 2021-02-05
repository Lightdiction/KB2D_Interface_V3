
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Ports **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to Ports selection
 * Open / Close / Update Ports (In / Out / Ext)
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"



/*
 * ===================================================
 * This function is called once the window is created
 * ===================================================
 */
void MainWindow::updateMidiPortsList()
{
    uint i;

    ui->midiOutComboBox->clear();
    ui->midiInComboBox->clear();
    ui->extMidiInComboBox->clear();
    ui->extMidiOutComboBox->clear();
    ui->midiOutComboBox->insertItem(0, tr("No Device"));
    ui->midiInComboBox->insertItem(0, tr("No Device"));
    ui->extMidiInComboBox->insertItem(0, tr("No Device"));
    ui->extMidiOutComboBox->insertItem(0, tr("No Device"));

    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    QString nameExtIn, nameExtOut;
    if (globQSettings.childGroups().contains("Global Settings", Qt::CaseInsensitive))
    {
        globQSettings.beginGroup("Global Settings");
        nameExtIn = globQSettings.value("Ext MIDI In", "").toString();
        nameExtOut = globQSettings.value("Ext MIDI Out", "").toString();
        globQSettings.endGroup();
    }

    for (i = 0 ; i < (midi::getNumDevOut()) ; i++)
    {
        ui->midiOutComboBox->insertItem(i + 1, midi::getNameDevOut(i));
        ui->extMidiOutComboBox->insertItem(i + 1, midi::getNameDevOut(i));

        if (QString::compare(midi::getNameDevOut(i), (QString)"KB2D Interactive") == 0)
            ui->midiOutComboBox->setCurrentIndex(i + 1);
        else if (QString::compare(midi::getNameDevOut(i), (QString)"LD Firmware Updater") == 0)
            ui->midiOutComboBox->setCurrentIndex(i + 1);
        else if (QString::compare(midi::getNameDevOut(i), nameExtOut) == 0)
                ui->extMidiOutComboBox->setCurrentIndex(i + 1);
    }
    for (i = 0 ; i < (midi::getNumDevIn()) ; i++)
    {
        ui->midiInComboBox->insertItem(i + 1, midi::getNameDevIn(i));
        ui->extMidiInComboBox->insertItem(i + 1, midi::getNameDevIn(i));

        if (QString::compare(midi::getNameDevIn(i), (QString)"MIDIIN2 (KB2D Interactive)") == 0)
            ui->midiInComboBox->setCurrentIndex(i + 1);
        else if (QString::compare(midi::getNameDevIn(i), (QString)"LD Firmware Updater") == 0)
            ui->midiInComboBox->setCurrentIndex(i + 1);
        else if (QString::compare(midi::getNameDevIn(i), nameExtIn) == 0)
                ui->extMidiInComboBox->setCurrentIndex(i + 1);
    }
}

/*
 * ===================================================
 * This function set MIDI ports to no entry
 * ===================================================
 */
void MainWindow::resetMidiPorts()
{
    kbDev.setConnected(0);
#ifndef TEST_MODE
    if ((dfuDev.isConnected() == 0) && (saveIndexMidiIn > 0) && (saveIndexMidiOut > 0))
    {
        ui->midiOutComboBox->setCurrentIndex(0);
        ui->midiInComboBox->setCurrentIndex(0);
    }
#endif

#ifndef NO_MORE_BUTTONS
    ui->stopCalButton->setHidden(1);
#endif
    ui->actionStopCal->setVisible(0);
    ui->menuOutils->setEnabled(1);
    ui->menuMenu->setEnabled(1);

#ifndef TEST_MODE
    groupList[Group_NotesParam]->setHidden(1);
    groupList[Group_DetXParam]->setHidden(1);
    groupList[Group_MidiPresets]->setHidden(1);
    groupList[Group_AnglesParam]->setHidden(1);
    groupList[Group_MidiParam]->setHidden(1);
    groupList[Group_DetZParam]->setHidden(1);
    groupList[Group_MainPresets]->setHidden(1);
    //ui->midiButtonsGroupBox->setHidden(1);
    setDetActionsVisibility(false, false);

    ui->SNButton->setHidden(1);

    ui->menuCommands->setEnabled(0);
    ui->menuMIDI->setEnabled(0);
    //ui->menuOutils->setEnabled(0);

    ui->readButton->setHidden(1);
    ui->SaveParamButton->setEnabled(0);
    ui->startButton->setEnabled(0);
    ui->pauseButton->setEnabled(0);
    ui->thresholdButton->setEnabled(0);
    //ui->extMapButton->setEnabled(0);
    //ui->extMidiInComboBox->setEnabled(0);
    ui->actionLoad_Firmware->setVisible(0);
    ui->actionLoad_Firmware->setEnabled(0);
    ui->actionLoad_Firmware_2_0->setEnabled(0);
#endif
#ifdef TEST_MODE
    ui->actionLoad_Firmware->setVisible(1);
    ui->actionLoad_Firmware->setEnabled(1);
    ui->actionLoad_now->setVisible(1);
    ui->actionLoad_now->setEnabled(1);
#endif

    if (dfuDev.isConnected() == 1)
    {
        ui->actionLoad_now->setVisible(1);
        ui->actionLoad_now->setEnabled(1);
        ui->actionLoad_Firmware_2_0->setEnabled(1);
        ui->flashProgButton->setVisible(1);
        ui->flashProgButton->setEnabled(1);
        ui->actionUpdate_All->setEnabled(0);
        ui->actionUpdate_All->setVisible(0);
        ui->menuExternal_mapping->setEnabled(0);
        ui->tabWidget->setCurrentIndex(0);
        ui->notesTab->setEnabled(0);
        ui->mappingTab->setEnabled(0);
        ui->tabWidget->setTabEnabled(1, 0);
        ui->tabWidget->setTabEnabled(2, 0);
        ui->extMapButton->setEnabled(0);

        ui->actionStart->setEnabled(0);
        ui->actionPause->setEnabled(0);
        ui->actionStopCal->setEnabled(0);
        ui->actionRestart->setEnabled(0);
        ui->actionRestore_Defaults->setEnabled(0);
        ui->actionSave_in_Memory->setEnabled(0);
    }
    else
    {
        ui->actionLoad_now->setEnabled(0);
        ui->actionLoad_now->setVisible(0);
        ui->flashProgButton->setEnabled(0);
        ui->flashProgButton->setVisible(0);
        ui->actionUpdate_All->setVisible(1);
        ui->actionUpdate_All->setEnabled(1);
        ui->menuExternal_mapping->setEnabled(1);
        ui->notesTab->setEnabled(1);
        ui->mappingTab->setEnabled(1);
        ui->tabWidget->setTabEnabled(1, 1);
        ui->tabWidget->setTabEnabled(2, 1);
        ui->extMapButton->setEnabled(1);

        ui->actionStart->setEnabled(1);
        ui->actionPause->setEnabled(1);
        ui->actionStopCal->setEnabled(1);
        ui->actionRestart->setEnabled(1);
        ui->actionRestore_Defaults->setEnabled(1);
        ui->actionSave_in_Memory->setEnabled(1);
    }

    //ui->statusBar->showMessage("KB2D not connected", 0);
    setStatus(tr("KB2D not connected"));
    //ui->statusLabel->setText("KB2D not connected");
#ifndef Z_DIMENSION
    ui->nBeamsZLabelName->setHidden(1);
    ui->nStepsZComboBox->setHidden(1);
#endif
}

/*
 * ============================================
 * Midi Out Combo Box
 * ============================================
 */
void MainWindow::on_midiOutComboBox_currentIndexChanged(int index)
{
    saveIndexMidiOut = index;
    harpOut.close();
    if (index > 0)
    {
        //midiOutGetDevCapsA(index - 1, &descDev, sizeof(descDev));
        if (harpOut.open(index - 1) != MMSYSERR_NOERROR)
        {
            SendError(this, tr("Cannot connect to MIDI Out device"), GrPorts_MidiOutCB);
            ui->midiOutComboBox->setCurrentIndex(0);
            //ui->statusBar->showMessage("KB2D not connected", 0);
            setStatus(tr("KB2D not connected"));
        }
        else
        {
            //QMessageBox::information(this, "Device connected", "MIDI Out: " + (QString)qstrdup(descDev.szPname) + " connected");
            saveNameMidi = midi::getNameDevOut(index - 1);
        }
    }
    else
    {
        kbDev.setConnected(0);
        dfuDev.setConnected(0);
        resetMidiPorts();
        setStatus(tr("KB2D not connected"));
    }

    if ((saveIndexMidiOut > 0) && (saveIndexMidiIn > 0))        // If Midi In and Midi Out are selected, read all param and enable all commands
    {
        if ((QString::compare((QString)saveNameMidi, (QString)"LD Firmware Updater") == 0) && (QString::compare((QString)saveNameMidiIn, (QString)"LD Firmware Updater") == 0))
        {
            kbDev.setConnected(0);
            dfuDev.setConnected(1);
            resetMidiPorts();
            //ui->statusBar->showMessage("DFU connected", 0);
            setStatus(tr("DFU connected"));
            ui->actionLoad_Firmware_2_0->setText(tr("Exit Firmware Updater"));
        }
        else
        {
            kbDev.setConnected(1);
            dfuDev.setConnected(0);
            updateAll(1);
            ui->actionLoad_Firmware_2_0->setText(tr("Start Firmware Updater"));
        }
    }
}

/*
 * ============================================
 * Midi In Combo Box
 * ============================================
 */
void MainWindow::on_midiInComboBox_currentIndexChanged(int index)
{
    saveIndexMidiIn = index;
    harpIn.close();
    harpIn.stop();
    //midiInClose(midiDeviceIn);
    //midiInStop(midiDeviceIn);
    if (index > 0)
    {
        if (harpIn.open(index - 1, (DWORD_PTR)this) != MMSYSERR_NOERROR)
        {
            SendError(this, tr("Cannot connect to MIDI In device."), GrPorts_MidiInCB);
            ui->midiInComboBox->setCurrentIndex(0);
            setStatus(tr("KB2D not connected"));
        }
        else
        {
            saveNameMidiIn = midi::getNameDevIn(index - 1);
            harpIn.start();
        }
    }
    else
    {
        resetMidiPorts();
        setStatus(tr("KB2D not connected"));
    }

    if ((saveIndexMidiOut > 0) && (saveIndexMidiIn > 0))        // If Midi In and Midi Out are selected, read all param and enable all commands
    {
        if ((QString::compare((QString)saveNameMidi, (QString)"LD Firmware Updater") == 0) && (QString::compare((QString)saveNameMidiIn, (QString)"LD Firmware Updater") == 0))
        {
            kbDev.setConnected(0);
            dfuDev.setConnected(1);
            resetMidiPorts();
            //ui->statusBar->showMessage("DFU connected", 0);
            setStatus(tr("DFU connected"));
            ui->actionLoad_Firmware_2_0->setText(tr("Exit Firmware Updater"));
        }
        else
        {
            kbDev.setConnected(1);
            dfuDev.setConnected(0);
            updateAll(1);
            ui->actionLoad_Firmware_2_0->setText(tr("Start Firmware Updater"));
        }
    }
}


/*
 * ============================================
 * Ext Midi In Combo Box
 * ============================================
 */
void MainWindow::on_extMidiInComboBox_currentIndexChanged(int index)
{
    extIn.close();
    extIn.stop();

    if (index > 0)
    {
        if (extIn.open(index - 1, (DWORD_PTR)this) != MMSYSERR_NOERROR)
        {
            SendError(this, tr("Cannot connect to external MIDI In device."), GrPorts_MidiExtCB);
            ui->extMidiInComboBox->setCurrentIndex(0);
            ui->statusBar->showMessage(tr("External MIDI Device In not connected"), 0);
        }
        else
        {
            extIn.start();
            ui->statusBar->showMessage(tr("External MIDI Device In connected!"), 0);
        }
    }
}

/*
 * ============================================
 * Ext Midi Out Combo Box
 * ============================================
 */
void MainWindow::on_extMidiOutComboBox_currentIndexChanged(int index)
{
    extOut.close();
    if (index > 0)
    {
        if (extOut.open(index - 1) != MMSYSERR_NOERROR)
        {
            SendError(this, tr("Cannot connect to external MIDI Out device."), GrPorts_MidiExtOutCB);
            ui->extMidiOutComboBox->setCurrentIndex(0);
            ui->statusBar->showMessage(tr("External MIDI Device Out not connected"), 0);
        }
        else
        {
            ui->statusBar->showMessage(tr("External MIDI Device Out connected!"), 0);
        }
    }
}



void MainWindow::on_extMapButton_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

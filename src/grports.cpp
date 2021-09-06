
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




void MainWindow::on_nbPortsCombo_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        ui->statusBar->showMessage(tr("Wait while restarting..."), 500);
        setStatus(tr("Wait while restarting..."));
        QApplication::processEvents();
        saveCurrentDisplayAndDisable();
        //ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_KB2DSettings]));
        //ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_ExternalMIDIMapping]));
        switch (index)
        {
        case 0:
            kbDev.sendCom(MIDI_2PORTS);
            break;
        case 1:
            kbDev.sendCom(MIDI_3PORTS);
            break;
        case 2:
            kbDev.sendCom(MIDI_4PORTS);
            break;
        }
        qSleep(2000);
        restoreDisplay();
        //ui->tabWidget->addTab(ui->mainTab, listNameTabs[Tab_KB2DSettings]);
        //ui->tabWidget->addTab(ui->mappingTab, listNameTabs[Tab_ExternalMIDIMapping]);
        //ui->tabWidget->setCurrentIndex(0);

        updateMidiPortsList();  // updateAll is automatically used when ports are updated.
    }
}

/*
 * ==================================
 * Try connecting MIDI Through ports
 * ==================================
 */
void MainWindow::connectThroughPorts(QString nameThroughIn, QString nameThroughOut)
{
    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.beginGroup("Global Settings");
    if (nameThroughIn == "")
        nameThroughIn = globQSettings.value("MIDI Through In", "").toString();
    if (nameThroughOut == "")
        nameThroughOut = globQSettings.value("MIDI Through Out", "").toString();

    // Through In
    if (throughIn.open(nameThroughIn, (DWORD_PTR)this) != MMSYSERR_NOERROR)
    {
        SendError(this, tr("Cannot connect to MIDI Through In device"), GrPorts_ConnectThroughIn);
        ui->statusBar->showMessage(tr("MIDI Through In not connected"));
    }
    else
    {
        if (throughIn.getName() != "")
        {
            throughIn.start();
            ui->statusBar->showMessage(tr("MIDI Through In connected"));
            globQSettings.setValue("MIDI Through In", nameThroughIn);
        }
        if (nameThroughIn == tr("No device"))
            globQSettings.setValue("MIDI Through In", nameThroughIn);
    }

    // Through Out
    if (throughOut.open(nameThroughOut) != MMSYSERR_NOERROR)
    {
        SendError(this, tr("Cannot connect to MIDI Through Out device"), GrPorts_ConnectThroughOut);
        ui->statusBar->showMessage(tr("MIDI Through Out not connected"), 0);
    }
    else
    {
        if (throughOut.getName() != "")
        {
            ui->statusBar->showMessage(tr("MIDI Through Out connected"), 0);
            globQSettings.setValue("MIDI Through Out", nameThroughOut);
        }
        if (nameThroughOut == tr("No device"))
            globQSettings.setValue("MIDI Through Out", nameThroughOut);
    }
    globQSettings.endGroup();
}

/*
 * ===================================================
 * This function is called once the window is created
 * ===================================================
 */
void MainWindow::updateMidiPortsList(bool forceDefault, QString nameKbIn, QString nameKbOut, QString nameExtIn, QString nameExtOut, QString nameThroughIn, QString nameThroughOut)
{
    throughIn.stop();
    throughIn.close();
    throughOut.close();

    connectionReq = false;

    ui->midiOutComboBox->clear();
    ui->midiInComboBox->clear();
    ui->extMidiInComboBox->clear();
    ui->extMidiOutComboBox->clear();
    ui->midiOutComboBox->insertItem(0, tr("No Device"));
    ui->midiInComboBox->insertItem(0, tr("No Device"));
    ui->extMidiInComboBox->insertItem(0, tr("No Device"));
    ui->extMidiOutComboBox->insertItem(0, tr("No Device"));

    QCoreApplication::processEvents();

    QSettings globQSettings(".kbsession", QSettings::IniFormat);
    globQSettings.beginGroup("Global Settings");

    // Fill and connect Dev Out
    for (uint _i = 0 ; _i < (midi::getNumDevOut()) ; _i++)
    {
        ui->midiOutComboBox->insertItem(_i + 1, midi::getNameDevOut(_i));
        ui->extMidiOutComboBox->insertItem(_i + 1, midi::getNameDevOut(_i));

        // KB2D
        if (midi::getNameDevOut(_i) == "LD Firmware Updater")
            ui->midiOutComboBox->setCurrentIndex(_i + 1);
        else if (nameKbOut == "")
        {
            if ((globQSettings.value("KB Out", "").toString() == "") || forceDefault)
            {
                if (midi::getNameDevOut(_i) == "KB2D Interactive")
                    ui->midiOutComboBox->setCurrentIndex(_i + 1);
            }
            else if (midi::getNameDevOut(_i) == globQSettings.value("KB Out", "").toString())
                ui->midiOutComboBox->setCurrentIndex(_i + 1);
        }
        else if (midi::getNameDevOut(_i) == nameKbOut)
        {
            globQSettings.setValue("KB Out", nameKbOut);
            ui->midiOutComboBox->setCurrentIndex(_i + 1);
        }

        // External mapping
        if (nameExtOut == "")
        {
            if (midi::getNameDevOut(_i) == globQSettings.value("Ext MIDI Out", "").toString())
                ui->extMidiOutComboBox->setCurrentIndex(_i + 1);
        }
        else if (midi::getNameDevOut(_i) == nameExtOut)
            ui->extMidiOutComboBox->setCurrentIndex(_i + 1);
    }
    if (nameKbOut == tr("No device"))
        ui->midiOutComboBox->setCurrentIndex(0);
    if (nameExtOut == tr("No device"))
        ui->extMidiOutComboBox->setCurrentIndex(0);

    // Fill and connect Dev In
    for (uint _i = 0 ; _i < (midi::getNumDevIn()) ; _i++)
    {
        ui->midiInComboBox->insertItem(_i + 1, midi::getNameDevIn(_i));
        ui->extMidiInComboBox->insertItem(_i + 1, midi::getNameDevIn(_i));

        // KB2D
        if (midi::getNameDevIn(_i) == "LD Firmware Updater")
            ui->midiInComboBox->setCurrentIndex(_i + 1);
        else if (nameKbIn == "")
        {
            if ((globQSettings.value("KB In", "").toString() == "") || forceDefault)
            {
                if (midi::getNameDevIn(_i) == "MIDIIN2 (KB2D Interactive)")
                    ui->midiInComboBox->setCurrentIndex(_i + 1);
            }
            else if (midi::getNameDevIn(_i) == globQSettings.value("KB In", "").toString())
                ui->midiInComboBox->setCurrentIndex(_i + 1);
        }
        else if (midi::getNameDevIn(_i) == nameKbIn)
        {
            globQSettings.setValue("KB In", nameKbIn);
            ui->midiInComboBox->setCurrentIndex(_i + 1);
        }

        // External mapping
        if (nameExtIn == "")
        {
            if (midi::getNameDevIn(_i) == globQSettings.value("Ext MIDI In", "").toString())
                ui->extMidiInComboBox->setCurrentIndex(_i + 1);
        }
        else if (midi::getNameDevIn(_i) == nameExtIn)
            ui->extMidiInComboBox->setCurrentIndex(_i + 1);
    }
    if (nameKbIn == tr("No device"))
        ui->midiInComboBox->setCurrentIndex(0);
    if (nameExtIn == tr("No device"))
        ui->extMidiInComboBox->setCurrentIndex(0);

    globQSettings.endGroup();

    // Connect MIDI Through
    connectThroughPorts(nameThroughIn, nameThroughOut);

    SendLog("KBIn= " + harpIn.getName() + " | KBOut= " + harpOut.getName() + \
            " | ExtIn = " + extIn.getName() + " | ExtOut = " + extOut.getName() + \
            " | ThIn = " + throughIn.getName() + " | ThOut = " + throughOut.getName());

    // Test connections (MIDI Ports are already opened, now check communication)
    connectionReq = true;
    testConnectedDevices();
}

/*
 * ===================================================
 * This function set MIDI ports to no entry
 * ===================================================
 */
void MainWindow::resetMidiPorts()
{
    ui->midiInComboBox->setEnabled(1);
    ui->midiOutComboBox->setEnabled(1);
    kbDev.setConnected(0);
#ifndef TEST_MODE
    if ((dfuDev.isConnected() == 0) && (saveIndexMidiIn > 0) && (saveIndexMidiOut > 0))
    {
        ui->midiOutComboBox->setCurrentIndex(0);
        ui->midiInComboBox->setCurrentIndex(0);
    }
#endif

    ui->actionStopCal->setVisible(0);
    ui->menuOutils->setEnabled(1);
    ui->menuMenu->setEnabled(1);

#ifndef TEST_MODE
    disableAllGroups(true);
    setEnableGroup(Group_KB2DPorts, true);
    setDetActionsVisibility(false, false);

    ui->SNButton->setHidden(1);

    ui->menuCommands->setEnabled(0);
    //ui->menuOutils->setEnabled(0);

    ui->thresholdButton->setEnabled(0);
    ui->actionLoad_Firmware->setVisible(0);
    ui->actionLoad_Firmware->setEnabled(0);
    ui->actionLoad_now->setVisible(0);
    ui->actionLoad_now->setEnabled(0);

    ui->flashProgButton->setEnabled(0);
    ui->actionLoad_Firmware_2_0->setEnabled(0);
    ui->exitUpdaterButton->setEnabled(0);

    ui->menuExternal_mapping->setEnabled(0);

    ui->actionStart->setEnabled(0);
    ui->actionPause->setEnabled(0);
    ui->actionStopCal->setEnabled(0);
    ui->actionRestart->setEnabled(0);
    ui->actionRestore_Defaults->setEnabled(0);
    ui->actionSave_in_Memory->setEnabled(0);

    ui->tabWidget->addTab(ui->mainTab, listNameTabs[Tab_KB2DSettings]);
    ui->tabWidget->addTab(ui->mappingTab, listNameTabs[Tab_ExternalMIDIMapping]);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_FirmwareUpdater]));
#endif
#ifdef TEST_MODE
    ui->actionLoad_Firmware->setVisible(1);
    ui->actionLoad_Firmware->setEnabled(1);
#endif

    ui->firmwareStatusValue->setText("Not connected");

    //ui->statusBar->showMessage("KB2D not connected", 0);
    setStatus(tr("KB2D not connected"));
    //ui->statusLabel->setText("KB2D not connected");
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
        if (harpOut.open(index - 1) != MMSYSERR_NOERROR)
        {
            SendError(this, tr("Cannot connect to MIDI Out device"), GrPorts_MidiOutCB);
            ui->midiOutComboBox->setCurrentIndex(0);
            setStatus(tr("KB2D not connected"));
        }
        else
        {
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

    testConnectedDevices();
}

/*
 * ============================================
 * Midi In Combo Box
 * ============================================
 */
void MainWindow::on_midiInComboBox_currentIndexChanged(int index)
{
    saveIndexMidiIn = index;
    harpIn.stop();
    harpIn.close();
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

    testConnectedDevices();
}

void MainWindow::testConnectedDevices()
{
    int toUpdate = -1;

    if (connectionReq)
    {
        QSettings globQSettings(".kbsession", QSettings::IniFormat);
        globQSettings.beginGroup("Global Settings");
        if ((saveIndexMidiOut > 0) && (saveIndexMidiIn > 0))        // If Midi In and Midi Out are selected, read all param and enable all commands
        {
            if ((saveNameMidi == "LD Firmware Updater") && (saveNameMidiIn == "LD Firmware Updater"))
            {
                kbDev.setConnected(0);
                dfuDev.setConnected(1);
                //resetMidiPorts();
                ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_KB2DSettings]));
                ui->tabWidget->removeTab(GetTabIndex(ui->tabWidget, listNameTabs[Tab_ExternalMIDIMapping]));
                ui->tabWidget->addTab(ui->firmwareTab, listNameTabs[Tab_FirmwareUpdater]);
                ui->tabWidget->setCurrentIndex(0);

                initializeFU();

                setStatus(tr("DFU connected"));
                ui->actionLoad_Firmware_2_0->setText(tr("Exit Firmware Updater"));
            }
            else
            {
                // Try to communicate with KB2D
                kbDev.setConnected(1);
                dfuDev.setConnected(0);
                disconnect(&kbDev, &ComHwKb2d::comFailed, this, &MainWindow::resetMidiPorts);   // Avoid loops on updateAll fails
                if (updateAll(1) == 0)  // KB2D Connected
                {
                    ui->tabWidget->setCurrentIndex(0);

                    ui->menuExternal_mapping->setEnabled(1);

                    ui->actionStart->setEnabled(1);
                    ui->actionPause->setEnabled(1);
                    ui->actionStopCal->setEnabled(1);
                    ui->actionRestart->setEnabled(1);
                    ui->actionRestore_Defaults->setEnabled(1);
                    ui->actionSave_in_Memory->setEnabled(1);

                    ui->actionLoad_Firmware_2_0->setText(tr("Start Firmware Updater"));
                }
                else
                {
                    if ((globQSettings.value("KB In", "").toString() != "") || (globQSettings.value("KB Out", "").toString() != ""))
                    {
                        globQSettings.setValue("KB In", "");
                        globQSettings.setValue("KB Out", "");
                        toUpdate = 0;
                    }
                }
                connect(&kbDev, &ComHwKb2d::comFailed, this, &MainWindow::resetMidiPorts);
            }
        }
        else if (((globQSettings.value("KB In", "").toString() != "") && !ui->midiInComboBox->currentIndex()) || \
                 ((globQSettings.value("KB Out", "").toString() != "") && !ui->midiOutComboBox->currentIndex()))
        {
            toUpdate = 1;
        }
        globQSettings.endGroup();
    }
    if (toUpdate == 1)
        QTimer::singleShot(0, this, [this] () { this->updateMidiPortsList(true); });    // Force connection to default ports, since register ports are not available.
    else if (toUpdate == 0)
        QTimer::singleShot(0, this, [this] () { this->updateMidiPortsList(false); });
}


/*
 * ============================================
 * Ext Midi In Combo Box
 * ============================================
 */
void MainWindow::on_extMidiInComboBox_currentIndexChanged(int index)
{
    extIn.stop();
    extIn.close();

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
            // QSettings
            QSettings globQSettings(".kbsession", QSettings::IniFormat);
            globQSettings.beginGroup("Global Settings");
            globQSettings.setValue("Ext MIDI In", ui->extMidiInComboBox->currentText());
            globQSettings.endGroup();
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
            // QSettings
            QSettings globQSettings(".kbsession", QSettings::IniFormat);
            globQSettings.beginGroup("Global Settings");
            globQSettings.setValue("Ext MIDI Out", ui->extMidiOutComboBox->currentText());
            globQSettings.endGroup();
        }
    }
}

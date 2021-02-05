
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Ext Mapping **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to the External Mapping
 * (3rd Tab)
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"


/*
 * =========================
 * Map Spin Box Class
 * =========================
 */
MapSpinBox::MapSpinBox(int min, int max, int mapInd, bool isController, QWidget* parent) : QSpinBox(parent)
{
    QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setSizePolicy(policy);
    setDisplayIntegerBase(16);
    setRange(min, max);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QWidget {background-color:#4A4A4A;text-transform:uppercase;}"
                  "QWidget:hover{background-color:#405080;}");
    setFocusPolicy(Qt::StrongFocus);
    if (isController)
    {
        if (mapInd == 0)
        {
            setValue(0x0);
        }
        else if (mapInd == 2)
        {
            setValue(-1);
            setEnabled(0);
            setToolTip(tr("The value assigned here corresponds to the value sent by the controller"));
        }
    }
    else if (mapInd == 0)
        setValue(0x0);
}

MapSpinBox::~MapSpinBox() {}

/*
 * ========================
 * Disable Wheel events
 * For Map Spin Box
 * (Allows easy scrolling)
 * ========================
 */
void MapSpinBox::wheelEvent(QWheelEvent *event)
{
    if (!hasFocus())
        event->ignore();
    else
        QSpinBox::wheelEvent(event);
}

/*
 * ===========================
 * Initialize Mapping
 * Layouts, Spin Box, Buttons
 * Signals and Slots
 * ===========================
 */
void MainWindow::InitializeMapping(bool setIni)
{
    LayoutList[Layout_Main] = ui->main_GridLayout;
    LayoutList[Layout_Midi] = ui->midi_GridLayout;
    LayoutList[Layout_DetX] = ui->detX_GridLayout;
    LayoutList[Layout_DetZ] = ui->detZ_GridLayout;
    LayoutList[Layout_MainPresets] = ui->mainPresets_GridLayout;
    LayoutList[Layout_MidiPresets] = ui->midiPresets_GridLayout;

    for (int _i = 0; _i < Layout_NumTotal; _i++)
    {
        QList <QWidget *> list = LayoutList[_i]->findChildren<QWidget *>();
        foreach (QWidget *qw, list)
            delete qw;
    }

    /////// Name ///////
    mapNames[Map_Start] =               tr("Start KB2D");
    mapNames[Map_Pause] =               tr("Pause KB2D");
    mapNames[Map_Restart] =             tr("Restart KB2D");

    mapNames[Map_Default] =             tr("Restore Defaults");
    mapNames[Map_SaveFlash] =           tr("Save in KB2D");
    mapNames[Map_LearnOne] =            tr("Learn One");
    mapNames[Map_InvertX] =             tr("Invert X");
    mapNames[Map_DetectionAssistant] =  tr("Detection Assistant");
    mapNames[Map_AutoCalibration] =     tr("Auto Calibration");

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapNames[Map_Note1 + _i] =    tr("Note #") + QString::number(_i + 1);
    mapNames[Map_SendNote1] =           tr("Send Note 1");
    mapNames[Map_EnableNotesOnOff] =    tr("Enable Note On/Off");
    mapNames[Map_DisableNotesOnOff] =   tr("Disable Note On/Off");
    mapNames[Map_EnablePitch] =         tr("Enable Pitch");
    mapNames[Map_DisablePitch] =        tr("Disable Pitch");
    mapNames[Map_EnableCC] =            tr("Enable CC");
    mapNames[Map_DisableCC] =           tr("Disable CC");

    mapNames[Map_NoteChanIndX] =        tr("Note Chan IndX");
    mapNames[Map_NoteChanIndZ] =        tr("Note Chan IndZ");
    mapNames[Map_NoteChan] =            tr("Note Channel");
    mapNames[Map_NoteValueVarX] =       tr("Note Value VarX");
    mapNames[Map_NoteValueVarZ] =       tr("Note Value VarZ");
    mapNames[Map_NoteValue] =           tr("Note Value");
    mapNames[Map_NoteVelocityVarX] =    tr("Note Velocity VarX");
    mapNames[Map_NoteVelocityVarZ] =    tr("Note Velocity VarZ");
    mapNames[Map_NoteVelocity] =        tr("Note Velocity");

    mapNames[Map_PitchChanIndX] =       tr("Pitch Chan IndX");
    mapNames[Map_PitchChanIndZ] =       tr("Pitch Chan IndZ");
    mapNames[Map_PitchChan] =           tr("Pitch Channel");
    mapNames[Map_PitchControlVarX] =    tr("Pitch Control VarX");
    mapNames[Map_PitchControlVarZ] =    tr("Pitch Control VarZ");
    mapNames[Map_PitchControl] =        tr("Pitch Control");
    mapNames[Map_PitchValueVarX] =      tr("Pitch Value VarX");
    mapNames[Map_PitchValueVarZ] =      tr("Pitch Value VarZ");
    mapNames[Map_PitchValue] =          tr("Pitch Value");

    mapNames[Map_CCChanIndX] =          tr("CC Chan IndX");
    mapNames[Map_CCChanIndZ] =          tr("CC Chan IndZ");
    mapNames[Map_CCChan] =              tr("CC Channel");
    mapNames[Map_CCControlVarX] =       tr("CC Control VarX");
    mapNames[Map_CCControlVarZ] =       tr("CC Control VarZ");
    mapNames[Map_CCControl] =           tr("CC Control");
    mapNames[Map_CCValueVarX] =         tr("CC Value VarX");
    mapNames[Map_CCValueVarZ] =         tr("CC Value VarZ");
    mapNames[Map_CCValue] =             tr("CC Value");

    mapNames[Map_NBeamsX] =             tr("Number of beams X");
    mapNames[Map_FPS] =                 tr("Frames Per Second");
    mapNames[Map_DetThreshold] =        tr("Detection Threshold");
    mapNames[Map_DetSpeed] =            tr("Detection Speed");
    mapNames[Map_SpeedSelectivity] =    tr("Speed Selectivity");
    mapNames[Map_AngleDeviation] =      tr("Angle Deviation");

    mapNames[Map_ZModeRelative] =       tr("Relative Z Mode");
    mapNames[Map_ZModeAbsolute] =       tr("Absolute Z Mode");
    mapNames[Map_ZRegularMod] =         tr("Z Regular Mod");
    mapNames[Map_ZInvertedMod] =        tr("Z Inverted Mod");
    mapNames[Map_ZSmooth] =             tr("Z Smooth Coeff");
    mapNames[Map_ZAttackFilter] =       tr("Z Attack Filter");
    mapNames[Map_ZAmplitude] =          tr("Z Amplitude");
    mapNames[Map_ZStabilization] =      tr("Z Stabilization");

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapNames[Map_MainPreset1 + _i] =    tr("Main Config #") + QString::number(_i + 1);

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapNames[Map_MidiPreset1 + _i] =    tr("MIDI Config #") + QString::number(_i + 1);

    /////// Controllers ///////
    mapIsController[Map_NoteChan] = true;
    mapIsController[Map_NoteValue] = true;
    mapIsController[Map_NoteVelocity] = true;
    mapIsController[Map_PitchChan] = true;
    mapIsController[Map_PitchControl] = true;
    mapIsController[Map_PitchValue] = true;
    mapIsController[Map_CCChan] = true;
    mapIsController[Map_CCControl] = true;
    mapIsController[Map_CCValue] = true;
    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapIsController[Map_Note1 + _i] = true;

    mapIsController[Map_NBeamsX] = true;
    mapIsController[Map_FPS] = true;
    mapIsController[Map_DetThreshold] = true;
    mapIsController[Map_DetSpeed] = true;
    mapIsController[Map_SpeedSelectivity] = true;
    mapIsController[Map_AngleDeviation] = true;

    mapIsController[Map_ZSmooth] = true;
    mapIsController[Map_ZAttackFilter] = true;
    mapIsController[Map_ZAmplitude] = true;
    mapIsController[Map_ZStabilization] = true;

    /////// Layout ///////
    mapGridLayout[Map_Start] =              LayoutList[Layout_Main];
    mapGridLayout[Map_Pause] =              LayoutList[Layout_Main];
    mapGridLayout[Map_Restart] =            LayoutList[Layout_Main];
    mapGridLayout[Map_Default] =            LayoutList[Layout_Main];
    mapGridLayout[Map_SaveFlash] =          LayoutList[Layout_Main];
    mapGridLayout[Map_LearnOne] =           LayoutList[Layout_Main];
    mapGridLayout[Map_InvertX] =            LayoutList[Layout_Main];
    mapGridLayout[Map_DetectionAssistant] = LayoutList[Layout_Main];
    mapGridLayout[Map_AutoCalibration] =    LayoutList[Layout_Main];

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapGridLayout[Map_Note1 + _i] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_SendNote1] =          LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableNotesOnOff] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableNotesOnOff] =  LayoutList[Layout_Midi];
    mapGridLayout[Map_EnablePitch] =        LayoutList[Layout_Midi];
    mapGridLayout[Map_DisablePitch] =       LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableCC] =           LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableCC] =          LayoutList[Layout_Midi];

    mapGridLayout[Map_NoteChanIndX] =       LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteChanIndZ] =       LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteChan] =           LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteValueVarX] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteValueVarZ] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteValue] =          LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteVelocityVarX] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteVelocityVarZ] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_NoteVelocity] =       LayoutList[Layout_Midi];

    mapGridLayout[Map_PitchChanIndX] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchChanIndZ] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchChan] =          LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchControlVarX] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchControlVarZ] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchControl] =       LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchValueVarX] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchValueVarZ] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_PitchValue] =         LayoutList[Layout_Midi];

    mapGridLayout[Map_CCChanIndX] =         LayoutList[Layout_Midi];
    mapGridLayout[Map_CCChanIndZ] =         LayoutList[Layout_Midi];
    mapGridLayout[Map_CCChan] =             LayoutList[Layout_Midi];
    mapGridLayout[Map_CCControlVarX] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_CCControlVarZ] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_CCControl] =          LayoutList[Layout_Midi];
    mapGridLayout[Map_CCValueVarX] =        LayoutList[Layout_Midi];
    mapGridLayout[Map_CCValueVarZ] =        LayoutList[Layout_Midi];
    mapGridLayout[Map_CCValue] =            LayoutList[Layout_Midi];

    mapGridLayout[Map_NBeamsX] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_FPS] =                LayoutList[Layout_DetX];
    mapGridLayout[Map_DetThreshold] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_DetSpeed] =           LayoutList[Layout_DetX];
    mapGridLayout[Map_SpeedSelectivity] =   LayoutList[Layout_DetX];
    mapGridLayout[Map_AngleDeviation] =     LayoutList[Layout_DetX];

    mapGridLayout[Map_ZModeRelative] =      LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZModeAbsolute] =      LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZRegularMod] =        LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZInvertedMod] =       LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZSmooth] =            LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZAttackFilter] =      LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZAmplitude] =         LayoutList[Layout_DetZ];
    mapGridLayout[Map_ZStabilization] =     LayoutList[Layout_DetZ];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_MainPreset1 + _i] =    LayoutList[Layout_MainPresets];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_MidiPreset1 + _i] =    LayoutList[Layout_MidiPresets];


#define START_ROW   0

    QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Create All Widgets
    for (int _i = 0; _i < Map_NumParam; _i++)
    {
        // Label
        mapLabel[_i] = new QLabel(this);
        mapLabel[_i]->setText(mapNames[_i]);
        mapLabel[_i]->setSizePolicy(policy);
        mapLabel[_i]->setStyleSheet("QLabel {background-color:transparent;}");
        mapGridLayout[_i]->addWidget(mapLabel[_i], (START_ROW + _i), 0);

        // Spin Box
        mapSpinBox[_i][0] = new MapSpinBox(0, 255, 0, mapIsController[_i]);
        mapSpinBox[_i][1] = new MapSpinBox(-1, 127, 1, mapIsController[_i]);
        mapSpinBox[_i][2] = new MapSpinBox(-1, 127, 2, mapIsController[_i]);
        mapGridLayout[_i]->addWidget(mapSpinBox[_i][0], (START_ROW + _i), 1);
        mapGridLayout[_i]->addWidget(mapSpinBox[_i][1], (START_ROW + _i), 2);
        mapGridLayout[_i]->addWidget(mapSpinBox[_i][2], (START_ROW + _i), 3);

        // Button
        mapLearnButton[_i] = new QPushButton(tr("Learn"));
        mapLearnButton[_i]->setStyleSheet("QPushButton {width:65px;}");
        mapLearnButton[_i]->setSizePolicy(policy);
        mapGridLayout[_i]->addWidget(mapLearnButton[_i], (START_ROW + _i), 4);

        // Connect all
        connect(mapSpinBox[_i][0], &QSpinBox::editingFinished, this, [this, _i] () {this->MapSpinUpdate(_i);});
        connect(mapSpinBox[_i][1], &QSpinBox::editingFinished, this, [this, _i] () {this->MapSpinUpdate(_i);});
        connect(mapSpinBox[_i][2], &QSpinBox::editingFinished, this, [this, _i] () {this->MapSpinUpdate(_i);});
        connect(mapLearnButton[_i], &QPushButton::clicked, this, [this, _i] () {this->MapButtonClicked(_i);});
    }

    // Layouts layout
    for (int _i = 0; _i < Layout_NumTotal; _i++)
    {
        QSpacerItem* spacerMap;
        spacerMap = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
        LayoutList[_i]->addItem(spacerMap, START_ROW + Map_NumParam, 0);

        LayoutList[_i]->setColumnStretch(0, 6);
        LayoutList[_i]->setColumnStretch(1, 2);
        LayoutList[_i]->setColumnStretch(2, 2);
        LayoutList[_i]->setColumnStretch(3, 2);
        LayoutList[_i]->setColumnStretch(4, 3);
    }

    // Set initial values
    if (setIni)
    {
        ReadTempMapping();
        updateMidiMappingValues();
    }
    else
    {
        updateMidiMappingValues();
        //WriteTempMapping();
    }
}


/*
 * ==============================
 * Learn MIDI ext signal
 * ==============================
 */
void MainWindow::learnExtMIDI(int extInd)
{
    if (extMidiIndexToLearn == extInd)
    {
        /// Reset design
        mapLearnButton[extInd]->setText(tr("Learn"));
        mapLearnButton[extInd]->setStyleSheet("QPushButton {background-color:#106070;width:65px;} QPushButton:hover {background-color:#104080;}");
        extMidiIndexToLearn = -1;
        ///
    }
    else
    {
        /// Learn...
        if (ui->extMidiInComboBox->currentIndex() == 0)
            SendError(this, tr("External MIDI In port (mapping) is not selected"), GrExtMapping_LearnExt);
        mapLearnButton[extInd]->setText(tr("Learning..."));
        mapLearnButton[extInd]->setStyleSheet("QPushButton {background-color:#c22;width:65px;} QPushButton:hover {background-color:#b11;}");
        extMidiIndexToLearn = extInd;
        ///

        for (int i_loc = 0; i_loc < Map_NumParam; i_loc++)
        {
            if (i_loc != extInd)
            {
                /// Reset design for other buttons
                mapLearnButton[i_loc]->setText(tr("Learn"));
                mapLearnButton[i_loc]->setStyleSheet("QPushButton {background-color:#106070;width:65px;} QPushButton:hover {background-color:#104080;}");
                ///
            }
        }
    }
}

/*
 * ===========================
 * Update MIDI Mapping values
 * ===========================
 */
void MainWindow::updateMidiMappingValues(int mapId)
{
    if (mapId < 0)
    {
        int indX1 = 0, indX2 = 0;

        for (indX1 = 0; indX1 < Map_NumParam; indX1++)
        {
            for (indX2 = 0; indX2 < 3; indX2++)
            {
                mappingCommand[indX1][indX2] = mapSpinBox[indX1][indX2]->value();
                if (mappingCommand[indX1][0] > 0)
                    mapLabel[indX1]->setStyleSheet("QLabel {color:#FE0;background-color:transparent;}");
                else
                    mapLabel[indX1]->setStyleSheet("QLabel {color:#EEE;background-color:transparent;}");
            }
        }
    }
    else
    {
        mappingCommand[mapId][0] = mapSpinBox[mapId][0]->value();
        mappingCommand[mapId][1] = mapSpinBox[mapId][1]->value();
        mappingCommand[mapId][2] = mapSpinBox[mapId][2]->value();
        if (mappingCommand[mapId][0] > 0)
            mapLabel[mapId]->setStyleSheet("QLabel {color:#FE0;background-color:transparent;}");
        else
            mapLabel[mapId]->setStyleSheet("QLabel {color:#EEE;background-color:transparent;}");
    }
}

/////////////////////////////////////


void MainWindow::WriteTempMapping(int mapId)
{
    if (mapId < 0)
    {
        QSettings mapQSettings(".kbsession", QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            mapQSettings.beginGroup(mapNames[_i]);
            mapQSettings.setValue("Channel", mappingCommand[_i][0]);
            mapQSettings.setValue("Data1", mappingCommand[_i][1]);
            mapQSettings.setValue("Data2", mappingCommand[_i][2]);
            mapQSettings.endGroup();
        }
    }
    else
    {
        QSettings mapQSettings(".kbsession", QSettings::IniFormat);
        mapQSettings.beginGroup(mapNames[mapId]);
        mapQSettings.setValue("Channel", mappingCommand[mapId][0]);
        mapQSettings.setValue("Data1", mappingCommand[mapId][1]);
        mapQSettings.setValue("Data2", mappingCommand[mapId][2]);
        mapQSettings.endGroup();
    }
}

void MainWindow::ReadTempMapping(int mapId)
{
    if (mapId < 0)
    {
        QSettings mapQSettings(".kbsession", QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            if (mapQSettings.childGroups().contains(mapNames[_i], Qt::CaseInsensitive))
            {
                mapQSettings.beginGroup(mapNames[_i]);
                mappingCommand[_i][0] = mapQSettings.value("Channel").toInt();
                mappingCommand[_i][1] = mapQSettings.value("Data1").toInt();
                mappingCommand[_i][2] = mapQSettings.value("Data2").toInt();

                mapSpinBox[_i][0]->setValue(mappingCommand[_i][0]);
                mapSpinBox[_i][1]->setValue(mappingCommand[_i][1]);
                mapSpinBox[_i][2]->setValue(mappingCommand[_i][2]);
                mapQSettings.endGroup();
            }
        }
    }
    else
    {
        QSettings mapQSettings(".kbsession", QSettings::IniFormat);
        if (mapQSettings.childGroups().contains(mapNames[mapId], Qt::CaseInsensitive))
        {
            mapQSettings.beginGroup(mapNames[mapId]);
            mappingCommand[mapId][0] = mapQSettings.value("Channel").toInt();
            mappingCommand[mapId][1] = mapQSettings.value("Data1").toInt();
            mappingCommand[mapId][2] = mapQSettings.value("Data2").toInt();

            mapSpinBox[mapId][0]->setValue(mappingCommand[mapId][0]);
            mapSpinBox[mapId][1]->setValue(mappingCommand[mapId][1]);
            mapSpinBox[mapId][2]->setValue(mappingCommand[mapId][2]);
            mapQSettings.endGroup();
        }
    }
}

/*
 * ===========================
 * Save Mapping commands
 * ===========================
 */
void MainWindow::saveMappingFunction(void)
{
    QString wText;

    wText = QFileDialog::getSaveFileName(this, tr("Enter mapping file name .kbmap"), QDir::currentPath(), "*.kbmap");
    if (wText != NULL)
    {
        QSettings mapQSettings(wText, QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            mapQSettings.beginGroup(mapNames[_i]);
            mapQSettings.setValue("Channel", mappingCommand[_i][0]);
            mapQSettings.setValue("Data1", mappingCommand[_i][1]);
            mapQSettings.setValue("Data2", mappingCommand[_i][2]);
            mapQSettings.endGroup();
        }
    }
}

/*
 * ===========================
 * Load Mapping commands
 * ===========================
 */
void MainWindow::loadMappingFunction(void)
{
    QString wText;

    wText = QFileDialog::getOpenFileName(this, tr("Load mapping file .kbmap"), QDir::currentPath(), "*.kbmap");
    if (wText != NULL)
    {
        QSettings mapQSettings(wText, QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            if (mapQSettings.childGroups().contains(mapNames[_i], Qt::CaseInsensitive))
            {
                mapQSettings.beginGroup(mapNames[_i]);
                mappingCommand[_i][0] = mapQSettings.value("Channel").toInt();
                mappingCommand[_i][1] = mapQSettings.value("Data1").toInt();
                mappingCommand[_i][2] = mapQSettings.value("Data2").toInt();

                mapSpinBox[_i][0]->setValue(mappingCommand[_i][0]);
                mapSpinBox[_i][1]->setValue(mappingCommand[_i][1]);
                mapSpinBox[_i][2]->setValue(mappingCommand[_i][2]);
                mapQSettings.endGroup();
            }
        }
    }
    updateMidiMappingValues();
    //WriteTempMapping();
}

/*
 * ===========================
 * Load Default Mapping
 * ===========================
 */
void MainWindow::defaultMappingFunction(void)
{
    // Clear all here
    if ((QMessageBox::information(this, tr("Restore Default Mapping"), \
                                  tr("Are you sure you want to clear all and restore Default mapping?"), \
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
    {
        InitializeMapping(false);
    }
}

///////////////////////////

void MainWindow::MapSpinUpdate(int mapSpinId)
{
    updateMidiMappingValues(mapSpinId);
    //WriteTempMapping(mapSpinId);
}

void MainWindow::MapButtonClicked(int indexButton)
{
    learnExtMIDI(indexButton);
}

///////////////////////////

void MainWindow::on_loadMappingPushButton_clicked()
{
    loadMappingFunction();
}

void MainWindow::on_saveMappingPushButton_clicked()
{
    saveMappingFunction();
}

void MainWindow::on_defaultMappingPushButton_clicked()
{
    defaultMappingFunction();
}

///////////////////////////


/*
 * =============================================
 * Ext In function linked to CALLBACK
 * =============================================
 */
void MainWindow::extInProc(int par1, int par2, int par3)
{
    int paramToSend = 0;
    static QElapsedTimer timeRec;

    if (timeRec.isValid())      // If the timer has already been started
    {
        while (timeRec.elapsed() < 10)  // Control the amount of data
            QCoreApplication::processEvents();
    }
    timeRec.start();

    // Send message to Midi Through
    if (ui->extMidiOutComboBox->currentIndex() > 0)
    {
        if (extOut.sendWord(par1, par2, par3) != MMSYSERR_NOERROR)
            ui->extMidiOutComboBox->setCurrentIndex(0);
    }

    if (extMidiIndexToLearn == -1)
    {
        for (int iExt = 0 ; iExt < Map_NumParam ; iExt++)
        {
            if ((par1 == mappingCommand[iExt][0]) && \
                    ((par2 == mappingCommand[iExt][1]) || (mappingCommand[iExt][1] == -1)) && \
                    ((par3 == mappingCommand[iExt][2]) || (mappingCommand[iExt][2] == -1)))
            {
                if (mappingCommand[iExt][2] == -1)
                    paramToSend = par3;
                else if (mappingCommand[iExt][1] == -1)
                    paramToSend = par2;

                ///// Test All Cases /////
                switch (iExt)
                {
                case Map_Start:
                    startFunc();
                    break;
                case Map_Pause:
                    pauseFunc();
                    break;
                case Map_Restart:
                    restartFunc();
                    break;
                case Map_Default:
                    defaultMappingFunction();
                    break;
                case Map_SaveFlash:
                    saveInFlashFunc();
                    break;
                case Map_LearnOne:
                    learnOneAngle();
                    break;
                case Map_InvertX:
                    invertX();
                    break;
                case Map_DetectionAssistant:
                    on_autosetButton_clicked();
                    break;
                case Map_AutoCalibration:
                    calibrateAngles();
                    break;
                case Map_SendNote1:
                    sendTestNote();
                    break;
                case Map_EnableNotesOnOff:
                    ui->DescNoteComboBox->setCurrentIndex(1);
                    break;
                case Map_DisableNotesOnOff:
                    ui->DescNoteComboBox->setCurrentIndex(0);
                    break;
                case Map_EnablePitch:
                    ui->DescCC1ComboBox->setCurrentIndex(1);
                    break;
                case Map_DisablePitch:
                    ui->DescCC1ComboBox->setCurrentIndex(0);
                    break;
                case Map_EnableCC:
                    ui->DescCC2ComboBox->setCurrentIndex(1);
                    break;
                case Map_DisableCC:
                    ui->DescCC2ComboBox->setCurrentIndex(0);
                    break;
                case Map_NoteChanIndX:
                    ui->ChanNoteComboBox->setCurrentIndex(0);
                    break;
                case Map_NoteChanIndZ:
                    ui->ChanNoteComboBox->setCurrentIndex(1);
                    break;
                case Map_NoteChan:
                    ui->ChanNoteComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_NoteValueVarX:
                    ui->NoteNoteComboBox->setCurrentIndex(0);
                    break;
                case Map_NoteValueVarZ:
                    ui->NoteNoteComboBox->setCurrentIndex(1);
                    break;
                case Map_NoteValue:
                    ui->NoteNoteComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_NoteVelocityVarX:
                    ui->VelNoteComboBox->setCurrentIndex(0);
                    break;
                case Map_NoteVelocityVarZ:
                    ui->VelNoteComboBox->setCurrentIndex(1);
                    break;
                case Map_NoteVelocity:
                    ui->VelNoteComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_PitchChanIndX:
                    ui->ChanCC1ComboBox->setCurrentIndex(0);
                    break;
                case Map_PitchChanIndZ:
                    ui->ChanCC1ComboBox->setCurrentIndex(1);
                    break;
                case Map_PitchChan:
                    ui->ChanCC1ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_PitchControlVarX:
                    ui->ControlCC1ComboBox->setCurrentIndex(0);
                    break;
                case Map_PitchControlVarZ:
                    ui->ControlCC1ComboBox->setCurrentIndex(1);
                    break;
                case Map_PitchControl:
                    ui->ControlCC1ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_PitchValueVarX:
                    ui->ValCC1ComboBox->setCurrentIndex(0);
                    break;
                case Map_PitchValueVarZ:
                    ui->ValCC1ComboBox->setCurrentIndex(1);
                    break;
                case Map_PitchValue:
                    ui->ValCC1ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_CCChanIndX:
                    ui->ChanCC2ComboBox->setCurrentIndex(0);
                    break;
                case Map_CCChanIndZ:
                    ui->ChanCC2ComboBox->setCurrentIndex(1);
                    break;
                case Map_CCChan:
                    ui->ChanCC2ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_CCControlVarX:
                    ui->ControlCC2ComboBox->setCurrentIndex(0);
                    break;
                case Map_CCControlVarZ:
                    ui->ControlCC2ComboBox->setCurrentIndex(1);
                    break;
                case Map_CCControl:
                    ui->ControlCC2ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_CCValueVarX:
                    ui->ValCC2ComboBox->setCurrentIndex(0);
                    break;
                case Map_CCValueVarZ:
                    ui->ValCC2ComboBox->setCurrentIndex(1);
                    break;
                case Map_CCValue:
                    ui->ValCC2ComboBox->setCurrentIndex(paramToSend + 2);
                    break;
                case Map_NBeamsX:
                    if (paramToSend > MAX_NBEAMS)
                        ui->nBeamsXComboBox->setCurrentIndex(MAX_NBEAMS);
                    else if (paramToSend < 1)
                        ui->nBeamsXComboBox->setCurrentIndex(1);
                    else
                        ui->nBeamsXComboBox->setCurrentIndex(paramToSend);
                    break;
                case Map_FPS:
                    if (paramToSend <= ui->FPSspinBox->maximum() - ui->FPSspinBox->minimum())
                        ui->FPSspinBox->setValue(ui->FPSspinBox->minimum() + paramToSend);
                    else
                        ui->FPSspinBox->setValue(ui->FPSspinBox->maximum());
                    ui->FPSspinBox->editingFinished();
                    break;
                case Map_DetThreshold:
                    if (paramToSend <= ui->detLevelspinBox->maximum() - ui->detLevelspinBox->minimum())
                        ui->detLevelspinBox->setValue(ui->detLevelspinBox->minimum() + paramToSend);
                    else
                        ui->detLevelspinBox->setValue(ui->detLevelspinBox->maximum());
                    ui->detLevelspinBox->editingFinished();
                    break;
                case Map_DetSpeed:
                    if (paramToSend <= ui->detSpeedspinBox->maximum() - ui->detSpeedspinBox->minimum())
                        ui->detSpeedspinBox->setValue(ui->detSpeedspinBox->minimum() + paramToSend);
                    else
                        ui->detSpeedspinBox->setValue(ui->detSpeedspinBox->maximum());
                    ui->detSpeedspinBox->editingFinished();
                    break;
                case Map_SpeedSelectivity:
                    if (paramToSend <= ui->detSelectivityspinBox->maximum() - ui->detSelectivityspinBox->minimum())
                        ui->detSelectivityspinBox->setValue(ui->detSelectivityspinBox->minimum() + paramToSend);
                    else
                        ui->detSelectivityspinBox->setValue(ui->detSelectivityspinBox->maximum());
                    ui->detSelectivityspinBox->editingFinished();
                    break;
                case Map_AngleDeviation:
                    if (paramToSend <= ui->accuracySpinBox->maximum() - ui->accuracySpinBox->minimum())
                        ui->accuracySpinBox->setValue(ui->accuracySpinBox->minimum() + paramToSend);
                    else
                        ui->accuracySpinBox->setValue(ui->accuracySpinBox->maximum());
                    ui->accuracySpinBox->editingFinished();
                    break;
                case Map_ZModeRelative:
                    ui->modulationZComboBox->setCurrentIndex(0);
                    break;
                case Map_ZModeAbsolute:
                    ui->modulationZComboBox->setCurrentIndex(1);
                    break;
                case Map_ZInvertedMod:
                    ui->invertZCheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_ZRegularMod:
                    ui->invertZCheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_ZSmooth:
                    if (paramToSend <= ui->smoothZSpinBox->maximum() - ui->smoothZSpinBox->minimum())
                        ui->smoothZSpinBox->setValue(ui->smoothZSpinBox->minimum() + paramToSend);
                    else
                        ui->smoothZSpinBox->setValue(ui->smoothZSpinBox->maximum());
                    ui->smoothZSpinBox->editingFinished();
                    break;
                case Map_ZAttackFilter:
                    if (paramToSend <= ui->filterZSpinBox->maximum() - ui->filterZSpinBox->minimum())
                        ui->filterZSpinBox->setValue(ui->filterZSpinBox->minimum() + paramToSend);
                    else
                        ui->filterZSpinBox->setValue(ui->filterZSpinBox->maximum());
                    ui->filterZSpinBox->editingFinished();
                    break;
                case Map_ZAmplitude:
                    if (paramToSend <= ui->ampZSpinBox->maximum() - ui->ampZSpinBox->minimum())
                        ui->ampZSpinBox->setValue(ui->ampZSpinBox->minimum() + paramToSend);
                    else
                        ui->ampZSpinBox->setValue(ui->ampZSpinBox->maximum());
                    ui->ampZSpinBox->editingFinished();
                    break;
                case Map_ZStabilization:
                    if (paramToSend <= ui->stabZSpinBox->maximum() - ui->stabZSpinBox->minimum())
                        ui->stabZSpinBox->setValue(ui->stabZSpinBox->minimum() + paramToSend);
                    else
                        ui->stabZSpinBox->setValue(ui->stabZSpinBox->maximum());
                    ui->stabZSpinBox->editingFinished();
                    break;
                default:
                    if ((iExt >= Map_Note1) && (iExt < (Map_Note1 + MAX_NBEAMS)))
                        Z0_ComboBox[iExt - Map_Note1]->setCurrentIndex(paramToSend);

                    if ((iExt >= Map_MainPreset1) && (iExt < (Map_MainPreset1 + NUM_CONFIGS)))
                        ui->mainConfigComboBox->setCurrentIndex(iExt - Map_MainPreset1 + 1);

                    if ((iExt >= Map_MidiPreset1) && (iExt < (Map_MidiPreset1 + NUM_CONFIGS)))
                        ui->midiConfigComboBox->setCurrentIndex(iExt - Map_MidiPreset1 + 1);
                    break;
                }
                // Do not exit the loop when the command has been found. (One MIDI command can control multiple mapping function
            }
        }
    }
    else
    {
        /// Reset design
        int saveIndex = extMidiIndexToLearn;    // extMidi is reset with learnExtMIDI

        mapSpinBox[saveIndex][0]->setValue(par1);
        mapSpinBox[saveIndex][1]->setValue(par2);
        mapSpinBox[saveIndex][2]->setValue(par3);
        updateMidiMappingValues(saveIndex);   // Update Color Display

        learnExtMIDI(extMidiIndexToLearn);      //
        //WriteTempMapping(saveIndex);     // Update temp file (based on mappingCommand)
        this->update();
    }
}

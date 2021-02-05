
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Presets **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions linked to the UI and Preset
 * Widgets
 * (Save and Load Presets)
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/savemididialog.h"
#include "../inc/managemididialog.h"
#include "../inc/savemaindialog.h"
#include "../inc/managemaindialog.h"

void MainWindow::InitializeMidiConfig()
{
    midiSettingsNames[Midi_DescNote] = "Midi_DescNote";
    midiSettingsNames[Midi_DescCC1] = "Midi_DescCC1";
    midiSettingsNames[Midi_DescCC2] = "Midi_DescCC2";
    midiSettingsNames[Midi_ChanNote] = "Midi_ChanNote";
    midiSettingsNames[Midi_ChanCC1] = "Midi_ChanCC1";
    midiSettingsNames[Midi_ChanCC2] = "Midi_ChanCC2";
    midiSettingsNames[Midi_NoteNote] = "Midi_NoteNote";
    midiSettingsNames[Midi_ControlCC1] = "Midi_ControlCC1";
    midiSettingsNames[Midi_ControlCC2] = "Midi_ControlCC2";
    midiSettingsNames[Midi_VelNote] = "Midi_VelNote";
    midiSettingsNames[Midi_ValCC1] = "Midi_ValCC1";
    midiSettingsNames[Midi_ValCC2] = "Midi_ValCC2";
    midiSettingsNames[Midi_Note0] = "Midi_Note0";
    midiSettingsNames[Midi_Note1] = "Midi_Note1";
    midiSettingsNames[Midi_Note2] = "Midi_Note2";
    midiSettingsNames[Midi_Note3] = "Midi_Note3";
    midiSettingsNames[Midi_Note4] = "Midi_Note4";
    midiSettingsNames[Midi_Note5] = "Midi_Note5";
    midiSettingsNames[Midi_Note6] = "Midi_Note6";
    midiSettingsNames[Midi_Note7] = "Midi_Note7";
    midiSettingsNames[Midi_Note8] = "Midi_Note8";
    midiSettingsNames[Midi_Note9] = "Midi_Note9";
    midiSettingsNames[Midi_Note10] = "Midi_Note10";
    midiSettingsNames[Midi_Note11] = "Midi_Note11";
    midiSettingsNames[Midi_Note12] = "Midi_Note12";
    midiSettingsNames[Midi_Note13] = "Midi_Note13";
    midiSettingsNames[Midi_Note14] = "Midi_Note14";
    midiSettingsNames[Midi_Note15] = "Midi_Note15";

    midiComboBox[Midi_DescNote] = ui->DescNoteComboBox;
    midiComboBox[Midi_DescCC1] = ui->DescCC1ComboBox;
    midiComboBox[Midi_DescCC2] = ui->DescCC2ComboBox;
    midiComboBox[Midi_ChanNote] = ui->ChanNoteComboBox;
    midiComboBox[Midi_ChanCC1] = ui->ChanCC1ComboBox;
    midiComboBox[Midi_ChanCC2] = ui->ChanCC2ComboBox;
    midiComboBox[Midi_NoteNote] = ui->NoteNoteComboBox;
    midiComboBox[Midi_ControlCC1] = ui->ControlCC1ComboBox;
    midiComboBox[Midi_ControlCC2] = ui->ControlCC2ComboBox;
    midiComboBox[Midi_VelNote] = ui->VelNoteComboBox;
    midiComboBox[Midi_ValCC1] = ui->ValCC1ComboBox;
    midiComboBox[Midi_ValCC2] = ui->ValCC2ComboBox;
    midiComboBox[Midi_Note0] = Z0_ComboBox[0];
    midiComboBox[Midi_Note1] = Z0_ComboBox[1];
    midiComboBox[Midi_Note2] = Z0_ComboBox[2];
    midiComboBox[Midi_Note3] = Z0_ComboBox[3];
    midiComboBox[Midi_Note4] = Z0_ComboBox[4];
    midiComboBox[Midi_Note5] = Z0_ComboBox[5];
    midiComboBox[Midi_Note6] = Z0_ComboBox[6];
    midiComboBox[Midi_Note7] = Z0_ComboBox[7];
    midiComboBox[Midi_Note8] = Z0_ComboBox[8];
    midiComboBox[Midi_Note9] = Z0_ComboBox[9];
    midiComboBox[Midi_Note10] = Z0_ComboBox[10];
    midiComboBox[Midi_Note11] = Z0_ComboBox[11];
    midiComboBox[Midi_Note12] = Z0_ComboBox[12];
    midiComboBox[Midi_Note13] = Z0_ComboBox[13];
    midiComboBox[Midi_Note14] = Z0_ComboBox[14];
    midiComboBox[Midi_Note15] = Z0_ComboBox[15];

    UpdateMidiConfigList();
}

void MainWindow::InitializeMainConfig()
{
    mainSettingsNames[Main_NBeamsX] = "Main_NBeamsX";
    mainSettingsNames[Main_Fps] = "Main_Fps";
    mainSettingsNames[Main_Threshold] = "Main_Threshold";
    mainSettingsNames[Main_DetSpeed] = "Main_DetSpeed";
    mainSettingsNames[Main_DetSelectivity] = "Main_DetSelectivity";
    mainSettingsNames[Main_Deviation] = "Main_Deviation";

    mainSettingsNames[Main_ModulationTypeZ] = "Main_ModulationTypeZ";
    mainSettingsNames[Main_NStepsZ] = "Main_NStepsZ";
    mainSettingsNames[Main_InvertZ] = "Main_InvertZ";
    mainSettingsNames[Main_SmoothZ] = "Main_SmoothZ";
    mainSettingsNames[Main_AttackZ] = "Main_AttackZ";
    mainSettingsNames[Main_AmplitudeZ] = "Main_AmplitudeZ";
    mainSettingsNames[Main_StabZ] = "Main_StabZ";

    mainSettingsNames[Main_AngleZ0X0] = "Main_AngleZ0X0";
    mainSettingsNames[Main_AngleZ0X1] = "Main_AngleZ0X1";
    mainSettingsNames[Main_AngleZ0X2] = "Main_AngleZ0X2";
    mainSettingsNames[Main_AngleZ0X3] = "Main_AngleZ0X3";
    mainSettingsNames[Main_AngleZ0X4] = "Main_AngleZ0X4";
    mainSettingsNames[Main_AngleZ0X5] = "Main_AngleZ0X5";
    mainSettingsNames[Main_AngleZ0X6] = "Main_AngleZ0X6";
    mainSettingsNames[Main_AngleZ0X7] = "Main_AngleZ0X7";
    mainSettingsNames[Main_AngleZ0X8] = "Main_AngleZ0X8";
    mainSettingsNames[Main_AngleZ0X9] = "Main_AngleZ0X9";
    mainSettingsNames[Main_AngleZ0X10] = "Main_AngleZ0X10";
    mainSettingsNames[Main_AngleZ0X11] = "Main_AngleZ0X11";
    mainSettingsNames[Main_AngleZ0X12] = "Main_AngleZ0X12";
    mainSettingsNames[Main_AngleZ0X13] = "Main_AngleZ0X13";
    mainSettingsNames[Main_AngleZ0X14] = "Main_AngleZ0X14";
    mainSettingsNames[Main_AngleZ0X15] = "Main_AngleZ0X15";

    UpdateMainConfigList();
}

void MainWindow::UpdateMidiConfigList()
{
    int saveIndex = ui->midiConfigComboBox->currentIndex();
    updateInProgress = true;

    ui->midiConfigComboBox->clear();
    ui->midiConfigComboBox->addItem(tr("[Select Midi Config]"));

    for (int _i = 0; _i < MAX_CONFIG_MIDI; _i++)
    {
        QString tempName;
        QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

        if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            midiQSettings.beginGroup("CONFIG_" + QString::number(_i + 1));
            if (midiQSettings.allKeys().contains("NameConfig"))
                tempName = "[MIDI CONF " + QString::number(_i + 1) + "] - " + midiQSettings.value("NameConfig").toString();
            else
                tempName = "[MIDI CONF " + QString::number(_i + 1) + "] - ";
            midiQSettings.endGroup();
        }
        else
            tempName = "[MIDI CONF " + QString::number(_i + 1) + "]";
        ui->midiConfigComboBox->addItem(tempName);
    }

    QString tempName;
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(saveIndex), Qt::CaseInsensitive))
        ui->midiConfigComboBox->setCurrentIndex(saveIndex);
    else
        ui->midiConfigComboBox->setCurrentIndex(0);

    QApplication::processEvents();
    updateInProgress = false;
}

void MainWindow::UpdateMainConfigList()
{
    int saveIndex = ui->mainConfigComboBox->currentIndex();
    updateInProgress = true;

    ui->mainConfigComboBox->clear();
    ui->mainConfigComboBox->addItem(tr("[Select Main Config]"));

    for (int _i = 0; _i < MAX_CONFIG_MAIN; _i++)
    {
        QString tempName;
        QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(_i + 1));
            if (mainQSettings.allKeys().contains("NameConfig"))
                tempName = "[MAIN CONF " + QString::number(_i + 1) + "] - " + mainQSettings.value("NameConfig").toString();
            else
                tempName = "[MAIN CONF " + QString::number(_i + 1) + "] - ";
            mainQSettings.endGroup();
        }
        else
            tempName = "[MAIN CONF " + QString::number(_i + 1) + "]";
        ui->mainConfigComboBox->addItem(tempName);
    }

    QString tempName;
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(saveIndex), Qt::CaseInsensitive))
        ui->mainConfigComboBox->setCurrentIndex(saveIndex);
    else
        ui->mainConfigComboBox->setCurrentIndex(0);

    QApplication::processEvents();
    updateInProgress = false;
}

void MainWindow::on_mainConfigComboBox_currentIndexChanged(int index)
{
    if ((updateInProgress == false) && (index > 0))
        loadPresetMain(index);
}

void MainWindow::on_midiConfigComboBox_currentIndexChanged(int index)
{
    if ((updateInProgress == false) && (index > 0))
        loadPresetMidi(index);
}



/*
 * ==============================
 * Load Preset Main
 * ==============================
 */
void MainWindow::loadPresetMain(int indPre)
{
    if (kbDev.isConnected())     // Prevent spamming warning windows
    {
        QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(indPre), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(indPre));
            if (indPre == 0)    // For live save
            {
                updateInProgress = true;
                ui->mainConfigComboBox->setCurrentIndex(mainQSettings.value("NameConfig").toInt());
                updateInProgress = false;
            }

            // List all Main Parameters
            ui->nBeamsXComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_NBeamsX]).toInt());
            ui->FPSspinBox->setValue(mainQSettings.value(mainSettingsNames[Main_Fps]).toInt());
            ui->FPSspinBox->editingFinished();
            ui->detLevelspinBox->setValue(mainQSettings.value(mainSettingsNames[Main_Threshold]).toInt());
            ui->detLevelspinBox->editingFinished();
            ui->detSpeedspinBox->setValue(mainQSettings.value(mainSettingsNames[Main_DetSpeed]).toInt());
            ui->detSpeedspinBox->editingFinished();
            ui->detSelectivityspinBox->setValue(mainQSettings.value(mainSettingsNames[Main_DetSelectivity]).toInt());
            ui->detSelectivityspinBox->editingFinished();
            ui->accuracySpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_Deviation]).toInt());
            ui->accuracySpinBox->editingFinished();

            ui->modulationZComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_ModulationTypeZ]).toInt());
            ui->nStepsZComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_NStepsZ]).toInt());
            ui->invertZCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_InvertZ]).toInt());
            ui->smoothZSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_SmoothZ]).toInt());
            ui->smoothZSpinBox->editingFinished();
            ui->filterZSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_AttackZ]).toInt());
            ui->filterZSpinBox->editingFinished();
            ui->ampZSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_AmplitudeZ]).toInt());
            ui->ampZSpinBox->editingFinished();
            ui->stabZSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_StabZ]).toInt());
            ui->stabZSpinBox->editingFinished();

            for (int _i = 0; _i < MAX_NBEAMS; _i++)
            {
                angleDoubleSpinBox[_i]->setValue(mainQSettings.value(mainSettingsNames[Main_AngleZ0X0 + _i]).toDouble());
                angleDoubleSpinBox[_i]->editingFinished();
            }

            mainQSettings.endGroup();

            ui->statusBar->showMessage(tr("===== Main Preset ") + QString::number(indPre) + tr(" loaded ====="), 5000);
        }
        else if (indPre != 0)
        {
            SendError(this, tr("Cannot open CONFIG_") + QString::number(indPre) + "\nIn _MainSettings.maicfg", GrPresets_LoadPresetMain);
            ui->mainConfigComboBox->setCurrentIndex(0);
        }
    }
}

/*
 * ==============================
 * Save Preset for Main
 * ==============================
 */
void MainWindow::savePresetMain(int indPre, QString nameConfig)
{
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    mainQSettings.beginGroup("CONFIG_" + QString::number(indPre));

    if (indPre == 0)    // Save Live config
        mainQSettings.setValue("NameConfig", ui->mainConfigComboBox->currentIndex());
    else
        mainQSettings.setValue("NameConfig", nameConfig);
    // List all MIDI Parameters
    mainQSettings.setValue(mainSettingsNames[Main_NBeamsX], ui->nBeamsXComboBox->currentIndex());
    mainQSettings.setValue(mainSettingsNames[Main_Fps], ui->FPSspinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_Threshold], ui->detLevelspinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_DetSpeed], ui->detSpeedspinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_DetSelectivity], ui->detSelectivityspinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_Deviation], ui->accuracySpinBox->value());

    mainQSettings.setValue(mainSettingsNames[Main_ModulationTypeZ], ui->modulationZComboBox->currentIndex());
    mainQSettings.setValue(mainSettingsNames[Main_NStepsZ], ui->nStepsZComboBox->currentIndex());
    mainQSettings.setValue(mainSettingsNames[Main_InvertZ], (int)ui->invertZCheckBox->checkState());
    mainQSettings.setValue(mainSettingsNames[Main_SmoothZ], ui->smoothZSpinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_AttackZ], ui->filterZSpinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_AmplitudeZ], ui->ampZSpinBox->value());
    mainQSettings.setValue(mainSettingsNames[Main_StabZ], ui->stabZSpinBox->value());

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mainQSettings.setValue(mainSettingsNames[Main_AngleZ0X0 + _i], angleDoubleSpinBox[_i]->value());

    mainQSettings.endGroup();

    if (indPre > 0)     // 0 is reserved for live save
    {
        ui->statusBar->showMessage(tr("===== Main Preset ") + QString::number(indPre) + tr(" saved ====="), 5000);

        UpdateMainConfigList();
        ui->mainConfigComboBox->setCurrentIndex(indPre);
    }
}

/////////////////////////////////

/*
 * ==============================
 * Load Preset for MIDI
 * ==============================
 */
void MainWindow::loadPresetMidi(int indPre)
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(indPre), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(indPre));
        if (indPre == 0)    // For live save
        {
            updateInProgress = true;
            ui->midiConfigComboBox->setCurrentIndex(midiQSettings.value("NameConfig").toInt());
            updateInProgress = false;
        }

        // List all MIDI Parameters
        for (int _i = 0; _i < Midi_NumParam; _i++)
        {
            midiComboBox[_i]->setCurrentIndex(midiQSettings.value(midiSettingsNames[_i]).toInt());
            if (kbDev.isConnected() == 0)     // Prevent spamming warning windows
                break;
        }

        midiQSettings.endGroup();

        ui->statusBar->showMessage(tr("===== MIDI Preset ") + QString::number(indPre) + tr(" loaded ====="), 5000);
    }
    else if (indPre != 0)
    {
        SendError(this, tr("Cannot open CONFIG_") + QString::number(indPre) + "\nIn _MidiSettings.midcfg", GrPresets_LoadPresetMidi);
        ui->midiConfigComboBox->setCurrentIndex(0);
    }
}

/*
 * ==============================
 * Save Preset for MIDI
 * ==============================
 */
void MainWindow::savePresetMidi(int indPre, QString nameConfig)
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    midiQSettings.beginGroup("CONFIG_" + QString::number(indPre));

    if (indPre == 0)    // Save Live config
        midiQSettings.setValue("NameConfig", ui->midiConfigComboBox->currentIndex());
    else
        midiQSettings.setValue("NameConfig", nameConfig);
    // List all MIDI Parameters
    for (int _i = 0; _i < Midi_NumParam; _i++)
        midiQSettings.setValue(midiSettingsNames[_i], midiComboBox[_i]->currentIndex());

    midiQSettings.endGroup();

    if (indPre > 0)     // 0 is reserved for live save
    {
        ui->statusBar->showMessage(tr("===== MIDI Preset ") + QString::number(indPre) + tr(" saved ====="), 5000);

        UpdateMidiConfigList();
        ui->midiConfigComboBox->setCurrentIndex(indPre);
    }
}


void MainWindow::on_midiSaveAsButton_clicked()
{
    SaveMidiDialog saveMidiDialog(ui->midiConfigComboBox->currentIndex());
    saveMidiDialog.setModal(true);
    connect(&saveMidiDialog, &SaveMidiDialog::saveConfigValidated, this, &MainWindow::savePresetMidi);
    saveMidiDialog.exec();
}

void MainWindow::on_midiManageButton_clicked()
{
    ManageMidiDialog manageMidiDialog(ui->midiConfigComboBox->currentIndex());
    manageMidiDialog.setModal(true);
    connect (&manageMidiDialog, &ManageMidiDialog::updateNow, this, &MainWindow::updatePresetsMidi);
    manageMidiDialog.exec();
}

void MainWindow::on_mainSaveAsButton_clicked()
{
    SaveMainDialog saveMainDialog(ui->mainConfigComboBox->currentIndex());
    saveMainDialog.setModal(true);
    connect(&saveMainDialog, &SaveMainDialog::saveConfigValidated, this, &MainWindow::savePresetMain);
    saveMainDialog.exec();
}

void MainWindow::on_mainManageButton_clicked()
{
    ManageMainDialog manageMainDialog(ui->mainConfigComboBox->currentIndex());
    manageMainDialog.setModal(true);
    connect (&manageMainDialog, &ManageMainDialog::updateNow, this, &MainWindow::updatePresetsMain);
    manageMainDialog.exec();
}

void MainWindow::checkModifications()
{
    if (kbDev.isConnected())
    {
        savePresetMain(0, "");
        savePresetMidi(0, "");
    }
}

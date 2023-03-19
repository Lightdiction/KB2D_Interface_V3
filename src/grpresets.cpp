
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

#include "../inc/savemaindialog.h"
#include "../inc/managemaindialog.h"


void MainWindow::InitializeMainConfig()
{
    mainSettingsNames[Main_HWGain] = "Main_HWGain";
    mainSettingsNames[Main_NBeamsX] = "Main_NBeamsX";
    mainSettingsNames[Main_Fps] = "Main_Fps";
    mainSettingsNames[Main_Threshold] = "Main_Threshold";
    mainSettingsNames[Main_DetSpeed] = "Main_DetSpeed";
    mainSettingsNames[Main_DetSelectivity] = "Main_DetSelectivity";
    mainSettingsNames[Main_Deviation] = "Main_Deviation";
    mainSettingsNames[Main_DeviationFilter] = "Main_DeviationFilter";
    mainSettingsNames[Main_OffRelease] = "Main_OffRelease";

    mainSettingsNames[Main_ModulationTypeZ] = "Main_ModulationTypeZ";
    mainSettingsNames[Main_InvertZ] = "Main_InvertZ";
    mainSettingsNames[Main_SmoothZ] = "Main_SmoothZ";
    mainSettingsNames[Main_AttackZ] = "Main_AttackZ";
    mainSettingsNames[Main_AmplitudeZ] = "Main_AmplitudeZ";
    mainSettingsNames[Main_StabZ] = "Main_StabZ";
    mainSettingsNames[Main_MinZ] = "Main_MinZ";
    mainSettingsNames[Main_MediumZ] = "Main_MediumZ";
    mainSettingsNames[Main_MaxZ] = "Main_MaxZ";
    mainSettingsNames[Main_SubZ] = "Main_SubZ";

    mainSettingsNames[Main_MinPosX] = "Main_MinPosX";
    mainSettingsNames[Main_MaxPosX] = "Main_MaxPosX";
    mainSettingsNames[Main_SubPosX] = "Main_SubPosX";
    mainSettingsNames[Main_InvertPosX] = "Main_InvertPosX";
    mainSettingsNames[Main_MinWidthX] = "Main_MinWidthX";
    mainSettingsNames[Main_MaxWidthX] = "Main_MaxWidthX";
    mainSettingsNames[Main_SubWidthX] = "Main_SubWidthX";
    mainSettingsNames[Main_InvertWidthX] = "Main_InvertWidthX";
    mainSettingsNames[Main_MinGlideX] = "Main_MinGlideX";
    mainSettingsNames[Main_MaxGlideX] = "Main_MaxGlideX";
    mainSettingsNames[Main_SubGlideX] = "Main_SubGlideX";
    mainSettingsNames[Main_InvertGlideX] = "Main_InvertGlideX";
    mainSettingsNames[Main_StabGlideX] = "Main_StabGlideX";
    mainSettingsNames[Main_EnableSub11] = "Main_EnableSub11";
    mainSettingsNames[Main_EnableSub12] = "Main_EnableSub12";
    mainSettingsNames[Main_EnableSub31] = "Main_EnableSub31";
    mainSettingsNames[Main_EnableSub32] = "Main_EnableSub32";
    mainSettingsNames[Main_EnableSub41] = "Main_EnableSub41";
    mainSettingsNames[Main_EnableSub42] = "Main_EnableSub42";

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

    // Midi Port1
    mainSettingsNames[Midi_BeamEnabled] = "Midi_BeamEnabled";
    mainSettingsNames[Midi_SendOnClick] = "Midi_SendOnClick";
    mainSettingsNames[Midi_FirstKey] = "Midi_FirstKey";
    mainSettingsNames[Midi_NbKey] = "Midi_NbKey";
    mainSettingsNames[Midi_SendOnClick] = "Midi_SendOnClick";
    mainSettingsNames[Midi_EnableNotes] = "Midi_EnableNotes";
    mainSettingsNames[Midi_EnableEffect1] = "Midi_EnableEffect1";
    mainSettingsNames[Midi_EnableEffect2] = "Midi_EnableEffect2";
    mainSettingsNames[Midi_DescEffect1] = "Midi_DescEffect1";
    mainSettingsNames[Midi_DescEffect2] = "Midi_DescEffect2";
    mainSettingsNames[Midi_NoteChan] = "Midi_NoteChan";
    mainSettingsNames[Midi_NoteNote] = "Midi_NoteNote";
    mainSettingsNames[Midi_NoteVel] = "Midi_NoteVel";
    mainSettingsNames[Midi_Eff1Chan] = "Midi_Eff1Chan";
    mainSettingsNames[Midi_Eff1Ctrl] = "Midi_Eff1Ctrl";
    mainSettingsNames[Midi_Eff1Val] = "Midi_Eff1Val";
    mainSettingsNames[Midi_Eff2Chan] = "Midi_Eff2Chan";
    mainSettingsNames[Midi_Eff2Ctrl] = "Midi_Eff2Ctrl";
    mainSettingsNames[Midi_Eff2Val] = "Midi_Eff2Val";

    mainSettingsNames[Midi_Note0] = "Midi_Note0";
    mainSettingsNames[Midi_Note1] = "Midi_Note1";
    mainSettingsNames[Midi_Note2] = "Midi_Note2";
    mainSettingsNames[Midi_Note3] = "Midi_Note3";
    mainSettingsNames[Midi_Note4] = "Midi_Note4";
    mainSettingsNames[Midi_Note5] = "Midi_Note5";
    mainSettingsNames[Midi_Note6] = "Midi_Note6";
    mainSettingsNames[Midi_Note7] = "Midi_Note7";
    mainSettingsNames[Midi_Note8] = "Midi_Note8";
    mainSettingsNames[Midi_Note9] = "Midi_Note9";
    mainSettingsNames[Midi_Note10] = "Midi_Note10";
    mainSettingsNames[Midi_Note11] = "Midi_Note11";
    mainSettingsNames[Midi_Note12] = "Midi_Note12";
    mainSettingsNames[Midi_Note13] = "Midi_Note13";
    mainSettingsNames[Midi_Note14] = "Midi_Note14";
    mainSettingsNames[Midi_Note15] = "Midi_Note15";

    // Midi Port3
    mainSettingsNames[Midi_BeamEnabled_3P] = "Midi_BeamEnabled_3P";
    mainSettingsNames[Midi_SendOnClick_3P] = "Midi_SendOnClick_3P";
    mainSettingsNames[Midi_FirstKey_3P] = "Midi_FirstKey_3P";
    mainSettingsNames[Midi_NbKey_3P] = "Midi_NbKey_3P";
    mainSettingsNames[Midi_EnableNotes_3P] = "Midi_EnableNotes_3P";
    mainSettingsNames[Midi_EnableEffect1_3P] = "Midi_EnableEffect1_3P";
    mainSettingsNames[Midi_EnableEffect2_3P] = "Midi_EnableEffect2_3P";
    mainSettingsNames[Midi_DescEffect1_3P] = "Midi_DescEffect1_3P";
    mainSettingsNames[Midi_DescEffect2_3P] = "Midi_DescEffect2_3P";
    mainSettingsNames[Midi_NoteChan_3P] = "Midi_NoteChan_3P";
    mainSettingsNames[Midi_NoteNote_3P] = "Midi_NoteNote_3P";
    mainSettingsNames[Midi_NoteVel_3P] = "Midi_NoteVel_3P";
    mainSettingsNames[Midi_Eff1Chan_3P] = "Midi_Eff1Chan_3P";
    mainSettingsNames[Midi_Eff1Ctrl_3P] = "Midi_Eff1Ctrl_3P";
    mainSettingsNames[Midi_Eff1Val_3P] = "Midi_Eff1Val_3P";
    mainSettingsNames[Midi_Eff2Chan_3P] = "Midi_Eff2Chan_3P";
    mainSettingsNames[Midi_Eff2Ctrl_3P] = "Midi_Eff2Ctrl_3P";
    mainSettingsNames[Midi_Eff2Val_3P] = "Midi_Eff2Val_3P";

    mainSettingsNames[Midi_Note0_3P] = "Midi_Note0_3P";
    mainSettingsNames[Midi_Note1_3P] = "Midi_Note1_3P";
    mainSettingsNames[Midi_Note2_3P] = "Midi_Note2_3P";
    mainSettingsNames[Midi_Note3_3P] = "Midi_Note3_3P";
    mainSettingsNames[Midi_Note4_3P] = "Midi_Note4_3P";
    mainSettingsNames[Midi_Note5_3P] = "Midi_Note5_3P";
    mainSettingsNames[Midi_Note6_3P] = "Midi_Note6_3P";
    mainSettingsNames[Midi_Note7_3P] = "Midi_Note7_3P";
    mainSettingsNames[Midi_Note8_3P] = "Midi_Note8_3P";
    mainSettingsNames[Midi_Note9_3P] = "Midi_Note9_3P";
    mainSettingsNames[Midi_Note10_3P] = "Midi_Note10_3P";
    mainSettingsNames[Midi_Note11_3P] = "Midi_Note11_3P";
    mainSettingsNames[Midi_Note12_3P] = "Midi_Note12_3P";
    mainSettingsNames[Midi_Note13_3P] = "Midi_Note13_3P";
    mainSettingsNames[Midi_Note14_3P] = "Midi_Note14_3P";
    mainSettingsNames[Midi_Note15_3P] = "Midi_Note15_3P";

    // Midi Port4
    mainSettingsNames[Midi_BeamEnabled_4P] = "Midi_BeamEnabled_4P";
    mainSettingsNames[Midi_SendOnClick_4P] = "Midi_SendOnClick_4P";
    mainSettingsNames[Midi_FirstKey_4P] = "Midi_FirstKey_4P";
    mainSettingsNames[Midi_NbKey_4P] = "Midi_NbKey_4P";
    mainSettingsNames[Midi_EnableNotes_4P] = "Midi_EnableNotes_4P";
    mainSettingsNames[Midi_EnableEffect1_4P] = "Midi_EnableEffect1_4P";
    mainSettingsNames[Midi_EnableEffect2_4P] = "Midi_EnableEffect2_4P";
    mainSettingsNames[Midi_DescEffect1_4P] = "Midi_DescEffect1_4P";
    mainSettingsNames[Midi_DescEffect2_4P] = "Midi_DescEffect2_4P";
    mainSettingsNames[Midi_NoteChan_4P] = "Midi_NoteChan_4P";
    mainSettingsNames[Midi_NoteNote_4P] = "Midi_NoteNote_4P";
    mainSettingsNames[Midi_NoteVel_4P] = "Midi_NoteVel_4P";
    mainSettingsNames[Midi_Eff1Chan_4P] = "Midi_Eff1Chan_4P";
    mainSettingsNames[Midi_Eff1Ctrl_4P] = "Midi_Eff1Ctrl_4P";
    mainSettingsNames[Midi_Eff1Val_4P] = "Midi_Eff1Val_4P";
    mainSettingsNames[Midi_Eff2Chan_4P] = "Midi_Eff2Chan_4P";
    mainSettingsNames[Midi_Eff2Ctrl_4P] = "Midi_Eff2Ctrl_4P";
    mainSettingsNames[Midi_Eff2Val_4P] = "Midi_Eff2Val_4P";

    mainSettingsNames[Midi_Note0_4P] = "Midi_Note0_4P";
    mainSettingsNames[Midi_Note1_4P] = "Midi_Note1_4P";
    mainSettingsNames[Midi_Note2_4P] = "Midi_Note2_4P";
    mainSettingsNames[Midi_Note3_4P] = "Midi_Note3_4P";
    mainSettingsNames[Midi_Note4_4P] = "Midi_Note4_4P";
    mainSettingsNames[Midi_Note5_4P] = "Midi_Note5_4P";
    mainSettingsNames[Midi_Note6_4P] = "Midi_Note6_4P";
    mainSettingsNames[Midi_Note7_4P] = "Midi_Note7_4P";
    mainSettingsNames[Midi_Note8_4P] = "Midi_Note8_4P";
    mainSettingsNames[Midi_Note9_4P] = "Midi_Note9_4P";
    mainSettingsNames[Midi_Note10_4P] = "Midi_Note10_4P";
    mainSettingsNames[Midi_Note11_4P] = "Midi_Note11_4P";
    mainSettingsNames[Midi_Note12_4P] = "Midi_Note12_4P";
    mainSettingsNames[Midi_Note13_4P] = "Midi_Note13_4P";
    mainSettingsNames[Midi_Note14_4P] = "Midi_Note14_4P";
    mainSettingsNames[Midi_Note15_4P] = "Midi_Note15_4P";

    UpdateMainConfigList();
}

void MainWindow::UpdateMainConfigList()
{
    int saveIndex = ui->mainConfigComboBox->currentIndex();
    bool saveInP = updateInProgress;
    updateInProgress = true;

    ui->mainConfigComboBox->clear();
    ui->mainConfigComboBox->addItem(tr("[Select Main Config]"));

    for (int _i = 0; _i < MAX_CONFIG_MAIN; _i++)
    {
        QString tempName;
        QSettings mainQSettings(NAME_MAIN_PRESETS, QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(_i + 1));
            tempName = "[MAIN CONF " + QString::number(_i + 1) + "] - " + mainQSettings.value("NameConfig", "").toString();
            mainQSettings.endGroup();
        }
        else
            tempName = "[MAIN CONF " + QString::number(_i + 1) + "]";
        ui->mainConfigComboBox->addItem(tempName);
    }

    QSettings mainQSettings(NAME_MAIN_PRESETS, QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(saveIndex), Qt::CaseInsensitive))
        ui->mainConfigComboBox->setCurrentIndex(saveIndex);
    else
        ui->mainConfigComboBox->setCurrentIndex(0);

    QApplication::processEvents();
    updateInProgress = saveInP;
}

void MainWindow::on_mainConfigComboBox_currentIndexChanged(int index)
{
    if ((updateInProgress == false) && (index > 0))
        loadPresetMain(index);
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
        QSettings mainQSettings(NAME_MAIN_PRESETS, QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(indPre), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(indPre));
            if (indPre == 0)    // For live save
            {
                bool saveInP = updateInProgress;
                updateInProgress = true;
                ui->mainConfigComboBox->setCurrentIndex(mainQSettings.value("NameConfig").toInt());
                updateInProgress = saveInP;
            }

            QVector <int> listN;
            int _MidiSetNote[3] = {MIDI_SETMIDINOTE0};
            int nPort;

            // List all Main Parameters
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_HWGain]))
                ui->hardAmpComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_HWGain]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_Fps]))
                ui->FPSSlider->setValue(mainQSettings.value(mainSettingsNames[Main_Fps]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_Threshold]))
                ui->detLevelSlider->setValue(mainQSettings.value(mainSettingsNames[Main_Threshold]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_DetSpeed]))
                ui->minTimeSlider->setValue(mainQSettings.value(mainSettingsNames[Main_DetSpeed]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_DetSelectivity]))
                ui->maxTimeSlider->setValue(mainQSettings.value(mainSettingsNames[Main_DetSelectivity]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_Deviation]))
                ui->accuracySpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_Deviation]).toInt());
            on_accuracySpinBox_editingFinished();
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_DeviationFilter]))
                ui->enableAngFilterCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_DeviationFilter]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_OffRelease]))
                ui->releaseSlider->setValue(mainQSettings.value(mainSettingsNames[Main_OffRelease]).toInt());
            QApplication::processEvents();

            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_ModulationTypeZ]))
                ui->modulationZComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_ModulationTypeZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_InvertZ]))
                ui->invertZCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_InvertZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_SmoothZ]))
                ui->smoothZSlider->setValue(mainQSettings.value(mainSettingsNames[Main_SmoothZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_AttackZ]))
                ui->filterZSlider->setValue(mainQSettings.value(mainSettingsNames[Main_AttackZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_AmplitudeZ]))
                ui->ampZSlider->setValue(mainQSettings.value(mainSettingsNames[Main_AmplitudeZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_StabZ]))
                ui->stabZSlider->setValue(mainQSettings.value(mainSettingsNames[Main_StabZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MinZ]))
                ui->minHeightSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MinZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MediumZ]))
                ui->centerHeightSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MediumZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MaxZ]))
                ui->maxHeightSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MaxZ]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_SubZ]))
                ui->subHeightSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_SubZ]).toInt());
            QApplication::processEvents();

            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MinPosX]))
                ui->minPosXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MinPosX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MaxPosX]))
                ui->maxPosXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MaxPosX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_SubPosX]))
                ui->subPosXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_SubPosX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MinWidthX]))
                ui->minWidthXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MinWidthX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MaxWidthX]))
                ui->maxWidthXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MaxWidthX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_SubWidthX]))
                ui->subWidthXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_SubWidthX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MinGlideX]))
                ui->minGlideXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MinGlideX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_MaxGlideX]))
                ui->maxGlideXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_MaxGlideX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_SubGlideX]))
                ui->subGlideXSpinBox->setValue(mainQSettings.value(mainSettingsNames[Main_SubGlideX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_StabGlideX]))
                ui->stabGlideSlider->setValue(mainQSettings.value(mainSettingsNames[Main_StabGlideX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_InvertPosX]))
                ui->invertPosXCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_InvertPosX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_InvertWidthX]))
                ui->invertWidthXCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_InvertWidthX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_InvertGlideX]))
                ui->invertGlideXCheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_InvertGlideX]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub11]))
                ui->activSubEffect11CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub11]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub12]))
                ui->activSubEffect12CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub12]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub31]))
                ui->activSubEffect31CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub31]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub32]))
                ui->activSubEffect32CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub32]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub41]))
                ui->activSubEffect41CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub41]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_EnableSub42]))
                ui->activSubEffect42CheckBox->setCheckState((Qt::CheckState)mainQSettings.value(mainSettingsNames[Main_EnableSub42]).toInt());
            QApplication::processEvents();

            for (int _i = 0; _i < MAX_NBEAMS; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Main_AngleZ0X0 + _i]))
                    angleDoubleSpinBox[_i]->setValue(mainQSettings.value(mainSettingsNames[Main_AngleZ0X0 + _i]).toDouble());
                emit angleDoubleSpinBox[_i]->editingFinished();
                QApplication::processEvents();
            }

            // Midi Presets
            // Port 1
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_BeamEnabled]))
                beamsEnabled[Ports_Midi1] = mainQSettings.value(mainSettingsNames[Midi_BeamEnabled]).toInt();
            enableButtonClicked(Ports_Midi1, -1);
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_SendOnClick]))
                ui->sendOnClickCheckBox->setChecked(mainQSettings.value(mainSettingsNames[Midi_SendOnClick]).toBool());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_FirstKey]))
                ui->startKeyComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_FirstKey]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NbKey]))
                ui->nKeysSpinBox->setValue(mainQSettings.value(mainSettingsNames[Midi_NbKey]).toInt());
            on_nKeysSpinBox_editingFinished();
            QApplication::processEvents();

            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableNotes]))
                if ((enabState[Ports_Midi1] & Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableNotes]).toBool())
                    on_enableNotesOnOffButton_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect1]))
                if ((((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect1]).toBool())
                    on_enableEffect1Button_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect2]))
                if ((((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect2]).toBool())
                    on_enableEffect2Button_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect1]))
                ui->DescCC1ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect1]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect2]))
                ui->DescCC2ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect2]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteChan]))
                ui->ChanNoteComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteChan]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteNote]))
                ui->NoteNoteComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteNote]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteVel]))
                ui->VelNoteComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteVel]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Chan]))
                ui->ChanCC1ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Chan]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Ctrl]))
                ui->ControlCC1ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Ctrl]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Val]))
                ui->ValCC1ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Val]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Chan]))
                ui->ChanCC2ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Chan]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Ctrl]))
                ui->ControlCC2ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Ctrl]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Val]))
                ui->ValCC2ComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Val]).toInt());
            QApplication::processEvents();

            /*for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0 + _i]))
                    Z0_ComboBox[Ports_Midi1][_i]->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Note0 + _i]).toInt());
                QApplication::processEvents();
            }*/

            nPort = Ports_Midi1;
            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0 + _i]))
                {
                    int tempNote = mainQSettings.value(mainSettingsNames[Midi_Note0 + _i]).toInt();
                    // Update Combobox and Send shifted notes to the KB2D
                    kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
                    bool saveInP = updateInProgress;
                    updateInProgress = true;
                    Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
                    QApplication::processEvents();
                    updateInProgress= saveInP;
                    if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_LoadNotesPreset);

                    // Save the list of the new notes for the display on the keyboard
                    if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
                        listN.append(tempNote);
                }
            }

            // Update Keyboard
            if (!updateInProgress && keyboard[nPort])
            {
                keyboard[nPort]->updateNotesOnKeyboard(listN);
            }
            listN.clear();

            // Port 3
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_BeamEnabled_3P]))
                beamsEnabled[Ports_Midi3] = mainQSettings.value(mainSettingsNames[Midi_BeamEnabled_3P]).toInt();
            enableButtonClicked(Ports_Midi3, -1);
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_SendOnClick_3P]))
                ui->sendOnClickCheckBox_2->setChecked(mainQSettings.value(mainSettingsNames[Midi_SendOnClick_3P]).toBool());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_FirstKey_3P]))
                ui->startKeyComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_FirstKey_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NbKey_3P]))
                ui->nKeysSpinBox_2->setValue(mainQSettings.value(mainSettingsNames[Midi_NbKey_3P]).toInt());
            on_nKeysSpinBox_2_editingFinished();
            QApplication::processEvents();

            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableNotes_3P]))
                if ((enabState[Ports_Midi3] & Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableNotes_3P]).toBool())
                    on_enableNotesOnOffButton_2_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect1_3P]))
                if ((((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect1_3P]).toBool())
                    on_enableEffect1Button_2_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect2_3P]))
                if ((((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect2_3P]).toBool())
                    on_enableEffect2Button_2_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect1_3P]))
                ui->DescCC1ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect1_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect2_3P]))
                ui->DescCC2ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect2_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteChan_3P]))
                ui->ChanNoteComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteChan_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteNote_3P]))
                ui->NoteNoteComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteNote_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteVel_3P]))
                ui->VelNoteComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteVel_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Chan_3P]))
                ui->ChanCC1ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Chan_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Ctrl_3P]))
                ui->ControlCC1ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Ctrl_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Val_3P]))
                ui->ValCC1ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Val_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Chan_3P]))
                ui->ChanCC2ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Chan_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Ctrl_3P]))
                ui->ControlCC2ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Ctrl_3P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Val_3P]))
                ui->ValCC2ComboBox_2->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Val_3P]).toInt());
            QApplication::processEvents();

            /*for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0_3P + _i]))
                    Z0_ComboBox[Ports_Midi3][_i]->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Note0_3P + _i]).toInt());
                QApplication::processEvents();
            }*/

            nPort = Ports_Midi3;
            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0 + _i]))
                {
                    int tempNote = mainQSettings.value(mainSettingsNames[Midi_Note0 + _i]).toInt();
                    // Update Combobox and Send shifted notes to the KB2D
                    kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
                    bool saveInP = updateInProgress;
                    updateInProgress = true;
                    Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
                    QApplication::processEvents();
                    updateInProgress= saveInP;
                    if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_LoadNotesPreset);

                    // Save the list of the new notes for the display on the keyboard
                    if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
                        listN.append(tempNote);
                }
            }

            // Update Keyboard
            if (!updateInProgress && keyboard[nPort])
            {
                keyboard[nPort]->updateNotesOnKeyboard(listN);
            }
            listN.clear();

            // Port 4
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_BeamEnabled_4P]))
                beamsEnabled[Ports_Midi4] = mainQSettings.value(mainSettingsNames[Midi_BeamEnabled_4P]).toInt();
            enableButtonClicked(Ports_Midi4, -1);
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_SendOnClick_4P]))
                ui->sendOnClickCheckBox_3->setChecked(mainQSettings.value(mainSettingsNames[Midi_SendOnClick_4P]).toBool());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_FirstKey_4P]))
                ui->startKeyComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_FirstKey_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NbKey_4P]))
                ui->nKeysSpinBox_3->setValue(mainQSettings.value(mainSettingsNames[Midi_NbKey_4P]).toInt());
            on_nKeysSpinBox_3_editingFinished();
            QApplication::processEvents();

            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableNotes_4P]))
                if ((enabState[Ports_Midi4] & Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableNotes_4P]).toBool())
                    on_enableNotesOnOffButton_3_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect1_4P]))
                if ((((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect1_4P]).toBool())
                    on_enableEffect1Button_3_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_EnableEffect2_4P]))
                if ((((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn) != mainQSettings.value(mainSettingsNames[Midi_EnableEffect2_4P]).toBool())
                    on_enableEffect2Button_3_clicked();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect1_4P]))
                ui->DescCC1ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect1_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_DescEffect2_4P]))
                ui->DescCC2ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_DescEffect2_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteChan_4P]))
                ui->ChanNoteComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteChan_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteNote_4P]))
                ui->NoteNoteComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteNote_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_NoteVel_4P]))
                ui->VelNoteComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_NoteVel_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Chan_4P]))
                ui->ChanCC1ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Chan_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Ctrl_4P]))
                ui->ControlCC1ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Ctrl_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff1Val_4P]))
                ui->ValCC1ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff1Val_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Chan_4P]))
                ui->ChanCC2ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Chan_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Ctrl_4P]))
                ui->ControlCC2ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Ctrl_4P]).toInt());
            QApplication::processEvents();
            if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Eff2Val_4P]))
                ui->ValCC2ComboBox_3->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Eff2Val_4P]).toInt());
            QApplication::processEvents();

            /*for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0_4P + _i]))
                    Z0_ComboBox[Ports_Midi4][_i]->setCurrentIndex(mainQSettings.value(mainSettingsNames[Midi_Note0_4P + _i]).toInt());
                QApplication::processEvents();
            }*/

            nPort = Ports_Midi4;
            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (mainQSettings.allKeys().contains(mainSettingsNames[Midi_Note0 + _i]))
                {
                    int tempNote = mainQSettings.value(mainSettingsNames[Midi_Note0 + _i]).toInt();
                    // Update Combobox and Send shifted notes to the KB2D
                    kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
                    bool saveInP = updateInProgress;
                    updateInProgress = true;
                    Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
                    QApplication::processEvents();
                    updateInProgress= saveInP;
                    if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_LoadNotesPreset);

                    // Save the list of the new notes for the display on the keyboard
                    if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
                        listN.append(tempNote);
                }
            }

            // Update Keyboard
            if (!updateInProgress && keyboard[nPort])
            {
                keyboard[nPort]->updateNotesOnKeyboard(listN);
            }
            listN.clear();

            // Update the beams at the end because it also updates the visibility
            if (mainQSettings.allKeys().contains(mainSettingsNames[Main_NBeamsX]))
                ui->nBeamsXComboBox->setCurrentIndex(mainQSettings.value(mainSettingsNames[Main_NBeamsX]).toInt());
            QApplication::processEvents();

            mainQSettings.endGroup();

            ui->statusBar->showMessage(tr("===== Main Preset ") + QString::number(indPre) + tr(" loaded ====="), 5000);
        }
        else if (indPre != 0)
        {
            SendError(this, tr("Cannot open CONFIG_") + QString::number(indPre) + "\nIn " NAME_MAIN_PRESETS, GrPresets_LoadPresetMain);
            ui->mainConfigComboBox->setCurrentIndex(0);
        }
    }
}

/*
 * ==============================
 * Save Preset for Main
 * ==============================
 */
void MainWindow::savePresetMain(int indPre, QString nameConfig, bool incDet, bool incHeight, bool incAngles, bool incNotes, bool incVarsX)
{
    QSettings mainQSettings(NAME_MAIN_PRESETS, QSettings::IniFormat);

    mainQSettings.beginGroup("CONFIG_" + QString::number(indPre));
    mainQSettings.remove("");   // Clear current group

    if (indPre == 0)    // Save Live config
        mainQSettings.setValue("NameConfig", ui->mainConfigComboBox->currentIndex());
    else
        mainQSettings.setValue("NameConfig", nameConfig);

    // List all Main Presets
    if (incDet)
    {
        mainQSettings.setValue(mainSettingsNames[Main_HWGain], ui->hardAmpComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Main_Fps], ui->FPSspinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_Threshold], ui->detLevelspinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_DetSpeed], ui->minTimeSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_DetSelectivity], ui->maxTimeSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_OffRelease], ui->releaseSpinBox->value());
    }
    if (incHeight)
    {
        mainQSettings.setValue(mainSettingsNames[Main_ModulationTypeZ], ui->modulationZComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Main_InvertZ], (int)ui->invertZCheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_SmoothZ], ui->smoothZSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_AttackZ], ui->filterZSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_AmplitudeZ], ui->ampZSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_StabZ], ui->stabZSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MinZ], ui->minHeightSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MediumZ], ui->centerHeightSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MaxZ], ui->maxHeightSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_SubZ], ui->subHeightSpinBox->value());
    }

    if (incVarsX)
    {
        mainQSettings.setValue(mainSettingsNames[Main_MinPosX], ui->minPosXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MaxPosX], ui->maxPosXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_SubPosX], ui->subPosXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_InvertPosX], (int)ui->invertPosXCheckBox->checkState());

        mainQSettings.setValue(mainSettingsNames[Main_MinWidthX], ui->minWidthXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MaxWidthX], ui->maxWidthXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_SubWidthX], ui->subWidthXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_InvertWidthX], (int)ui->invertWidthXCheckBox->checkState());

        mainQSettings.setValue(mainSettingsNames[Main_MinGlideX], ui->minGlideXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_MaxGlideX], ui->maxGlideXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_SubGlideX], ui->subGlideXSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_InvertGlideX], (int)ui->invertGlideXCheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_StabGlideX], ui->stabGlideSpinBox->value());

        mainQSettings.setValue(mainSettingsNames[Main_EnableSub11], (int)ui->activSubEffect11CheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_EnableSub12], (int)ui->activSubEffect12CheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_EnableSub31], (int)ui->activSubEffect31CheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_EnableSub32], (int)ui->activSubEffect32CheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_EnableSub41], (int)ui->activSubEffect41CheckBox->checkState());
        mainQSettings.setValue(mainSettingsNames[Main_EnableSub42], (int)ui->activSubEffect42CheckBox->checkState());
    }

    // Angles + N Beams
    if (incAngles)
    {
        mainQSettings.setValue(mainSettingsNames[Main_NBeamsX], ui->nBeamsXComboBox->currentIndex());
        for (int _i = 0; _i < MAX_NBEAMS; _i++)
            mainQSettings.setValue(mainSettingsNames[Main_AngleZ0X0 + _i], angleDoubleSpinBox[_i]->value());
        mainQSettings.setValue(mainSettingsNames[Main_Deviation], ui->accuracySpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Main_DeviationFilter], (int)ui->enableAngFilterCheckBox->checkState());
    }

    // Midi Presets
    if (incNotes)
    {
        /// PORT 1 ///
        mainQSettings.setValue(mainSettingsNames[Midi_BeamEnabled], beamsEnabled[Ports_Midi1]);
        mainQSettings.setValue(mainSettingsNames[Midi_SendOnClick], ui->sendOnClickCheckBox->isChecked());
        mainQSettings.setValue(mainSettingsNames[Midi_FirstKey], ui->startKeyComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_NbKey], ui->nKeysSpinBox->value());
        mainQSettings.setValue(mainSettingsNames[Midi_EnableNotes], (bool)(enabState[Ports_Midi1] & Mode_NoteOn));
        mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect1], (bool)(((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn));
        mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect2], (bool)(((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn));
        mainQSettings.setValue(mainSettingsNames[Midi_DescEffect1], ui->DescCC1ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_DescEffect2], ui->DescCC2ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_NoteChan], ui->ChanNoteComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_NoteNote], ui->NoteNoteComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_NoteVel], ui->VelNoteComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff1Chan], ui->ChanCC1ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff1Ctrl], ui->ControlCC1ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff1Val], ui->ValCC1ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff2Chan], ui->ChanCC2ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff2Ctrl], ui->ControlCC2ComboBox->currentIndex());
        mainQSettings.setValue(mainSettingsNames[Midi_Eff2Val], ui->ValCC2ComboBox->currentIndex());

        for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            mainQSettings.setValue(mainSettingsNames[Midi_Note0 + _i], Z0_ComboBox[Ports_Midi1][_i]->currentIndex());

        /// PORT 3 ///
        if (ui->nbPortsCombo->currentIndex() >= 1)
        {
            mainQSettings.setValue(mainSettingsNames[Midi_BeamEnabled_3P], beamsEnabled[Ports_Midi3]);
            mainQSettings.setValue(mainSettingsNames[Midi_SendOnClick_3P], ui->sendOnClickCheckBox_2->isChecked());
            mainQSettings.setValue(mainSettingsNames[Midi_FirstKey_3P], ui->startKeyComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NbKey_3P], ui->nKeysSpinBox_2->value());
            mainQSettings.setValue(mainSettingsNames[Midi_EnableNotes_3P], (bool)(enabState[Ports_Midi3] & Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect1_3P], (bool)(((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect2_3P], (bool)(((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_DescEffect1_3P], ui->DescCC1ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_DescEffect2_3P], ui->DescCC2ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteChan_3P], ui->ChanNoteComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteNote_3P], ui->NoteNoteComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteVel_3P], ui->VelNoteComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Chan_3P], ui->ChanCC1ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Ctrl_3P], ui->ControlCC1ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Val_3P], ui->ValCC1ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Chan_3P], ui->ChanCC2ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Ctrl_3P], ui->ControlCC2ComboBox_2->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Val_3P], ui->ValCC2ComboBox_2->currentIndex());

            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
                mainQSettings.setValue(mainSettingsNames[Midi_Note0_3P + _i], Z0_ComboBox[Ports_Midi3][_i]->currentIndex());
        }

        /// PORT 4 ///
        if (ui->nbPortsCombo->currentIndex() >= 2)
        {
            mainQSettings.setValue(mainSettingsNames[Midi_BeamEnabled_4P], beamsEnabled[Ports_Midi4]);
            mainQSettings.setValue(mainSettingsNames[Midi_SendOnClick_4P], ui->sendOnClickCheckBox_3->isChecked());
            mainQSettings.setValue(mainSettingsNames[Midi_FirstKey_4P], ui->startKeyComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NbKey_4P], ui->nKeysSpinBox_3->value());
            mainQSettings.setValue(mainSettingsNames[Midi_EnableNotes_4P], (bool)(enabState[Ports_Midi4] & Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect1_4P], (bool)(((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_EnableEffect2_4P], (bool)(((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn));
            mainQSettings.setValue(mainSettingsNames[Midi_DescEffect1_4P], ui->DescCC1ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_DescEffect2_4P], ui->DescCC2ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteChan_4P], ui->ChanNoteComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteNote_4P], ui->NoteNoteComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_NoteVel_4P], ui->VelNoteComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Chan_4P], ui->ChanCC1ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Ctrl_4P], ui->ControlCC1ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff1Val_4P], ui->ValCC1ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Chan_4P], ui->ChanCC2ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Ctrl_4P], ui->ControlCC2ComboBox_3->currentIndex());
            mainQSettings.setValue(mainSettingsNames[Midi_Eff2Val_4P], ui->ValCC2ComboBox_3->currentIndex());

            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
                mainQSettings.setValue(mainSettingsNames[Midi_Note0_4P + _i], Z0_ComboBox[Ports_Midi4][_i]->currentIndex());
        }
    }

    mainQSettings.endGroup();

    if (indPre > 0)     // 0 is reserved for live save
    {
        ui->statusBar->showMessage(tr("===== Main Preset ") + QString::number(indPre) + tr(" saved ====="), 5000);

        UpdateMainConfigList();
        ui->mainConfigComboBox->setCurrentIndex(indPre);
    }
}

/////////////////////////////////


void MainWindow::on_mainSaveAsButton_clicked()
{
    SaveMainDialog saveMainDialog(ui->mainConfigComboBox->currentIndex(), this);
    saveMainDialog.setModal(true);
    connect(&saveMainDialog, &SaveMainDialog::saveConfigValidated, this, &MainWindow::savePresetMain);
    saveMainDialog.exec();
}

void MainWindow::on_mainManageButton_clicked()
{
    ManageMainDialog manageMainDialog(ui->mainConfigComboBox->currentIndex(), this);
    manageMainDialog.setModal(true);
    connect (&manageMainDialog, &ManageMainDialog::updateNow, this, &MainWindow::updatePresetsMain);
    manageMainDialog.exec();
}

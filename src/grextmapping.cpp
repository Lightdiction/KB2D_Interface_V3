
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
    LayoutList[Layout_NotesCtrl] = ui->notesCtrl_GridLayout;
    LayoutList[Layout_NotesPresets] = ui->notesPresets_GridLayout;
    LayoutList[Layout_DetX] = ui->detX_GridLayout;
    LayoutList[Layout_MainPresets] = ui->mainPresets_GridLayout;

    for (int _i = 0; _i < Layout_NumTotal; _i++)
    {
        clearLayout(LayoutList[_i]);
        QApplication::processEvents();
    }

    /////// Name ///////
    mapNames[Map_Start][0] =               "Start KB2D";
    mapNames[Map_Start][1] =               tr("Start KB2D");
    mapNames[Map_Pause][0] =               "Pause KB2D";
    mapNames[Map_Pause][1] =               tr("Pause KB2D");
    mapNames[Map_Restart][0] =             "Restart KB2D";
    mapNames[Map_Restart][1] =             tr("Restart KB2D");
    mapNames[Map_Default][0] =             "Restore Defaults";
    mapNames[Map_Default][1] =             tr("Restore Defaults");
    mapNames[Map_SaveFlash][0] =           "Save in KB2D";
    mapNames[Map_SaveFlash][1] =           tr("Save in KB2D");
    mapNames[Map_InvertX][0] =             "Invert X";
    mapNames[Map_InvertX][1] =             tr("Invert X");
    mapNames[Map_DetectionAssistant][0] =  "Detection Assistant";
    mapNames[Map_DetectionAssistant][1] =  tr("Detection Assistant");
    mapNames[Map_AutoCalibration][0] =     "Auto Calibration";
    mapNames[Map_AutoCalibration][1] =     tr("Auto Calibration");
    mapNames[Map_LearnOne][0] =             "Learn One";
    mapNames[Map_LearnOne][1] =             tr("Learn One");
    mapNames[Map_LearnAll][0] =             "Learn All";
    mapNames[Map_LearnAll][1] =             tr("Learn All");

    // Notes Control
    mapNames[Map_PlusHalfTone][0] =         "Plus Half Tone - Port 1";
    mapNames[Map_PlusHalfTone][1] =         tr("Plus Half Tone - Port 1");
    mapNames[Map_MinusHalfTone][0] =         "Minus Half Tone - Port 1";
    mapNames[Map_MinusHalfTone][1] =         tr("Minus Half Tone - Port 1");
    mapNames[Map_PlusTone][0] =             "Plus Tone - Port 1";
    mapNames[Map_PlusTone][1] =             tr("Plus Tone - Port 1");
    mapNames[Map_MinusTone][0] =            "Minus Tone - Port 1";
    mapNames[Map_MinusTone][1] =            tr("Minus Tone - Port 1");
    mapNames[Map_User1][0] =                "User Notes 1 - Port 1";
    mapNames[Map_User1][1] =                tr("User Notes 1 - Port 1");
    mapNames[Map_User2][0] =                "User Notes 2 - Port 1";
    mapNames[Map_User2][1] =                tr("User Notes 2 - Port 1");
    mapNames[Map_User3][0] =                "User Notes 3 - Port 1";
    mapNames[Map_User3][1] =                tr("User Notes 3 - Port 1");

    mapNames[Map_PlusHalfTone_3P][0] =         "Plus Half Tone - Port 3";
    mapNames[Map_PlusHalfTone_3P][1] =         tr("Plus Half Tone - Port 3");
    mapNames[Map_MinusHalfTone_3P][0] =         "Minus Half Tone - Port 3";
    mapNames[Map_MinusHalfTone_3P][1] =         tr("Minus Half Tone - Port 3");
    mapNames[Map_PlusTone_3P][0] =             "Plus Tone - Port 3";
    mapNames[Map_PlusTone_3P][1] =             tr("Plus Tone - Port 3");
    mapNames[Map_MinusTone_3P][0] =            "Minus Tone - Port 3";
    mapNames[Map_MinusTone_3P][1] =            tr("Minus Tone - Port 3");
    mapNames[Map_User1_3P][0] =                "User Notes 1 - Port 3";
    mapNames[Map_User1_3P][1] =                tr("User Notes 1 - Port 3");
    mapNames[Map_User2_3P][0] =                "User Notes 2 - Port 3";
    mapNames[Map_User2_3P][1] =                tr("User Notes 2 - Port 3");
    mapNames[Map_User3_3P][0] =                "User Notes 3 - Port 3";
    mapNames[Map_User3_3P][1] =                tr("User Notes 3 - Port 3");

    mapNames[Map_PlusHalfTone_4P][0] =         "Plus Half Tone - Port 4";
    mapNames[Map_PlusHalfTone_4P][1] =         tr("Plus Half Tone - Port 4");
    mapNames[Map_MinusHalfTone_4P][0] =         "Minus Half Tone - Port 4";
    mapNames[Map_MinusHalfTone_4P][1] =         tr("Minus Half Tone - Port 4");
    mapNames[Map_PlusTone_4P][0] =             "Plus Tone - Port 4";
    mapNames[Map_PlusTone_4P][1] =             tr("Plus Tone - Port 4");
    mapNames[Map_MinusTone_4P][0] =            "Minus Tone - Port 4";
    mapNames[Map_MinusTone_4P][1] =            tr("Minus Tone - Port 4");
    mapNames[Map_User1_4P][0] =                "User Notes 1 - Port 4";
    mapNames[Map_User1_4P][1] =                tr("User Notes 1 - Port 4");
    mapNames[Map_User2_4P][0] =                "User Notes 2 - Port 4";
    mapNames[Map_User2_4P][1] =                tr("User Notes 2 - Port 4");
    mapNames[Map_User3_4P][0] =                "User Notes 3 - Port 4";
    mapNames[Map_User3_4P][1] =                tr("User Notes 3 - Port 4");

    // Port 1
    for (int _i = 0; _i < MAX_NBEAMS; _i++)
    {
        mapNames[Map_SendNote1 + _i][0] =    "Send Note " + QString::number(_i + 1) + " - Port 1";
        mapNames[Map_SendNote1 + _i][1] =    tr("Send Note ") + QString::number(_i + 1) + " - Port 1";
    }

    mapNames[Map_EnableNotesOnOff][0] =    "Enable Note On/Off - Port 1";
    mapNames[Map_EnableNotesOnOff][1] =    tr("Enable Note On/Off - Port 1");
    mapNames[Map_DisableNotesOnOff][0] =   "Disable Note On/Off - Port 1";
    mapNames[Map_DisableNotesOnOff][1] =   tr("Disable Note On/Off - Port 1");
    mapNames[Map_ToggleNotesOnOff][0] =    "Toggle Note On/Off - Port 1";
    mapNames[Map_ToggleNotesOnOff][1] =    tr("Toggle Note On/Off - Port 1");
    mapNames[Map_EnableEffect1][0] =       "Enable Effect 1 - Port 1";
    mapNames[Map_EnableEffect1][1] =       tr("Enable Effect 1 - Port 1");
    mapNames[Map_DisableEffect1][0] =      "Disable Effect 1 - Port 1";
    mapNames[Map_DisableEffect1][1] =      tr("Disable Effect 1 - Port 1");
    mapNames[Map_ToggleEffect1][0] =       "Toggle Effect 1 - Port 1";
    mapNames[Map_ToggleEffect1][1] =       tr("Toggle Effect 1 - Port 1");
    mapNames[Map_EnableEffect2][0] =       "Enable Effect 2 - Port 1";
    mapNames[Map_EnableEffect2][1] =       tr("Enable Effect 2 - Port 1");
    mapNames[Map_DisableEffect2][0] =      "Disable Effect 2 - Port 1";
    mapNames[Map_DisableEffect2][1] =      tr("Disable Effect 2 - Port 1");
    mapNames[Map_ToggleEffect2][0] =       "Toggle Effect 2 - Port 1";
    mapNames[Map_ToggleEffect2][1] =       tr("Toggle Effect 2 - Port 1");

    // Port 3
    for (int _i = 0; _i < MAX_NBEAMS; _i++)
    {
        mapNames[Map_SendNote1_3P + _i][0] =    "Send Note " + QString::number(_i + 1) + " - Port 3";
        mapNames[Map_SendNote1_3P + _i][1] =    tr("Send Note ") + QString::number(_i + 1) + " - Port 3";
    }

    mapNames[Map_EnableNotesOnOff_3P][0] =    "Enable Note On/Off - Port 3";
    mapNames[Map_EnableNotesOnOff_3P][1] =    tr("Enable Note On/Off - Port 3");
    mapNames[Map_DisableNotesOnOff_3P][0] =   "Disable Note On/Off - Port 3";
    mapNames[Map_DisableNotesOnOff_3P][1] =   tr("Disable Note On/Off - Port 3");
    mapNames[Map_ToggleNotesOnOff_3P][0] =    "Toggle Note On/Off - Port 3";
    mapNames[Map_ToggleNotesOnOff_3P][1] =    tr("Toggle Note On/Off - Port 3");
    mapNames[Map_EnableEffect1_3P][0] =       "Enable Effect 1 - Port 3";
    mapNames[Map_EnableEffect1_3P][1] =       tr("Enable Effect 1 - Port 3");
    mapNames[Map_DisableEffect1_3P][0] =      "Disable Effect 1 - Port 3";
    mapNames[Map_DisableEffect1_3P][1] =      tr("Disable Effect 1 - Port 3");
    mapNames[Map_ToggleEffect1_3P][0] =       "Toggle Effect 1 - Port 3";
    mapNames[Map_ToggleEffect1_3P][1] =       tr("Toggle Effect 1 - Port 3");
    mapNames[Map_EnableEffect2_3P][0] =       "Enable Effect 2 - Port 3";
    mapNames[Map_EnableEffect2_3P][1] =       tr("Enable Effect 2 - Port 3");
    mapNames[Map_DisableEffect2_3P][0] =      "Disable Effect 2 - Port 3";
    mapNames[Map_DisableEffect2_3P][1] =      tr("Disable Effect 2 - Port 3");
    mapNames[Map_ToggleEffect2_3P][0] =       "Toggle Effect 2 - Port 3";
    mapNames[Map_ToggleEffect2_3P][1] =       tr("Toggle Effect 2 - Port 3");

    // Port 4
    for (int _i = 0; _i < MAX_NBEAMS; _i++)
    {
        mapNames[Map_SendNote1_4P + _i][0] =    "Send Note " + QString::number(_i + 1) + " - Port 4";
        mapNames[Map_SendNote1_4P + _i][1] =    tr("Send Note ") + QString::number(_i + 1) + " - Port 4";
    }

    mapNames[Map_EnableNotesOnOff_4P][0] =    "Enable Note On/Off - Port 4";
    mapNames[Map_EnableNotesOnOff_4P][1] =    tr("Enable Note On/Off - Port 4");
    mapNames[Map_DisableNotesOnOff_4P][0] =   "Disable Note On/Off - Port 4";
    mapNames[Map_DisableNotesOnOff_4P][1] =   tr("Disable Note On/Off - Port 4");
    mapNames[Map_ToggleNotesOnOff_4P][0] =    "Toggle Note On/Off - Port 4";
    mapNames[Map_ToggleNotesOnOff_4P][1] =    tr("Toggle Note On/Off - Port 4");
    mapNames[Map_EnableEffect1_4P][0] =       "Enable Effect 1 - Port 4";
    mapNames[Map_EnableEffect1_4P][1] =       tr("Enable Effect 1 - Port 4");
    mapNames[Map_DisableEffect1_4P][0] =      "Disable Effect 1 - Port 4";
    mapNames[Map_DisableEffect1_4P][1] =      tr("Disable Effect 1 - Port 4");
    mapNames[Map_ToggleEffect1_4P][0] =       "Toggle Effect 1 - Port 4";
    mapNames[Map_ToggleEffect1_4P][1] =       tr("Toggle Effect 1 - Port 4");
    mapNames[Map_EnableEffect2_4P][0] =       "Enable Effect 2 - Port 4";
    mapNames[Map_EnableEffect2_4P][1] =       tr("Enable Effect 2 - Port 4");
    mapNames[Map_DisableEffect2_4P][0] =      "Disable Effect 2 - Port 4";
    mapNames[Map_DisableEffect2_4P][1] =      tr("Disable Effect 2 - Port 4");
    mapNames[Map_ToggleEffect2_4P][0] =       "Toggle Effect 2 - Port 4";
    mapNames[Map_ToggleEffect2_4P][1] =       tr("Toggle Effect 2 - Port 4");


    mapNames[Map_HWAmp][0] =               "Hardware Amplification";
    mapNames[Map_HWAmp][1] =               tr("Hardware Amplification");
    mapNames[Map_NBeamsX][0] =             "Number of beams X";
    mapNames[Map_NBeamsX][1] =             tr("Number of beams X");
    mapNames[Map_FPS][0] =                 "Frames Per Second";
    mapNames[Map_FPS][1] =                 tr("Frames Per Second");
    mapNames[Map_DetThreshold][0] =        "Detection Threshold";
    mapNames[Map_DetThreshold][1] =        tr("Detection Threshold");
    mapNames[Map_DetSpeed][0] =            "Detection Speed";
    mapNames[Map_DetSpeed][1] =            tr("Detection Speed");
    mapNames[Map_SpeedSelectivity][0] =    "Speed Selectivity";
    mapNames[Map_SpeedSelectivity][1] =    tr("Speed Selectivity");
    mapNames[Map_AngleDeviation][0] =      "Angle Deviation";
    mapNames[Map_AngleDeviation][1] =      tr("Angle Deviation");
    mapNames[Map_Release][0] =             "Note Off Release";
    mapNames[Map_Release][1] =             tr("Note Off Release");

    mapNames[Map_ZModeRelative][0] =       "Relative Height";
    mapNames[Map_ZModeRelative][1] =       tr("Relative Height");
    mapNames[Map_ZModeAbsolute][0] =       "Absolute Height";
    mapNames[Map_ZModeAbsolute][1] =       tr("Absolute Height");
    mapNames[Map_ZRegularMod][0] =         "Height Regular Mod";
    mapNames[Map_ZRegularMod][1] =         tr("Height Not Inverted");
    mapNames[Map_ZInvertedMod][0] =        "Height Inverted Mod";
    mapNames[Map_ZInvertedMod][1] =        tr("Height Inverted");
    mapNames[Map_ZSmooth][0] =             "Height Smooth Coeff";
    mapNames[Map_ZSmooth][1] =             tr("Height Smooth Coeff");
    mapNames[Map_ZAttackFilter][0] =       "Height Attack Filter";
    mapNames[Map_ZAttackFilter][1] =       tr("Height Attack Filter");
    mapNames[Map_ZAmplitude][0] =          "Height Amplitude";
    mapNames[Map_ZAmplitude][1] =          tr("Height Amplitude");
    mapNames[Map_ZStabilization][0] =      "Height Stabilization";
    mapNames[Map_ZStabilization][1] =      tr("Height Stabilization");

    mapNames[Map_ZMin][0] =                 "Min Height";
    mapNames[Map_ZMin][1] =                 tr("Min Height");
    mapNames[Map_ZCenter][0] =              "Center Height";
    mapNames[Map_ZCenter][1] =              tr("Center Height");
    mapNames[Map_ZMax][0] =                 "Max Height";
    mapNames[Map_ZMax][1] =                 tr("Max Height");
    mapNames[Map_ZSub][0] =                 "Substitute Height";
    mapNames[Map_ZSub][1] =                 tr("Substitute Height");

    mapNames[Map_MinPosX][0] =              "Min Position";
    mapNames[Map_MinPosX][1] =              tr("Min Position");
    mapNames[Map_MaxPosX][0] =              "Max Position";
    mapNames[Map_MaxPosX][1] =              tr("Max Position");
    mapNames[Map_SubPosX][0] =              "Substitute Position";
    mapNames[Map_SubPosX][1] =              tr("Substitute Position");
    mapNames[Map_InvertedPosX][0] =         "Position Inverted";
    mapNames[Map_InvertedPosX][1] =         tr("Position Inverted");
    mapNames[Map_NotInvertedPosX][0] =      "Position Not Inverted";
    mapNames[Map_NotInvertedPosX][1] =      tr("Position Not Inverted");
    mapNames[Map_MinWidthX][0] =            "Min Width";
    mapNames[Map_MinWidthX][1] =            tr("Min Width");
    mapNames[Map_MaxWidthX][0] =            "Max Width";
    mapNames[Map_MaxWidthX][1] =            tr("Max Width");
    mapNames[Map_SubWidthX][0] =            "Substitute Width";
    mapNames[Map_SubWidthX][1] =            tr("Substitute Width");
    mapNames[Map_InvertedWidthX][0] =       "Width Inverted";
    mapNames[Map_InvertedWidthX][1] =       tr("Width Inverted");
    mapNames[Map_NotInvertedWidthX][0] =    "Width Not Inverted";
    mapNames[Map_NotInvertedWidthX][1] =    tr("Width Not Inverted");
    mapNames[Map_MinGlideX][0] =            "Min Glide";
    mapNames[Map_MinGlideX][1] =            tr("Min Glide");
    mapNames[Map_MaxGlideX][0] =            "Max Glide";
    mapNames[Map_MaxGlideX][1] =            tr("Max Glide");
    mapNames[Map_SubGlideX][0] =            "Substitute Glide";
    mapNames[Map_SubGlideX][1] =            tr("Substitute Glide");
    mapNames[Map_InvertedGlideX][0] =       "Glide Inverted";
    mapNames[Map_InvertedGlideX][1] =       tr("Glide Inverted");
    mapNames[Map_NotInvertedGlideX][0] =    "Glide Not Inverted";
    mapNames[Map_NotInvertedGlideX][1] =    tr("Glide Not Inverted");
    mapNames[Map_StabGlideX][0] =           "Stab Glide";
    mapNames[Map_StabGlideX][1] =           tr("Stab Glide");
    mapNames[Map_EnableSub11][0] =          "Enable Sub Effect Port 1 - 1";
    mapNames[Map_EnableSub11][1] =          tr("Enable Sub Effect Port 1 - 1");
    mapNames[Map_DisableSub11][0] =         "Disable Sub Effect Port 1 - 1";
    mapNames[Map_DisableSub11][1] =         tr("Disable Sub Effect Port 1 - 1");
    mapNames[Map_EnableSub12][0] =          "Enable Sub Effect Port 1 - 2";
    mapNames[Map_EnableSub12][1] =          tr("Enable Sub Effect Port 1 - 2");
    mapNames[Map_DisableSub12][0] =         "Disable Sub Effect Port 1 - 2";
    mapNames[Map_DisableSub12][1] =         tr("Disable Sub Effect Port 1 - 2");
    mapNames[Map_EnableSub31][0] =          "Enable Sub Effect Port 3 - 1";
    mapNames[Map_EnableSub31][1] =          tr("Enable Sub Effect Port 3 - 1");
    mapNames[Map_DisableSub31][0] =         "Disable Sub Effect Port 3 - 1";
    mapNames[Map_DisableSub31][1] =         tr("Disable Sub Effect Port 3 - 1");
    mapNames[Map_EnableSub32][0] =          "Enable Sub Effect Port 3 - 2";
    mapNames[Map_EnableSub32][1] =          tr("Enable Sub Effect Port 3 - 2");
    mapNames[Map_DisableSub32][0] =         "Disable Sub Effect Port 3 - 2";
    mapNames[Map_DisableSub32][1] =         tr("Disable Sub Effect Port 3 - 2");
    mapNames[Map_EnableSub41][0] =          "Enable Sub Effect Port 4 - 1";
    mapNames[Map_EnableSub41][1] =          tr("Enable Sub Effect Port 4 - 1");
    mapNames[Map_DisableSub41][0] =         "Disable Sub Effect Port 4 - 1";
    mapNames[Map_DisableSub41][1] =         tr("Disable Sub Effect Port 4 - 1");
    mapNames[Map_EnableSub42][0] =          "Enable Sub Effect Port 4 - 2";
    mapNames[Map_EnableSub42][1] =          tr("Enable Sub Effect Port 4 - 2");
    mapNames[Map_DisableSub42][0] =         "Disable Sub Effect Port 4 - 2";
    mapNames[Map_DisableSub42][1] =         tr("Disable Sub Effect Port 4 - 2");

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
    {
        mapNames[Map_MainPreset1 + _i][0] =    "Main Config #" + QString::number(_i + 1);
        mapNames[Map_MainPreset1 + _i][1] =    tr("Main Config #") + QString::number(_i + 1);
    }

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
    {
        mapNames[Map_NotesPreset1 + _i][0] =    "Notes Preset #" + QString::number(_i + 1) + " - Port 1";
        mapNames[Map_NotesPreset1 + _i][1] =    tr("Notes Preset #") + QString::number(_i + 1) + " - Port 1";
    }

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
    {
        mapNames[Map_NotesPreset1_3P + _i][0] =    "Notes Preset #" + QString::number(_i + 1) + " - Port 3";
        mapNames[Map_NotesPreset1_3P + _i][1] =    tr("Notes Preset #") + QString::number(_i + 1) + " - Port 3";
    }

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
    {
        mapNames[Map_NotesPreset1_4P + _i][0] =    "Notes Preset #" + QString::number(_i + 1) + " - Port 4";
        mapNames[Map_NotesPreset1_4P + _i][1] =    tr("Notes Preset #") + QString::number(_i + 1) + " - Port 4";
    }

    /////// Controllers ///////

    mapIsController[Map_LearnOne] = true;

    mapIsController[Map_HWAmp] = true;
    mapIsController[Map_NBeamsX] = true;
    mapIsController[Map_FPS] = true;
    mapIsController[Map_DetThreshold] = true;
    mapIsController[Map_DetSpeed] = true;
    mapIsController[Map_SpeedSelectivity] = true;
    mapIsController[Map_AngleDeviation] = true;
    mapIsController[Map_Release] = true;

    mapIsController[Map_ZSmooth] = true;
    mapIsController[Map_ZAttackFilter] = true;
    mapIsController[Map_ZAmplitude] = true;
    mapIsController[Map_ZStabilization] = true;
    mapIsController[Map_ZMin] = true;
    mapIsController[Map_ZCenter] = true;
    mapIsController[Map_ZMax] = true;
    mapIsController[Map_ZSub] = true;

    mapIsController[Map_MinPosX] = true;
    mapIsController[Map_MaxPosX] = true;
    mapIsController[Map_SubPosX] = true;
    mapIsController[Map_MinWidthX] = true;
    mapIsController[Map_MaxWidthX] = true;
    mapIsController[Map_SubWidthX] = true;
    mapIsController[Map_MinGlideX] = true;
    mapIsController[Map_MaxGlideX] = true;
    mapIsController[Map_SubGlideX] = true;
    mapIsController[Map_StabGlideX] = true;

    /////// Layout ///////
    mapGridLayout[Map_Start] =              LayoutList[Layout_Main];
    mapGridLayout[Map_Pause] =              LayoutList[Layout_Main];
    mapGridLayout[Map_Restart] =            LayoutList[Layout_Main];
    mapGridLayout[Map_Default] =            LayoutList[Layout_Main];
    mapGridLayout[Map_SaveFlash] =          LayoutList[Layout_Main];
    mapGridLayout[Map_InvertX] =            LayoutList[Layout_Main];
    mapGridLayout[Map_DetectionAssistant] = LayoutList[Layout_Main];
    mapGridLayout[Map_AutoCalibration] =    LayoutList[Layout_Main];
    mapGridLayout[Map_LearnOne] =           LayoutList[Layout_Main];
    mapGridLayout[Map_LearnAll] =           LayoutList[Layout_Main];

    mapGridLayout[Map_PlusHalfTone] =       LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusHalfTone] =      LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_PlusTone] =           LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusTone] =          LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User1] =              LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User2] =              LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User3] =              LayoutList[Layout_NotesCtrl];

    mapGridLayout[Map_PlusHalfTone_3P] =    LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusHalfTone_3P] =   LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_PlusTone_3P] =        LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusTone_3P] =       LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User1_3P] =           LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User2_3P] =           LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User3_3P] =           LayoutList[Layout_NotesCtrl];

    mapGridLayout[Map_PlusHalfTone_4P] =    LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusHalfTone_4P] =   LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_PlusTone_4P] =        LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_MinusTone_4P] =       LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User1_4P] =           LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User2_4P] =           LayoutList[Layout_NotesCtrl];
    mapGridLayout[Map_User3_4P] =           LayoutList[Layout_NotesCtrl];

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapGridLayout[Map_SendNote1 + _i] =     LayoutList[Layout_Midi];

    mapGridLayout[Map_EnableNotesOnOff] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableNotesOnOff] =  LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleNotesOnOff] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect1] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect1] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect1] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect2] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect2] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect2] =      LayoutList[Layout_Midi];

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapGridLayout[Map_SendNote1_3P + _i] =     LayoutList[Layout_Midi];

    mapGridLayout[Map_EnableNotesOnOff_3P] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableNotesOnOff_3P] =  LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleNotesOnOff_3P] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect1_3P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect1_3P] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect1_3P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect2_3P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect2_3P] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect2_3P] =      LayoutList[Layout_Midi];

    for (int _i = 0; _i < MAX_NBEAMS; _i++)
        mapGridLayout[Map_SendNote1_4P + _i] =     LayoutList[Layout_Midi];

    mapGridLayout[Map_EnableNotesOnOff_4P] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableNotesOnOff_4P] =  LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleNotesOnOff_4P] =   LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect1_4P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect1_4P] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect1_4P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_EnableEffect2_4P] =      LayoutList[Layout_Midi];
    mapGridLayout[Map_DisableEffect2_4P] =     LayoutList[Layout_Midi];
    mapGridLayout[Map_ToggleEffect2_4P] =      LayoutList[Layout_Midi];


    mapGridLayout[Map_HWAmp] =              LayoutList[Layout_DetX];
    mapGridLayout[Map_NBeamsX] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_FPS] =                LayoutList[Layout_DetX];
    mapGridLayout[Map_DetThreshold] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_DetSpeed] =           LayoutList[Layout_DetX];
    mapGridLayout[Map_SpeedSelectivity] =   LayoutList[Layout_DetX];
    mapGridLayout[Map_AngleDeviation] =     LayoutList[Layout_DetX];
    mapGridLayout[Map_Release] =            LayoutList[Layout_DetX];

    mapGridLayout[Map_ZModeRelative] =      LayoutList[Layout_DetX];
    mapGridLayout[Map_ZModeAbsolute] =      LayoutList[Layout_DetX];
    mapGridLayout[Map_ZRegularMod] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_ZInvertedMod] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_ZSmooth] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_ZAttackFilter] =      LayoutList[Layout_DetX];
    mapGridLayout[Map_ZAmplitude] =         LayoutList[Layout_DetX];
    mapGridLayout[Map_ZStabilization] =     LayoutList[Layout_DetX];
    mapGridLayout[Map_ZMin] =               LayoutList[Layout_DetX];
    mapGridLayout[Map_ZCenter] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_ZMax] =               LayoutList[Layout_DetX];
    mapGridLayout[Map_ZSub] =               LayoutList[Layout_DetX];

    mapGridLayout[Map_MinPosX] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_MaxPosX] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_SubPosX] =            LayoutList[Layout_DetX];
    mapGridLayout[Map_InvertedPosX] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_NotInvertedPosX] =    LayoutList[Layout_DetX];
    mapGridLayout[Map_MinWidthX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_MaxWidthX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_SubWidthX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_InvertedWidthX] =     LayoutList[Layout_DetX];
    mapGridLayout[Map_NotInvertedWidthX] =  LayoutList[Layout_DetX];
    mapGridLayout[Map_MinGlideX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_MaxGlideX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_SubGlideX] =          LayoutList[Layout_DetX];
    mapGridLayout[Map_InvertedGlideX] =     LayoutList[Layout_DetX];
    mapGridLayout[Map_NotInvertedGlideX] =  LayoutList[Layout_DetX];
    mapGridLayout[Map_StabGlideX] =         LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub11] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub11] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub12] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub12] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub31] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub31] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub32] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub32] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub41] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub41] =       LayoutList[Layout_DetX];
    mapGridLayout[Map_EnableSub42] =        LayoutList[Layout_DetX];
    mapGridLayout[Map_DisableSub42] =       LayoutList[Layout_DetX];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_MainPreset1 + _i] =    LayoutList[Layout_MainPresets];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_NotesPreset1 + _i] =    LayoutList[Layout_NotesPresets];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_NotesPreset1_3P + _i] =    LayoutList[Layout_NotesPresets];

    for (int _i = 0; _i < NUM_CONFIGS; _i++)
        mapGridLayout[Map_NotesPreset1_4P + _i] =    LayoutList[Layout_NotesPresets];


#define START_ROW   0

    QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Create All Widgets
    for (int _i = 0; _i < Map_NumParam; _i++)
    {
        if (mapGridLayout[_i])
        {
            // Label
            mapLabel[_i] = new QLabel(this);
            mapLabel[_i]->setText(mapNames[_i][1]);
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
                if (mapNames[indX1][1] != "")
                {
                    mappingCommand[indX1][indX2] = mapSpinBox[indX1][indX2]->value();
                    if (mappingCommand[indX1][0] > 0)
                        mapLabel[indX1]->setStyleSheet("QLabel {color:#FE0;background-color:transparent;}");
                    else
                        mapLabel[indX1]->setStyleSheet("QLabel {color:#EEE;background-color:transparent;}");
                }
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
            mapQSettings.beginGroup(mapNames[_i][0]);
            mapQSettings.setValue("Channel", mappingCommand[_i][0]);
            mapQSettings.setValue("Data1", mappingCommand[_i][1]);
            mapQSettings.setValue("Data2", mappingCommand[_i][2]);
            mapQSettings.endGroup();
        }
    }
    else
    {
        QSettings mapQSettings(".kbsession", QSettings::IniFormat);
        mapQSettings.beginGroup(mapNames[mapId][0]);
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
            if ((mapNames[_i][0] != "") && mapQSettings.childGroups().contains(mapNames[_i][0], Qt::CaseInsensitive))
            {
                mapQSettings.beginGroup(mapNames[_i][0]);
                mappingCommand[_i][0] = mapQSettings.value("Channel").toInt();
                mappingCommand[_i][1] = mapQSettings.value("Data1").toInt();
                if (mapIsController[_i])
                    mappingCommand[_i][2] = -1;
                else
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
        if (mapQSettings.childGroups().contains(mapNames[mapId][0], Qt::CaseInsensitive))
        {
            mapQSettings.beginGroup(mapNames[mapId][0]);
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
    if (wText != QString())
    {
        QSettings mapQSettings(wText, QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            mapQSettings.beginGroup(mapNames[_i][0]);
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
    if (wText != QString())
    {
        QSettings mapQSettings(wText, QSettings::IniFormat);
        for (int _i = 0; _i < Map_NumParam; _i++)
        {
            if (mapQSettings.childGroups().contains(mapNames[_i][0], Qt::CaseInsensitive))
            {
                mapQSettings.beginGroup(mapNames[_i][0]);
                mappingCommand[_i][0] = mapQSettings.value("Channel").toInt();
                mappingCommand[_i][1] = mapQSettings.value("Data1").toInt();
                if (mapIsController[_i])
                    mappingCommand[_i][2] = -1;
                else
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
#ifdef WIN_PLATFORM
        if (extOut.sendWord(par1, par2, par3) != MMSYSERR_NOERROR)
#endif
#ifdef LIN_PLATFORM
        if (extOut.sendWord(par1, par2, par3) < 0)
#endif
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
                case Map_InvertX:
                    invertX();
                    break;
                case Map_DetectionAssistant:
                    QTimer::singleShot(100, this, [this] () { this->autoSetDet(); });
                    break;
                case Map_AutoCalibration:
                    calibrateAngles();
                    break;
                case Map_LearnOne:
                    learnOneAngle(paramToSend);
                    break;
                case Map_LearnAll:
                    on_actionLearn_All_One_by_One_triggered();
                    break;

                case Map_PlusHalfTone:
                    toneShiftClicked(Ports_Midi1, ToneShift_PlusHalfTone);
                    break;
                case Map_MinusHalfTone:
                    toneShiftClicked(Ports_Midi1, ToneShift_MinusHalfTone);
                    break;
                case Map_PlusTone:
                    toneShiftClicked(Ports_Midi1, ToneShift_PlusTone);
                    break;
                case Map_MinusTone:
                    toneShiftClicked(Ports_Midi1, ToneShift_MinusTone);
                    break;
                case Map_User1:
                    notePresetClicked(Ports_Midi1, 0);
                    break;
                case Map_User2:
                    notePresetClicked(Ports_Midi1, 1);
                    break;
                case Map_User3:
                    notePresetClicked(Ports_Midi1, 2);
                    break;

                case Map_PlusHalfTone_3P:
                    toneShiftClicked(Ports_Midi3, ToneShift_PlusHalfTone);
                    break;
                case Map_MinusHalfTone_3P:
                    toneShiftClicked(Ports_Midi3, ToneShift_MinusHalfTone);
                    break;
                case Map_PlusTone_3P:
                    toneShiftClicked(Ports_Midi3, ToneShift_PlusTone);
                    break;
                case Map_MinusTone_3P:
                    toneShiftClicked(Ports_Midi3, ToneShift_MinusTone);
                    break;
                case Map_User1_3P:
                    notePresetClicked(Ports_Midi3, 0);
                    break;
                case Map_User2_3P:
                    notePresetClicked(Ports_Midi3, 1);
                    break;
                case Map_User3_3P:
                    notePresetClicked(Ports_Midi3, 2);
                    break;

                case Map_PlusHalfTone_4P:
                    toneShiftClicked(Ports_Midi4, ToneShift_PlusHalfTone);
                    break;
                case Map_MinusHalfTone_4P:
                    toneShiftClicked(Ports_Midi4, ToneShift_MinusHalfTone);
                    break;
                case Map_PlusTone_4P:
                    toneShiftClicked(Ports_Midi4, ToneShift_PlusTone);
                    break;
                case Map_MinusTone_4P:
                    toneShiftClicked(Ports_Midi4, ToneShift_MinusTone);
                    break;
                case Map_User1_4P:
                    notePresetClicked(Ports_Midi4, 0);
                    break;
                case Map_User2_4P:
                    notePresetClicked(Ports_Midi4, 1);
                    break;
                case Map_User3_4P:
                    notePresetClicked(Ports_Midi4, 2);
                    break;

                case Map_SendNote1:
                    if (Z0_ComboBox[Ports_Midi1][0])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][0]->currentIndex());
                    break;
                case Map_SendNote2:
                    if (Z0_ComboBox[Ports_Midi1][1])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][1]->currentIndex());
                    break;
                case Map_SendNote3:
                    if (Z0_ComboBox[Ports_Midi1][2])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][2]->currentIndex());
                    break;
                case Map_SendNote4:
                    if (Z0_ComboBox[Ports_Midi1][3])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][3]->currentIndex());
                    break;
                case Map_SendNote5:
                    if (Z0_ComboBox[Ports_Midi1][4])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][4]->currentIndex());
                    break;
                case Map_SendNote6:
                    if (Z0_ComboBox[Ports_Midi1][5])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][5]->currentIndex());
                    break;
                case Map_SendNote7:
                    if (Z0_ComboBox[Ports_Midi1][6])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][6]->currentIndex());
                    break;
                case Map_SendNote8:
                    if (Z0_ComboBox[Ports_Midi1][7])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][7]->currentIndex());
                    break;
                case Map_SendNote9:
                    if (Z0_ComboBox[Ports_Midi1][8])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][8]->currentIndex());
                    break;
                case Map_SendNote10:
                    if (Z0_ComboBox[Ports_Midi1][9])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][9]->currentIndex());
                    break;
                case Map_SendNote11:
                    if (Z0_ComboBox[Ports_Midi1][10])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][10]->currentIndex());
                    break;
                case Map_SendNote12:
                    if (Z0_ComboBox[Ports_Midi1][11])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][11]->currentIndex());
                    break;
                case Map_SendNote13:
                    if (Z0_ComboBox[Ports_Midi1][12])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][12]->currentIndex());
                    break;
                case Map_SendNote14:
                    if (Z0_ComboBox[Ports_Midi1][13])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][13]->currentIndex());
                    break;
                case Map_SendNote15:
                    if (Z0_ComboBox[Ports_Midi1][14])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][14]->currentIndex());
                    break;
                case Map_SendNote16:
                    if (Z0_ComboBox[Ports_Midi1][15])
                        kbDev.sendCom(MIDI_FORCESEND + Z0_ComboBox[Ports_Midi1][15]->currentIndex());
                    break;

                    // Port 1
                case Map_EnableNotesOnOff:
                    if (!(enabState[Ports_Midi1] & Mode_NoteOn))
                        on_enableNotesOnOffButton_clicked();
                    break;
                case Map_DisableNotesOnOff:
                    if (enabState[Ports_Midi1] & Mode_NoteOn)
                        on_enableNotesOnOffButton_clicked();
                    break;
                case Map_ToggleNotesOnOff:
                    on_enableNotesOnOffButton_clicked();
                    break;
                case Map_EnableEffect1:
                    if (!(((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn))
                        on_enableEffect1Button_clicked();
                    break;
                case Map_DisableEffect1:
                    if (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)
                        on_enableEffect1Button_clicked();
                    break;
                case Map_ToggleEffect1:
                    on_enableEffect1Button_clicked();
                    break;
                case Map_EnableEffect2:
                    if (!(((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn))
                        on_enableEffect2Button_clicked();
                    break;
                case Map_DisableEffect2:
                    if (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)
                        on_enableEffect2Button_clicked();
                    break;
                case Map_ToggleEffect2:
                    on_enableEffect2Button_clicked();
                    break;

                case Map_SendNote1_3P:
                    if (Z0_ComboBox[Ports_Midi3][0])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][0]->currentIndex());
                    break;
                case Map_SendNote2_3P:
                    if (Z0_ComboBox[Ports_Midi3][1])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][1]->currentIndex());
                    break;
                case Map_SendNote3_3P:
                    if (Z0_ComboBox[Ports_Midi3][2])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][2]->currentIndex());
                    break;
                case Map_SendNote4_3P:
                    if (Z0_ComboBox[Ports_Midi3][3])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][3]->currentIndex());
                    break;
                case Map_SendNote5_3P:
                    if (Z0_ComboBox[Ports_Midi3][4])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][4]->currentIndex());
                    break;
                case Map_SendNote6_3P:
                    if (Z0_ComboBox[Ports_Midi3][5])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][5]->currentIndex());
                    break;
                case Map_SendNote7_3P:
                    if (Z0_ComboBox[Ports_Midi3][6])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][6]->currentIndex());
                    break;
                case Map_SendNote8_3P:
                    if (Z0_ComboBox[Ports_Midi3][7])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][7]->currentIndex());
                    break;
                case Map_SendNote9_3P:
                    if (Z0_ComboBox[Ports_Midi3][8])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][8]->currentIndex());
                    break;
                case Map_SendNote10_3P:
                    if (Z0_ComboBox[Ports_Midi3][9])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][9]->currentIndex());
                    break;
                case Map_SendNote11_3P:
                    if (Z0_ComboBox[Ports_Midi3][10])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][10]->currentIndex());
                    break;
                case Map_SendNote12_3P:
                    if (Z0_ComboBox[Ports_Midi3][11])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][11]->currentIndex());
                    break;
                case Map_SendNote13_3P:
                    if (Z0_ComboBox[Ports_Midi3][12])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][12]->currentIndex());
                    break;
                case Map_SendNote14_3P:
                    if (Z0_ComboBox[Ports_Midi3][13])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][13]->currentIndex());
                    break;
                case Map_SendNote15_3P:
                    if (Z0_ComboBox[Ports_Midi3][14])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][14]->currentIndex());
                    break;
                case Map_SendNote16_3P:
                    if (Z0_ComboBox[Ports_Midi3][15])
                        kbDev.sendCom(MIDI_FORCESEND_3P + Z0_ComboBox[Ports_Midi3][15]->currentIndex());
                    break;

                    // Port 3
                case Map_EnableNotesOnOff_3P:
                    if (!(enabState[Ports_Midi3] & Mode_NoteOn))
                        on_enableNotesOnOffButton_2_clicked();
                    break;
                case Map_DisableNotesOnOff_3P:
                    if (enabState[Ports_Midi3] & Mode_NoteOn)
                        on_enableNotesOnOffButton_2_clicked();
                    break;
                case Map_ToggleNotesOnOff_3P:
                    on_enableNotesOnOffButton_2_clicked();
                    break;
                case Map_EnableEffect1_3P:
                    if (!(((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn))
                        on_enableEffect1Button_2_clicked();
                    break;
                case Map_DisableEffect1_3P:
                    if (((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn)
                        on_enableEffect1Button_2_clicked();
                    break;
                case Map_ToggleEffect1_3P:
                    on_enableEffect1Button_2_clicked();
                    break;
                case Map_EnableEffect2_3P:
                    if (!(((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn))
                        on_enableEffect2Button_2_clicked();
                    break;
                case Map_DisableEffect2_3P:
                    if (((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn)
                        on_enableEffect2Button_2_clicked();
                    break;
                case Map_ToggleEffect2_3P:
                    on_enableEffect2Button_2_clicked();
                    break;

                case Map_SendNote1_4P:
                    if (Z0_ComboBox[Ports_Midi4][0])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][0]->currentIndex());
                    break;
                case Map_SendNote2_4P:
                    if (Z0_ComboBox[Ports_Midi4][1])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][1]->currentIndex());
                    break;
                case Map_SendNote3_4P:
                    if (Z0_ComboBox[Ports_Midi4][2])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][2]->currentIndex());
                    break;
                case Map_SendNote4_4P:
                    if (Z0_ComboBox[Ports_Midi4][3])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][3]->currentIndex());
                    break;
                case Map_SendNote5_4P:
                    if (Z0_ComboBox[Ports_Midi4][4])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][4]->currentIndex());
                    break;
                case Map_SendNote6_4P:
                    if (Z0_ComboBox[Ports_Midi4][5])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][5]->currentIndex());
                    break;
                case Map_SendNote7_4P:
                    if (Z0_ComboBox[Ports_Midi4][6])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][6]->currentIndex());
                    break;
                case Map_SendNote8_4P:
                    if (Z0_ComboBox[Ports_Midi4][7])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][7]->currentIndex());
                    break;
                case Map_SendNote9_4P:
                    if (Z0_ComboBox[Ports_Midi4][8])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][8]->currentIndex());
                    break;
                case Map_SendNote10_4P:
                    if (Z0_ComboBox[Ports_Midi4][9])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][9]->currentIndex());
                    break;
                case Map_SendNote11_4P:
                    if (Z0_ComboBox[Ports_Midi4][10])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][10]->currentIndex());
                    break;
                case Map_SendNote12_4P:
                    if (Z0_ComboBox[Ports_Midi4][11])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][11]->currentIndex());
                    break;
                case Map_SendNote13_4P:
                    if (Z0_ComboBox[Ports_Midi4][12])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][12]->currentIndex());
                    break;
                case Map_SendNote14_4P:
                    if (Z0_ComboBox[Ports_Midi4][13])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][13]->currentIndex());
                    break;
                case Map_SendNote15_4P:
                    if (Z0_ComboBox[Ports_Midi4][14])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][14]->currentIndex());
                    break;
                case Map_SendNote16_4P:
                    if (Z0_ComboBox[Ports_Midi4][15])
                        kbDev.sendCom(MIDI_FORCESEND_4P + Z0_ComboBox[Ports_Midi4][15]->currentIndex());
                    break;

                    // Port 4
                case Map_EnableNotesOnOff_4P:
                    if (!(enabState[Ports_Midi4] & Mode_NoteOn))
                        on_enableNotesOnOffButton_3_clicked();
                    break;
                case Map_DisableNotesOnOff_4P:
                    if (enabState[Ports_Midi4] & Mode_NoteOn)
                        on_enableNotesOnOffButton_3_clicked();
                    break;
                case Map_ToggleNotesOnOff_4P:
                    on_enableNotesOnOffButton_3_clicked();
                    break;
                case Map_EnableEffect1_4P:
                    if (!(((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn))
                        on_enableEffect1Button_3_clicked();
                    break;
                case Map_DisableEffect1_4P:
                    if (((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn)
                        on_enableEffect1Button_3_clicked();
                    break;
                case Map_ToggleEffect1_4P:
                    on_enableEffect1Button_3_clicked();
                    break;
                case Map_EnableEffect2_4P:
                    if (!(((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn))
                        on_enableEffect2Button_3_clicked();
                    break;
                case Map_DisableEffect2_4P:
                    if (((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn)
                        on_enableEffect2Button_3_clicked();
                    break;
                case Map_ToggleEffect2_4P:
                    on_enableEffect2Button_3_clicked();
                    break;

                case Map_HWAmp:
                    if (paramToSend > ui->hardAmpComboBox->count() - 1)
                        ui->hardAmpComboBox->setCurrentIndex(ui->hardAmpComboBox->count() - 1);
                    else
                        ui->hardAmpComboBox->setCurrentIndex(paramToSend);
                    break;
                case Map_NBeamsX:
                    if (paramToSend > ui->nBeamsXComboBox->count() - 1)
                        ui->nBeamsXComboBox->setCurrentIndex(ui->nBeamsXComboBox->count() - 1);
                    else
                        ui->nBeamsXComboBox->setCurrentIndex(paramToSend);
                    break;
                case Map_FPS:
                    if (paramToSend <= ui->FPSSlider->maximum() - ui->FPSSlider->minimum())
                        ui->FPSSlider->setValue(ui->FPSSlider->minimum() + paramToSend);
                    else
                        ui->FPSSlider->setValue(ui->FPSSlider->maximum());
                    break;
                case Map_DetThreshold:
                    if (paramToSend <= ui->detLevelSlider->maximum() - ui->detLevelSlider->minimum())
                        ui->detLevelSlider->setValue(ui->detLevelSlider->minimum() + paramToSend);
                    else
                        ui->detLevelSlider->setValue(ui->detLevelSlider->maximum());
                    break;
                case Map_DetSpeed:
                    if (paramToSend <= ui->minTimeSlider->maximum() - ui->minTimeSlider->minimum())
                        ui->minTimeSlider->setValue(ui->minTimeSlider->minimum() + paramToSend);
                    else
                        ui->minTimeSlider->setValue(ui->minTimeSlider->maximum());
                    break;
                case Map_SpeedSelectivity:
                    if (paramToSend <= ui->maxTimeSlider->maximum() - ui->maxTimeSlider->minimum())
                        ui->maxTimeSlider->setValue(ui->maxTimeSlider->minimum() + paramToSend);
                    else
                        ui->maxTimeSlider->setValue(ui->maxTimeSlider->maximum());
                    break;
                case Map_AngleDeviation:
                    if (paramToSend <= ui->accuracySpinBox->maximum() - ui->accuracySpinBox->minimum())
                        ui->accuracySpinBox->setValue(ui->accuracySpinBox->minimum() + paramToSend);
                    else
                        ui->accuracySpinBox->setValue(ui->accuracySpinBox->maximum());
                    on_accuracySpinBox_editingFinished();
                    break;
                case Map_Release:
                    if (paramToSend <= ui->releaseSlider->maximum() - ui->releaseSlider->minimum())
                        ui->releaseSlider->setValue(ui->releaseSlider->minimum() + paramToSend);
                    else
                        ui->releaseSlider->setValue(ui->releaseSlider->maximum());
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
                    if (paramToSend <= ui->smoothZSlider->maximum() - ui->smoothZSlider->minimum())
                        ui->smoothZSlider->setValue(ui->smoothZSlider->minimum() + paramToSend);
                    else
                        ui->smoothZSlider->setValue(ui->smoothZSlider->maximum());
                    break;
                case Map_ZAttackFilter:
                    if (paramToSend <= ui->filterZSlider->maximum() - ui->filterZSlider->minimum())
                        ui->filterZSlider->setValue(ui->filterZSlider->minimum() + paramToSend);
                    else
                        ui->filterZSlider->setValue(ui->filterZSlider->maximum());
                    break;
                case Map_ZAmplitude:
                    if (paramToSend <= ui->ampZSlider->maximum() - ui->ampZSlider->minimum())
                        ui->ampZSlider->setValue(ui->ampZSlider->minimum() + paramToSend);
                    else
                        ui->ampZSlider->setValue(ui->ampZSlider->maximum());
                    break;
                case Map_ZStabilization:
                    if (paramToSend <= ui->stabZSlider->maximum() - ui->stabZSlider->minimum())
                        ui->stabZSlider->setValue(ui->stabZSlider->minimum() + paramToSend);
                    else
                        ui->stabZSlider->setValue(ui->stabZSlider->maximum());
                    break;
                case Map_ZMin:
                    if (paramToSend <= ui->minHeightSpinBox->maximum() - ui->minHeightSpinBox->minimum())
                        ui->minHeightSpinBox->setValue(ui->minHeightSpinBox->minimum() + paramToSend);
                    else
                        ui->minHeightSpinBox->setValue(ui->minHeightSpinBox->maximum());
                    on_minHeightSpinBox_editingFinished();
                    break;
                case Map_ZMax:
                    if (paramToSend <= ui->maxHeightSpinBox->maximum() - ui->maxHeightSpinBox->minimum())
                        ui->maxHeightSpinBox->setValue(ui->maxHeightSpinBox->minimum() + paramToSend);
                    else
                        ui->maxHeightSpinBox->setValue(ui->maxHeightSpinBox->maximum());
                    on_maxHeightSpinBox_editingFinished();
                    break;
                case Map_ZCenter:
                    if (paramToSend <= ui->centerHeightSpinBox->maximum() - ui->centerHeightSpinBox->minimum())
                        ui->centerHeightSpinBox->setValue(ui->centerHeightSpinBox->minimum() + paramToSend);
                    else
                        ui->centerHeightSpinBox->setValue(ui->centerHeightSpinBox->maximum());
                    on_centerHeightSpinBox_editingFinished();
                    break;
                case Map_ZSub:
                    if (paramToSend <= ui->subHeightSpinBox->maximum() - ui->subHeightSpinBox->minimum())
                        ui->subHeightSpinBox->setValue(ui->subHeightSpinBox->minimum() + paramToSend);
                    else
                        ui->subHeightSpinBox->setValue(ui->subHeightSpinBox->maximum());
                    on_subHeightSpinBox_editingFinished();
                    break;

                case Map_MinPosX:
                    if (paramToSend <= ui->minPosXSpinBox->maximum() - ui->minPosXSpinBox->minimum())
                        ui->minPosXSpinBox->setValue(ui->minPosXSpinBox->minimum() + paramToSend);
                    else
                        ui->minPosXSpinBox->setValue(ui->minPosXSpinBox->maximum());
                    on_minPosXSpinBox_editingFinished();
                    break;
                case Map_MaxPosX:
                    if (paramToSend <= ui->maxPosXSpinBox->maximum() - ui->maxPosXSpinBox->minimum())
                        ui->maxPosXSpinBox->setValue(ui->maxPosXSpinBox->minimum() + paramToSend);
                    else
                        ui->maxPosXSpinBox->setValue(ui->maxPosXSpinBox->maximum());
                    on_maxPosXSpinBox_editingFinished();
                    break;
                case Map_SubPosX:
                    if (paramToSend <= ui->subPosXSpinBox->maximum() - ui->subPosXSpinBox->minimum())
                        ui->subPosXSpinBox->setValue(ui->subPosXSpinBox->minimum() + paramToSend);
                    else
                        ui->subPosXSpinBox->setValue(ui->subPosXSpinBox->maximum());
                    on_subPosXSpinBox_editingFinished();
                    break;
                case Map_MinWidthX:
                    if (paramToSend <= ui->minWidthXSpinBox->maximum() - ui->minWidthXSpinBox->minimum())
                        ui->minWidthXSpinBox->setValue(ui->minWidthXSpinBox->minimum() + paramToSend);
                    else
                        ui->minWidthXSpinBox->setValue(ui->minWidthXSpinBox->maximum());
                    on_minWidthXSpinBox_editingFinished();
                    break;
                case Map_MaxWidthX:
                    if (paramToSend <= ui->maxWidthXSpinBox->maximum() - ui->maxWidthXSpinBox->minimum())
                        ui->maxWidthXSpinBox->setValue(ui->maxWidthXSpinBox->minimum() + paramToSend);
                    else
                        ui->maxWidthXSpinBox->setValue(ui->maxWidthXSpinBox->maximum());
                    on_maxWidthXSpinBox_editingFinished();
                    break;
                case Map_SubWidthX:
                    if (paramToSend <= ui->subWidthXSpinBox->maximum() - ui->subWidthXSpinBox->minimum())
                        ui->subWidthXSpinBox->setValue(ui->subWidthXSpinBox->minimum() + paramToSend);
                    else
                        ui->subWidthXSpinBox->setValue(ui->subWidthXSpinBox->maximum());
                    on_subWidthXSpinBox_editingFinished();
                    break;
                case Map_MinGlideX:
                    if (paramToSend <= ui->minGlideXSpinBox->maximum() - ui->minGlideXSpinBox->minimum())
                        ui->minGlideXSpinBox->setValue(ui->minGlideXSpinBox->minimum() + paramToSend);
                    else
                        ui->minGlideXSpinBox->setValue(ui->minGlideXSpinBox->maximum());
                    on_minGlideXSpinBox_editingFinished();
                    break;
                case Map_MaxGlideX:
                    if (paramToSend <= ui->maxGlideXSpinBox->maximum() - ui->maxGlideXSpinBox->minimum())
                        ui->maxGlideXSpinBox->setValue(ui->maxGlideXSpinBox->minimum() + paramToSend);
                    else
                        ui->maxGlideXSpinBox->setValue(ui->maxGlideXSpinBox->maximum());
                    on_maxGlideXSpinBox_editingFinished();
                    break;
                case Map_SubGlideX:
                    if (paramToSend <= ui->subGlideXSpinBox->maximum() - ui->subGlideXSpinBox->minimum())
                        ui->subGlideXSpinBox->setValue(ui->subGlideXSpinBox->minimum() + paramToSend);
                    else
                        ui->subGlideXSpinBox->setValue(ui->subGlideXSpinBox->maximum());
                    on_subGlideXSpinBox_editingFinished();
                    break;
                case Map_StabGlideX:
                    if (paramToSend <= ui->stabGlideSlider->maximum() - ui->stabGlideSlider->minimum())
                        ui->stabGlideSlider->setValue(ui->stabGlideSlider->minimum() + paramToSend);
                    else
                        ui->stabGlideSlider->setValue(ui->stabGlideSlider->maximum());
                    break;
                case Map_InvertedPosX:
                    ui->invertPosXCheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_NotInvertedPosX:
                    ui->invertPosXCheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_InvertedWidthX:
                    ui->invertWidthXCheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_NotInvertedWidthX:
                    ui->invertWidthXCheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_InvertedGlideX:
                    ui->invertGlideXCheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_NotInvertedGlideX:
                    ui->invertGlideXCheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub11:
                    ui->activSubEffect11CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub11:
                    ui->activSubEffect11CheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub12:
                    ui->activSubEffect12CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub12:
                    ui->activSubEffect12CheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub31:
                    ui->activSubEffect31CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub31:
                    ui->activSubEffect31CheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub32:
                    ui->activSubEffect32CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub32:
                    ui->activSubEffect32CheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub41:
                    ui->activSubEffect41CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub41:
                    ui->activSubEffect41CheckBox->setCheckState(Qt::Unchecked);
                    break;
                case Map_EnableSub42:
                    ui->activSubEffect42CheckBox->setCheckState(Qt::Checked);
                    break;
                case Map_DisableSub42:
                    ui->activSubEffect42CheckBox->setCheckState(Qt::Unchecked);
                    break;
                default:

                    if ((iExt >= Map_MainPreset1) && (iExt < (Map_MainPreset1 + NUM_CONFIGS)))
                        ui->mainConfigComboBox->setCurrentIndex(iExt - Map_MainPreset1 + 1);

                    else if ((iExt >= Map_NotesPreset1) && (iExt < (Map_NotesPreset1 + NUM_CONFIGS)))
                        notesPresetCombos[Ports_Midi1]->setCurrentIndex(iExt - Map_NotesPreset1 + 1);

                    else if ((iExt >= Map_NotesPreset1_3P) && (iExt < (Map_NotesPreset1_3P + NUM_CONFIGS)))
                        notesPresetCombos[Ports_Midi3]->setCurrentIndex(iExt - Map_NotesPreset1_3P + 1);

                    else if ((iExt >= Map_NotesPreset1_4P) && (iExt < (Map_NotesPreset1_4P + NUM_CONFIGS)))
                        notesPresetCombos[Ports_Midi4]->setCurrentIndex(iExt - Map_NotesPreset1_4P + 1);
                    break;
                    QApplication::processEvents();
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
        if (mapIsController[saveIndex])
            mapSpinBox[saveIndex][2]->setValue(-1);
        else
            mapSpinBox[saveIndex][2]->setValue(par3);
        updateMidiMappingValues(saveIndex);   // Update Color Display

        learnExtMIDI(extMidiIndexToLearn);      //
        //WriteTempMapping(saveIndex);     // Update temp file (based on mappingCommand)
        this->update();
    }
}

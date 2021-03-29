#ifndef ERRORENUM_H
#define ERRORENUM_H

#include <QDebug>
#include <QDateTime>

/*
 * ======================================================================
 * This is the list of all error codes that can be displayed by functions
 * The format of code number is:
 * FFXX for warning
 * 1FFXX for critical
 * FF is an index relative to the file where there is the error
 * XX is an index of the error in the file
 * Each warning or critical pop-up should have a unique error ID
 * ======================================================================
 */
enum ErrorList : int
{
    GrPorts_MidiOutCB = 100,
    GrPorts_MidiInCB,
    GrPorts_MidiExtCB,
    GrPorts_MidiExtOutCB,

    MenuFunc_LoadFW = 200,

    GrDet_AutoSet_1 = 300,
    GrDet_AutoSet_2,

    MainWindow_UpdateAll_FWUP = 400,

    ComHw_SendCom_1 = 500,
    ComHw_SendCom_2,
    ComHw_SendAndCheck_1,
    ComHw_SendAndCheck_2,
    ComHw_CheckFeedback_1,
    ComHw_CheckFeedback_2,
    ComHw_CheckDfuFeedback_1,

    GrExtMapping_LearnExt = 600,

    GrPresets_LoadPresetMidi = 700,
    GrPresets_LoadPresetMain,

    VersionDialog_VersionDialog = 800,

    GrDet_AutoSet_1_C = 10100,
    GrDet_AutoSet_2_C,
    GrDet_AutoSet_3_C,
    GrDet_AutoSet_4_C,
    GrDet_AutoSet_5_C,
    GrDet_AutoSet_6_C,
    GrDet_AutoSet_7_C,
    GrDet_AutoSet_8_C,
    GrDet_AutoSet_9_C,
    GrDet_AutoSet_10_C,
    GrDet_AutoSet_11_C,
    GrDet_AutoSet_12_C,
    GrDet_AutoSet_13_C,
    GrDet_AutoSet_14_C,
    GrDet_AutoSet_15_C,
    GrDet_AutoSet_16_C,
    GrDet_AutoSet_17_C,
    GrDet_AutoSet_18_C,
    GrDet_AutoSet_19_C,
    GrDet_AutoSet_20_C,
    GrDet_NBeamsX_C,
    GrDet_NBeamsX_2_C,
    GrDet_HardAmp_C,
    GrDet_DetLevelSlider_C,
    GrDet_DetSpeedSlider_C,
    GrDet_DetSelectivitySlider_C,
    GrDet_FPSSlider_C,
    GrDet_AccuracySlider_C,

    Functions_LoadMapping_C = 10200,

    GrAngles_SpinBox1_C = 10300,
    GrAngles_SpinBox2_C,
    GrAngles_SpinBox3_C,
    GrAngles_SpinBox4_C,
    GrAngles_SpinBox5_C,
    GrAngles_SpinBox6_C,
    GrAngles_SpinBox7_C,
    GrAngles_SpinBox8_C,
    GrAngles_SpinBox9_C,
    GrAngles_SpinBox10_C,
    GrAngles_SpinBox11_C,
    GrAngles_SpinBox12_C,
    GrAngles_SpinBox13_C,
    GrAngles_SpinBox14_C,
    GrAngles_SpinBox15_C,
    GrAngles_SpinBox16_C,
    GrAngles_SpinBoxMin_C,
    GrAngles_SpinBoxMax_C,

    GrHeight_SmoothZSlider_C = 10400,
    GrHeight_FilterZSlider_C,
    GrHeight_AmpZSlider_C,
    GrHeight_StabZSlider_C,
    GrHeight_ModulationZ_1_C,
    GrHeight_ModulationZ_2_C,
    GrHeight_InvertZ_1_C,
    GrHeight_InvertZ_2_C,

    GrNotes_DescNote_C = 10500,
    GrNotes_DescCC1_C,
    GrNotes_DescCC2_C,
    GrNotes_ChanNote_C,
    GrNotes_ChanCC1_C,
    GrNotes_ChanCC2_C,
    GrNotes_NoteNote_1_C,
    GrNotes_NoteNote_2_C,
    GrNotes_ControlCC1_1_C,
    GrNotes_ControlCC1_2_C,
    GrNotes_ControlCC2_1_C,
    GrNotes_ControlCC2_2_C,
    GrNotes_VelNote_1_C,
    GrNotes_VelNote_2_C,
    GrNotes_ValCC1_1_C,
    GrNotes_ValCC1_2_C,
    GrNotes_ValCC2_1_C,
    GrNotes_ValCC2_2_C,
    GrNotes_X0Z0_C,
    GrNotes_X1Z0_C,
    GrNotes_X2Z0_C,
    GrNotes_X3Z0_C,
    GrNotes_X4Z0_C,
    GrNotes_X5Z0_C,
    GrNotes_X6Z0_C,
    GrNotes_X7Z0_C,
    GrNotes_X8Z0_C,
    GrNotes_X9Z0_C,
    GrNotes_X10Z0_C,
    GrNotes_X11Z0_C,
    GrNotes_X12Z0_C,
    GrNotes_X13Z0_C,
    GrNotes_X14Z0_C,
    GrNotes_X15Z0_C,

    GrPresets_LoadPresetMain_1_C = 10600,
    GrPresets_LoadPresetMain_2_C,
    GrPresets_LoadCustPreset_1_C,
    GrPresets_LoadCustPreset_2_C,
    GrPresets_LoadPresetMidi_1_C,
    GrPresets_LoadPresetMidi_2_C,
    GrPresets_LoadCustPresetMidi_1_C,
    GrPresets_LoadCustPresetMidi_2_C,

    MainWindow_FlashProg_1_C = 10700,
    MainWindow_FlashProg_2_C,
    MainWindow_UpdateAll_1_C,
};

#endif // ERRORENUM_H

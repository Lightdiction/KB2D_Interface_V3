#ifndef ERRORENUM_H
#define ERRORENUM_H


#define _ENUM_(name, base) enum name : base

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
_ENUM_(ErrorList, int)
{
    GrPorts_MidiOutCB = 100,
    GrPorts_MidiInCB,
    GrPorts_MidiExtCB,
    GrPorts_MidiExtOutCB,
    GrPorts_ConnectThroughIn,
    GrPorts_ConnectThroughOut,

    MenuFunc_LoadFW = 200,

    GrDet_AutoSet_1 = 300,
    GrDet_AutoSet_2,
    GrDet_AutoSet_2a,
    GrDet_AutoSet_3,
    GrDet_AutoSet_4,
    GrDet_AutoSet_5,
    GrDet_AutoSet_6,
    GrDet_DetLevelSlider,
    GrDet_DetLevelSlider_2,
    GrDet_DetSpeedSlider,
    GrDet_DetSelectivitySlider,
    GrDet_FPSSlider,
    GrDet_ReleaseSlider,

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

    FUpdater_Exit = 900,

    GrNotes_UpdateMidiNoteValues = 1000,
    GrNotes_UpdateMidiNoteValues_1,
    GrNotes_UpdateMidiNoteValues_2,
    GrNotes_UpdateMidiNoteValues_3,
    GrNotes_ComboNoteSel,
    GrNotes_DescNote,
    GrNotes_DescCC1,
    GrNotes_DescCC2,
    GrNotes_ToneShift,
    GrNotes_LoadNotesPreset,
    GrNotes_LoadNotesPreset_2,
    GrNotes_LoadNotesUser,
    GrNotes_LoadNotesUser_2,

    GrAngles_SpinBoxMulti = 1100,
    GrAngles_AngFilter_1,
    GrAngles_AngFilter_2,
    GrAngles_AccuracySlider,
    GrAngles_NBeamsX,

    GrVarsX_InvertPosX = 1200,
    GrVarsX_InvertWidthX,
    GrVarsX_InvertGlideX,
    GrVarsX_GlideStabSlider,
    GrVarsX_MinPosXSpinBox,
    GrVarsX_MaxPosXSpinBox,
    GrVarsX_MinWidthXSpinBox,
    GrVarsX_MaxWidthXSpinBox,
    GrVarsX_MinGlideXSpinBox,
    GrVarsX_MaxGlideXSpinBox,

    GrHeight_MinZSpinBox = 1300,
    GrHeight_MaxZSpinBox,
    GrHeight_SmoothZSlider,
    GrHeight_FilterZSlider,
    GrHeight_AmpZSlider,
    GrHeight_StabZSlider,
    GrHeight_ModulationZ_1,
    GrHeight_ModulationZ_2,
    GrHeight_InvertZ_1,
    GrHeight_InvertZ_2,

    GrMidiDevices_KbIn = 1400,
    GrMidiDevices_KbOut,
    GrMidiDevices_ExtIn,
    GrMidiDevices_ExtOut,
    GrMidiDevices_ThroughIn,
    GrMidiDevices_ThroughOut,

    GrDet_AutoSet_1_C = 10100,
    GrDet_AutoSet_1b_C,
    GrDet_AutoSet_1c_C,
    GrDet_AutoSet_2_C,
    GrDet_AutoSet_3_C,
    GrDet_AutoSet_4_C,
    GrDet_AutoSet_5_C,
    GrDet_AutoSet_5b_C,
    GrDet_AutoSet_5c_C,
    GrDet_AutoSet_6_C,
    GrDet_AutoSet_6b_C,
    GrDet_AutoSet_6c_C,
    GrDet_AutoSet_7_C,
    GrDet_AutoSet_7b_C,
    GrDet_AutoSet_7c_C,
    GrDet_AutoSet_8_C,
    GrDet_AutoSet_8b_C,
    GrDet_AutoSet_8c_C,
    GrDet_AutoSet_9_C,
    GrDet_AutoSet_10_C,
    GrDet_AutoSet_10b_C,
    GrDet_AutoSet_10c_C,
    GrDet_AutoSet_11_C,
    GrDet_AutoSet_12_C,
    GrDet_AutoSet_13_C,
    GrDet_AutoSet_13b_C,
    GrDet_AutoSet_13c_C,
    GrDet_AutoSet_14_C,
    GrDet_AutoSet_15_C,
    GrDet_AutoSet_16_C,
    GrDet_AutoSet_17_C,
    GrDet_AutoSet_18_C,
    GrDet_AutoSet_18b_C,
    GrDet_AutoSet_18c_C,
    GrDet_AutoSet_19_C,
    GrDet_AutoSet_20_C,
    GrDet_HardAmp_C,

    Functions_LoadMapping_C = 10200,

    GrNotes_Assign_1_C = 10500,
    GrNotes_Assign_2_C,
    GrNotes_Assign_3_C,
    GrNotes_Assign_4_C,
    GrNotes_Assign_5_C,
    GrNotes_Assign_6_C,
    GrNotes_Assign_7_C,
    GrNotes_Assign_8_C,
    GrNotes_Assign_9_C,
    GrNotes_Assign_10_C,
    GrNotes_Assign_11_C,
    GrNotes_Assign_12_C,
    GrNotes_Assign_13_C,
    GrNotes_Assign_14_C,
    GrNotes_Assign_15_C,
    GrNotes_Assign_16_C,

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

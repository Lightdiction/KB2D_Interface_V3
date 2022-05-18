#ifndef GREXTMAPPING_H
#define GREXTMAPPING_H


#include "utils.h"
#include <QSpinBox>

_ENUM_(MappingList, int)
{
    Map_Start,
    Map_Pause,
    Map_Restart,
    Map_Default,
    Map_SaveFlash,
    Map_InvertX,
    Map_DetectionAssistant,
    Map_AutoCalibration,
            Map_LearnOne,
            Map_LearnAll,

            // Port 1
            Map_PlusHalfTone,
            Map_MinusHalfTone,
            Map_PlusTone,
            Map_MinusTone,
            Map_User1,
            Map_User2,
            Map_User3,

            // Port 3
            Map_PlusHalfTone_3P,
            Map_MinusHalfTone_3P,
            Map_PlusTone_3P,
            Map_MinusTone_3P,
            Map_User1_3P,
            Map_User2_3P,
            Map_User3_3P,

            // Port 4
            Map_PlusHalfTone_4P,
            Map_MinusHalfTone_4P,
            Map_PlusTone_4P,
            Map_MinusTone_4P,
            Map_User1_4P,
            Map_User2_4P,
            Map_User3_4P,

    // Port 1
    // 16 Beams
    Map_SendNote1,
    Map_SendNote2,
    Map_SendNote3,
    Map_SendNote4,
    Map_SendNote5,
    Map_SendNote6,
    Map_SendNote7,
    Map_SendNote8,
    Map_SendNote9,
    Map_SendNote10,
    Map_SendNote11,
    Map_SendNote12,
    Map_SendNote13,
    Map_SendNote14,
    Map_SendNote15,
    Map_SendNote16,

    Map_EnableNotesOnOff,
    Map_DisableNotesOnOff,
    Map_ToggleNotesOnOff,
    Map_EnableEffect1,
    Map_DisableEffect1,
    Map_ToggleEffect1,
    Map_EnableEffect2,
    Map_DisableEffect2,
    Map_ToggleEffect2,

    // Port 3
    // 16 Beams
    Map_SendNote1_3P,
    Map_SendNote2_3P,
    Map_SendNote3_3P,
    Map_SendNote4_3P,
    Map_SendNote5_3P,
    Map_SendNote6_3P,
    Map_SendNote7_3P,
    Map_SendNote8_3P,
    Map_SendNote9_3P,
    Map_SendNote10_3P,
    Map_SendNote11_3P,
    Map_SendNote12_3P,
    Map_SendNote13_3P,
    Map_SendNote14_3P,
    Map_SendNote15_3P,
    Map_SendNote16_3P,

    Map_EnableNotesOnOff_3P,
    Map_DisableNotesOnOff_3P,
    Map_ToggleNotesOnOff_3P,
    Map_EnableEffect1_3P,
    Map_DisableEffect1_3P,
    Map_ToggleEffect1_3P,
    Map_EnableEffect2_3P,
    Map_DisableEffect2_3P,
    Map_ToggleEffect2_3P,

    // Port 4
    // 16 Beams
    Map_SendNote1_4P,
    Map_SendNote2_4P,
    Map_SendNote3_4P,
    Map_SendNote4_4P,
    Map_SendNote5_4P,
    Map_SendNote6_4P,
    Map_SendNote7_4P,
    Map_SendNote8_4P,
    Map_SendNote9_4P,
    Map_SendNote10_4P,
    Map_SendNote11_4P,
    Map_SendNote12_4P,
    Map_SendNote13_4P,
    Map_SendNote14_4P,
    Map_SendNote15_4P,
    Map_SendNote16_4P,

    Map_EnableNotesOnOff_4P,
    Map_DisableNotesOnOff_4P,
    Map_ToggleNotesOnOff_4P,
    Map_EnableEffect1_4P,
    Map_DisableEffect1_4P,
    Map_ToggleEffect1_4P,
    Map_EnableEffect2_4P,
    Map_DisableEffect2_4P,
    Map_ToggleEffect2_4P,

    Map_HWAmp,
    Map_NBeamsX,
    Map_FPS,
    Map_DetThreshold,
    Map_DetSpeed,
    Map_SpeedSelectivity,
    Map_AngleDeviation,
    Map_Release,

    Map_ZModeRelative,
    Map_ZModeAbsolute,
    Map_ZInvertedMod,
    Map_ZRegularMod,
    Map_ZSmooth,
    Map_ZAttackFilter,
    Map_ZAmplitude,
    Map_ZStabilization,
            Map_ZMin,
            Map_ZCenter,
            Map_ZMax,
            Map_ZSub,

            Map_MinPosX,
            Map_MaxPosX,
            Map_SubPosX,
            Map_InvertedPosX,
            Map_NotInvertedPosX,
            Map_MinWidthX,
            Map_MaxWidthX,
            Map_SubWidthX,
            Map_InvertedWidthX,
            Map_NotInvertedWidthX,
            Map_MinGlideX,
            Map_MaxGlideX,
            Map_SubGlideX,
            Map_InvertedGlideX,
            Map_NotInvertedGlideX,
            Map_StabGlideX,
            Map_EnableSub11,
            Map_DisableSub11,
            Map_EnableSub12,
            Map_DisableSub12,
            Map_EnableSub31,
            Map_DisableSub31,
            Map_EnableSub32,
            Map_DisableSub32,
            Map_EnableSub41,
            Map_DisableSub41,
            Map_EnableSub42,
            Map_DisableSub42,

    /// 128 Configs
    Map_MainPreset1,

            /// 128 Notes Presets
            Map_NotesPreset1 = Map_MainPreset1 + NUM_CONFIGS,

            /// 128 Notes Presets
            Map_NotesPreset1_3P = Map_NotesPreset1 + NUM_CONFIGS,

            /// 128 Notes Presets
            Map_NotesPreset1_4P = Map_NotesPreset1_3P + NUM_CONFIGS,

    Map_NumParam = Map_NotesPreset1_4P + NUM_CONFIGS
};

_ENUM_(EnumLayouts, int)
{
    Layout_Main,
    Layout_Midi,
    Layout_NotesCtrl,
    Layout_NotesPresets,
    Layout_DetX,
    Layout_MainPresets,

    Layout_NumTotal
};

extern int extMidiIndexToLearn;


/*
 * ===================
 * Class MapSpinBox
 * ===================
 */
class MapSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    MapSpinBox(int min, int max, int mapInd, bool isController = false, QWidget *parent = nullptr);
    ~MapSpinBox();

protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // GREXTMAPPING_H

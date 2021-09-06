#ifndef GRNOTES_H
#define GRNOTES_H

#include <QWidget>
#include <QPushButton>
#include "utils.h"

#define KEYS_WIDTH          40
#define KEYS_BLACK_WIDTH    26


/*
 * =====================
 * For Control ComboBox
 * (Enab Var)
 * =====================
 */
enum ModeActivated
{
    Mode_NoteOff,
    Mode_NoteOn,
    Mode_PolyAftertouch,
    Mode_ControlChange,
    Mode_ProgramChange,
    Mode_ChanAftertouch,
    Mode_PitchBend
};

enum VarInvertList
{
    VarInvert_PosX = 0x1,
    VarInvert_WidthX = 0x2,
    VarInvert_GlideX = 0x4,
};

/*
 * =====================
 * For CheckVarUse
 * =====================
 */
enum VarUseList
{
    VarUse_NoteNote = 0b1,
    VarUse_NoteVel 	= 0b10,
    VarUse_CC1Ctrl 	= 0b100,
    VarUse_CC1Val 	= 0b1000,
    VarUse_CC2Ctrl 	= 0b10000,
    VarUse_CC2Val 	= 0b100000
};

enum ChannelList
{
    Channel_IndX,
    Channel_IndY,

    Channel_1,
    Channel_16 = Channel_1 + 15,

    Channel_Num
};

enum MidiValuesList
{
    Val_Keyboard,
    Val_Combos,
    Val_PosX,
    Val_HeightZ,
    Val_WidthX,
    Val_GlideX,

    Val_NumVars,

    Val_0 = 128,

    Val_127 = Val_0 + 127
};

enum ListPortsEnum
{
    Ports_Midi1,
    Ports_Midi3,
    Ports_Midi4,

    Ports_Num
};

enum ListModeActiv
{
    ModeActiv_Notes,
    ModeActiv_Control1,
    ModeActiv_Control2,

    ModeActiv_NumModes
};

enum MidiValSelection
{
    ValSelection_Channel,
    ValSelection_CtrlNotes,
    ValSelection_ValVel,

    ValSelection_NumCombo
};

_ENUM_(ListMIDINotes, int)
{
    Note_Cm1,
    Note_Cm1d,
    Note_Dm1,
    Note_Dm1d,
    Note_Em1,
    Note_Fm1,
    Note_Fm1d,
    Note_Gm1,
    Note_Gm1d,
    Note_Am1,
    Note_Am1d,
    Note_Bm1,

    Note_C0,
    Note_C0d,
    Note_D0,
    Note_D0d,
    Note_E0,
    Note_F0,
    Note_F0d,
    Note_G0,
    Note_G0d,
    Note_A0,
    Note_A0d,
    Note_B0,

    Note_C1,
    Note_C1d,
    Note_D1,
    Note_D1d,
    Note_E1,
    Note_F1,
    Note_F1d,
    Note_G1,
    Note_G1d,
    Note_A1,
    Note_A1d,
    Note_B1,

    Note_C2,
    Note_C2d,
    Note_D2,
    Note_D2d,
    Note_E2,
    Note_F2,
    Note_F2d,
    Note_G2,
    Note_G2d,
    Note_A2,
    Note_A2d,
    Note_B2,

    Note_C3,
    Note_C3d,
    Note_D3,
    Note_D3d,
    Note_E3,
    Note_F3,
    Note_F3d,
    Note_G3,
    Note_G3d,
    Note_A3,
    Note_A3d,
    Note_B3,

    Note_C4,
    Note_C4d,
    Note_D4,
    Note_D4d,
    Note_E4,
    Note_F4,
    Note_F4d,
    Note_G4,
    Note_G4d,
    Note_A4,
    Note_A4d,
    Note_B4,

    Note_C5,
    Note_C5d,
    Note_D5,
    Note_D5d,
    Note_E5,
    Note_F5,
    Note_F5d,
    Note_G5,
    Note_G5d,
    Note_A5,
    Note_A5d,
    Note_B5,

    Note_C6,
    Note_C6d,
    Note_D6,
    Note_D6d,
    Note_E6,
    Note_F6,
    Note_F6d,
    Note_G6,
    Note_G6d,
    Note_A6,
    Note_A6d,
    Note_B6,

    Note_C7,
    Note_C7d,
    Note_D7,
    Note_D7d,
    Note_E7,
    Note_F7,
    Note_F7d,
    Note_G7,
    Note_G7d,
    Note_A7,
    Note_A7d,
    Note_B7,

    Note_C8,
    Note_C8d,
    Note_D8,
    Note_D8d,
    Note_E8,
    Note_F8,
    Note_F8d,
    Note_G8,
    Note_G8d,
    Note_A8,
    Note_A8d,
    Note_B8,

    Note_C9,
    Note_C9d,
    Note_D9,
    Note_D9d,
    Note_E9,
    Note_F9,
    Note_F9d,
    Note_G9,

    Note_Number     // Supposed to be 128
};

_ENUM_(ListToneShift, int)
{
    ToneShift_PlusHalfTone,
    ToneShift_MinusHalfTone,
    ToneShift_PlusTone,
    ToneShift_MinusTone,

    ToneShift_NumTotal
};

_ENUM_(ListNotePresets, int)
{
    NotePreset_User1,
    NotePreset_User2,
    NotePreset_User3,

    NotePreset_NumTotal
};

extern QString ListNameNotes[Note_Number];

#endif // GRNOTES_H

#ifndef COMENUM_H
#define COMENUM_H

/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Com Enum.h **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Here you can find all commands sent to KB2D / DFU
 * Also, you can find the list of messages read by
 * readvar function
 *
 * =================================================
 */

#include "utils.h"


///////////////////////////////////
// MIDI Commands to send to KB2D //


#define MIDI_2PORTS 		0xC0, 0x72, 0x00
#define MIDI_3PORTS 		0xC0, 0x73, 0x00
#define MIDI_4PORTS 		0xC0, 0x74, 0x00

#define MIDI_SN 			0x90, 0x10, 0x00
#define MIDI_SUBSN 			0x90, 0x11, 0x00

#define MIDI_FORCESEND 		0xB7, 0x70, 0x00
#define MIDI_FORCESEND_3P 	0xB7, 0x71, 0x00
#define MIDI_FORCESEND_4P 	0xB7, 0x72, 0x00

#define MIDI_START 			0xC0, 0x00, 0x00
#define MIDI_PAUSE 			0xC0, 0x11, 0x00
#define MIDI_RESTART 		0xC0, 0x22, 0x00
#define MIDI_GAIN 			0xB0, 0x0F, 0x00
#define MIDI_DET 			0xB0, 0x10, 0x00
#define MIDI_DETH 			0xB0, 0x11, 0x00
#define MIDI_MINPOS 		0xB0, 0x12, 0x00
#define MIDI_MAXPOS 		0xB0, 0x13, 0x00
#define MIDI_FPS 			0xB0, 0x14, 0x00
#define MIDI_RELEASE 		0xB0, 0x15, 0x00
#define MIDI_HALFDELTA 		0xB0, 0x16, 0x00
#define MIDI_GLIDESTAB 		0xB0, 0x17, 0x00
#define MIDI_ANGFILTER 		0xB0, 0x18, 0x00

#define MIDI_MINPOSX 		0xB0, 0x70, 0x00
#define MIDI_MAXPOSX 		0xB0, 0x71, 0x00
#define MIDI_MINWIDTHX 		0xB0, 0x72, 0x00
#define MIDI_MAXWIDTHX 		0xB0, 0x73, 0x00
#define MIDI_MINGLIDEX 		0xB0, 0x74, 0x00
#define MIDI_MAXGLIDEX 		0xB0, 0x75, 0x00

#define MIDI_STABZ 			0xB6, 0x01, 0x00 	// Stability on Z (delta where value dos not change)
#define MIDI_SMOOTHZ 		0xB6, 0x0F, 0x00 	// Z average
#define MIDI_RELATIVEH 		0xB6, 0x10, 0x00 	// Always start at 63
#define MIDI_AMPZ 			0xB6, 0x20, 0x00 	// Ampli on Z variation
#define MIDI_FILTZ 			0xB6, 0x30, 0x00 	// Filter few first Z detection
#define MIDI_MINZ 			0xB6, 0x40, 0x00
#define MIDI_MAXZ 			0xB6, 0x41, 0x00
#define MIDI_CENTERZ 		0xB6, 0x42, 0x00

#define MIDI_DEFAULT 		0xC7, 0x58, 0x00

#define MIDI_NBEAMSX 		0xB1, 0x20, 0x00
#define MIDI_NBEAMSY 		0xB2, 0x20, 0x00

#define MIDI_DISBASEZ 		0xB3, 0x30, 0x00
#define MIDI_DISBASEZH 		0xB3, 0x31, 0x00

#define MIDI_SUBPOSX 		0xB7, 0x00, 0x00
#define MIDI_SUBWIDTHX 		0xB7, 0x01, 0x00
#define MIDI_SUBGLIDEX 		0xB7, 0x02, 0x00
#define MIDI_SUBHEIGHT 		0xB7, 0x03, 0x00

#define MIDI_ENAB 			0xB7, 0x40, 0x00
#define MIDI_ENAB_3P 		0xB7, 0x41, 0x00
#define MIDI_ENAB_4P 		0xB7, 0x42, 0x00

#define MIDI_CHKVARUSE 		0xB7, 0x43, 0x00
#define MIDI_CHKVARUSE_3P 	0xB7, 0x44, 0x00
#define MIDI_CHKVARUSE_4P 	0xB7, 0x45, 0x00

#define MIDI_ACTIVESUB 		0xB7, 0x46, 0x00

#define MIDI_NOTECHANSPIN 	0xB0, 0x21, 0x00
#define MIDI_NOTENOTESPIN 	0xB0, 0x22, 0x00
#define MIDI_NOTEVELSPIN 	0xB0, 0x23, 0x00

#define MIDI_CC1CHANSPIN 	0xB0, 0x31, 0x00
#define MIDI_CC1CTRLSPIN 	0xB0, 0x32, 0x00
#define MIDI_CC1VALSPIN 	0xB0, 0x33, 0x00

#define MIDI_CC2CHANSPIN 	0xB0, 0x41, 0x00
#define MIDI_CC2CTRLSPIN 	0xB0, 0x42, 0x00
#define MIDI_CC2VALSPIN 	0xB0, 0x43, 0x00

#define MIDI_NOTECHANSPIN_3P 	0xB0, 0x24, 0x00
#define MIDI_NOTENOTESPIN_3P 	0xB0, 0x25, 0x00
#define MIDI_NOTEVELSPIN_3P 	0xB0, 0x26, 0x00

#define MIDI_CC1CHANSPIN_3P 	0xB0, 0x34, 0x00
#define MIDI_CC1CTRLSPIN_3P 	0xB0, 0x35, 0x00
#define MIDI_CC1VALSPIN_3P 		0xB0, 0x36, 0x00

#define MIDI_CC2CHANSPIN_3P 	0xB0, 0x44, 0x00
#define MIDI_CC2CTRLSPIN_3P 	0xB0, 0x45, 0x00
#define MIDI_CC2VALSPIN_3P 		0xB0, 0x46, 0x00

#define MIDI_NOTECHANSPIN_4P 	0xB0, 0x27, 0x00
#define MIDI_NOTENOTESPIN_4P 	0xB0, 0x28, 0x00
#define MIDI_NOTEVELSPIN_4P 	0xB0, 0x29, 0x00

#define MIDI_CC1CHANSPIN_4P 	0xB0, 0x37, 0x00
#define MIDI_CC1CTRLSPIN_4P 	0xB0, 0x38, 0x00
#define MIDI_CC1VALSPIN_4P 		0xB0, 0x39, 0x00

#define MIDI_CC2CHANSPIN_4P 	0xB0, 0x47, 0x00
#define MIDI_CC2CTRLSPIN_4P 	0xB0, 0x48, 0x00
#define MIDI_CC2VALSPIN_4P 		0xB0, 0x49, 0x00

#define MIDI_BUTTONONOFF 	0xB7, 0x7C, 0x00

#define MIDI_READVAR2 		0xB7, 0x7E, 0x00
#define MIDI_READVAR 		0xB7, 0x7F, 0x00

#define MIDI_BOOTMODE 		0xC4, 0x7F, 0x00
#define MIDI_INAPPBOOT 		0xC4, 0x7E, 0x00

#define MIDI_INVERTX 		0xC0, 0x40, 0x00
#define MIDI_INVERTVARSX 	0xB4, 0x7F, 0x00
#define MIDI_INVERTY 		0xB5, 0x7F, 0x00
#define MIDI_INVERTZ 		0xB6, 0x7F, 0x00

#define MIDI_LEARNONE 		0xB0, 0x30, 0x00

#define MIDI_ACTIVATE2PL 	0xB4, 0x00, 0x00
#define MIDI_ACTIVATE2PM 	0xB4, 0x01, 0x00
#define MIDI_ACTIVATE2PH 	0xB4, 0x02, 0x00

#define MIDI_ACTIVATE3PL 	0xB4, 0x10, 0x00
#define MIDI_ACTIVATE3PM 	0xB4, 0x11, 0x00
#define MIDI_ACTIVATE3PH 	0xB4, 0x12, 0x00

#define MIDI_ACTIVATE4PL 	0xB4, 0x20, 0x00
#define MIDI_ACTIVATE4PM 	0xB4, 0x21, 0x00
#define MIDI_ACTIVATE4PH 	0xB4, 0x22, 0x00

#define MIDI_SETMIDINOTE0 	0xB4, 0x30, 0x00
#define MIDI_SETMIDINOTE1 	0xB4, 0x31, 0x00
#define MIDI_SETMIDINOTE2 	0xB4, 0x32, 0x00
#define MIDI_SETMIDINOTE3 	0xB4, 0x33, 0x00
#define MIDI_SETMIDINOTE4 	0xB4, 0x34, 0x00
#define MIDI_SETMIDINOTE5 	0xB4, 0x35, 0x00
#define MIDI_SETMIDINOTE6 	0xB4, 0x36, 0x00
#define MIDI_SETMIDINOTE7 	0xB4, 0x37, 0x00
#define MIDI_SETMIDINOTE8 	0xB4, 0x38, 0x00
#define MIDI_SETMIDINOTE9 	0xB4, 0x39, 0x00
#define MIDI_SETMIDINOTE10 	0xB4, 0x3A, 0x00
#define MIDI_SETMIDINOTE11 	0xB4, 0x3B, 0x00
#define MIDI_SETMIDINOTE12 	0xB4, 0x3C, 0x00
#define MIDI_SETMIDINOTE13 	0xB4, 0x3D, 0x00
#define MIDI_SETMIDINOTE14 	0xB4, 0x3E, 0x00
#define MIDI_SETMIDINOTE15 	0xB4, 0x3F, 0x00

#define MIDI_SETMIDINOTE0_3P 	0xB4, 0x40, 0x00
#define MIDI_SETMIDINOTE1_3P 	0xB4, 0x41, 0x00
#define MIDI_SETMIDINOTE2_3P 	0xB4, 0x42, 0x00
#define MIDI_SETMIDINOTE3_3P 	0xB4, 0x43, 0x00
#define MIDI_SETMIDINOTE4_3P 	0xB4, 0x44, 0x00
#define MIDI_SETMIDINOTE5_3P 	0xB4, 0x45, 0x00
#define MIDI_SETMIDINOTE6_3P 	0xB4, 0x46, 0x00
#define MIDI_SETMIDINOTE7_3P 	0xB4, 0x47, 0x00
#define MIDI_SETMIDINOTE8_3P 	0xB4, 0x48, 0x00
#define MIDI_SETMIDINOTE9_3P 	0xB4, 0x49, 0x00
#define MIDI_SETMIDINOTE10_3P 	0xB4, 0x4A, 0x00
#define MIDI_SETMIDINOTE11_3P 	0xB4, 0x4B, 0x00
#define MIDI_SETMIDINOTE12_3P 	0xB4, 0x4C, 0x00
#define MIDI_SETMIDINOTE13_3P 	0xB4, 0x4D, 0x00
#define MIDI_SETMIDINOTE14_3P 	0xB4, 0x4E, 0x00
#define MIDI_SETMIDINOTE15_3P 	0xB4, 0x4F, 0x00

#define MIDI_SETMIDINOTE0_4P 	0xB4, 0x50, 0x00
#define MIDI_SETMIDINOTE1_4P 	0xB4, 0x51, 0x00
#define MIDI_SETMIDINOTE2_4P 	0xB4, 0x52, 0x00
#define MIDI_SETMIDINOTE3_4P 	0xB4, 0x53, 0x00
#define MIDI_SETMIDINOTE4_4P 	0xB4, 0x54, 0x00
#define MIDI_SETMIDINOTE5_4P 	0xB4, 0x55, 0x00
#define MIDI_SETMIDINOTE6_4P 	0xB4, 0x56, 0x00
#define MIDI_SETMIDINOTE7_4P 	0xB4, 0x57, 0x00
#define MIDI_SETMIDINOTE8_4P 	0xB4, 0x58, 0x00
#define MIDI_SETMIDINOTE9_4P 	0xB4, 0x59, 0x00
#define MIDI_SETMIDINOTE10_4P 	0xB4, 0x5A, 0x00
#define MIDI_SETMIDINOTE11_4P 	0xB4, 0x5B, 0x00
#define MIDI_SETMIDINOTE12_4P 	0xB4, 0x5C, 0x00
#define MIDI_SETMIDINOTE13_4P 	0xB4, 0x5D, 0x00
#define MIDI_SETMIDINOTE14_4P 	0xB4, 0x5E, 0x00
#define MIDI_SETMIDINOTE15_4P 	0xB4, 0x5F, 0x00

#define MIDI_ANGLEXL0 		0xB1, 0x50, 0x00
#define MIDI_ANGLEXH0 		0xB1, 0x60, 0x00
#define MIDI_ANGLEXL1 		0xB1, 0x51, 0x00
#define MIDI_ANGLEXH1 		0xB1, 0x61, 0x00
#define MIDI_ANGLEXL2 		0xB1, 0x52, 0x00
#define MIDI_ANGLEXH2 		0xB1, 0x62, 0x00
#define MIDI_ANGLEXL3 		0xB1, 0x53, 0x00
#define MIDI_ANGLEXH3 		0xB1, 0x63, 0x00
#define MIDI_ANGLEXL4 		0xB1, 0x54, 0x00
#define MIDI_ANGLEXH4 		0xB1, 0x64, 0x00
#define MIDI_ANGLEXL5 		0xB1, 0x55, 0x00
#define MIDI_ANGLEXH5 		0xB1, 0x65, 0x00
#define MIDI_ANGLEXL6 		0xB1, 0x56, 0x00
#define MIDI_ANGLEXH6 		0xB1, 0x66, 0x00
#define MIDI_ANGLEXL7 		0xB1, 0x57, 0x00
#define MIDI_ANGLEXH7 		0xB1, 0x67, 0x00
#define MIDI_ANGLEXL8 		0xB1, 0x58, 0x00
#define MIDI_ANGLEXH8 		0xB1, 0x68, 0x00
#define MIDI_ANGLEXL9 		0xB1, 0x59, 0x00
#define MIDI_ANGLEXH9 		0xB1, 0x69, 0x00
#define MIDI_ANGLEXL10 		0xB1, 0x5A, 0x00
#define MIDI_ANGLEXH10 		0xB1, 0x6A, 0x00
#define MIDI_ANGLEXL11 		0xB1, 0x5B, 0x00
#define MIDI_ANGLEXH11 		0xB1, 0x6B, 0x00
#define MIDI_ANGLEXL12 		0xB1, 0x5C, 0x00
#define MIDI_ANGLEXH12 		0xB1, 0x6C, 0x00
#define MIDI_ANGLEXL13 		0xB1, 0x5D, 0x00
#define MIDI_ANGLEXH13 		0xB1, 0x6D, 0x00
#define MIDI_ANGLEXL14 		0xB1, 0x5E, 0x00
#define MIDI_ANGLEXH14 		0xB1, 0x6E, 0x00
#define MIDI_ANGLEXL15 		0xB1, 0x5F, 0x00
#define MIDI_ANGLEXH15 		0xB1, 0x6F, 0x00

////////// DFU //////////
/// LIGHTDICTION ONLY ///
/////////////////////////
#define MIDI_PROGMEM 		0xB0
#define MIDI_SETPAGENUMBER 	0xB1
#define MIDI_STARTFLASHING 	0xB2
#define MIDI_ENDOFPROG 		0xC7, 0x66, 0x00

/////////////////////////
const int _DEPLOY_READVAR[3] = { MIDI_READVAR };
const int _DEPLOY_MIDIBUTTON[3] = { MIDI_BUTTONONOFF };

// checkList = Return from Readvar //
_ENUM_(checkList, unsigned char)
{
    Check_PauseOn,

    Check_nBeamsX,
    Check_DetLevel,
    Check_DetLevelH,
    Check_FPS,
    Check_MinPos,
    Check_MultPos,
    Check_HalfDelta,
    Check_Gain,
    Check_Release,
    Check_InvertVarsX,
    Check_GlideStab,
    Check_AngFilter,

    Check_RelativeH = 15,
    Check_InvertZ,
    Check_StabZ,
    Check_AmpZ,
    Check_SmoothZ,
    Check_FiltZ,
    Check_MinZ,
    Check_MaxZ,
    Check_CenterZ,

    Check_EnabMidiMode = 25,
    Check_EnabMidiMode_3P,
    Check_EnabMidiMode_4P,
    Check_CheckVarUse,
    Check_CheckVarUse_3P,
    Check_CheckVarUse_4P,

    Check_NoteChan,
    Check_NoteNote,
    Check_NoteVel,
    Check_CC1Chan,
    Check_CC1Ctrl,
    Check_CC1Val,
    Check_CC2Chan,
    Check_CC2Ctrl,
    Check_CC2Val,

    Check_NoteChan_3P,
    Check_NoteNote_3P,
    Check_NoteVel_3P,
    Check_CC1Chan_3P,
    Check_CC1Ctrl_3P,
    Check_CC1Val_3P,
    Check_CC2Chan_3P,
    Check_CC2Ctrl_3P,
    Check_CC2Val_3P,

    Check_NoteChan_4P,
    Check_NoteNote_4P,
    Check_NoteVel_4P,
    Check_CC1Chan_4P,
    Check_CC1Ctrl_4P,
    Check_CC1Val_4P,
    Check_CC2Chan_4P,
    Check_CC2Ctrl_4P,
    Check_CC2Val_4P,

    Check_Activate2PL = 65,
    Check_Activate2PM,
    Check_Activate2PH,

    Check_Activate3PL,
    Check_Activate3PM,
    Check_Activate3PH,

    Check_Activate4PL,
    Check_Activate4PM,
    Check_Activate4PH,

    Check_MinPosX,
    Check_MaxPosX,
    Check_MinWidthX,
    Check_MaxWidthX,
    Check_MinGlideX,
    Check_MaxGlideX,

            Check_SubPosX,
            Check_SubWidthX,
            Check_SubGlideX,
            Check_SubHeight,

            Check_ActiveSub,

    // Do not change / Add below

    Check_BeamAngleListX0 = 90,
    Check_BeamAngleListX1,
    Check_BeamAngleListX2,
    Check_BeamAngleListX3,
    Check_BeamAngleListX4,
    Check_BeamAngleListX5,
    Check_BeamAngleListX6,
    Check_BeamAngleListX7,
    Check_BeamAngleListX8,
    Check_BeamAngleListX9,
    Check_BeamAngleListX10,
    Check_BeamAngleListX11,
    Check_BeamAngleListX12,
    Check_BeamAngleListX13,
    Check_BeamAngleListX14,
    Check_BeamAngleListX15,
    Check_BeamAngleListXH0,
    Check_BeamAngleListXH1,
    Check_BeamAngleListXH2,
    Check_BeamAngleListXH3,
    Check_BeamAngleListXH4,
    Check_BeamAngleListXH5,
    Check_BeamAngleListXH6,
    Check_BeamAngleListXH7,
    Check_BeamAngleListXH8,
    Check_BeamAngleListXH9,
    Check_BeamAngleListXH10,
    Check_BeamAngleListXH11,
    Check_BeamAngleListXH12,
    Check_BeamAngleListXH13,
    Check_BeamAngleListXH14,
    Check_BeamAngleListXH15,

    Check_SaveInFlash = 122,
    Check_SN,
    Check_SubSN,
    Check_Version,
    Check_SubVersion,
    Check_NbPorts,

    //// Use second Read command for commands below ////

    Check_NoteToPlay0 = 128,
    Check_NoteToPlay1,
    Check_NoteToPlay2,
    Check_NoteToPlay3,
    Check_NoteToPlay4,
    Check_NoteToPlay5,
    Check_NoteToPlay6,
    Check_NoteToPlay7,
    Check_NoteToPlay8,
    Check_NoteToPlay9,
    Check_NoteToPlay10,
    Check_NoteToPlay11,
    Check_NoteToPlay12,
    Check_NoteToPlay13,
    Check_NoteToPlay14,
    Check_NoteToPlay15,

    Check_NoteToPlay0_3P = 144,
    Check_NoteToPlay1_3P,
    Check_NoteToPlay2_3P,
    Check_NoteToPlay3_3P,
    Check_NoteToPlay4_3P,
    Check_NoteToPlay5_3P,
    Check_NoteToPlay6_3P,
    Check_NoteToPlay7_3P,
    Check_NoteToPlay8_3P,
    Check_NoteToPlay9_3P,
    Check_NoteToPlay10_3P,
    Check_NoteToPlay11_3P,
    Check_NoteToPlay12_3P,
    Check_NoteToPlay13_3P,
    Check_NoteToPlay14_3P,
    Check_NoteToPlay15_3P,

    Check_NoteToPlay0_4P = 160,
    Check_NoteToPlay1_4P,
    Check_NoteToPlay2_4P,
    Check_NoteToPlay3_4P,
    Check_NoteToPlay4_4P,
    Check_NoteToPlay5_4P,
    Check_NoteToPlay6_4P,
    Check_NoteToPlay7_4P,
    Check_NoteToPlay8_4P,
    Check_NoteToPlay9_4P,
    Check_NoteToPlay10_4P,
    Check_NoteToPlay11_4P,
    Check_NoteToPlay12_4P,
    Check_NoteToPlay13_4P,
    Check_NoteToPlay14_4P,
    Check_NoteToPlay15_4P,
};

// checkListDfu = Return from Readvar in Dfu //
enum checkListDfu : unsigned char
{
    Check_Dfu_ID0 = 50,
    Check_Dfu_ID0H,
    Check_Dfu_ID1,
    Check_Dfu_ID1H,
    Check_Dfu_ID2,
    Check_Dfu_ID2H,
    Check_Dfu_ID3,
    Check_Dfu_ID3H,
    Check_Dfu_ID4,
    Check_Dfu_ID4H,
    Check_Dfu_ID5,
    Check_Dfu_ID5H,
    Check_Dfu_ID6,
    Check_Dfu_ID6H,
    Check_Dfu_ID7,
    Check_Dfu_ID7H,
    Check_Dfu_ID8,
    Check_Dfu_ID8H,
    Check_Dfu_ID9,
    Check_Dfu_ID9H,
    Check_Dfu_ID10,
    Check_Dfu_ID10H,
    Check_Dfu_ID11,
    Check_Dfu_ID11H,

    Check_Dfu_SN = 123,
    Check_Dfu_SubSN,
    Check_Dfu_Version,
    Check_Dfu_SubVersion,
};

#endif // COMENUM_H

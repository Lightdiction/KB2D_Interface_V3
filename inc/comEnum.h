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

///////////////////////////////////
// MIDI Commands to send to KB2D //
#define MIDI_SN 			0x90, 0x10, 0x00
#define MIDI_SUBSN 			0x90, 0x11, 0x00

#define MIDI_START 			0xC0, 0x00, 0x00
#define MIDI_PAUSE 			0xC0, 0x11, 0x00
#define MIDI_RESTART 		0xC0, 0x22, 0x00
#define MIDI_GAIN           0xB0, 0x0F, 0x00
#define MIDI_DET 			0xB0, 0x10, 0x00
#define MIDI_MINPOS 		0xB0, 0x11, 0x00
#define MIDI_MAXPOS 		0xB0, 0x12, 0x00
#define MIDI_DETH 			0xB0, 0x13, 0x00
#define MIDI_SAVEALL 		0xC7, 0x50, 0x00
#define MIDI_FPS 			0xB0, 0x14, 0x00
#define MIDI_RELEASE 		0xB0, 0x15, 0x00
#define MIDI_DEFAULT 		0xC7, 0x58, 0x00

#define MIDI_NBEAMSX 		0xB1, 0x20, 0x00
#define MIDI_NBEAMSY 		0xB2, 0x20, 0x00
#define MIDI_NBEAMSZ 		0xB3, 0x20, 0x00
#define MIDI_ANGMINX 		0xB1, 0x30, 0x00 	//
#define MIDI_ANGMINXH 		0xB1, 0x31, 0x00 	//
#define MIDI_ANGMAXX 		0xB1, 0x32, 0x00 	//
#define MIDI_ANGMAXXH 		0xB1, 0x33, 0x00 	//
#define MIDI_ANGMINY 		0xB2, 0x30, 0x00 	//
#define MIDI_ANGMINYH 		0xB2, 0x31, 0x00 	//
#define MIDI_ANGMAXY 		0xB2, 0x32, 0x00 	//
#define MIDI_ANGMAXYH 		0xB2, 0x33, 0x00 	//
#define MIDI_DISBASEZ 		0xB3, 0x30, 0x00
#define MIDI_DISBASEZH 		0xB3, 0x31, 0x00

#define MIDI_STABZ 			0xB6, 0x01, 0x00 	// Stability on Z (delta where value dos not change)
#define MIDI_SMOOTHZ 		0xB6, 0x0F, 0x00 	// Z average
#define MIDI_RELATIVEH 		0xB6, 0x10, 0x00 	//
#define MIDI_AMPZ 			0xB6, 0x20, 0x00 	// Ampli on Z variation
#define MIDI_FILTZ 			0xB6, 0x30, 0x00 	// Filter few first Z detection

#define MIDI_ENAB 			0xB7, 0x40, 0x00

#define MIDI_NOTECHANSPIN 	0xB0, 0x21, 0x00
#define MIDI_CC1CHANSPIN 	0xB0, 0x31, 0x00
#define MIDI_CC2CHANSPIN 	0xB0, 0x41, 0x00

#define MIDI_NOTENOTESPIN 	0xB0, 0x22, 0x00
#define MIDI_CC1CTRLSPIN 	0xB0, 0x32, 0x00
#define MIDI_CC2CTRLSPIN 	0xB0, 0x42, 0x00

#define MIDI_NOTEVELSPIN 	0xB0, 0x24, 0x00
#define MIDI_CC1VALSPIN 	0xB0, 0x34, 0x00
#define MIDI_CC2VALSPIN 	0xB0, 0x44, 0x00

#define MIDI_NOTENOTESPIN2 	0xB0, 0x23, 0x00
#define MIDI_CC1CTRLSPIN2 	0xB0, 0x33, 0x00
#define MIDI_CC2CTRLSPIN2 	0xB0, 0x43, 0x00

#define MIDI_NOTEVELSPIN2 	0xB0, 0x25, 0x00
#define MIDI_CC1VALSPIN2 	0xB0, 0x35, 0x00
#define MIDI_CC2VALSPIN2 	0xB0, 0x45, 0x00

#define MIDI_READVAR 		0xB7, 0x7F, 0x00

#define MIDI_BOOTMODE 		0xC4, 0x7F, 0x00    // DO NOT USE THIS - LIGHTDICTION ONLY - (Unless you want to kill your firmware)
#define MIDI_INAPPBOOT 		0xC4, 0x7E, 0x00

#define MIDI_HALFDELTA 		0xB0, 0x20, 0x00

#define MIDI_INVERTX 		0xC0, 0x40, 0x00
#define MIDI_INVERTY 		0xB5, 0x7F, 0x00
#define MIDI_INVERTZ 		0xB6, 0x7F, 0x00

#define MIDI_LEARNONE 		0xB0, 0x30, 0x00

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

#define MIDI_STARTNOTES 	0xC0, 0x30, 0x00
#define MIDI_STOPNOTES 		0xC0, 0x38, 0x00

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

// checkList = Return from Readvar //
enum checkList : unsigned char
{
    Check_TestNote1,
    Check_nBeamsX,
    Check_nBeamsZ,
    Check_DetLevel,
    Check_FPS,
    Check_MinPos,
    Check_MultPos,
    Check_EnabMidiMode,
    Check_NoteChan,
    Check_CC1Chan,
    Check_CC2Chan,
    Check_NoteNote,
    Check_CC1Ctrl,
    Check_CC2Ctrl,
    Check_NoteVel,
    Check_CC1Val,
    Check_CC2Val,
    Check_CheckVarUse,
    Check_ContX,
    Check_ContY,
    Check_RelativeH,
    Check_HalfDelta,
    Check_StabZ,
    Check_AmpZ,
    Check_NoteToPlay0,
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
    Check_DetLevelH,

    Check_PauseOn = 44,
    Check_SmoothZ,
    Check_FiltZ,
    Check_InvertZ,
    Check_Gain,
    Check_Release,

    Check_BeamAngleListX0 = 80,
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
    Check_AngleMinX,
    Check_AngleMaxX,
    Check_AngleMinXH,
    Check_AngleMaxXH,

    Check_SaveInFlash = 122,
    Check_SN,
    Check_SubSN,
    Check_Version,
    Check_SubVersion,
    Check_TestNote2,
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

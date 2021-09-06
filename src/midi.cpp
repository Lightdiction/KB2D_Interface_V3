
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** MIDI **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Custom MIDI Class to Handle communication in MIDI
 * This class use Windows functions
 *
 * =================================================
 */

#include "../inc/midi.h"

midi::midi()
{

}


unsigned int midi::getNumDevIn()
{
    return midiInGetNumDevs();
}

unsigned int midi::getNumDevOut()
{
    return midiOutGetNumDevs();
}

QString midi::getNameDevIn(int ind)
{
    MIDIINCAPSA devIn;
    if ((ind >= 0) && ((unsigned int)ind < midi::getNumDevIn()))
    {
        midiInGetDevCapsA(ind, &devIn, sizeof(devIn));
        return (QString)qstrdup(devIn.szPname);
    }
    else
        return (QString)"";
}

QString midi::getNameDevOut(int ind)
{
    MIDIOUTCAPSA devOut;
    if ((ind >= 0) && ((unsigned int)ind < midi::getNumDevOut()))
    {
        midiOutGetDevCapsA(ind, &devOut, sizeof(devOut));
        return (QString)qstrdup(devOut.szPname);
    }
    else
        return (QString)"";
}

/*
 * ======================
 * MidiDevIn Class
 * ======================
 */
MidiDevIn::MidiDevIn()
{
    index = -1;
    name = (QString)"";
    paramIn[0] = 0;
    paramIn[1] = 0;
    paramIn[2] = 0;
}

HMIDIIN MidiDevIn::getDev() const {
    return devIn; }

LPHMIDIIN MidiDevIn::getLPDev() {
    return &devIn; }

int MidiDevIn::getIndex() const {
    return index; }

QString MidiDevIn::getName() const {
    return name; }

unsigned char MidiDevIn::getParam(unsigned int ind) const {
    return (ind < 3) ? paramIn[ind] : paramIn[2]; }

void MidiDevIn::setParam(unsigned int ind, unsigned char ch) {
    (ind < 3) ? paramIn[ind] = ch : paramIn[2] = ch; }

int MidiDevIn::close()
{
    index = -1;
    name = (QString)"";
    return midiInClose(devIn);
}

int MidiDevIn::stop()
{
    return midiInStop(devIn);
}

int MidiDevIn::open(int ind, DWORD_PTR dwInstance)
{
    int res;
    //close();
    //stop();
    res = midiInOpen(&devIn, ind, (DWORD_PTR)(MidiDevIn::MidiInProc), (DWORD_PTR)dwInstance, CALLBACK_FUNCTION);
    if (res == 0)
    {
        index = ind;
        name = midi::getNameDevIn(index);
    }
    return res;
}

int MidiDevIn::open(QString nam, DWORD_PTR dwInstance)
{
    int res = 0;
    for (uint _i = 0 ; _i < midi::getNumDevIn() ; _i++)
    {
        if (getNameDevIn(_i) == nam)
        {
            res = midiInOpen(&devIn, _i, (DWORD_PTR)(MidiDevIn::MidiInProc), (DWORD_PTR)dwInstance, CALLBACK_FUNCTION);
            if (res == 0)
            {
                index = _i;
                name = midi::getNameDevIn(index);
            }
            return res;
        }
    }
    return res;     // return 0 (if the device does not exist
}

int MidiDevIn::start()
{
    return midiInStart(devIn);
}

/*
 * =====================================================
 * hMidiIn: Handle to MIDI Device
 * wMsg: Type of message
 * dwInstance: Pointer to Instance
 * dwParam1: MIM_DATA MIDI message received
 * dwParam2: MIM_DATA timestamp of message received
 * =====================================================
 */
void CALLBACK MidiDevIn::MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    //MainWindow *_this = (MainWindow*) (dwInstance);

    switch(wMsg)
    {
    case MIM_OPEN:
        //QMessageBox::information(_this, "wMsg", "MIM_OPEN");
        break;
    case MIM_CLOSE:
        //QMessageBox::information(_this, "wMsg", "MIM_CLOSE");
        break;
    case MIM_DATA:
        //
        MidiDevIn::midiInCallback(hMidiIn, dwInstance, (dwParam1) & 0xFF, ((dwParam1) >> 8) & 0xFF, ((dwParam1) >> 16) & 0xFF, dwParam2);

        break;
    case MIM_LONGDATA:
        //QMessageBox::information(_this, "wMsg", "MIM_LONGDATA");
        break;
    case MIM_ERROR:
        //QMessageBox::information(_this, "wMsg", "MIM_ERROR");
        break;
    case MIM_LONGERROR:
        //QMessageBox::information(_this, "wMsg", "MIM_LONGERROR");
        break;
    case MIM_MOREDATA:
        //QMessageBox::information(_this, "wMsg", "MIM_MOREDATA");
        break;
    default:
        //QMessageBox::information(_this, "wMsg", "unknown");
        break;
    }
}

/*
 * ======================
 * MidiDevOut Class
 * ======================
 */
MidiDevOut::MidiDevOut()
{
    index = -1;
    name = (QString)"";
}

HMIDIOUT MidiDevOut::getDev() const {
    return devOut; }

LPHMIDIOUT MidiDevOut::getLPDev() {
    return &devOut; }

int MidiDevOut::getIndex() const {
    return index; }

QString MidiDevOut::getName() const {
    return name; }

int MidiDevOut::close()
{
    index = -1;
    name = (QString)"";
    return midiOutClose(devOut);
}

int MidiDevOut::open(int ind)
{
    int res;
    //close();
    res = midiOutOpen(&devOut, ind, 0, 0, CALLBACK_NULL);
    if (res == 0)
    {
        index = ind;
        name = midi::getNameDevOut(index);
    }
    return res;
}

int MidiDevOut::open(QString nam)
{
    int res = 0;
    for (uint _i = 0 ; _i < midi::getNumDevOut() ; _i++)
    {
        if (getNameDevOut(_i) == nam)
        {
            res = midiOutOpen(&devOut, _i, 0, 0, CALLBACK_NULL);
            if (res == 0)
            {
                index = _i;
                name = midi::getNameDevOut(index);
            }
            return res;
        }
    }
    return res;     // return 0 (if the device does not exist
}

int MidiDevOut::sendWord(char data1, char data2, char data3)
{
    // variable which is both an integer and an array of characters:
    union { unsigned long word; unsigned char data[4]; } mess;
    mess.data[0] = data1;  // MIDI note-on message (requires to data bytes)
    mess.data[1] = data2;    // MIDI note-on message: Key number (60 = middle C)
    mess.data[2] = data3;   // MIDI note-on message: Key velocity (100 = loud)
    mess.data[3] = 0;     // Unused parameter

    return midiOutShortMsg(devOut, mess.word);
}


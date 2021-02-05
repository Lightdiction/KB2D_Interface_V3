#ifndef MIDI_H
#define MIDI_H

#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */

#include <QString>

class midi
{
public:
    midi();
    static unsigned int getNumDevOut(void);  // static: this function can be used without midi instance
    static unsigned int getNumDevIn(void);
    static QString getNameDevIn(int ind);
    static QString getNameDevOut(int ind);
};

/*
 * ======================
 * MidiDevIn Class
 * ======================
 */
class MidiDevIn : public midi
{
public:
    MidiDevIn();

    HMIDIIN getDev() const;
    LPHMIDIIN getLPDev();
    int getIndex() const;
    QString getName() const;
    unsigned char getParam(unsigned int ind) const;
    void setParam(unsigned int ind, unsigned char ch);
    int close();
    int stop();
    int open(int ind, DWORD_PTR dwInstance);
    int start();

    static void midiInCallback(HMIDIIN hMidiIn, DWORD_PTR dwInstance, unsigned char data1, unsigned char data2, unsigned char data3, DWORD_PTR mdTimestamp);

private:
    static void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

protected:
    HMIDIIN devIn;
    int index;
    QString name;
    unsigned char paramIn[3];
};

/*
 * ======================
 * MidiDevOut Class
 * ======================
 */
class MidiDevOut : public midi
{
public:
    MidiDevOut();

    HMIDIOUT getDev() const;
    LPHMIDIOUT getLPDev();
    int getIndex() const;
    QString getName() const;
    int close();
    int open(int ind);
    int sendWord(char data1, char data2, char data3);

protected:
    HMIDIOUT devOut;
    int index;
    QString name;
};

#endif // MIDI_H

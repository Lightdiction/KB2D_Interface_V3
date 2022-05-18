#ifndef MIDI_H
#define MIDI_H

#ifdef WIN_PLATFORM
#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */
#endif
#ifdef LIN_PLATFORM
#include <alsa/asoundlib.h>
#define DWORD_PTR               unsigned long long
#define MMSYSERR_NOERROR        0
#endif
#ifdef MAC_PLATFORM
#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>
#define DWORD_PTR               unsigned long long
#define MMSYSERR_NOERROR        0
#endif

#include <QString>
#include <QObject>
#include <QThread>

class midi : public QObject
{
    Q_OBJECT

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
    Q_OBJECT

public:
    MidiDevIn();
    ~MidiDevIn();
#ifdef WIN_PLATFORM
    HMIDIIN getDev() const;
    LPHMIDIIN getLPDev();

    static void midiInCallback(HMIDIIN hMidiIn, DWORD_PTR dwInstance, unsigned char data1, unsigned char data2, unsigned char data3, DWORD_PTR mdTimestamp);
#endif
#ifdef LIN_PLATFORM
    snd_rawmidi_t* getDev() const;
    snd_rawmidi_t** getLPDev();

    void midiInThread();
#endif
#ifdef MAC_PLATFORM
    MIDIEndpointRef getDev() const;
    MIDIEndpointRef* getLPDev();

    //static void midiInProc(const MIDIEventList* listEventsIn, void* refCon);
    static void midiInProc(const MIDIPacketList* listEventsIn, void* readProcRef, void* refCon);
#endif
    int open(int ind, DWORD_PTR ptr);
    int open(QString name, DWORD_PTR ptr);
    int close();
    int stop();
    int start();

    int getIndex() const;
    QString getName() const;
    unsigned char getParam(unsigned int ind) const;
    void setParam(unsigned int ind, unsigned char ch);

    void setThread();

signals:
    void harpInCalled();
    void extInCalled(unsigned char data1, unsigned char data2, unsigned char data3);

    void startMonitoring();
    void killThread();

private:
#ifdef WIN_PLATFORM
    static void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
#endif

protected:
#ifdef WIN_PLATFORM
    HMIDIIN devIn;
#endif
#ifdef LIN_PLATFORM
    snd_rawmidi_t* devIn = nullptr;
#endif
#ifdef MAC_PLATFORM
    MIDIClientRef clientRef = (unsigned int)NULL;
    MIDIPortRef portRef = (unsigned int)NULL;
    MIDIEndpointRef devIn = (unsigned int)NULL;
#endif
    QThread* inThread = nullptr;
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
    Q_OBJECT

public:
    MidiDevOut();

#ifdef WIN_PLATFORM
    HMIDIOUT getDev() const;
    LPHMIDIOUT getLPDev();
#endif
#ifdef LIN_PLATFORM
    snd_rawmidi_t* getDev() const;
    snd_rawmidi_t** getLPDev();
#endif
#ifdef MAC_PLATFORM
    MIDIEndpointRef getDev() const;
    MIDIEndpointRef* getLPDev();
#endif
    int getIndex() const;
    QString getName() const;
    int close();
    int open(int ind);
    int open(QString nam);
    int sendWord(char data1, char data2, char data3);

protected:
#ifdef WIN_PLATFORM
    HMIDIOUT devOut;
#endif
#ifdef LIN_PLATFORM
    snd_rawmidi_t* devOut = nullptr;
#endif
#ifdef MAC_PLATFORM
    MIDIClientRef clientRef = (unsigned int)NULL;
    MIDIPortRef portRef = (unsigned int)NULL;
    MIDIEndpointRef devOut = (unsigned int)NULL;

    Byte buffOut[512];
    MIDIPacketList* packetList = (MIDIPacketList*)buffOut;
#endif
    int index;
    QString name;
};

#endif // MIDI_H

#ifndef COMHW_H
#define COMHW_H

//#include "mainwindow.h"
//#include "kblfw.h"

enum IdType
{
    VERSION,
    SUBVERSION,
    SERIAL
};

enum MidiMode : unsigned int
{
    NOTES_ONOFF = 0x01,
    PITCH = 0x02,
    CONTROL_CHANGE = 0x04
};

enum CheckId : unsigned int
{
};


///////////////////////////////////////////
/// \brief Class:
/// General Communication class for devices
///
class ComHw
{
public:
    ComHw();
    int sendCom(unsigned char data1, unsigned char data2, unsigned char data3);
    bool isConnected() const;
    void setConnected(bool state);
    bool isWaitingFb() const;
    void waitForFeedback(bool waitState);

    unsigned int getID(IdType idType) const;
    void setID(IdType idType, unsigned int value);

private:

protected:
    bool connected;
    bool waitingFeedback;

    unsigned int version;
    unsigned int subVersion;
    unsigned int serialNumber;
};


///////////////////////////////////////////
/// \brief Class:
/// Handles all functions relative to KB2D device and communication
///
class ComHwKb2d : public ComHw
{
public:
    ComHwKb2d();

    unsigned int getMidiMode () const;
    void enMidiMode(MidiMode midiMode);
    void disMidiMode(MidiMode midiMode);
    void setMidiMode(unsigned int midiMode);
    int checkFeedback(unsigned char commIndex);


private:
    unsigned int enabMidiMode;
};


///////////////////////////////////////////
/// \brief Class:
/// Handles all functions relative to DFU device and communication
///
class ComHwDfu : public ComHw
{
public:
    ComHwDfu();

    int sendAndCheck(unsigned char data1, unsigned char data2, unsigned char data3);
    int checkDfuFeedback(unsigned char commIndex);

private:
};


extern ComHwKb2d kbDev;
extern ComHwDfu dfuDev;

#endif // COMHW_H

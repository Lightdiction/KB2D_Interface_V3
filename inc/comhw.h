#ifndef COMHW_H
#define COMHW_H

#include <QObject>


#define _ENUM_(name, base) enum name : base

enum IdType
{
    VERSION,
    SUBVERSION,
    SERIAL
};

_ENUM_(MidiMode, unsigned int)
{
    NOTES_ONOFF = 0x01,
    PITCH = 0x02,
    CONTROL_CHANGE = 0x04
};


///////////////////////////////////////////
/// \brief Class:
/// General Communication class for devices
///
class ComHw : public QObject
{
    Q_OBJECT

public:
    ComHw();
    int sendCom(unsigned char data1, unsigned char data2, unsigned char data3);
    bool isConnected() const;
    void setConnected(bool state);
    bool isWaitingFb() const;
    void waitForFeedback(bool waitState);

    unsigned int getID(IdType idType) const;
    void setID(IdType idType, unsigned int value);

signals:
    void comFailed();

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
    Q_OBJECT

public:
    ComHwKb2d();

    unsigned int getMidiMode () const;
    void enMidiMode(MidiMode midiMode);
    void disMidiMode(MidiMode midiMode);
    void setMidiMode(unsigned int midiMode);
    int checkFeedback(unsigned char commIndex);

signals:
    void comFailed();

private:
    unsigned int enabMidiMode;
};


///////////////////////////////////////////
/// \brief Class:
/// Handles all functions relative to DFU device and communication
///
class ComHwDfu : public ComHw
{
    Q_OBJECT

public:
    ComHwDfu();

    int sendAndCheck(unsigned char data1, unsigned char data2, unsigned char data3);
    int checkDfuFeedback(unsigned char commIndex);

signals:
    void comFailed();

private:
};


extern ComHwKb2d kbDev;
extern ComHwDfu dfuDev;

#endif // COMHW_H

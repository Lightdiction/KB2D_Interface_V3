
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Com Hw **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Manage Global functions related to the device
 * and to the communication to it
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
//#include "comhw.h"

extern int catchCommIndex;
extern unsigned char catchPar1;
extern unsigned char catchPar2;
extern unsigned char catchPar3;

/*
 * ==============================
 * General Hardware Class
 * ==============================
 */
ComHw::ComHw()
{
    connected = false;
    waitingFeedback = false;
}

bool ComHw::isConnected() const {
    return connected; }

void ComHw::setConnected(bool state) {
    connected = state; }

bool ComHw::isWaitingFb() const {
    return waitingFeedback; }

void ComHw::waitForFeedback(bool waitState) {
    waitingFeedback = waitState; }

/*
 * ======================
 * Send Command to Device
 * ======================
 */
int ComHw::sendCom(unsigned char data1, unsigned char data2, unsigned char data3)
{
    int numDev = 0;
    int i = 0;

    //if ((configDone) && ((kbDev.isConnected() == 1) || (dfuDev.isConnected() == 1)))    //
    if ((configDone) && (isConnected() == 1))    //
    {
        if (harpOut.sendWord(data1, data2, data3) != MMSYSERR_NOERROR)
        {
            if (saveIndexMidiOut > 0)
            {
                numDev = midi::getNumDevOut();
                while ((i < numDev) && (i >= 0))    // Scan all Midi Out
                {
                    if (QString::compare(midi::getNameDevOut(i), saveNameMidi) == 0)
                    {
                        harpOut.close();
                        if (harpOut.open(i) == MMSYSERR_NOERROR)    // Try to reconnect
                        {
                            if (harpOut.sendWord(data1, data2, data3) == MMSYSERR_NOERROR)  // Try to send the message again
                            {
                                saveIndexMidiOut = i + 1;
                                i = -2;     // Leave the loop with i < 0 (SUCCESS)
                            }
                        }
                    }
                    i += 1;
                }
                if (i > 0)      // Not connected
                {
                    SendError(0, QObject::tr("Message not sent<br/>") + (QString::number(data1)) + " " + (QString::number(data2)) + " " + (QString::number(data3)), ComHw_SendCom_1);
                    dfuDev.setConnected(0);
                    emit comFailed();
                    return -1;
                }
            }
            else
            {
                SendError(0, QObject::tr("No device Out found"), ComHw_SendCom_2);
                dfuDev.setConnected(0);
                emit comFailed();
                return -1;
            }
        }
    }
    return 0;
}

/*
 * ==========================
 * Get ID Parameters
 * ==========================
 */
unsigned int ComHw::getID(IdType idType) const
{
    switch (idType)
    {
    case VERSION:
        return version;
        break;
    case SUBVERSION:
        return subVersion;
        break;
    case SERIAL:
        return serialNumber;
        break;
    }
    return 0;
}

/*
 * ==========================
 * Set ID Parameters
 * ==========================
 */
void ComHw::setID(IdType idType, unsigned int value)
{
    switch (idType)
    {
    case VERSION:
        version = value;
        break;
    case SUBVERSION:
        subVersion = value;
        break;
    case SERIAL:
        serialNumber = value;
        break;
    }
}


/*
 * =====================
 * Class for KB2D Mode
 * =====================
 */
ComHwKb2d::ComHwKb2d()
{
    enabMidiMode = NOTES_ONOFF;
    version = 0;
    subVersion = 0;
    serialNumber = 0;
}

/*
 * ===========================
 * Get Midi Mode
 * Notes ON/OFF | PITCH | CC
 * ===========================
 */
unsigned int ComHwKb2d::getMidiMode() const {
    return enabMidiMode; }

void ComHwKb2d::enMidiMode(MidiMode midiMode)
{
    if ((unsigned int)midiMode > 7)
        midiMode = NOTES_ONOFF;
    enabMidiMode |= midiMode;
}

void ComHwKb2d::disMidiMode(MidiMode midiMode)
{
    if ((unsigned int)midiMode > 7)
        midiMode = NOTES_ONOFF;
    enabMidiMode &= ~(midiMode);
}

void ComHwKb2d::setMidiMode(unsigned int midiMode) {
    enabMidiMode = midiMode & (NOTES_ONOFF | PITCH | CONTROL_CHANGE); }

/*
 * ==============================
 * Check Reception Feedback
 * For KB2D Mode Only
 * ==============================
 */
int ComHwKb2d::checkFeedback(unsigned char commIndex)
{
    QElapsedTimer timer;
    timer.start();

    QCoreApplication::processEvents();
    kbDev.waitForFeedback(1);
    if (kbDev.isConnected() == 1)
    {
        for (int tryN = 0; tryN < 3; tryN++)
        {
            if (commIndex < 128)
                kbDev.sendCom(MIDI_READVAR + (char)commIndex);
            else
            {
                commIndex -= 128;
                kbDev.sendCom(MIDI_READVAR2 + (char)commIndex);
            }
            while (kbDev.isWaitingFb())
            {
                QCoreApplication::processEvents();
                if (timer.elapsed() > 500)
                {
                    if (tryN == 2)
                    {
                        // Communication error...
                        SendError(0, QObject::tr("Timeout - No communication with Device"), ComHw_CheckFeedback_1);
                        emit comFailed();
                        return -1;
                    }
                    SendLog("CheckFeedback fail - CommIndex = " + QString::number(commIndex) + ": try no" + QString::number(tryN + 2));
                    break;
                }
            }
            catchCommIndex = commIndex;
            catchPar1 = harpIn.getParam(0);
            catchPar2 = harpIn.getParam(1);
            catchPar3 = harpIn.getParam(2);
            if ((kbDev.isWaitingFb() == 0) && (harpIn.getParam(0) == _DEPLOY_READVAR[0]) && (harpIn.getParam(1) == commIndex) && (harpIn.getParam(2) < 0x80))
                return (int)harpIn.getParam(2);
        }

        catchCommIndex = commIndex;
        catchPar1 = harpIn.getParam(0);
        catchPar2 = harpIn.getParam(1);
        catchPar3 = harpIn.getParam(2);
        SendError(0, QObject::tr("Incorrect Communication with Device"), ComHw_CheckFeedback_2);
    }

    return -1;
}



/*
 * =====================
 * Class for DFU Mode
 * =====================
 */
ComHwDfu::ComHwDfu()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////// Use this function to make firmware tests and send firmware update commands //////////
////////////////////////////////////////////////////////////////////////////////////////////////
int ComHwDfu::sendAndCheck(unsigned char data1, unsigned char data2, unsigned char data3)
{
    QElapsedTimer timer;
    timer.start();

    if (isConnected() == 1)
    {
        if (sendCom(data1, data2, data3) != 0)
            return -1;

        if ((data1 == MIDI_SETPAGENUMBER) || (data1 == MIDI_PROGMEM)) // Set page number command || prog meme command, does not ask for a feedback
        {
            return 0;
        }
        else
        {
            waitForFeedback(1);
            while (isWaitingFb())
            {
                QCoreApplication::processEvents();
                if (timer.elapsed() > 2000)
                {
                    // Communication error...
                    //QMessageBox::warning(0, "Error", "Timeout - No communication with Device<br/>\nWarning code: " + QString::number(ComHw_SendAndCheck_1));
                    //qobject_cast<MainWindow*>(QApplication::activeWindow())->resetMidiPorts();
                    return -10;
                }
            }
            //qDebug() << "Feedback: " << harpIn.getParam(0) << " " << harpIn.getParam(1) << " " << harpIn.getParam(2);

            switch (data1)
            {
            case 0xC7:  // End of prog command (ask for a feedback).
                if ((harpIn.getParam(0) == 0xC7) && (harpIn.getParam(1) == 0) && (harpIn.getParam(2) == 0))
                    return 0;
                else
                    return -2;
                break;

            case 0xB2:  // Start flashing command (ask for a feedback)
                if ((harpIn.getParam(0) == 0xC6) && (harpIn.getParam(1) == 0) && (harpIn.getParam(2) == 0))     // No error
                    return 0;
                else if (harpIn.getParam(0) == 0xB6)    // Error, returns it
                    return (int)(-100 - harpIn.getParam(2) - (1000 * harpIn.getParam(1)));
                else
                    return -1;
                break;

            default:
                break;
            }

            SendError(0, QObject::tr("Incorrect Communication with Device") + (QString::number(harpIn.getParam(0))) + " " + (QString::number(harpIn.getParam(1))) + " " + \
                      (QString::number(harpIn.getParam(2))), ComHw_SendAndCheck_2);
        }

    }

    return -1;
}

/*
 * ==============================
 * Check Reception Feedback
 * ==============================
 */
int ComHwDfu::checkDfuFeedback(unsigned char commIndex)
{
    QElapsedTimer timer;
    timer.start();

    QCoreApplication::processEvents();
    waitForFeedback(1);
    if (isConnected() == 1)
    {
        for (int tryN = 0; tryN < 3; tryN++)
        {
            sendCom(MIDI_READVAR + (char)commIndex);
            while (isWaitingFb())
            {
                QCoreApplication::processEvents();
                if (timer.elapsed() > 500)
                {
                    // Communication error...
                    if (tryN == 2)
                    {
                        qDebug() << "Dfu Fail comm";
                        return -2;
                    }
                    break;
                }
            }
            if ((isWaitingFb() == 0) && (harpIn.getParam(0) == _DEPLOY_READVAR[0]) && (harpIn.getParam(1) == commIndex) && (harpIn.getParam(2) < 0x80))
                return (int)harpIn.getParam(2);
        }

        SendError(0, QObject::tr("Error: Incorrect Communication with Device\n"), ComHw_CheckDfuFeedback_1);
    }

    return -1;
}



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
#ifdef WIN_PLATFORM
    return midiInGetNumDevs();
#endif
#ifdef MAC_PLATFORM
    return (unsigned int)MIDIGetNumberOfSources();
#endif
#ifdef LIN_PLATFORM
    int cardN = -1;
    unsigned int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports In
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
                snd_ctl_rawmidi_info(ctl, info);
                nDev += snd_rawmidi_info_get_subdevices_count(info);

                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
    return nDev;
#endif
}

unsigned int midi::getNumDevOut()
{
#ifdef WIN_PLATFORM
    return midiOutGetNumDevs();
#endif
#ifdef MAC_PLATFORM
    return (unsigned int)MIDIGetNumberOfDestinations();
#endif
#ifdef LIN_PLATFORM
    int cardN = -1;
    unsigned int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports In
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
                snd_ctl_rawmidi_info(ctl, info);
                nDev += snd_rawmidi_info_get_subdevices_count(info);

                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
    return nDev;
#endif
}

QString midi::getNameDevIn(int ind)
{
    if (ind < 0)
        return (QString)"";
#ifdef WIN_PLATFORM
    MIDIINCAPSA devIn;
    if ((unsigned int)ind < midi::getNumDevIn())
    {
        midiInGetDevCapsA(ind, &devIn, sizeof(devIn));
        return (QString)qstrdup(devIn.szPname);
    }
#endif
#ifdef MAC_PLATFORM
    if ((unsigned int)ind < midi::getNumDevIn())
    {
        CFStringRef nam = CFSTR("");
        MIDIEndpointRef ref = MIDIGetSource(ind);
        MIDIObjectGetStringProperty(ref, kMIDIPropertyDisplayName, &nam);
        return QString::fromCFString(nam);
    }
#endif
#ifdef LIN_PLATFORM
    int cardN = -1;
    unsigned int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports In
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    if ((int)nDev == ind)
                    {
                        snd_rawmidi_info_set_subdevice(info, _i);
                        snd_ctl_rawmidi_info(ctl, info);
                        return QString(snd_rawmidi_info_get_subdevice_name(info));
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
    return (QString)"";
}

QString midi::getNameDevOut(int ind)
{
    if (ind < 0)
        return (QString)"";
#ifdef WIN_PLATFORM
    MIDIOUTCAPSA devOut;
    if ((unsigned int)ind < midi::getNumDevOut())
    {
        midiOutGetDevCapsA(ind, &devOut, sizeof(devOut));
        return (QString)qstrdup(devOut.szPname);
    }
#endif
#ifdef MAC_PLATFORM
    if ((unsigned int)ind < midi::getNumDevOut())
    {
        CFStringRef nam = CFSTR("");
        MIDIEndpointRef ref = MIDIGetDestination(ind);
        MIDIObjectGetStringProperty(ref, kMIDIPropertyDisplayName, &nam);
        return QString::fromCFString(nam);
    }
#endif
#ifdef LIN_PLATFORM
    int cardN = -1;
    unsigned int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports Out
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    if ((int)nDev == ind)
                    {
                        snd_rawmidi_info_set_subdevice(info, _i);
                        snd_ctl_rawmidi_info(ctl, info);
                        return QString(snd_rawmidi_info_get_subdevice_name(info));
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
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
#ifdef LIN_PLATFORM
    connect (this, &MidiDevIn::startMonitoring, this, &MidiDevIn::midiInThread);
#endif
}

MidiDevIn::~MidiDevIn()
{
    emit killThread();
    while (inThread && inThread->isRunning()); // Wait for the end of the thread
}

void MidiDevIn::setThread()
{
    inThread = new QThread();
    connect (this, &MidiDevIn::killThread, inThread, &QThread::quit);
    connect (inThread, &QThread::finished, inThread, &QThread::deleteLater);
    this->moveToThread(inThread);
    inThread->start();
}

#ifdef WIN_PLATFORM
HMIDIIN MidiDevIn::getDev() const {
    return devIn; }

LPHMIDIIN MidiDevIn::getLPDev() {
    return &devIn; }
#endif
#ifdef LIN_PLATFORM
snd_rawmidi_t* MidiDevIn::getDev() const {
    return devIn; }

snd_rawmidi_t** MidiDevIn::getLPDev() {
    return &devIn; }
#endif
#ifdef MAC_PLATFORM
MIDIEndpointRef MidiDevIn::getDev() const {
    return devIn; }

MIDIEndpointRef* MidiDevIn::getLPDev() {
    return &devIn; }
#endif

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
#ifdef WIN_PLATFORM
    return midiInClose(devIn);
#endif
#ifdef LIN_PLATFORM
    if (devIn)
    {
        snd_rawmidi_close(devIn);
        devIn = nullptr;
    }
#endif
#ifdef MAC_PLATFORM
    MIDIPortDisconnectSource(portRef, devIn);
    devIn = (unsigned int)NULL;
    MIDIPortDispose(portRef);
    MIDIClientDispose(clientRef);
#endif
    return 0;
}

int MidiDevIn::stop()
{
#ifdef WIN_PLATFORM
    return midiInStop(devIn);
#endif
    return 0;
}

int MidiDevIn::open(int ind, DWORD_PTR dwInstance)
{
    int res = 0;
    (void)dwInstance;
    //close();
    //stop();
#ifdef WIN_PLATFORM
    res = midiInOpen(&devIn, ind, (DWORD_PTR)(MidiDevIn::MidiInProc), (DWORD_PTR)dwInstance, CALLBACK_FUNCTION);
    if (res == 0)
    {
        index = ind;
        name = midi::getNameDevIn(index);
    }
#endif
#ifdef LIN_PLATFORM
    QString idPort;
    int cardN = -1;
    int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports Out
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    if (nDev == ind)
                    {
                        idPort = "hw:" + QString::number(cardN) + "," + QString::number(midiDev) + "," + QString::number(_i);
                        res = snd_rawmidi_open(&devIn, NULL, idPort.toStdString().c_str(), SND_RAWMIDI_SYNC);
                        if (res >= 0)
                        {
                            index = ind;
                            name = midi::getNameDevIn(index);
                            if (!inThread)
                                setThread();     // Create a separate thread for data reading for each In device
                            return MMSYSERR_NOERROR;
                        }
                        return res;
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
#ifdef MAC_PLATFORM
    if ((unsigned int)ind < midi::getNumDevIn())
    {
        devIn = MIDIGetSource(ind);
        if (devIn == (unsigned int)NULL)
            return -1;
        if (MIDIClientCreate(midi::getNameDevIn(ind).toCFString(), NULL, NULL, &clientRef))
            return -1;
        //MIDIReceiveBlock receiveBlock = ^void (const MIDIEventList* evList, void* refCon) { midiInProc(evList, refCon); };
        //MIDIInputPortCreateWithProtocol(clientRef, ("OUT - " + name).toCFString(), kMIDIProtocol_1_0, &portRef, receiveBlock);
        if (MIDIInputPortCreate(clientRef, ("OUT - " + midi::getNameDevIn(ind)).toCFString(), midiInProc, NULL, &portRef))
            return -1;
        if (MIDIPortConnectSource(portRef, devIn, &devIn))
            return -1;
        index = ind;
        name = midi::getNameDevIn(ind);
    }
#endif
    return res;
}

int MidiDevIn::open(QString nam, DWORD_PTR dwInstance)
{
    (void)dwInstance;
    int res = 0;
#ifdef WIN_PLATFORM
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
#endif
#ifdef LIN_PLATFORM
    QString idPort;
    int cardN = -1;
    int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports Out
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    snd_rawmidi_info_set_subdevice(info, _i);
                    snd_ctl_rawmidi_info(ctl, info);
                    if (QString(snd_rawmidi_info_get_subdevice_name(info)) == nam)
                    {
                        idPort = "hw:" + QString::number(cardN) + "," + QString::number(midiDev) + "," + QString::number(_i);
                        res = snd_rawmidi_open(&devIn, NULL, idPort.toStdString().c_str(), SND_RAWMIDI_SYNC);
                        if (res >= 0)
                        {
                            index = nDev;
                            name = midi::getNameDevIn(index);
                            if (!inThread)
                                setThread();       // Create a separate thread for data reading for each In device
                            return MMSYSERR_NOERROR;
                        }
                        return res;
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
#ifdef MAC_PLATFORM
    for (uint _i = 0 ; _i < midi::getNumDevIn() ; _i++)
    {
        if (getNameDevIn(_i) == nam)
        {
            devIn = MIDIGetSource(index);
            if (devIn == (unsigned int)NULL)
                return -1;
            if (MIDIClientCreate(nam.toCFString(), NULL, NULL, &clientRef))
                return -1;
            //MIDIReceiveBlock receiveBlock = ^void (const MIDIEventList* evList, void* refCon) { midiInProc(evList, refCon); };
            //MIDIInputPortCreateWithProtocol(clientRef, ("IN - " + nam).toCFString(), kMIDIProtocol_1_0, &portRef, receiveBlock);
            if (MIDIInputPortCreate(clientRef, ("IN - " + nam).toCFString(), midiInProc, NULL, &portRef))
                return -1;
            if (MIDIPortConnectSource(portRef, devIn, &devIn))
                return -1;
            index = _i;
            name = midi::getNameDevIn(index);
        }
    }
#endif
    return res;     // return 0 (if the device does not exist)
}

int MidiDevIn::start()
{
#ifdef WIN_PLATFORM
    return midiInStart(devIn);
#endif
#ifdef LIN_PLATFORM
    if (inThread)
        emit startMonitoring();
#endif
#ifdef MAC_PLATFORM
#endif
    return 0;
}

#ifdef WIN_PLATFORM
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
#endif

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

#ifdef WIN_PLATFORM
HMIDIOUT MidiDevOut::getDev() const {
    return devOut; }

LPHMIDIOUT MidiDevOut::getLPDev() {
    return &devOut; }
#endif
#ifdef LIN_PLATFORM
snd_rawmidi_t* MidiDevOut::getDev() const {
    return devOut; }

snd_rawmidi_t** MidiDevOut::getLPDev() {
    return &devOut; }
#endif
#ifdef MAC_PLATFORM
MIDIEndpointRef MidiDevOut::getDev() const {
    return devOut; }

MIDIEndpointRef* MidiDevOut::getLPDev() {
    return &devOut; }
#endif

int MidiDevOut::getIndex() const {
    return index; }

QString MidiDevOut::getName() const {
    return name; }

int MidiDevOut::close()
{
    index = -1;
    name = (QString)"";
#ifdef WIN_PLATFORM
    return midiOutClose(devOut);
#endif
#ifdef LIN_PLATFORM
    if (devOut)
    {
        snd_rawmidi_close(devOut);
        devOut = nullptr;
    }
#endif
#ifdef MAC_PLATFORM
    devOut = (unsigned int)NULL;
    MIDIPortDispose(portRef);
    MIDIClientDispose(clientRef);
#endif
    return 0;
}

int MidiDevOut::open(int ind)
{
    int res = 0;
#ifdef LIN_PLATFORM
    QString idPort;
    int cardN = -1;
    int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports Out
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    if (nDev == ind)
                    {
                        idPort = "hw:" + QString::number(cardN) + "," + QString::number(midiDev) + "," + QString::number(_i);
                        res = snd_rawmidi_open(NULL, &devOut, idPort.toStdString().c_str(), SND_RAWMIDI_SYNC);
                        if (res >= 0)
                        {
                            index = ind;
                            name = midi::getNameDevOut(index);
                            return MMSYSERR_NOERROR;
                        }
                        return res;
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
#ifdef WIN_PLATFORM
    //close();
    res = midiOutOpen(&devOut, ind, 0, 0, CALLBACK_NULL);
    if (res == 0)
    {
        index = ind;
        name = midi::getNameDevOut(index);
    }
#endif
#ifdef MAC_PLATFORM
    if ((unsigned int)ind < midi::getNumDevOut())
    {
        devOut = MIDIGetDestination(ind);
        if (devOut == (unsigned int)NULL)
            return -1;
        if (MIDIClientCreate(midi::getNameDevOut(ind).toCFString(), NULL, NULL, &clientRef))
            return -1;
        if (MIDIOutputPortCreate(clientRef, ("OUT - " + midi::getNameDevOut(ind)).toCFString(), &portRef))
            return -1;
        index = ind;
        name = midi::getNameDevOut(ind);
    }
#endif
    return res;
}

int MidiDevOut::open(QString nam)
{
    int res = 0;
#ifdef LIN_PLATFORM
    QString idPort;
    int cardN = -1;
    int nDev = 0;

    // List Sound cards
    snd_card_next(&cardN);
    while (cardN >= 0)
    {
        snd_ctl_t *ctl = nullptr;
        if (snd_ctl_open(&ctl, ("hw:" + QString::number(cardN)).toStdString().c_str(), 0) >= 0)
        {
            int midiDev = -1;
            // List midi devices
            snd_ctl_rawmidi_next_device(ctl, &midiDev);
            while (midiDev >= 0)
            {
                // Allocate information of the device
                snd_rawmidi_info_t* info = nullptr;
                snd_rawmidi_info_alloca(&info);
                snd_rawmidi_info_set_device(info, midiDev);

                // List ports Out
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
                snd_ctl_rawmidi_info(ctl, info);
                for (int _i = 0 ; _i < (int)snd_rawmidi_info_get_subdevices_count(info) ; _i++)
                {
                    snd_rawmidi_info_set_subdevice(info, _i);
                    snd_ctl_rawmidi_info(ctl, info);
                    if (QString(snd_rawmidi_info_get_subdevice_name(info)) == nam)
                    {
                        idPort = "hw:" + QString::number(cardN) + "," + QString::number(midiDev) + "," + QString::number(_i);
                        res = snd_rawmidi_open(NULL, &devOut, idPort.toStdString().c_str(), SND_RAWMIDI_SYNC);
                        if (res >= 0)
                        {
                            index = nDev;
                            name = midi::getNameDevOut(index);
                            return MMSYSERR_NOERROR;
                        }
                        return res;
                    }
                    nDev++;
                }
                snd_ctl_rawmidi_next_device(ctl, &midiDev);     // Get next device
            }
            snd_ctl_close(ctl);
        }
        snd_card_next(&cardN);
    }
#endif
#ifdef WIN_PLATFORM
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
#endif
#ifdef MAC_PLATFORM
    for (uint _i = 0 ; _i < midi::getNumDevOut() ; _i++)
    {
        if (getNameDevOut(_i) == nam)
        {
            devOut = MIDIGetDestination(_i);
            if (devOut == (unsigned int)NULL)
                return -1;
            if (MIDIClientCreate(nam.toCFString(), NULL, NULL, &clientRef))
                return -1;
            if (MIDIOutputPortCreate(clientRef, ("OUT - " + nam).toCFString(), &portRef))
                return -1;
            index = _i;
            name = midi::getNameDevOut(index);
        }
    }
#endif
    return res;     // return 0 (if the device does not exist
}

int MidiDevOut::sendWord(char data1, char data2, char data3)
{
#ifdef WIN_PLATFORM
    // variable which is both an integer and an array of characters:
    union { unsigned long word; unsigned char data[4]; } mess;
    mess.data[0] = data1;  // MIDI note-on message (requires to data bytes)
    mess.data[1] = data2;    // MIDI note-on message: Key number (60 = middle C)
    mess.data[2] = data3;   // MIDI note-on message: Key velocity (100 = loud)
    mess.data[3] = 0;     // Unused parameter

    return midiOutShortMsg(devOut, mess.word);
#endif
#ifdef LIN_PLATFORM
    if (!devOut)
        return -1;
    char data[3] = { data1, data2, data3 };
    //qDebug() << "Sent " << QString::number((unsigned char)data1) + " " + QString::number((unsigned char)data2) + " " + QString::number((unsigned char)data3);
    if (snd_rawmidi_write(devOut, data, 3) >= 0)
        return MMSYSERR_NOERROR;
#endif
#ifdef MAC_PLATFORM
    MIDIPacket* currentPacket = MIDIPacketListInit(packetList);
    Byte messOut[3] = { (Byte)data1, (Byte)data2, (Byte)data3 };
    currentPacket = MIDIPacketListAdd(packetList, sizeof(buffOut), currentPacket, 0, 3, messOut);
    return MIDISend(portRef, devOut, packetList);
#endif
    return -1;
}


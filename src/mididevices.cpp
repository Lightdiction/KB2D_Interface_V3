#include "../inc/mididevices.h"
#include "ui_mididevices.h"
#include "inc/mainwindow.h"

MidiDevices::MidiDevices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MidiDevices)
{
    ui->setupUi(this);

    parentPtr = parent;

    saveNameKbIn = harpIn.getName();
    saveNameKbOut = harpOut.getName();
    saveNameExtIn = extIn.getName();
    saveNameExtOut = extOut.getName();
    saveNameThroughIn = throughIn.getName();
    saveNameThroughOut = throughOut.getName();

    connect(ui->updateAllButton, &QPushButton::clicked, this, &MidiDevices::updateAllCombos);

    updateAllCombos();
}

MidiDevices::~MidiDevices()
{
    delete ui;
}

void MidiDevices::closeEvent(QCloseEvent* event)
{
    hide();
    emit midiDevicesUpdated(false, saveNameKbIn, saveNameKbOut, saveNameExtIn, saveNameExtOut, saveNameThroughIn, saveNameThroughOut);
    event->accept();
}

void MidiDevices::kbInChanged(int index)
{
    harpIn.stop();
    harpIn.close();
    if (index)
    {
        if (harpIn.open(index - 1, (DWORD_PTR)parentPtr) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI In device"), GrMidiDevices_KbIn);
            ui->kbInComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::kbOutChanged(int index)
{
    harpOut.close();
    if (index)
    {
        if (harpOut.open(index - 1) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI Out device"), GrMidiDevices_KbOut);
            ui->kbOutComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::extInChanged(int index)
{
    extIn.stop();
    extIn.close();
    if (index)
    {
        if (extIn.open(index - 1, (DWORD_PTR)parentPtr) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI In device"), GrMidiDevices_ExtIn);
            ui->extInComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::extOutChanged(int index)
{
    extOut.close();
    if (index)
    {
        if (extOut.open(index - 1) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI Out device"), GrMidiDevices_ExtOut);
            ui->extOutComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::throughInChanged(int index)
{
    throughIn.stop();
    throughIn.close();
    if (index)
    {
        if (throughIn.open(index - 1, (DWORD_PTR)parentPtr) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI In device"), GrMidiDevices_ThroughIn);
            ui->throughInComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::throughOutChanged(int index)
{
    throughOut.close();
    if (index)
    {
        if (throughOut.open(index - 1) != 0)
        {
            SendError(this, tr("Cannot connect to MIDI Out device"), GrMidiDevices_ThroughOut);
            ui->throughOutComboBox->setCurrentIndex(0);
        }
    }
}

void MidiDevices::on_validateButton_clicked()
{
    saveNameKbIn = ui->kbInComboBox->currentText();
    saveNameKbOut = ui->kbOutComboBox->currentText();
    saveNameExtIn = ui->extInComboBox->currentText();
    saveNameExtOut = ui->extOutComboBox->currentText();
    saveNameThroughIn = ui->throughInComboBox->currentText();
    saveNameThroughOut = ui->throughOutComboBox->currentText();

    close();
}

void MidiDevices::on_cancelButton_clicked()
{
    close();
}

void MidiDevices::updateAllCombos()
{

    disconnect(ui->kbInComboBox, &QComboBox::currentIndexChanged, this, nullptr);
    disconnect(ui->kbOutComboBox, &QComboBox::currentIndexChanged, this, nullptr);
    disconnect(ui->extInComboBox, &QComboBox::currentIndexChanged, this, nullptr);
    disconnect(ui->extOutComboBox, &QComboBox::currentIndexChanged, this, nullptr);
    disconnect(ui->throughInComboBox, &QComboBox::currentIndexChanged, this, nullptr);
    disconnect(ui->throughOutComboBox, &QComboBox::currentIndexChanged, this, nullptr);

    ui->kbInComboBox->clear();
    ui->kbOutComboBox->clear();
    ui->extInComboBox->clear();
    ui->extOutComboBox->clear();
    ui->throughInComboBox->clear();
    ui->throughOutComboBox->clear();

    ui->kbInComboBox->addItem(tr("No device"));
    ui->kbOutComboBox->addItem(tr("No device"));
    ui->extInComboBox->addItem(tr("No device"));
    ui->extOutComboBox->addItem(tr("No device"));
    ui->throughInComboBox->addItem(tr("No device"));
    ui->throughOutComboBox->addItem(tr("No device"));

    ui->kbInComboBox->setCurrentIndex(0);
    ui->kbOutComboBox->setCurrentIndex(0);
    ui->extInComboBox->setCurrentIndex(0);
    ui->extOutComboBox->setCurrentIndex(0);
    ui->throughInComboBox->setCurrentIndex(0);
    ui->throughOutComboBox->setCurrentIndex(0);

    for (uint _i = 0 ; _i < (midi::getNumDevIn()) ; _i++)
    {
        ui->kbInComboBox->addItem(midi::getNameDevIn(_i));
        ui->extInComboBox->addItem(midi::getNameDevIn(_i));
        ui->throughInComboBox->addItem(midi::getNameDevIn(_i));

        if (harpIn.getName() == midi::getNameDevIn(_i))
            ui->kbInComboBox->setCurrentIndex(_i + 1);
        if (extIn.getName() == midi::getNameDevIn(_i))
            ui->extInComboBox->setCurrentIndex(_i + 1);
        if (throughIn.getName() == midi::getNameDevIn(_i))
            ui->throughInComboBox->setCurrentIndex(_i + 1);
    }

    for (uint _i = 0 ; _i < (midi::getNumDevOut()) ; _i++)
    {
        ui->kbOutComboBox->addItem(midi::getNameDevOut(_i));
        ui->extOutComboBox->addItem(midi::getNameDevOut(_i));
        ui->throughOutComboBox->addItem(midi::getNameDevOut(_i));

        if (harpOut.getName() == midi::getNameDevOut(_i))
            ui->kbOutComboBox->setCurrentIndex(_i + 1);
        if (extOut.getName() == midi::getNameDevOut(_i))
            ui->extOutComboBox->setCurrentIndex(_i + 1);
        if (throughOut.getName() == midi::getNameDevOut(_i))
            ui->throughOutComboBox->setCurrentIndex(_i + 1);
    }

    connect(ui->kbInComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::kbInChanged);
    connect(ui->kbOutComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::kbOutChanged);
    connect(ui->extInComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::extInChanged);
    connect(ui->extOutComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::extOutChanged);
    connect(ui->throughInComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::throughInChanged);
    connect(ui->throughOutComboBox, &QComboBox::currentIndexChanged, this, &MidiDevices::throughOutChanged);
}

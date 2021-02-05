#include "../inc/savemididialog.h"
#include "ui_savemididialog.h"

SaveMidiDialog::SaveMidiDialog(int actualConf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveMidiDialog)
{
    ui->setupUi(this);

    existingConfig = false;

    ui->saveListComboBox->clear();

    for (int _i = 0; _i < MAX_CONFIG_MIDI; _i++)
    {
        QString tempName;
        QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

        if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            midiQSettings.beginGroup("CONFIG_" + QString::number(_i + 1));
            if (midiQSettings.allKeys().contains("NameConfig"))
                tempName = "[MIDI CONF " + QString::number(_i + 1) + "] - " + midiQSettings.value("NameConfig").toString();
            else
                tempName = "[MIDI CONF " + QString::number(_i + 1) + "] - ";
            midiQSettings.endGroup();
        }
        else
            tempName = "[MIDI CONF " + QString::number(_i + 1) + "]";
        ui->saveListComboBox->addItem(tempName);
    }

    if (actualConf > 0)
        ui->saveListComboBox->setCurrentIndex(actualConf - 1);
    else
        ui->saveListComboBox->setCurrentIndex(0);
}

SaveMidiDialog::~SaveMidiDialog()
{
    delete ui;
}

void SaveMidiDialog::on_savePushButton_clicked()
{
    if (existingConfig == true)
    {
        if ((QMessageBox::information(this, tr("Configuration already exists"), tr("Configuration ") + QString::number(ui->saveListComboBox->currentIndex() + 1) + tr(" already exists."
                             "\nDo you want to overwrite it?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
        {
            emit saveConfigValidated(ui->saveListComboBox->currentIndex() + 1, ui->nameLineEdit->text());
            close();
        }
    }
    else
    {
        emit saveConfigValidated(ui->saveListComboBox->currentIndex() + 1, ui->nameLineEdit->text());
        close();
    }
}

void SaveMidiDialog::on_cancelPushButton_clicked()
{
    close();
}

void SaveMidiDialog::on_saveListComboBox_currentIndexChanged(int index)
{

    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(index + 1));
        if (midiQSettings.allKeys().contains("NameConfig"))
            ui->nameLineEdit->setText(midiQSettings.value("NameConfig").toString());
        midiQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

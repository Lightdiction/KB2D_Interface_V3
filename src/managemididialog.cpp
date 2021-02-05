#include "../inc/managemididialog.h"
#include "ui_managemididialog.h"

#define MAX_CONFIG_MIDI 128

ManageMidiDialog::ManageMidiDialog(int actualConf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageMidiDialog)
{
    ui->setupUi(this);

    existingConfig = false;

    UpdateConfBoxes();

    if (actualConf > 0)
    {
        ui->confAComboBox->setCurrentIndex(actualConf - 1);
        ui->confBComboBox->setCurrentIndex(actualConf - 1);
    }
    else
    {
        ui->confAComboBox->setCurrentIndex(0);
        ui->confBComboBox->setCurrentIndex(0);
    }
}

ManageMidiDialog::~ManageMidiDialog()
{
    delete ui;
}

void ManageMidiDialog::UpdateConfBoxes()
{
    int saveIndA = ui->confAComboBox->currentIndex();
    int saveIndB = ui->confBComboBox->currentIndex();

    ui->confAComboBox->clear();
    ui->confBComboBox->clear();

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
        ui->confAComboBox->addItem(tempName);
        ui->confBComboBox->addItem(tempName);
    }

    ui->confAComboBox->setCurrentIndex(saveIndA);
    ui->confBComboBox->setCurrentIndex(saveIndB);
}

//// Conf A Selection ////

void ManageMidiDialog::on_confAComboBox_currentIndexChanged(int index)
{

    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(index + 1));
        if (midiQSettings.allKeys().contains("NameConfig"))
            ui->renameLineEdit->setText(midiQSettings.value("NameConfig").toString());
        midiQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

//// ACTIONS On CONF ////

void ManageMidiDialog::on_deletePushButton_clicked()
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        if ((QMessageBox::information(this, tr("Remove Configuration ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                      tr("Are you sure you want to Remove CONFIG_") + QString::number(ui->confAComboBox->currentIndex() + 1) + "?", \
                                      QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
        {
            midiQSettings.remove("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            UpdateConfBoxes();
            QMessageBox::information(this, tr("Configuration removed"), "CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1) + tr(" has been correctly removed."));
        }
    }
    else
        QMessageBox::warning(this, tr("Conf does not exist"), tr("Cannot remove this configuration.\nThis configuration does not exist."));
}

void ManageMidiDialog::on_renamePushButton_clicked()
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        midiQSettings.setValue("NameConfig", ui->renameLineEdit->text());
        midiQSettings.endGroup();
        UpdateConfBoxes();
    }
    else
        QMessageBox::warning(this, tr("Conf does not exist"), tr("Cannot rename this configuration.\nThis configuration does not exist."));
}

void ManageMidiDialog::on_swapPushButton_clicked()
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = midiQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = midiQSettings.allKeys()[_i];
            qVar[_i] = midiQSettings.value(midiQSettings.allKeys()[_i]);
        }
        midiQSettings.endGroup();

        if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            int nKeysB = midiQSettings.allKeys().size();
            QString qStringB[nKeysB];
            QVariant qVarB[nKeysB];
            for (int _i = 0; _i < nKeysB; _i++)
            {
                qStringB[_i] = midiQSettings.allKeys()[_i];
                qVarB[_i] = midiQSettings.value(midiQSettings.allKeys()[_i]);
            }
            midiQSettings.endGroup();

            midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeysB; _i++)
            {
                midiQSettings.setValue(qStringB[_i], qVarB[_i]);
            }
            midiQSettings.endGroup();
            midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                midiQSettings.setValue(qString[_i], qVar[_i]);
            }
            midiQSettings.endGroup();
            UpdateConfBoxes();
        }
        else
            QMessageBox::warning(this, tr("Conf B does not exist"), tr("Cannot copy this configuration.\nThis configuration (B) does not exist."));
    }
    else
        QMessageBox::warning(this, tr("Conf A does not exist"), tr("Cannot copy this configuration.\nThis configuration (A) does not exist."));
}

void ManageMidiDialog::on_copyPushButton_clicked()
{
    QSettings midiQSettings("_MidiSettings.midcfg", QSettings::IniFormat);

    if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = midiQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = midiQSettings.allKeys()[_i];
            qVar[_i] = midiQSettings.value(midiQSettings.allKeys()[_i]);
        }
        midiQSettings.endGroup();

        if (midiQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            if ((QMessageBox::information(this, tr("Copy Configuration ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                          "CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1) + tr(" already exists, do you want to overwrite it?"), \
                                          QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
            {
                midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
                for (int _i = 0; _i < nKeys; _i++)
                {
                    midiQSettings.setValue(qString[_i], qVar[_i]);
                }
                midiQSettings.endGroup();
                UpdateConfBoxes();
            }
        }
        else
        {
            midiQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                midiQSettings.setValue(qString[_i], qVar[_i]);
            }
            midiQSettings.endGroup();
            UpdateConfBoxes();
        }
    }
    else
        QMessageBox::warning(this, tr("Conf A does not exist"), tr("Cannot copy this configuration.\nThis configuration (A) does not exist."));
}

//// Close ////

void ManageMidiDialog::on_closePushButton_clicked()
{
    emit updateNow();
    close();
}

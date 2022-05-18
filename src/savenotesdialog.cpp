#include "../inc/savenotesdialog.h"
#include "ui_savenotesdialog.h"

SaveNotesDialog::SaveNotesDialog(int actualPreset, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveNotesDialog)
{
    ui->setupUi(this);

    existingConfig = false;

    ui->saveListComboBox->clear();

    for (int _i = 0; _i < MAX_PRESETS_NOTES; _i++)
    {
        QString tempName;
        QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

        if (prstQSettings.childGroups().contains("PRST_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            prstQSettings.beginGroup("PRST_" + QString::number(_i + 1));
            tempName = "[PRST " + QString::number(_i + 1) + "] - " + prstQSettings.value("NamePreset", "").toString();
            prstQSettings.endGroup();
        }
        else
            tempName = "[PRST " + QString::number(_i + 1) + "]";
        ui->saveListComboBox->addItem(tempName);
    }
    if (actualPreset > 0)
        ui->saveListComboBox->setCurrentIndex(actualPreset - 1);
    else
        ui->saveListComboBox->setCurrentIndex(actualPreset);

    ui->custRadio->setChecked(true);
    ui->user1Radio->setChecked(true);
}

SaveNotesDialog::~SaveNotesDialog()
{
    delete ui;
}

void SaveNotesDialog::on_custRadio_toggled(bool checked)
{
    if (checked)
    {
        ui->saveListComboBox->setEnabled(true);
        ui->nameLabel->setEnabled(true);
        ui->nameLineEdit->setEnabled(true);
    }
    else
    {
        ui->saveListComboBox->setEnabled(false);
        ui->nameLabel->setEnabled(false);
        ui->nameLineEdit->setEnabled(false);
    }
}

void SaveNotesDialog::on_cancelPushButton_clicked()
{
    close();
}

void SaveNotesDialog::on_savePushButton_clicked()
{
    if (existingConfig && ui->custRadio->isChecked())
    {
        if ((QMessageBox::information(this, tr("Preset already exists"), tr("Preset ") + QString::number(ui->saveListComboBox->currentIndex() + 1) + tr(" already exists."
                             "\nDo you want to overwrite it?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
        {
            if (ui->user1Radio->isChecked())
                emit userSaved(1);
            else if (ui->user2Radio->isChecked())
                emit userSaved(2);
            else if (ui->user3Radio->isChecked())
                emit userSaved(3);
            else if (ui->custRadio->isChecked())
                emit presetSaved(ui->saveListComboBox->currentIndex() + 1, ui->nameLineEdit->text());

            close();
        }
    }
    else
    {
        if (ui->user1Radio->isChecked())
            emit userSaved(1);
        else if (ui->user2Radio->isChecked())
            emit userSaved(2);
        else if (ui->user3Radio->isChecked())
            emit userSaved(3);
        else if (ui->custRadio->isChecked())
            emit presetSaved(ui->saveListComboBox->currentIndex() + 1, ui->nameLineEdit->text());

        close();
    }
}

void SaveNotesDialog::on_saveListComboBox_currentIndexChanged(int index)
{
    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        prstQSettings.beginGroup("PRST_" + QString::number(index + 1));
        ui->nameLineEdit->setText(prstQSettings.value("NamePreset", "").toString());
        prstQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

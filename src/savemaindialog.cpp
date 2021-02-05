#include "../inc/savemaindialog.h"
#include "ui_savemaindialog.h"

SaveMainDialog::SaveMainDialog(int actualConf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveMainDialog)
{
    ui->setupUi(this);

    existingConfig = false;

    ui->saveListComboBox->clear();

    for (int _i = 0; _i < MAX_CONFIG_MAIN; _i++)
    {
        QString tempName;
        QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(_i + 1), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(_i + 1));
            if (mainQSettings.allKeys().contains("NameConfig"))
                tempName = "[MAIN CONF " + QString::number(_i + 1) + "] - " + mainQSettings.value("NameConfig").toString();
            else
                tempName = "[MAIN CONF " + QString::number(_i + 1) + "] - ";
            mainQSettings.endGroup();
        }
        else
            tempName = "[MAIN CONF " + QString::number(_i + 1) + "]";
        ui->saveListComboBox->addItem(tempName);
    }

    if (actualConf > 0)
        ui->saveListComboBox->setCurrentIndex(actualConf - 1);
    else
        ui->saveListComboBox->setCurrentIndex(0);
}

SaveMainDialog::~SaveMainDialog()
{
    delete ui;
}

void SaveMainDialog::on_savePushButton_clicked()
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

void SaveMainDialog::on_cancelPushButton_clicked()
{
    close();
}

void SaveMainDialog::on_saveListComboBox_currentIndexChanged(int index)
{

    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        mainQSettings.beginGroup("CONFIG_" + QString::number(index + 1));
        if (mainQSettings.allKeys().contains("NameConfig"))
            ui->nameLineEdit->setText(mainQSettings.value("NameConfig").toString());
        mainQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

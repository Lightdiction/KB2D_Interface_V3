#include "../inc/managemaindialog.h"
#include "ui_managemaindialog.h"

#define MAX_CONFIG_MAIN 128

ManageMainDialog::ManageMainDialog(int actualConf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageMainDialog)
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

ManageMainDialog::~ManageMainDialog()
{
    delete ui;
}

void ManageMainDialog::UpdateConfBoxes()
{
    int saveIndA = ui->confAComboBox->currentIndex();
    int saveIndB = ui->confBComboBox->currentIndex();

    ui->confAComboBox->clear();
    ui->confBComboBox->clear();

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
        ui->confAComboBox->addItem(tempName);
        ui->confBComboBox->addItem(tempName);
    }

    ui->confAComboBox->setCurrentIndex(saveIndA);
    ui->confBComboBox->setCurrentIndex(saveIndB);
}

//// Conf A Selection ////

void ManageMainDialog::on_confAComboBox_currentIndexChanged(int index)
{

    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        mainQSettings.beginGroup("CONFIG_" + QString::number(index + 1));
        if (mainQSettings.allKeys().contains("NameConfig"))
            ui->renameLineEdit->setText(mainQSettings.value("NameConfig").toString());
        mainQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

//// ACTIONS On CONF ////

void ManageMainDialog::on_deletePushButton_clicked()
{
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        if ((QMessageBox::information(this, tr("Remove Configuration ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                      tr("Are you sure you want to Remove CONFIG_") + QString::number(ui->confAComboBox->currentIndex() + 1) + "?", \
                                      QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
        {
            mainQSettings.remove("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            UpdateConfBoxes();
            QMessageBox::information(this, tr("Configuration removed"), "CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1) + tr(" has been correctly removed."));
        }
    }
    else
        QMessageBox::warning(this, tr("Conf does not exist"), tr("Cannot remove this configuration.\nThis configuration does not exist."));
}

void ManageMainDialog::on_renamePushButton_clicked()
{
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        mainQSettings.setValue("NameConfig", ui->renameLineEdit->text());
        mainQSettings.endGroup();
        UpdateConfBoxes();
    }
    else
        QMessageBox::warning(this, tr("Conf does not exist"), tr("Cannot rename this configuration.\nThis configuration does not exist."));
}

void ManageMainDialog::on_swapPushButton_clicked()
{
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = mainQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = mainQSettings.allKeys()[_i];
            qVar[_i] = mainQSettings.value(mainQSettings.allKeys()[_i]);
        }
        mainQSettings.endGroup();

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            int nKeysB = mainQSettings.allKeys().size();
            QString qStringB[nKeysB];
            QVariant qVarB[nKeysB];
            for (int _i = 0; _i < nKeysB; _i++)
            {
                qStringB[_i] = mainQSettings.allKeys()[_i];
                qVarB[_i] = mainQSettings.value(mainQSettings.allKeys()[_i]);
            }
            mainQSettings.endGroup();

            mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeysB; _i++)
            {
                mainQSettings.setValue(qStringB[_i], qVarB[_i]);
            }
            mainQSettings.endGroup();
            mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                mainQSettings.setValue(qString[_i], qVar[_i]);
            }
            mainQSettings.endGroup();
            UpdateConfBoxes();
        }
        else
            QMessageBox::warning(this, tr("Conf B does not exist"), tr("Cannot copy this configuration.\nThis configuration (B) does not exist."));
    }
    else
        QMessageBox::warning(this, tr("Conf A does not exist"), tr("Cannot copy this configuration.\nThis configuration (A) does not exist."));
}

void ManageMainDialog::on_copyPushButton_clicked()
{
    QSettings mainQSettings("_MainSettings.maicfg", QSettings::IniFormat);

    if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = mainQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = mainQSettings.allKeys()[_i];
            qVar[_i] = mainQSettings.value(mainQSettings.allKeys()[_i]);
        }
        mainQSettings.endGroup();

        if (mainQSettings.childGroups().contains("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            if ((QMessageBox::information(this, tr("Copy Configuration ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                          "CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1) + tr(" already exists, do you want to overwrite it?"), \
                                          QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
            {
                mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
                for (int _i = 0; _i < nKeys; _i++)
                {
                    mainQSettings.setValue(qString[_i], qVar[_i]);
                }
                mainQSettings.endGroup();
                UpdateConfBoxes();
            }
        }
        else
        {
            mainQSettings.beginGroup("CONFIG_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                mainQSettings.setValue(qString[_i], qVar[_i]);
            }
            mainQSettings.endGroup();
            UpdateConfBoxes();
        }
    }
    else
        QMessageBox::warning(this, tr("Conf A does not exist"), tr("Cannot copy this configuration.\nThis configuration (A) does not exist."));
}

//// Close ////

void ManageMainDialog::on_closePushButton_clicked()
{
    emit updateNow();
    close();
}

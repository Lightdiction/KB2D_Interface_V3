#include "../inc/managenotesdialog.h"
#include "ui_managenotesdialog.h"

ManageNotesDialog::ManageNotesDialog(int actualPreset, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageNotesDialog)
{
    ui->setupUi(this);

    existingConfig = false;

    updateConfBoxes();

    if (actualPreset > 0)
    {
        ui->confAComboBox->setCurrentIndex(actualPreset - 1);
        ui->confBComboBox->setCurrentIndex(actualPreset - 1);
    }
    else
    {
        ui->confAComboBox->setCurrentIndex(0);
        ui->confBComboBox->setCurrentIndex(0);
    }
}

ManageNotesDialog::~ManageNotesDialog()
{
    delete ui;
}

void ManageNotesDialog::updateConfBoxes()
{
    int saveIndA = ui->confAComboBox->currentIndex();
    int saveIndB = ui->confBComboBox->currentIndex();

    ui->confAComboBox->clear();
    ui->confBComboBox->clear();

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
        ui->confAComboBox->addItem(tempName);
        ui->confBComboBox->addItem(tempName);
    }

    ui->confAComboBox->setCurrentIndex(saveIndA);
    ui->confBComboBox->setCurrentIndex(saveIndB);
}

//// Conf A Selection ////

void ManageNotesDialog::on_confAComboBox_currentIndexChanged(int index)
{

    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(index + 1), Qt::CaseInsensitive))
    {
        prstQSettings.beginGroup("PRST_" + QString::number(index + 1));
        if (prstQSettings.allKeys().contains("NamePreset"))
            ui->renameLineEdit->setText(prstQSettings.value("NamePreset").toString());
        prstQSettings.endGroup();

        existingConfig = true;
    }
    else
        existingConfig = false;
}

//// ACTIONS On CONF ////

void ManageNotesDialog::on_deletePushButton_clicked()
{
    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        if ((QMessageBox::information(this, tr("Remove Preset ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                      tr("Are you sure you want to Remove PRST_") + QString::number(ui->confAComboBox->currentIndex() + 1) + "?", \
                                      QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
        {
            prstQSettings.remove("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            updateConfBoxes();
            QMessageBox::information(this, tr("Preset removed"), "PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1) + tr(" has been correctly removed."));
        }
    }
    else
        QMessageBox::warning(this, tr("Preset does not exist"), tr("Cannot remove this preset.\nThis preset does not exist."));
}

void ManageNotesDialog::on_renamePushButton_clicked()
{
    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        prstQSettings.beginGroup("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        prstQSettings.setValue("NamePreset", ui->renameLineEdit->text());
        prstQSettings.endGroup();
        updateConfBoxes();
    }
    else
        QMessageBox::warning(this, tr("Preset does not exist"), tr("Cannot rename this preset.\nThis preset does not exist."));
}

void ManageNotesDialog::on_swapPushButton_clicked()
{
    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        prstQSettings.beginGroup("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = prstQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = prstQSettings.allKeys().at(_i);
            qVar[_i] = prstQSettings.value(prstQSettings.allKeys().at(_i));
        }
        prstQSettings.endGroup();

        if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            prstQSettings.beginGroup("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            int nKeysB = prstQSettings.allKeys().size();
            QString qStringB[nKeysB];
            QVariant qVarB[nKeysB];
            for (int _i = 0; _i < nKeysB; _i++)
            {
                qStringB[_i] = prstQSettings.allKeys().at(_i);
                qVarB[_i] = prstQSettings.value(prstQSettings.allKeys().at(_i));
            }
            prstQSettings.endGroup();

            prstQSettings.beginGroup("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeysB; _i++)
            {
                prstQSettings.setValue(qStringB[_i], qVarB[_i]);
            }
            prstQSettings.endGroup();
            prstQSettings.beginGroup("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                prstQSettings.setValue(qString[_i], qVar[_i]);
            }
            prstQSettings.endGroup();
            updateConfBoxes();
        }
        else
            QMessageBox::warning(this, tr("Preset B does not exist"), tr("Cannot copy this preset.\nThis preset (B) does not exist."));
    }
    else
        QMessageBox::warning(this, tr("Preset A does not exist"), tr("Cannot copy this preset.\nThis preset (A) does not exist."));
}

void ManageNotesDialog::on_copyPushButton_clicked()
{
    QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

    if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1), Qt::CaseInsensitive))
    {
        prstQSettings.beginGroup("PRST_" + QString::number(ui->confAComboBox->currentIndex() + 1));
        int nKeys = prstQSettings.allKeys().size();
        QString qString[nKeys];
        QVariant qVar[nKeys];
        for (int _i = 0; _i < nKeys; _i++)
        {
            qString[_i] = prstQSettings.allKeys().at(_i);
            qVar[_i] = prstQSettings.value(prstQSettings.allKeys().at(_i));
        }
        prstQSettings.endGroup();

        if (prstQSettings.childGroups().contains("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1), Qt::CaseInsensitive))
        {
            if ((QMessageBox::information(this, tr("Copy Preset ") + QString::number(ui->confAComboBox->currentIndex() + 1), \
                                          "PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1) + tr(" already exists, do you want to overwrite it?"), \
                                          QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) != QMessageBox::Cancel)
            {
                prstQSettings.beginGroup("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1));
                for (int _i = 0; _i < nKeys; _i++)
                {
                    prstQSettings.setValue(qString[_i], qVar[_i]);
                }
                prstQSettings.endGroup();
                updateConfBoxes();
            }
        }
        else
        {
            prstQSettings.beginGroup("PRST_" + QString::number(ui->confBComboBox->currentIndex() + 1));
            for (int _i = 0; _i < nKeys; _i++)
            {
                prstQSettings.setValue(qString[_i], qVar[_i]);
            }
            prstQSettings.endGroup();
            updateConfBoxes();
        }
    }
    else
        QMessageBox::warning(this, tr("Preset A does not exist"), tr("Cannot copy this preset.\nThis preset (A) does not exist."));
}

//// Close ////

void ManageNotesDialog::on_closePushButton_clicked()
{
    emit updateNow();
    close();
}


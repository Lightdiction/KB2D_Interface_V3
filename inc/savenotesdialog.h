#ifndef SAVENOTESDIALOG_H
#define SAVENOTESDIALOG_H

#include "inc/utils.h"
#include <QDialog>
#include <QSettings>
#include <QMessageBox>


namespace Ui {
class SaveNotesDialog;
}

class SaveNotesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveNotesDialog(int actualPreset, QWidget *parent = nullptr);
    ~SaveNotesDialog();

signals:
    void presetSaved(int indPreset, QString namePreset);
    void userSaved(int numUser);

private slots:

    void on_custRadio_toggled(bool checked);

    void on_cancelPushButton_clicked();
    void on_savePushButton_clicked();

    void on_saveListComboBox_currentIndexChanged(int index);

private:
    Ui::SaveNotesDialog *ui;

    bool existingConfig;
};

#endif // SAVENOTESDIALOG_H

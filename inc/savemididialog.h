#ifndef SAVEMIDIDIALOG_H
#define SAVEMIDIDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

#define MAX_CONFIG_MIDI 128

namespace Ui {
class SaveMidiDialog;
}

class SaveMidiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveMidiDialog(int actualConf, QWidget *parent = nullptr);
    ~SaveMidiDialog();

signals:
    void saveConfigValidated(int numConfig, QString nameConfig);

private slots:
    void on_savePushButton_clicked();
    void on_cancelPushButton_clicked();

    void on_saveListComboBox_currentIndexChanged(int index);

private:
    Ui::SaveMidiDialog *ui;

    bool existingConfig;
};

#endif // SAVEMIDIDIALOG_H

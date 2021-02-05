#ifndef SAVEMAINDIALOG_H
#define SAVEMAINDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

#define MAX_CONFIG_MAIN 128

namespace Ui {
class SaveMainDialog;
}

class SaveMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveMainDialog(int actualConf, QWidget *parent = nullptr);
    ~SaveMainDialog();

signals:
    void saveConfigValidated(int numConfig, QString nameConfig);

private slots:
    void on_savePushButton_clicked();
    void on_cancelPushButton_clicked();

    void on_saveListComboBox_currentIndexChanged(int index);

private:
    Ui::SaveMainDialog *ui;

    bool existingConfig;
};

#endif // SAVEMAINDIALOG_H

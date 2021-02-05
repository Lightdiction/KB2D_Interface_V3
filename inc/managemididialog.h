#ifndef MANAGEMIDIDIALOG_H
#define MANAGEMIDIDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class ManageMidiDialog;
}

class ManageMidiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageMidiDialog(int actualConf, QWidget *parent = nullptr);
    ~ManageMidiDialog();

    void UpdateConfBoxes();

signals:
    void updateNow();

private slots:
    void on_closePushButton_clicked();
    void on_deletePushButton_clicked();
    void on_renamePushButton_clicked();
    void on_swapPushButton_clicked();
    void on_copyPushButton_clicked();

    void on_confAComboBox_currentIndexChanged(int index);

private:
    Ui::ManageMidiDialog *ui;

    bool existingConfig;
};

#endif // MANAGEMIDIDIALOG_H

#ifndef MANAGEMAINDIALOG_H
#define MANAGEMAINDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class ManageMainDialog;
}

class ManageMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageMainDialog(int actualConf, QWidget *parent = nullptr);
    ~ManageMainDialog();

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
    void UpdateConfBoxes();

    Ui::ManageMainDialog *ui;
    bool existingConfig;
};

#endif // MANAGEMAINDIALOG_H

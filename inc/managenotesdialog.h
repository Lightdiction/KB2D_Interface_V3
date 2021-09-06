#ifndef MANAGENOTESDIALOG_H
#define MANAGENOTESDIALOG_H

#include "inc/utils.h"
#include <QDialog>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class ManageNotesDialog;
}

class ManageNotesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageNotesDialog(int actualPreset, QWidget *parent = nullptr);
    ~ManageNotesDialog();

signals:
    void updateNow(void);

private slots:
    void on_closePushButton_clicked();
    void on_copyPushButton_clicked();
    void on_swapPushButton_clicked();
    void on_renamePushButton_clicked();
    void on_deletePushButton_clicked();

    void on_confAComboBox_currentIndexChanged(int index);

private:
    void updateConfBoxes();

    Ui::ManageNotesDialog *ui;
    bool existingConfig;
};

#endif // MANAGENOTESDIALOG_H

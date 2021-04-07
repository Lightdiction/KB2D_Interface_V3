#ifndef VERSIONDIALOG_H
#define VERSIONDIALOG_H

#include "mainwindow.h"

#define LAST_VERSION    313

namespace Ui {
class VersionDialog;
}

class VersionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VersionDialog(QWidget *parent = nullptr);
    ~VersionDialog();

private slots:
    void on_closePushButton_clicked();

private:
    Ui::VersionDialog *ui;
};

#endif // VERSIONDIALOG_H

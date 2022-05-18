#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** About Dialog **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Really.
 * 2 Files, just for that About Dialog...
 *
 * =================================================
 */

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private slots:
    void on_closeButton_clicked();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H

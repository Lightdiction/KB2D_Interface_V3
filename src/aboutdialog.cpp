
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** About Dialog **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Just shows the About Dialog
 *
 * =================================================
 */

#include "../inc/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_closeButton_clicked()
{
    this->close();
}

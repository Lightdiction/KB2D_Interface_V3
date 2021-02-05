#include "inc/versiondialog.h"
#include "ui_versiondialog.h"

VersionDialog::VersionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionDialog)
{
    QFile verNoteFile(tr("VersionNotes.txt"));

    ui->setupUi(this);

    if (!verNoteFile.open(QFile::ReadOnly | QFile::Text))
        SendError(this, tr("Cannot open VersionNotes.txt") , VersionDialog_VersionDialog);
    else
    {
       // QTextStream fileContent(&verNoteFile);

        ui->label->setText(verNoteFile.readAll());
        ui->label->setWordWrap(true);
    }
}

VersionDialog::~VersionDialog()
{
    delete ui;
}

void VersionDialog::on_closePushButton_clicked()
{
    this->close();
}

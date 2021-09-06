#ifndef MIDIDEVICES_H
#define MIDIDEVICES_H

#include <QDialog>

namespace Ui {
class MidiDevices;
}

class MidiDevices : public QDialog
{
    Q_OBJECT

public:
    explicit MidiDevices(QWidget *parent);
    ~MidiDevices();

signals:
    void midiDevicesUpdated(bool forceDefault, QString kbInName, QString kbOutName, QString extInName, QString extOutName, QString throughIn, QString throughOut);

private slots:
    void closeEvent(QCloseEvent* event) override;

    void kbInChanged(int index);
    void kbOutChanged(int index);
    void extInChanged(int index);
    void extOutChanged(int index);
    void throughInChanged(int index);
    void throughOutChanged(int index);

    void on_validateButton_clicked();
    void on_cancelButton_clicked();
    void updateAllCombos();

private:
    Ui::MidiDevices *ui;

    QWidget* parentPtr;

    QString saveNameKbIn;
    QString saveNameKbOut;
    QString saveNameExtIn;
    QString saveNameExtOut;
    QString saveNameThroughIn;
    QString saveNameThroughOut;

    bool accept = false;
};

#endif // MIDIDEVICES_H

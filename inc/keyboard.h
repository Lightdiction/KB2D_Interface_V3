#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include "grnotes.h"
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <QApplication>




/*
 * ===================
 * Class KeyboardKey
 * ===================
 */
class KeyboardKey : public QPushButton
{
    Q_OBJECT

public:
    KeyboardKey(int width, QString name = "",  QString color = "#EEE", QString hoverColor = "#FBB", QString clickColor = "#BBB", QWidget *parent = nullptr);
    ~KeyboardKey();
};


/*
 * ===================
 * Class Keyboard
 * ===================
 */
class Keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit Keyboard(QGridLayout* mainGridLayout, QWidget *parent = nullptr);
    explicit Keyboard(QGridLayout* mainGridLayout, int initK, int nKey, QWidget *parent = nullptr);
    ~Keyboard();

    void refreshKeyboard();
    void refreshKeyboard(int initialNote, int numNotes);
    void updateNotesOnKeyboard(QVector <int> &listNotes);

    void setNextAssign(int nIndex);
    int getNextAssign();

signals:
    void keyClicked(int indexKey);

private slots:

private:
    QGridLayout* globKbLayout = nullptr;

    QGridLayout* whiteKeysLayout = nullptr;
    QGridLayout* blackKeysLayout = nullptr;

    KeyboardKey* noteKeys[Note_Number] = {nullptr};

    // Label Display for current notes
    QVector <QLabel*> keyLabel;
    QVector <int> actualNotes;
    QVector <int> blackKeyList;

    int saveInitialKey = 0;
    int saveNumKeys = 60;

    int nextAssign = -1;

};

#endif // KEYBOARD_H

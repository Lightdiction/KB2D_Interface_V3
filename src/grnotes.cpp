
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Gr Notes **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * All functions related to Notes selections
 * (Combo Box)
 * Also buttons and functions associated to notes:
 * - Invert
 * - Test Note
 * - MIDI Mode (Notes ON/OFF | PITCH | CC)
 * (2nd Tab)
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "../inc/comhw.h"
#include "../inc/grnotes.h"

#include "../inc/savenotesdialog.h"
#include "../inc/managenotesdialog.h"


static QString NameMidiVars[Val_NumVars] = {
QObject::tr("Keyboard"),
QObject::tr("Combos"),
QObject::tr("Position"),
QObject::tr("Height"),
QObject::tr("Width"),
QObject::tr("Glide")};


QString ListNameNotes[Note_Number] = { \
    _TR("C -1"), _TR("C# -1"), _TR("D -1"), _TR("D# -1"), _TR("E -1"), _TR("F -1"), _TR("F# -1"), _TR("G -1"), _TR("G# -1"), _TR("A -1"), _TR("A# -1"), _TR("B -1"), \
    _TR("C 0"), _TR("C# 0"), _TR("D 0"), _TR("D# 0"), _TR("E 0"), _TR("F 0"), _TR("F# 0"), _TR("G 0"), _TR("G# 0"), _TR("A 0"), _TR("A# 0"), _TR("B 0"), \
    _TR("C 1"), _TR("C# 1"), _TR("D 1"), _TR("D# 1"), _TR("E 1"), _TR("F 1"), _TR("F# 1"), _TR("G 1"), _TR("G# 1"), _TR("A 1"), _TR("A# 1"), _TR("B 1"), \
    _TR("C 2"), _TR("C# 2"), _TR("D 2"), _TR("D# 2"), _TR("E 2"), _TR("F 2"), _TR("F# 2"), _TR("G 2"), _TR("G# 2"), _TR("A 2"), _TR("A# 2"), _TR("B 2"), \
    _TR("C 3"), _TR("C# 3"), _TR("D 3"), _TR("D# 3"), _TR("E 3"), _TR("F 3"), _TR("F# 3"), _TR("G 3"), _TR("G# 3"), _TR("A 3"), _TR("A# 3"), _TR("B 3"), \
    _TR("C 4"), _TR("C# 4"), _TR("D 4"), _TR("D# 4"), _TR("E 4"), _TR("F 4"), _TR("F# 4"), _TR("G 4"), _TR("G# 4"), _TR("A 4"), _TR("A# 4"), _TR("B 4"), \
    _TR("C 5"), _TR("C# 5"), _TR("D 5"), _TR("D# 5"), _TR("E 5"), _TR("F 5"), _TR("F# 5"), _TR("G 5"), _TR("G# 5"), _TR("A 5"), _TR("A# 5"), _TR("B 5"), \
    _TR("C 6"), _TR("C# 6"), _TR("D 6"), _TR("D# 6"), _TR("E 6"), _TR("F 6"), _TR("F# 6"), _TR("G 6"), _TR("G# 6"), _TR("A 6"), _TR("A# 6"), _TR("B 6"), \
    _TR("C 7"), _TR("C# 7"), _TR("D 7"), _TR("D# 7"), _TR("E 7"), _TR("F 7"), _TR("F# 7"), _TR("G 7"), _TR("G# 7"), _TR("A 7"), _TR("A# 7"), _TR("B 7"), \
    _TR("C 8"), _TR("C# 8"), _TR("D 8"), _TR("D# 8"), _TR("E 8"), _TR("F 8"), _TR("F# 8"), _TR("G 8"), _TR("G# 8"), _TR("A 8"), _TR("A# 8"), _TR("B 8"), \
    _TR("C 9"), _TR("C# 9"), _TR("D 9"), _TR("D# 9"), _TR("E 9"), _TR("F 9"), _TR("F# 9"), _TR("G 9")};


/////////////////////////////////////
////////////// KEYBOARD /////////////
/////////////////////////////////////


void MainWindow::on_nKeysSpinBox_editingFinished()
{
    static int nKeysSave = 0;
    if (!updateInProgress && keyboard[Ports_Midi1] && (ui->nKeysSpinBox->value() != nKeysSave))
    {
        nKeysSave = ui->nKeysSpinBox->value();
        keyboard[Ports_Midi1]->refreshKeyboard(ui->startKeyComboBox->currentIndex(), nKeysSave);
    }
}

void MainWindow::on_startKeyComboBox_currentIndexChanged(int index)
{
    static int startKeySave = 0;
    if (!updateInProgress && keyboard[Ports_Midi1] && (index != startKeySave))
    {
        startKeySave = index;
        keyboard[Ports_Midi1]->refreshKeyboard(index, ui->nKeysSpinBox->value());
    }
}

void MainWindow::on_sendOnClickCheckBox_toggled(bool checked)
{
    (void)checked;
    if (!updateInProgress && keyboard[Ports_Midi1])
        keyboard[Ports_Midi1]->refreshKeyboard(ui->startKeyComboBox->currentIndex(), ui->nKeysSpinBox->value());
}

void MainWindow::on_nKeysSpinBox_2_editingFinished()
{
    static int nKeysSave = 0;
    if (!updateInProgress && keyboard[Ports_Midi3] && (ui->nKeysSpinBox_2->value() != nKeysSave))
    {
        nKeysSave = ui->nKeysSpinBox_2->value();
        keyboard[Ports_Midi3]->refreshKeyboard(ui->startKeyComboBox_2->currentIndex(), nKeysSave);
    }
}

void MainWindow::on_startKeyComboBox_2_currentIndexChanged(int index)
{
    static int startKeySave = 0;
    if (!updateInProgress && keyboard[Ports_Midi3] && (index != startKeySave))
    {
        startKeySave = index;
        keyboard[Ports_Midi3]->refreshKeyboard(index, ui->nKeysSpinBox_2->value());
    }
}

void MainWindow::on_sendOnClickCheckBox_2_stateChanged(int arg1)
{
    (void)arg1;
    if (!updateInProgress && keyboard[Ports_Midi3])
        keyboard[Ports_Midi3]->refreshKeyboard(ui->startKeyComboBox_2->currentIndex(), ui->nKeysSpinBox_2->value());
}

void MainWindow::on_nKeysSpinBox_3_editingFinished()
{
    static int nKeysSave = 0;
    if (!updateInProgress && keyboard[Ports_Midi4] && (ui->nKeysSpinBox_3->value() != nKeysSave))
    {
        nKeysSave = ui->nKeysSpinBox_3->value();
        keyboard[Ports_Midi4]->refreshKeyboard(ui->startKeyComboBox_3->currentIndex(), nKeysSave);
    }
}

void MainWindow::on_startKeyComboBox_3_currentIndexChanged(int index)
{
    static int startKeySave = 0;
    if (!updateInProgress && keyboard[Ports_Midi4] && (index != startKeySave))
    {
        startKeySave = index;
        keyboard[Ports_Midi4]->refreshKeyboard(index, ui->nKeysSpinBox_3->value());
    }
}

void MainWindow::on_sendOnClickCheckBox_3_stateChanged(int arg1)
{
    (void)arg1;
    if (!updateInProgress && keyboard[Ports_Midi4])
        keyboard[Ports_Midi4]->refreshKeyboard(ui->startKeyComboBox_3->currentIndex(), ui->nKeysSpinBox_3->value());
}

/*
 * =================================
 * Assign a Note to a Beam
 * When we click on a Key
 * =================================
 */
void MainWindow::assignNoteToKey(int portNum, int noteToAssign)
{
    int beamToRead = 1;
    bool ok = false;
    int _MidiSetNote[3] = {MIDI_SETMIDINOTE0};

    int saveNBeamsX = kbDev.checkFeedback(Check_nBeamsX);

    if (noteToAssign == -1)
    {
        QVector <int> listN;
        for (int _i = 0 ; _i < saveNBeamsX ; _i++)
        {
            int tempNote = kbDev.checkFeedback(Check_NoteToPlay0 + (16 * portNum) + _i);
            if (tempNote >= 0)
                listN.append(tempNote);
        }

        if (!updateInProgress && keyboard[portNum])
        {
            keyboard[portNum]->updateNotesOnKeyboard(listN);
        }
    }
    else
    {
        if (ui->sendOnClickCheckBox->isChecked())
            kbDev.sendCom(MIDI_FORCESEND + noteToAssign);

        if (keyboard[portNum] && (keyboard[portNum]->getNextAssign() >= 0))
        {
            ok = true;
            beamToRead = keyboard[portNum]->getNextAssign() + 1;
            if (assignAllActivated[portNum] && (beamToRead < MAX_NBEAMS) && assignButton[portNum][beamToRead] && assignButton[portNum][beamToRead]->isVisible())
                keyboard[portNum]->setNextAssign(beamToRead);
            else
            {
                keyboard[portNum]->setNextAssign(-1);
                assignAllActivated[portNum] = false;
            }
            repaintAssignButtons();
        }
        else
            beamToRead = QInputDialog::getInt(this, tr("Beam To Assign ?"), tr("Enter the index of the beam to which you want to assign this note (") + ListNameNotes[noteToAssign] + \
                                          tr(").\n\n~ Beam to assign? (From 1 to ") + QString::number(saveNBeamsX) + ")", 1, 1, saveNBeamsX, 1, &ok);

        if (ok)
        {
            kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * portNum) + beamToRead - 1, _MidiSetNote[2] + (char)noteToAssign);
            if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * portNum) + beamToRead - 1) != noteToAssign)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_Assign_1_C);

            // Update Z0 ComboBox too
            bool saveUpdate = updateInProgress;
            updateInProgress = true;
            Z0_ComboBox[portNum][beamToRead - 1]->setCurrentIndex(noteToAssign);
            updateInProgress = saveUpdate;

            // Update Keyboard
            QVector <int> listN;
            for (int _i = 0 ; _i < saveNBeamsX ; _i++)
            {
                int tempNote = kbDev.checkFeedback(Check_NoteToPlay0 + (16 * portNum) + _i);
                if (tempNote >= 0)
                    listN.append(tempNote);
            }

            if (!updateInProgress && keyboard[portNum])
            {
                keyboard[portNum]->updateNotesOnKeyboard(listN);
            }
        }
    }
}

/////////////////////////////////
/// NOTES
/////////////////////////////////



void MainWindow::initializeMidiCombos()
{
    bool saveInP = updateInProgress;
    updateInProgress = true;
    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0; _j < ModeActiv_NumModes; _j++)
        {
            for (int _k = 0; _k < ValSelection_NumCombo; _k++)
            {
                if (midiSelection_Combo[_i][_j][_k])
                {
                    midiSelection_Combo[_i][_j][_k]->clear();
                    if ((_k == ValSelection_CtrlNotes) || (_k == ValSelection_ValVel))
                    {
                        for (int _l = 0; _l < Val_NumVars; _l++)
                            midiSelection_Combo[_i][_j][_k]->addItem(NameMidiVars[_l]);
                        for (int _l = 0; _l < 128; _l++)
                            midiSelection_Combo[_i][_j][_k]->addItem(QString::number(_l));
                    }
                    else
                    {
                        midiSelection_Combo[_i][_j][_k]->addItem("N° beam");
                        midiSelection_Combo[_i][_j][_k]->addItem("- NA -");
                        for (int _l = 1; _l <= 16; _l++)
                            midiSelection_Combo[_i][_j][_k]->addItem(QString::number(_l));
                    }
                }
            }
        }
    }
    QApplication::processEvents();
    updateInProgress = saveInP;
}

void MainWindow::initializeZ0Combos()
{
    bool saveInP = updateInProgress;
    updateInProgress = true;
    for (int _i = 0; _i < Ports_Num; _i++)
    {
        for (int _j = 0; _j < MAX_NBEAMS; _j++)
        {
            if (Z0_ComboBox[_i][_j])
            {
                Z0_ComboBox[_i][_j]->clear();
                for (int _k = 0; _k < 128; _k++)
                    Z0_ComboBox[_i][_j]->addItem(QString::number(_k));
            }
        }
    }
    QApplication::processEvents();
    updateInProgress = saveInP;
}

void MainWindow::updateMidiModeWidgets(int nPort)
{
    bool saveInP = updateInProgress;
    updateInProgress = true;
    if (nPort == Ports_Midi1)
    {
        ui->ChanNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteChan));
        ui->ChanCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Chan));
        ui->ChanCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Chan));

        int chkVarUse = kbDev.checkFeedback(Check_CheckVarUse);
        ui->NoteNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteNote) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteNote) / VarUse_NoteNote));
        ui->VelNoteComboBox->setCurrentIndex(kbDev.checkFeedback(Check_NoteVel) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteVel) / VarUse_NoteVel));
        ui->ControlCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Ctrl) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Ctrl) / VarUse_CC1Ctrl));
        ui->ValCC1ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC1Val) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Val) / VarUse_CC1Val));
        ui->ControlCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Ctrl) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Ctrl) / VarUse_CC2Ctrl));
        ui->ValCC2ComboBox->setCurrentIndex(kbDev.checkFeedback(Check_CC2Val) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Val) / VarUse_CC2Val));

        QApplication::processEvents();
        setEnableGroup(Group_Enable, false, true);

        if ((((ui->NoteNoteComboBox->currentIndex() == Val_Keyboard) || (ui->VelNoteComboBox->currentIndex() == Val_Keyboard)) && \
             (enabState[Ports_Midi1] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox->currentIndex() == Val_Keyboard) || (ui->ValCC1ComboBox->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox->currentIndex() == Val_Keyboard) || (ui->ValCC2ComboBox->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesScroll, true);
            setEnableGroup(Group_KeyboardSetWidget, true);
            setEnableGroup(Group_NotesSetWidget, true);
            setEnableGroup(Group_Assign, true);
            setEnableGroup(Group_Enable, true);
        }
        else
        {
            setEnableGroup(Group_NotesScroll, false, true);
            setEnableGroup(Group_KeyboardSetWidget, false, true);
            setEnableGroup(Group_NotesSetWidget, false, true);
            setEnableGroup(Group_Assign, false, true);
        }
        if ((((ui->NoteNoteComboBox->currentIndex() == Val_Combos) || (ui->VelNoteComboBox->currentIndex() == Val_Combos)) && \
             (enabState[Ports_Midi1] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox->currentIndex() == Val_Combos) || (ui->ValCC1ComboBox->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox->currentIndex() == Val_Combos) || (ui->ValCC2ComboBox->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesParam, true);
            setEnableGroup(Group_Enable, true);
        }
        else
        {
            setEnableGroup(Group_NotesParam, false, true);
        }
    }
    else if (nPort == Ports_Midi3)
    {
        ui->ChanNoteComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_NoteChan_3P));
        ui->ChanCC1ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC1Chan_3P));
        ui->ChanCC2ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC2Chan_3P));

        int chkVarUse = kbDev.checkFeedback(Check_CheckVarUse_3P);
        ui->NoteNoteComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_NoteNote_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteNote) / VarUse_NoteNote));
        ui->VelNoteComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_NoteVel_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteVel) / VarUse_NoteVel));
        ui->ControlCC1ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC1Ctrl_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Ctrl) / VarUse_CC1Ctrl));
        ui->ValCC1ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC1Val_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Val) / VarUse_CC1Val));
        ui->ControlCC2ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC2Ctrl_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Ctrl) / VarUse_CC2Ctrl));
        ui->ValCC2ComboBox_2->setCurrentIndex(kbDev.checkFeedback(Check_CC2Val_3P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Val) / VarUse_CC2Val));

        QApplication::processEvents();
        setEnableGroup(Group_Enable_2, false, true);

        if ((((ui->NoteNoteComboBox_2->currentIndex() == Val_Keyboard) || (ui->VelNoteComboBox_2->currentIndex() == Val_Keyboard)) && \
             (enabState[Ports_Midi3] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox_2->currentIndex() == Val_Keyboard) || (ui->ValCC1ComboBox_2->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox_2->currentIndex() == Val_Keyboard) || (ui->ValCC2ComboBox_2->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesScroll_2, true);
            setEnableGroup(Group_KeyboardSetWidget_2, true);
            setEnableGroup(Group_NotesSetWidget_2, true);
            setEnableGroup(Group_Assign_2, true);
            setEnableGroup(Group_Enable_2, true);
        }
        else
        {
            setEnableGroup(Group_NotesScroll_2, false, true);
            setEnableGroup(Group_KeyboardSetWidget_2, false, true);
            setEnableGroup(Group_NotesSetWidget_2, false, true);
            setEnableGroup(Group_Assign_2, false, true);
        }
        if ((((ui->NoteNoteComboBox_2->currentIndex() == Val_Combos) || (ui->VelNoteComboBox_2->currentIndex() == Val_Combos)) && \
             (enabState[Ports_Midi3] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox_2->currentIndex() == Val_Combos) || (ui->ValCC1ComboBox_2->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox_2->currentIndex() == Val_Combos) || (ui->ValCC2ComboBox_2->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesParam_2, true);
            setEnableGroup(Group_Enable_2, true);
        }
        else
        {
            setEnableGroup(Group_NotesParam_2, false, true);
        }
    }
    else if (nPort == Ports_Midi4)
    {
        ui->ChanNoteComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_NoteChan_4P));
        ui->ChanCC1ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC1Chan_4P));
        ui->ChanCC2ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC2Chan_4P));

        int chkVarUse = kbDev.checkFeedback(Check_CheckVarUse_4P);
        ui->NoteNoteComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_NoteNote_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteNote) / VarUse_NoteNote));
        ui->VelNoteComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_NoteVel_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_NoteVel) / VarUse_NoteVel));
        ui->ControlCC1ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC1Ctrl_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Ctrl) / VarUse_CC1Ctrl));
        ui->ValCC1ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC1Val_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC1Val) / VarUse_CC1Val));
        ui->ControlCC2ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC2Ctrl_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Ctrl) / VarUse_CC2Ctrl));
        ui->ValCC2ComboBox_3->setCurrentIndex(kbDev.checkFeedback(Check_CC2Val_4P) + Val_NumVars * (1 - (chkVarUse & VarUse_CC2Val) / VarUse_CC2Val));

        QApplication::processEvents();
        setEnableGroup(Group_Enable_3, false, true);

        if ((((ui->NoteNoteComboBox_3->currentIndex() == Val_Keyboard) || (ui->VelNoteComboBox_3->currentIndex() == Val_Keyboard)) && \
             (enabState[Ports_Midi4] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox_3->currentIndex() == Val_Keyboard) || (ui->ValCC1ComboBox_3->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox_3->currentIndex() == Val_Keyboard) || (ui->ValCC2ComboBox_3->currentIndex() == Val_Keyboard)) && \
            (((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesScroll_3, true);
            setEnableGroup(Group_KeyboardSetWidget_3, true);
            setEnableGroup(Group_NotesSetWidget_3, true);
            setEnableGroup(Group_Assign_3, true);
            setEnableGroup(Group_Enable_3, true);
        }
        else
        {
            setEnableGroup(Group_NotesScroll_3, false, true);
            setEnableGroup(Group_KeyboardSetWidget_3, false, true);
            setEnableGroup(Group_NotesSetWidget_3, false, true);
            setEnableGroup(Group_Assign_3, false, true);
        }
        if ((((ui->NoteNoteComboBox_3->currentIndex() == Val_Combos) || (ui->VelNoteComboBox_3->currentIndex() == Val_Combos)) && \
             (enabState[Ports_Midi4] & Mode_NoteOn)) || \
           (((ui->ControlCC1ComboBox_3->currentIndex() == Val_Combos) || (ui->ValCC1ComboBox_3->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn)) || \
           (((ui->ControlCC2ComboBox_3->currentIndex() == Val_Combos) || (ui->ValCC2ComboBox_3->currentIndex() == Val_Combos)) && \
            (((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn)))
        {
            setEnableGroup(Group_NotesParam_3, true);
            setEnableGroup(Group_Enable_3, true);
        }
        else
        {
            setEnableGroup(Group_NotesParam_3, false, true);
        }
    }
    updateInProgress = saveInP;
}

/*
 * ==============================================
 * Send Parameters to the KB2D for MIDI commands
 * ==============================================
 */
void MainWindow::sendMidiModeValues(int nPorts, int nMode, int nMidi, int value)
{
    int chkVarUse = 0;

    if (!updateInProgress)
    {
        if (nPorts == Ports_Midi1)
            chkVarUse = kbDev.checkFeedback(Check_CheckVarUse);
        else if (nPorts == Ports_Midi3)
            chkVarUse = kbDev.checkFeedback(Check_CheckVarUse_3P);
        else
            chkVarUse = kbDev.checkFeedback(Check_CheckVarUse_4P);

        if ((nMidi == ValSelection_CtrlNotes) || (nMidi == ValSelection_ValVel))
        {
            if (value < Val_NumVars)
                chkVarUse |= (int)0b1 << ((nMidi - 1) + (2 * nMode));
            else
            {
                chkVarUse &= ~((int)0b1 << ((nMidi - 1) + (2 * nMode)));
                value -= Val_NumVars;
            }
        }
        int midiNoteChan[3] = {MIDI_NOTECHANSPIN};
        kbDev.sendCom((uchar)midiNoteChan[0], (uchar)midiNoteChan[1] + (nMode * 0x10) + nMidi + (3 * nPorts), (uchar)value);

        if (kbDev.checkFeedback(Check_NoteChan + (9 * nPorts) + (3 * nMode) + nMidi) != value)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_UpdateMidiNoteValues);

        if (nPorts == Ports_Midi1)
        {
            kbDev.sendCom(MIDI_CHKVARUSE + chkVarUse);
            if (kbDev.checkFeedback(Check_CheckVarUse) != chkVarUse)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_UpdateMidiNoteValues_1);
        }
        else if (nPorts == Ports_Midi3)
        {
            kbDev.sendCom(MIDI_CHKVARUSE_3P + chkVarUse);
            if (kbDev.checkFeedback(Check_CheckVarUse_3P) != chkVarUse)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_UpdateMidiNoteValues_2);
        }
        else
        {
            kbDev.sendCom(MIDI_CHKVARUSE_4P + chkVarUse);
            if (kbDev.checkFeedback(Check_CheckVarUse_4P) != chkVarUse)
                SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_UpdateMidiNoteValues_3);
        }

        updateMidiModeWidgets(nPorts);
    }
}

/////////////////////////////////////
////////// MIDI SELECTION ///////////
/////////////////////////////////////

// PORT1

void MainWindow::on_DescCC1ComboBox_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC1ComboBox->isEnabled())
        {
            lastMidiMode[Ports_Midi1][0] = index;
            enabState[Ports_Midi1] &= ~((int)0x7 << 1);
            enabState[Ports_Midi1] |= ((lastMidiMode[Ports_Midi1][0] + Mode_PolyAftertouch) << 1);
            kbDev.sendCom(MIDI_ENAB + enabState[Ports_Midi1]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi1);
        }
    }
}

void MainWindow::on_DescCC2ComboBox_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC2ComboBox->isEnabled())
        {
            lastMidiMode[Ports_Midi1][1] = index;
            enabState[Ports_Midi1] &= ~((int)0x7 << 4);
            enabState[Ports_Midi1] |= ((lastMidiMode[Ports_Midi1][1] + Mode_PolyAftertouch) << 4);
            kbDev.sendCom(MIDI_ENAB + enabState[Ports_Midi1]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi1);
        }
    }
}

void MainWindow::on_enableNotesOnOffButton_clicked()
{
    if (enabState[Ports_Midi1] & Mode_NoteOn)
        enabState[Ports_Midi1] &= ~(int)Mode_NoteOn;
    else
        enabState[Ports_Midi1] |= Mode_NoteOn;
    kbDev.sendCom(MIDI_ENAB + enabState[Ports_Midi1]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi1);
    updateMidiModeWidgets(Ports_Midi1);
}

void MainWindow::on_enableEffect1Button_clicked()
{
    if (((enabState[Ports_Midi1] >> 1) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi1] &= ~((int)0x7 << 1);
    else
        enabState[Ports_Midi1] |= ((int)(lastMidiMode[Ports_Midi1][0] + Mode_PolyAftertouch) << 1);
    kbDev.sendCom(MIDI_ENAB + enabState[Ports_Midi1]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi1);
    updateMidiModeWidgets(Ports_Midi1);
}

void MainWindow::on_enableEffect2Button_clicked()
{
    if (((enabState[Ports_Midi1] >> 4) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi1] &= ~((int)0x7 << 4);
    else
        enabState[Ports_Midi1] |= ((int)(lastMidiMode[Ports_Midi1][1] + Mode_PolyAftertouch) << 4);
    kbDev.sendCom(MIDI_ENAB + enabState[Ports_Midi1]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi1);
    updateMidiModeWidgets(Ports_Midi1);
}

// PORT 3

void MainWindow::on_DescCC1ComboBox_2_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC1ComboBox_2->isEnabled())
        {
            lastMidiMode[Ports_Midi3][0] = index;
            enabState[Ports_Midi3] &= ~((int)0x7 << 1);
            enabState[Ports_Midi3] |= ((lastMidiMode[Ports_Midi3][0] + Mode_PolyAftertouch) << 1);
            kbDev.sendCom(MIDI_ENAB_3P + enabState[Ports_Midi3]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi3);
        }
    }
}

void MainWindow::on_DescCC2ComboBox_2_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC2ComboBox_2->isEnabled())
        {
            lastMidiMode[Ports_Midi3][1] = index;
            enabState[Ports_Midi3] &= ~((int)0x7 << 4);
            enabState[Ports_Midi3] |= ((lastMidiMode[Ports_Midi3][1] + Mode_PolyAftertouch) << 4);
            kbDev.sendCom(MIDI_ENAB_3P + enabState[Ports_Midi3]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi3);
        }
    }
}

void MainWindow::on_enableNotesOnOffButton_2_clicked()
{
    if (enabState[Ports_Midi3] & Mode_NoteOn)
        enabState[Ports_Midi3] &= ~(int)Mode_NoteOn;
    else
        enabState[Ports_Midi3] |= Mode_NoteOn;
    kbDev.sendCom(MIDI_ENAB_3P + enabState[Ports_Midi3]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi3);
    updateMidiModeWidgets(Ports_Midi3);
}

void MainWindow::on_enableEffect1Button_2_clicked()
{
    if (((enabState[Ports_Midi3] >> 1) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi3] &= ~((int)0x7 << 1);
    else
        enabState[Ports_Midi3] |= ((int)(lastMidiMode[Ports_Midi3][0] + Mode_PolyAftertouch) << 1);
    kbDev.sendCom(MIDI_ENAB_3P + enabState[Ports_Midi3]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi3);
    updateMidiModeWidgets(Ports_Midi3);
}

void MainWindow::on_enableEffect2Button_2_clicked()
{
    if (((enabState[Ports_Midi3] >> 4) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi3] &= ~((int)0x7 << 4);
    else
        enabState[Ports_Midi3] |= ((int)(lastMidiMode[Ports_Midi3][1] + Mode_PolyAftertouch) << 4);
    kbDev.sendCom(MIDI_ENAB_3P + enabState[Ports_Midi3]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi3);
    updateMidiModeWidgets(Ports_Midi3);
}

// PORT 4

void MainWindow::on_DescCC1ComboBox_3_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC1ComboBox_3->isEnabled())
        {
            lastMidiMode[Ports_Midi4][0] = index;
            enabState[Ports_Midi4] &= ~((int)0x7 << 1);
            enabState[Ports_Midi4] |= ((lastMidiMode[Ports_Midi4][0] + Mode_PolyAftertouch) << 1);
            kbDev.sendCom(MIDI_ENAB_4P + enabState[Ports_Midi4]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi4);
        }
    }
}

void MainWindow::on_DescCC2ComboBox_3_currentIndexChanged(int index)
{
    if (!updateInProgress)
    {
        if (ui->DescCC2ComboBox_3->isEnabled())
        {
            lastMidiMode[Ports_Midi4][1] = index;
            enabState[Ports_Midi4] &= ~((int)0x7 << 4);
            enabState[Ports_Midi4] |= ((lastMidiMode[Ports_Midi4][1] + Mode_PolyAftertouch) << 4);
            kbDev.sendCom(MIDI_ENAB_4P + enabState[Ports_Midi4]);
            qSleep(100);
            updateMidiComboVisibility(Ports_Midi4);
        }
    }
}

void MainWindow::on_enableNotesOnOffButton_3_clicked()
{
    if (enabState[Ports_Midi4] & Mode_NoteOn)
        enabState[Ports_Midi4] &= ~(int)Mode_NoteOn;
    else
        enabState[Ports_Midi4] |= Mode_NoteOn;
    kbDev.sendCom(MIDI_ENAB_4P + enabState[Ports_Midi4]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi4);
    updateMidiModeWidgets(Ports_Midi4);
}

void MainWindow::on_enableEffect1Button_3_clicked()
{
    if (((enabState[Ports_Midi4] >> 1) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi4] &= ~((int)0x7 << 1);
    else
        enabState[Ports_Midi4] |= ((int)(lastMidiMode[Ports_Midi4][0] + Mode_PolyAftertouch) << 1);
    kbDev.sendCom(MIDI_ENAB_4P + enabState[Ports_Midi4]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi4);
    updateMidiModeWidgets(Ports_Midi4);
}

void MainWindow::on_enableEffect2Button_3_clicked()
{
    if (((enabState[Ports_Midi4] >> 4) & 0x7) > Mode_NoteOn)
        enabState[Ports_Midi4] &= ~((int)0x7 << 4);
    else
        enabState[Ports_Midi4] |= ((int)(lastMidiMode[Ports_Midi4][1] + Mode_PolyAftertouch) << 4);
    kbDev.sendCom(MIDI_ENAB_4P + enabState[Ports_Midi4]);
    qSleep(100);

    updateMidiComboVisibility(Ports_Midi4);
    updateMidiModeWidgets(Ports_Midi4);
}

////////////////////////////////
////////// VISIBILITY //////////
////////////////////////////////


void MainWindow::updateMidiComboVisibility(int nPort)
{
    enabState[Ports_Midi1] = kbDev.checkFeedback(Check_EnabMidiMode);
    enabState[Ports_Midi3] = kbDev.checkFeedback(Check_EnabMidiMode_3P);
    enabState[Ports_Midi4] = kbDev.checkFeedback(Check_EnabMidiMode_4P);

    // Notes ON OFF
    if (enabState[nPort] & Mode_NoteOn)
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableNotesOnOffButton->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton->setText(tr("Disable Notes On / Off"));
            setEnableGroup(Group_NotesMidi, true);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableNotesOnOffButton_2->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton_2->setText(tr("Disable Notes On / Off"));
            setEnableGroup(Group_NotesMidi_2, true);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableNotesOnOffButton_3->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton_3->setText(tr("Disable Notes On / Off"));
            setEnableGroup(Group_NotesMidi_3, true);
        }
    }
    else
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableNotesOnOffButton->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton->setText(tr("Enable Notes On / Off"));
            setEnableGroup(Group_NotesMidi, false);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableNotesOnOffButton_2->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton_2->setText(tr("Enable Notes On / Off"));
            setEnableGroup(Group_NotesMidi_2, false);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableNotesOnOffButton_3->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableNotesOnOffButton_3->setText(tr("Enable Notes On / Off"));
            setEnableGroup(Group_NotesMidi_3, false);
        }
    }
    // EFFECT 1
    if (((enabState[nPort] >> 1) & 0x7) >= Mode_PolyAftertouch)
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableEffect1Button->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button->setText(tr("Disable Effect 1"));
            setEnableGroup(Group_CC1Midi, true);
            ui->DescCC1ComboBox->setEnabled(true);
            lastMidiMode[Ports_Midi1][0] = ((enabState[nPort] >> 1) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC1ComboBox->setCurrentIndex(lastMidiMode[Ports_Midi1][0]);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableEffect1Button_2->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button_2->setText(tr("Disable Effect 1"));
            setEnableGroup(Group_CC1Midi_2, true);
            ui->DescCC1ComboBox_2->setEnabled(true);
            lastMidiMode[Ports_Midi3][0] = ((enabState[nPort] >> 1) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC1ComboBox_2->setCurrentIndex(lastMidiMode[Ports_Midi3][0]);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableEffect1Button_3->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button_3->setText(tr("Disable Effect 1"));
            setEnableGroup(Group_CC1Midi_3, true);
            ui->DescCC1ComboBox_3->setEnabled(true);
            lastMidiMode[Ports_Midi4][0] = ((enabState[nPort] >> 1) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC1ComboBox_3->setCurrentIndex(lastMidiMode[Ports_Midi4][0]);
        }
    }
    else
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableEffect1Button->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button->setText(tr("Enable Effect 1"));
            setEnableGroup(Group_CC1Midi, false);
            ui->DescCC1ComboBox->setEnabled(false);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableEffect1Button_2->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button_2->setText(tr("Enable Effect 1"));
            setEnableGroup(Group_CC1Midi_2, false);
            ui->DescCC1ComboBox_2->setEnabled(false);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableEffect1Button_3->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect1Button_3->setText(tr("Enable Effect 1"));
            setEnableGroup(Group_CC1Midi_3, false);
            ui->DescCC1ComboBox_3->setEnabled(false);
        }
    }
    // EFFECT 2
    if (((enabState[nPort] >> 4) & 0x7) >= Mode_PolyAftertouch)
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableEffect2Button->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button->setText(tr("Disable Effect 2"));
            setEnableGroup(Group_CC2Midi, true);
            ui->DescCC2ComboBox->setEnabled(true);
            lastMidiMode[Ports_Midi1][1] = ((enabState[nPort] >> 4) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC2ComboBox->setCurrentIndex(lastMidiMode[Ports_Midi1][1]);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableEffect2Button_2->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button_2->setText(tr("Disable Effect 2"));
            setEnableGroup(Group_CC2Midi_2, true);
            ui->DescCC2ComboBox_2->setEnabled(true);
            lastMidiMode[Ports_Midi3][1] = ((enabState[nPort] >> 4) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC2ComboBox_2->setCurrentIndex(lastMidiMode[Ports_Midi3][1]);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableEffect2Button_3->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #555555; border-radius:3px;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button_3->setText(tr("Disable Effect 2"));
            setEnableGroup(Group_CC2Midi_3, true);
            ui->DescCC2ComboBox_3->setEnabled(true);
            lastMidiMode[Ports_Midi4][1] = ((enabState[nPort] >> 4) & 0x7) - Mode_PolyAftertouch;
            ui->DescCC2ComboBox_3->setCurrentIndex(lastMidiMode[Ports_Midi4][1]);
        }
    }
    else
    {
        // Port 1
        if (nPort == Ports_Midi1)
        {
            ui->enableEffect2Button->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button->setText(tr("Enable Effect 2"));
            setEnableGroup(Group_CC2Midi, false);
            ui->DescCC2ComboBox->setEnabled(false);
        }
        // Port 3
        else if (nPort == Ports_Midi3)
        {
            ui->enableEffect2Button_2->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button_2->setText(tr("Enable Effect 2"));
            setEnableGroup(Group_CC2Midi_2, false);
            ui->DescCC2ComboBox_2->setEnabled(false);
        }
        // Port 4
        else if (nPort == Ports_Midi4)
        {
            ui->enableEffect2Button_3->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            ui->enableEffect2Button_3->setText(tr("Enable Effect 2"));
            setEnableGroup(Group_CC2Midi_3, false);
            ui->DescCC2ComboBox_3->setEnabled(false);
        }
    }
}


///////////////////////////
////////// NOTES //////////
///////////////////////////

void MainWindow::comboNoteSelected(int nPort, int indCombo, int index)
{
    if (!updateInProgress)
    {
        int depMidi[3] = {MIDI_SETMIDINOTE0};
        kbDev.sendCom(depMidi[0], depMidi[1] + (0x10 * nPort) + indCombo, index);
        if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + indCombo) != index)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_ComboNoteSel);
        assignNoteToKey(nPort, -1);
    }
}

void MainWindow::updateEnableButtons(int nPort)
{
    if (nPort == Ports_Midi1)
        beamsEnabled[nPort] = kbDev.checkFeedback(Check_Activate2PL) + (kbDev.checkFeedback(Check_Activate2PM) << 7) + (kbDev.checkFeedback(Check_Activate2PH) << 14);
    else if (nPort == Ports_Midi3)
        beamsEnabled[nPort] = kbDev.checkFeedback(Check_Activate3PL) + (kbDev.checkFeedback(Check_Activate3PM) << 7) + (kbDev.checkFeedback(Check_Activate3PH) << 14);
    else
        beamsEnabled[nPort] = kbDev.checkFeedback(Check_Activate4PL) + (kbDev.checkFeedback(Check_Activate4PM) << 7) + (kbDev.checkFeedback(Check_Activate4PH) << 14);

    for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
    {
        if (enableButton[nPort][_i])
        {
            if (beamsEnabled[nPort] & ((int)0b1 << _i))
            {
                enableButton[nPort][_i]->setStyleSheet("QPushButton {background-color:#aaaa00;}"
                                                    "QPushButton {border:1px solid #aa5500;}"
                                                    "QPushButton:hover {background-color:#bb8800;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            }
            else
            {
                enableButton[nPort][_i]->setStyleSheet("QPushButton {background-color:#555555;}"
                                                    "QPushButton {border:1px solid #888;}"
                                                    "QPushButton:hover {background-color:#777;}"
                                                    "QPushButton:pressed {border:1px inset #333;background-color:#555555;}");
            }
        }
    }
}

void MainWindow::enableButtonClicked(int nPort, int nIndex)
{
    int _iStart, _iStop;
    if (nIndex < 0)
    {
        _iStart = 0;
        _iStop = MAX_NBEAMS;
    }
    else
    {
        _iStart = nIndex;
        _iStop = nIndex + 1;
    }
    for ( ; _iStart < _iStop ; _iStart++)
    {
        if (beamsEnabled[nPort] & (0b1 << nIndex))
        {
            if (nPort == Ports_Midi1)
            {
                kbDev.sendCom(MIDI_ACTIVATE2PL + ((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE2PM + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE2PH + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 14) & 0x7F));
            }
            else if (nPort == Ports_Midi3)
            {
                kbDev.sendCom(MIDI_ACTIVATE3PL + ((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE3PM + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE3PH + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 14) & 0x7F));
            }
            else if (nPort == Ports_Midi4)
            {
                kbDev.sendCom(MIDI_ACTIVATE4PL + ((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE4PM + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE4PH + (((beamsEnabled[nPort] & (~((int)0b1 << nIndex))) >> 14) & 0x7F));
            }
        }
        else
        {
            if (nPort == Ports_Midi1)
            {
                kbDev.sendCom(MIDI_ACTIVATE2PL + ((beamsEnabled[nPort] | ((int)0b1 << nIndex)) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE2PM + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE2PH + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 14) & 0x7F));
            }
            else if (nPort == Ports_Midi3)
            {
                kbDev.sendCom(MIDI_ACTIVATE3PL + ((beamsEnabled[nPort] | ((int)0b1 << nIndex)) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE3PM + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE3PH + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 14) & 0x7F));
            }
            else if (nPort == Ports_Midi4)
            {
                kbDev.sendCom(MIDI_ACTIVATE4PL + ((beamsEnabled[nPort] | ((int)0b1 << nIndex)) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE4PM + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 7) & 0x7F));
                kbDev.sendCom(MIDI_ACTIVATE4PH + (((beamsEnabled[nPort] | ((int)0b1 << nIndex)) >> 14) & 0x7F));
            }
        }
    }

    updateEnableButtons(nPort);
}

/*
 * ========================
 * Slot to assign one beam
 * ========================
 */
void MainWindow::assignButtonClicked(int nPort, int nIndex)
{
    if (keyboard[nPort])
    {
        if (keyboard[nPort]->getNextAssign() == nIndex)
        {
            keyboard[nPort]->setNextAssign(-1);
            assignAllActivated[nPort] = false;
        }
        else
            keyboard[nPort]->setNextAssign(nIndex);
    }
    repaintAssignButtons();
}

/*
 * ====================================
 * Slot to assign all beams one by one
 * ====================================
 */
void MainWindow::assignAllButtonClicked(int nPort)
{
    if (assignAllActivated[nPort])
        assignAllActivated[nPort] = false;
    else
    {
        assignAllActivated[nPort] = true;
        if (keyboard[nPort] && (keyboard[nPort]->getNextAssign() < 0))
            keyboard[nPort]->setNextAssign(0);
    }
    repaintAssignButtons();
}

/*
 * ========================
 * Slot to Shift all notes
 * ========================
 */
void MainWindow::toneShiftClicked(int nPort, int typeShift)
{
    int _MidiSetNote[3] = {MIDI_SETMIDINOTE0};
    int shiftApplied;
    switch (typeShift)
    {
    case ToneShift_PlusHalfTone:
        shiftApplied = 1;
        break;
    case ToneShift_MinusHalfTone:
        shiftApplied = -1;
        break;
    case ToneShift_PlusTone:
        shiftApplied = 2;
        break;
    case ToneShift_MinusTone:
        shiftApplied = -2;
        break;
    default:
        shiftApplied = 0;
        break;
    }

    QVector <int> listN;
    for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
    {
        int tempNote = kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i);

        if (tempNote < 0)
            return;

        if (tempNote + shiftApplied > 127)
            tempNote = 127;
        else if (tempNote + shiftApplied < 0)
            tempNote = 0;
        else
            tempNote += shiftApplied;

        // Update Combobox and Send shifted notes to the KB2D
        kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
        bool saveInP = updateInProgress;
        updateInProgress = true;
        Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
        QApplication::processEvents();
        updateInProgress= saveInP;
        if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
            SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_ToneShift);

        // Save the list of the new notes for the display on the keyboard
        if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
            listN.append(tempNote);
    }

    // Update Keyboard
    if (!updateInProgress && keyboard[nPort])
    {
        keyboard[nPort]->updateNotesOnKeyboard(listN);
    }
}

void MainWindow::notePresetClicked(int nPort, int user)
{
    if (updateInProgress == false)
        loadNotesUser(nPort, "_User" + QString::number(user + 1));
}

void MainWindow::notesPresetComboChanged(int nPort, int index)
{
    if ((updateInProgress == false) && (index > 0))
        loadNotesPreset(nPort, index);
}

void MainWindow::updateNotesPresetList()
{
    for (int nPort = 0 ; nPort < Ports_Num ; nPort++)
    {
        int saveIndex = notesPresetCombos[nPort]->currentIndex();
        bool saveInP = updateInProgress;
        updateInProgress = true;

        notesPresetCombos[nPort]->clear();
        notesPresetCombos[nPort]->addItem(tr("[Select Preset]"));

        for (int _i = 0; _i < MAX_PRESETS_NOTES; _i++)
        {
            QString tempName;
            QSettings mainQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

            if (mainQSettings.childGroups().contains("PRST_" + QString::number(_i + 1), Qt::CaseInsensitive))
            {
                mainQSettings.beginGroup("PRST_" + QString::number(_i + 1));
                tempName = "[PRST " + QString::number(_i + 1) + "] - " + mainQSettings.value("NamePreset", "").toString();
                mainQSettings.endGroup();
            }
            else
                tempName = "[PRST " + QString::number(_i + 1) + "]";
            notesPresetCombos[nPort]->addItem(tempName);
        }

        QSettings mainQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

        if (mainQSettings.childGroups().contains("PRST_" + QString::number(saveIndex), Qt::CaseInsensitive))
            notesPresetCombos[nPort]->setCurrentIndex(saveIndex);
        else
            notesPresetCombos[nPort]->setCurrentIndex(0);

        QApplication::processEvents();
        updateInProgress = saveInP;
    }
}

void MainWindow::loadNotesPreset(int nPort, int nPreset)
{
    int _MidiSetNote[3] = {MIDI_SETMIDINOTE0};
    if (kbDev.isConnected())     // Prevent spamming warning windows
    {
        QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);

        if (prstQSettings.childGroups().contains("PRST_" + QString::number(nPreset), Qt::CaseInsensitive))
        {
            prstQSettings.beginGroup("PRST_" + QString::number(nPreset));
            if (nPreset == 0)    // For live save
            {
                bool saveInP = updateInProgress;
                updateInProgress = true;
                notesPresetCombos[nPort]->setCurrentIndex(prstQSettings.value("NamePreset").toInt());
                updateInProgress = saveInP;
            }

            QVector <int> listN;
            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (prstQSettings.allKeys().contains("Note" + QString::number(_i)))
                {
                    int tempNote = prstQSettings.value("Note" + QString::number(_i), 0).toInt();
                    // Update Combobox and Send shifted notes to the KB2D
                    kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
                    bool saveInP = updateInProgress;
                    updateInProgress = true;
                    Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
                    QApplication::processEvents();
                    updateInProgress= saveInP;
                    if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_LoadNotesPreset);

                    // Save the list of the new notes for the display on the keyboard
                    if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
                        listN.append(tempNote);
                }
            }
            prstQSettings.endGroup();
            // Update Keyboard
            if (!updateInProgress && keyboard[nPort])
            {
                keyboard[nPort]->updateNotesOnKeyboard(listN);
            }

            ui->statusBar->showMessage(tr("===== Notes Preset ") + QString::number(nPreset) + tr(" loaded ====="), 5000);
        }
        else if (nPreset != 0)
        {
            SendError(this, tr("Cannot open PRST_") + QString::number(nPreset) + "\nIn " NAME_NOTES_PRESETS, GrNotes_LoadNotesPreset_2);
            notesPresetCombos[nPort]->setCurrentIndex(0);
        }
    }
}

void MainWindow::loadNotesUser(int nPort, QString userName)
{
    int _MidiSetNote[3] = {MIDI_SETMIDINOTE0};
    if (kbDev.isConnected())     // Prevent spamming warning windows
    {
        QSettings prstQSettings(userName + NAME_NOTES_USER, QSettings::IniFormat);
        if (prstQSettings.allKeys().contains("Valid"))
        {
            QVector <int> listN;
            for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            {
                if (prstQSettings.allKeys().contains("Note" + QString::number(_i)))
                {
                    int tempNote = prstQSettings.value("Note" + QString::number(_i), 0).toInt();
                    // Update Combobox and Send shifted notes to the KB2D
                    kbDev.sendCom(_MidiSetNote[0], _MidiSetNote[1] + (0x10 * nPort) + _i, _MidiSetNote[2] + (char)tempNote);
                    bool saveInP = updateInProgress;
                    updateInProgress = true;
                    Z0_ComboBox[nPort][_i]->setCurrentIndex(tempNote);
                    QApplication::processEvents();
                    updateInProgress= saveInP;
                    if (kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i) != tempNote)
                        SendError(this, tr("No Feedback / Error on Feedback received."), GrNotes_LoadNotesUser);

                    // Save the list of the new notes for the display on the keyboard
                    if (_i < ui->nBeamsXComboBox->currentIndex() + 1)
                        listN.append(tempNote);
                }
            }
            // Update Keyboard
            if (!updateInProgress && keyboard[nPort])
            {
                keyboard[nPort]->updateNotesOnKeyboard(listN);
            }
            ui->statusBar->showMessage(tr("===== ") + userName + tr(" loaded ====="), 5000);
        }
        else
        {
            SendError(this, tr("Cannot open ") + userName + NAME_NOTES_USER, GrNotes_LoadNotesUser_2);
        }
    }
}

void MainWindow::saveNotesPreset(int nPort, int indPreset, QString custName)
{
    if (kbDev.isConnected())
    {
        QList <int> listNotes;
        for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            listNotes.append(kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i));
        ///////
        QSettings prstQSettings(NAME_NOTES_PRESETS, QSettings::IniFormat);
        prstQSettings.setValue("Valid", true);
        // Begin Preset Group
        prstQSettings.beginGroup("PRST_" + QString::number(indPreset));
        // Set Name
        if (custName != "")
            prstQSettings.setValue("NamePreset", custName);
        // Set Notes
        for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            if (listNotes.at(_i) >= 0)
                prstQSettings.setValue("Note" + QString::number(_i), listNotes.at(_i));
        prstQSettings.endGroup();
        updateNotesPresetList();
    }
}

void MainWindow::saveNotesUser(int nPort, int numUser)
{
    if (kbDev.isConnected())
    {
        QList <int> listNotes;
        for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            listNotes.append(kbDev.checkFeedback(Check_NoteToPlay0 + (16 * nPort) + _i));
        ///////
        QSettings prstQSettings("_User" + QString::number(numUser) + NAME_NOTES_USER, QSettings::IniFormat);
        prstQSettings.setValue("Valid", true);
        // Set Notes
        for (int _i = 0 ; _i < MAX_NBEAMS ; _i++)
            if (listNotes.at(_i) >= 0)
                prstQSettings.setValue("Note" + QString::number(_i), listNotes.at(_i));
        updateNotesPresetList();
    }
}

void MainWindow::saveNotesDialogClicked(int nPort)
{
    if (kbDev.isConnected())
    {
        SaveNotesDialog saveNoteDialog(notesPresetCombos[nPort]->currentIndex(), this);
        saveNoteDialog.setModal(true);
        connect(&saveNoteDialog, &SaveNotesDialog::presetSaved, this, [this, nPort] (int indPreset, QString custName) { this->saveNotesPreset(nPort, indPreset, custName); });
        connect(&saveNoteDialog, &SaveNotesDialog::userSaved, this, [this, nPort] (int numUser) { this->saveNotesUser(nPort, numUser); });
        saveNoteDialog.exec();
    }
}

void MainWindow::manageNotesDialogClicked(int nPort)
{
    ManageNotesDialog manageNoteDialog(notesPresetCombos[nPort]->currentIndex(), this);
    manageNoteDialog.setModal(true);
    connect(&manageNoteDialog, &ManageNotesDialog::updateNow, this, &MainWindow::updateNotesPresetList);
    manageNoteDialog.exec();
}


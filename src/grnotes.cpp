
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


void MainWindow::on_readButton_clicked()
{
    sendTestNote();
}

void MainWindow::on_invertXButton_clicked()
{
    invertX();
}


/*
 * ==============================
 * Invert X angles / Notes
 * ==============================
 */
void MainWindow::invertX()
{
    kbDev.sendCom(MIDI_INVERTX);
    updateAll(0);
}

/*
 * ==============================
 * send Test Note
 * ==============================
 */
void MainWindow::sendTestNote()
{
    kbDev.sendCom(MIDI_READVAR + 127);
}

/////////////////////////////////////
////////// MIDI SELECTION ///////////
/////////////////////////////////////

void MainWindow::on_DescNoteComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->ChanNoteComboBox->setDisabled(1);
        ui->ChanNoteLabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->NoteNoteComboBox->setDisabled(1);
        ui->NoteNoteLabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->VelNoteComboBox->setDisabled(1);
        ui->VelNoteLabelName->setStyleSheet("QLabel {color:#808080;}");
        kbDev.disMidiMode(NOTES_ONOFF);
    }
    else
    {
        ui->ChanNoteComboBox->setEnabled(1);
        ui->ChanNoteLabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->NoteNoteComboBox->setEnabled(1);
        ui->NoteNoteLabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->VelNoteComboBox->setEnabled(1);
        ui->VelNoteLabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        kbDev.enMidiMode(NOTES_ONOFF);
    }
    kbDev.sendCom(MIDI_ENAB + kbDev.getMidiMode());
    if ((kbDev.checkFeedback(Check_EnabMidiMode) &0x01) != ui->DescNoteComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_DescNote_C);
}

void MainWindow::on_DescCC1ComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->ChanCC1ComboBox->setDisabled(1);
        ui->ChanCC1LabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->ControlCC1ComboBox->setDisabled(1);
        ui->ControlCC1LabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->ValCC1ComboBox->setDisabled(1);
        ui->ValCC1LabelName->setStyleSheet("QLabel {color:#808080;}");
        kbDev.disMidiMode(PITCH);
    }
    else
    {
        ui->ChanCC1ComboBox->setEnabled(1);
        ui->ChanCC1LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->ControlCC1ComboBox->setEnabled(1);
        ui->ControlCC1LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->ValCC1ComboBox->setEnabled(1);
        ui->ValCC1LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        kbDev.enMidiMode(PITCH);
    }
    kbDev.sendCom(MIDI_ENAB + kbDev.getMidiMode());
    if (((kbDev.checkFeedback(Check_EnabMidiMode) & 0x02) >> 1) != ui->DescCC1ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_DescCC1_C);
}

void MainWindow::on_DescCC2ComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->ChanCC2ComboBox->setDisabled(1);
        ui->ChanCC2LabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->ControlCC2ComboBox->setDisabled(1);
        ui->ControlCC2LabelName->setStyleSheet("QLabel {color:#808080;}");
        ui->ValCC2ComboBox->setDisabled(1);
        ui->ValCC2LabelName->setStyleSheet("QLabel {color:#808080;}");
        kbDev.disMidiMode(CONTROL_CHANGE);
    }
    else
    {
        ui->ChanCC2ComboBox->setEnabled(1);
        ui->ChanCC2LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->ControlCC2ComboBox->setEnabled(1);
        ui->ControlCC2LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        ui->ValCC2ComboBox->setEnabled(1);
        ui->ValCC2LabelName->setStyleSheet("QLabel {color:#FFFFFF;}");
        kbDev.enMidiMode(CONTROL_CHANGE);
    }
    kbDev.sendCom(MIDI_ENAB + kbDev.getMidiMode());
    if (((kbDev.checkFeedback(Check_EnabMidiMode) & 0x04) >> 2) != ui->DescCC2ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_DescCC2_C);
}

void MainWindow::on_ChanNoteComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_NOTECHANSPIN + (char)index);
    if (kbDev.checkFeedback(Check_NoteChan) != ui->ChanNoteComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ChanNote_C);
}

void MainWindow::on_ChanCC1ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_CC1CHANSPIN + (char)index);
    if (kbDev.checkFeedback(Check_CC1Chan) != ui->ChanCC1ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ChanCC1_C);
}

void MainWindow::on_ChanCC2ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_CC2CHANSPIN + (char)index);
    if (kbDev.checkFeedback(Check_CC2Chan) != ui->ChanCC2ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ChanCC2_C);
}

void MainWindow::on_NoteNoteComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_NOTENOTESPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_NoteNote) + 2) != ui->NoteNoteComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_NoteNote_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_NOTENOTESPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_NoteNote) != ui->NoteNoteComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1) != 0b1))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_NoteNote_2_C);
    }
}

void MainWindow::on_ControlCC1ComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_CC1CTRLSPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_CC1Ctrl) + 2) != ui->ControlCC1ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ControlCC1_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_CC1CTRLSPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_CC1Ctrl) != ui->ControlCC1ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10) != 0b10))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ControlCC1_2_C);
    }
}

void MainWindow::on_ControlCC2ComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_CC2CTRLSPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_CC2Ctrl) + 2) != ui->ControlCC2ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ControlCC2_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_CC2CTRLSPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_CC2Ctrl) != ui->ControlCC2ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100) != 0b100))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ControlCC2_2_C);
    }
}

void MainWindow::on_VelNoteComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_NOTEVELSPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_NoteVel) + 2) != ui->VelNoteComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1000) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_VelNote_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_NOTEVELSPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_NoteVel) != ui->VelNoteComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b1000) != 0b1000))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_VelNote_2_C);
    }
}

void MainWindow::on_ValCC1ComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_CC1VALSPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_CC1Val) + 2) != ui->ValCC1ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10000) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ValCC1_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_CC1VALSPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_CC1Val) != ui->ValCC1ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b10000) != 0b10000))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ValCC1_2_C);
    }
}

void MainWindow::on_ValCC2ComboBox_currentIndexChanged(int index)
{
    if (index >= 2)
    {
        kbDev.sendCom(MIDI_CC2VALSPIN + (char)(index - 2));
        if (((kbDev.checkFeedback(Check_CC2Val) + 2) != ui->ValCC2ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100000) != 0))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ValCC2_1_C);
    }
    else
    {
        kbDev.sendCom(MIDI_CC2VALSPIN2 + (char)index);
        if ((kbDev.checkFeedback(Check_CC2Val) != ui->ValCC2ComboBox->currentIndex()) || ((kbDev.checkFeedback(Check_CheckVarUse) & 0b100000) != 0b100000))
            SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_ValCC2_2_C);
    }
}


///////////////////////////
////////// NOTES //////////
///////////////////////////


void MainWindow::on_X0Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE0 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay0) != ui->X0Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X0Z0_C);
}

void MainWindow::on_X1Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE1 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay1) != ui->X1Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X1Z0_C);
}

void MainWindow::on_X2Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE2 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay2) != ui->X2Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X2Z0_C);
}

void MainWindow::on_X3Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE3 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay3) != ui->X3Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X3Z0_C);
}

void MainWindow::on_X4Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE4 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay4) != ui->X4Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X4Z0_C);
}

void MainWindow::on_X5Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE5 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay5) != ui->X5Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X5Z0_C);
}

void MainWindow::on_X6Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE6 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay6) != ui->X6Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X6Z0_C);
}

void MainWindow::on_X7Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE7 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay7) != ui->X7Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X7Z0_C);
}

void MainWindow::on_X8Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE8 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay8) != ui->X8Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X8Z0_C);
}

void MainWindow::on_X9Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE9 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay9) != ui->X9Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X9Z0_C);
}

void MainWindow::on_X10Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE10 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay10) != ui->X10Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X10Z0_C);
}

void MainWindow::on_X11Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE11 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay11) != ui->X11Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X11Z0_C);
}

void MainWindow::on_X12Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE12 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay12) != ui->X12Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X12Z0_C);
}

void MainWindow::on_X13Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE13 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay13) != ui->X13Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X13Z0_C);
}

void MainWindow::on_X14Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE14 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay14) != ui->X14Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X14Z0_C);
}

void MainWindow::on_X15Z0_ComboBox_currentIndexChanged(int index)
{
    kbDev.sendCom(MIDI_SETMIDINOTE15 + (char)index);
    if (kbDev.checkFeedback(Check_NoteToPlay15) != ui->X15Z0_ComboBox->currentIndex())
        SendError(this, tr("No Feedback received / Select MIDI Input."), GrNotes_X15Z0_C);
}


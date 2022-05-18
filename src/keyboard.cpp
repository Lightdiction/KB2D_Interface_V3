
#include "../inc/mainwindow.h"
#include "../inc/keyboard.h"


/*
 * =========================
 * KeyBoard PushButton Class
 * =========================
 */
KeyboardKey::KeyboardKey(int kwidth, QString name, QString color, QString hoverColor, QString clickColor, QWidget *parent) : QPushButton(parent)
{
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    setSizePolicy(policy);
    setStyleSheet("QWidget {background-color:" + color + ";color:#555; font-weight:bold;}"
                  "QWidget:hover{background-color:" + hoverColor + ";}"
                  "QWidget:pressed{background-color:" + clickColor + ";}"
                  "QPushButton {text-align:left;" + tr("padding-left:5px;}"));
    setFocusPolicy(Qt::StrongFocus);
    setToolTip(tr("Click to Send or Assign a Note"));
    setFixedWidth(kwidth);
    setText(name);
}

KeyboardKey::~KeyboardKey() {}


/*
 * =========================
 * KeyBoard Class
 * =========================
 */
Keyboard::Keyboard(QGridLayout* mainGridLayout, QWidget *parent) : Keyboard(mainGridLayout, 48, 60, parent) { }

Keyboard::Keyboard(QGridLayout* mainGridLayout, int initK, int nKey, QWidget *parent) : QWidget(parent)
{
    globKbLayout = mainGridLayout;

    refreshKeyboard(initK, nKey);
}

Keyboard::~Keyboard()
{
}

/////////////////////



void Keyboard::refreshKeyboard()
{
    refreshKeyboard(saveInitialKey, saveNumKeys);
}

/*
 * =========================
 * Initialize the Keyboard
 * =========================
 */
void Keyboard::refreshKeyboard(int initialNote, int numNotes)
{
    if ((initialNote + numNotes) > Note_Number)
        numNotes = Note_Number - initialNote;

    if (initialNote < 0)
        initialNote = 48;
    if (numNotes < 0)
        numNotes = 60;
    saveInitialKey = initialNote;
    saveNumKeys = numNotes;

    // Clear the layouts
    if (blackKeysLayout)
    {
        clearLayout(blackKeysLayout);
        QApplication::processEvents();
        delete blackKeysLayout;
        blackKeysLayout = nullptr;
    }

    if (whiteKeysLayout)
    {
        clearLayout(whiteKeysLayout);
        QApplication::processEvents();
        delete whiteKeysLayout;
        whiteKeysLayout = nullptr;
    }
    setUpdatesEnabled(false);
    QApplication::processEvents();
    /*
    QList <QWidget *> list = ui->whiteKeysLayout->findChildren<QWidget *>();
    foreach (QWidget *qw, list)
        delete qw;
*/
    int indexWhiteCol = 0;
    int indexBlackCol = 0;
    int indexSpaceBlackCol = 0;

    blackKeysLayout = new QGridLayout();
    whiteKeysLayout = new QGridLayout();
    globKbLayout->addLayout(whiteKeysLayout, 0, 0);
    globKbLayout->addLayout(blackKeysLayout, 0, 0);

    blackKeyList.clear();

    for (int _i = 0 ; _i < keyLabel.length() ; _i++)
        delete keyLabel[_i];
    keyLabel.clear();

    // Fill the Keyboard
    for (int _i = initialNote ; _i < (initialNote + numNotes) ; _i++)
    {
        // Black Key
        if (((_i % 12) == Note_Cm1d) || ((_i % 12) == Note_Dm1d) || ((_i % 12) == Note_Fm1d) || ((_i % 12) == Note_Gm1d) || ((_i % 12) == Note_Am1d))
        {

            if (_i == initialNote)
            {
                // Fill White Keys with space
                QSpacerItem* spacerFirstWhite = new QSpacerItem(KEYS_WIDTH / 2, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
                whiteKeysLayout->addItem(spacerFirstWhite, 0, indexWhiteCol);
                indexWhiteCol ++;
            }

            // Fill Black Keys with space
            QSpacerItem* spacerPreBlack = new QSpacerItem((KEYS_WIDTH - KEYS_BLACK_WIDTH) / 2, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
            blackKeysLayout->addItem(spacerPreBlack, 0, indexBlackCol);
            indexBlackCol ++;
            indexSpaceBlackCol ++;
            // Create Black Key
            if (actualNotes.contains(_i))
            {
                noteKeys[_i] = new KeyboardKey(KEYS_BLACK_WIDTH, "", "#282800", "#411", "#333");
                // Add beam Label
                keyLabel.append(new QLabel(this));
                keyLabel.last()->setText("(" + QString::number(actualNotes.indexOf(_i) + 1) + ")");
                keyLabel.last()->setStyleSheet("color:#05F;font-weight:bold;");
                keyLabel.last()->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
                keyLabel.last()->setFixedHeight(18);
                blackKeysLayout->addWidget(keyLabel.last(), 0, indexBlackCol);
                keyLabel.last()->show();
            }
            else
                noteKeys[_i] = new KeyboardKey(KEYS_BLACK_WIDTH, "", "#111", "#411", "#333");
            blackKeysLayout->addWidget(noteKeys[_i], 0, indexBlackCol);
            indexBlackCol ++;
            blackKeyList.append(_i);
            // Fill Black Keys with space
            QSpacerItem* spacerPostBlack = new QSpacerItem((KEYS_WIDTH - KEYS_BLACK_WIDTH) / 2, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
            blackKeysLayout->addItem(spacerPostBlack, 0, indexBlackCol);
            indexBlackCol ++;
            indexSpaceBlackCol ++;
        }
        // White Key
        else
        {
            QString nameK = "";
            if (_i % 12)
            {
            }
            else
                nameK = tr("C") + QString::number(_i / 12 - 1);

            if (_i == initialNote)
            {
                // Fill Black Keys with space
                QSpacerItem* spacerFirstBlack = new QSpacerItem(KEYS_WIDTH / 2, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
                blackKeysLayout->addItem(spacerFirstBlack, 0, indexBlackCol);
                indexBlackCol++;
                indexWhiteCol = 1;  // Start at 1 for white when white is first
            }

            // Fill Black Keys with space if needed
            if (indexWhiteCol > (indexBlackCol - indexSpaceBlackCol))
            {
                QSpacerItem* spacerBlack = new QSpacerItem(KEYS_WIDTH, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
                blackKeysLayout->addItem(spacerBlack, 0, indexBlackCol);
                indexBlackCol ++;
            }

            // Create White Key
            if (actualNotes.contains(_i))
            {
                noteKeys[_i] = new KeyboardKey(KEYS_WIDTH, nameK, "#EE9");
                // Add beam Label
                keyLabel.append(new QLabel(this));
                keyLabel.last()->setText("(" + QString::number(actualNotes.indexOf(_i) + 1) + ")");
                keyLabel.last()->setStyleSheet("color:#03F;font-weight:bold;");
                keyLabel.last()->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
                keyLabel.last()->setFixedHeight(18);
                whiteKeysLayout->addWidget(keyLabel.last(), 1, indexWhiteCol);
                keyLabel.last()->show();
            }
            else
                noteKeys[_i] = new KeyboardKey(KEYS_WIDTH, nameK);
            whiteKeysLayout->addWidget(noteKeys[_i], 0, indexWhiteCol, 3, 1);
            indexWhiteCol ++;
        }
        connect(noteKeys[_i], &QPushButton::clicked, this, [this, _i] () {emit this->keyClicked(_i);});
    }

    // Add Final spacers
    QSpacerItem* spacerStopWhite = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem* spacerStopBlack = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    whiteKeysLayout->addItem(spacerStopWhite, 0, indexWhiteCol);
    blackKeysLayout->addItem(spacerStopBlack, 0, indexBlackCol);

    // Move Black Keys on front plane
    for (int _i = 0 ; _i < blackKeyList.size() ; _i ++)
    {
        noteKeys[blackKeyList[_i]]->raise();
    }

    // Move Label on front of Keys
    for (int _i = 0 ; _i < keyLabel.size() ; _i ++)
    {
        keyLabel[_i]->raise();
    }

    // Add vertical space for Black keys
    QSpacerItem* blackSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    blackKeysLayout->addItem(blackSpacer, 1, 1);
    blackKeysLayout->setRowStretch(0, 10);
    blackKeysLayout->setRowStretch(1, 6);

    // Add vertical space for White Labels
    QSpacerItem* whiteLabelSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem* whiteBLabelSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    whiteKeysLayout->addItem(whiteLabelSpacer, 0, 0);
    whiteKeysLayout->addItem(whiteBLabelSpacer, 2, 0);
    whiteKeysLayout->setRowStretch(0, 5);
    whiteKeysLayout->setRowStretch(1, 1);
    whiteKeysLayout->setRowStretch(2, 1);
    setUpdatesEnabled(true);
}

/*
 * ===============================
 * Updates Keys and Labels
 * In function of currente notes
 * ===============================
 */
void Keyboard::updateNotesOnKeyboard(QVector <int> &listNotes)
{
    actualNotes.clear();

    for (int _i = 0 ; _i < listNotes.length() ; _i++)
    {
        actualNotes.append(listNotes[_i]);
    }
    refreshKeyboard();
}

void Keyboard::setNextAssign(int nIndex)
{
    nextAssign = nIndex;
    if (nextAssign >= MAX_NBEAMS)
        nextAssign = -1;
}

int Keyboard::getNextAssign()
{
    return nextAssign;
}


///// SLOTS /////

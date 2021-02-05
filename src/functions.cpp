
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Functions **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Various Functions:
 * - qSleep -
 * - readCyFile - Read Firmware File and Load Data
 * - transposeHex - Transpose Hex Character
 * - readLegacyFile -
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/comhw.h"

#include <QDebug>

//using namespace std;

#define SIZE_CY_FILE_BYTEMAX    100000
#define BYTE_SHIFT              11
#define PAGEDATA_MULTIPLE       (1 << BYTE_SHIFT)


/*
 * ======================================
 * Read Crypt File and load in Flash
 * Returns 0 if this is a SUCCESS
 * ======================================
 */
int MainWindow::readCyFile(FILE *cyFile)
{
    qDebug() << "Read Cy File...";
    SendLog("Starting firmware Update");
    unsigned long countChar = 0;
    int thCountPage;
    int countPage;
    int dataCy[SIZE_CY_FILE_BYTEMAX] = {0};
    int err = 0, err2 = 0;
    int failLoadPage = 0;

    // Read All file and stock it
    do
    {
        dataCy[countChar] = fgetc(cyFile);
        countChar += 1;
    }
    while ((dataCy[countChar - 1] >= 0) && (dataCy[countChar - 1] != EOF));
    //return dataCy[121];

    qDebug() << "File read" << countChar;
    // Wrong Data Number
    if (countChar < 2)
        return -1;
    countChar -= 2;     // Remove EOF and page Count
    if ((countChar & (PAGEDATA_MULTIPLE - 1)) != 0)
        return countChar;

    countPage = countChar >> 11;
    thCountPage = dataCy[countChar];


    // Wrong symbol, or can't read
    if (dataCy[countChar + 1] != EOF)
        return -4;

    // No correspondance between theoretical page Number and read page Number
    if (countPage != thCountPage)
        return -2;

    //ui->statusBar->showMessage("Upgrading Firmware... 0KB", 0);
    setStatus(tr("Upgrading Firmware... 0KB"));
    setFlashText(tr("Upgrading Firmware... 0KB out of ") + QString::number(countPage * 2) + tr("KB"));
    QCoreApplication::processEvents();
    // Send all Data Page by Page
    for (int _ii = 0; _ii < countPage; _ii++)
    {
        // Send all Data in 1 page
        for (int _jj = 0; _jj < PAGEDATA_MULTIPLE; _jj++)
        {
            dfuDev.sendAndCheck(MIDI_PROGMEM, ((dataCy[(_ii * PAGEDATA_MULTIPLE) + _jj] & 0xF0) >> 4), (dataCy[(_ii * PAGEDATA_MULTIPLE) + _jj] & 0xF));
            if (failLoadPage == 2)  // If data were saturated twice on reception, add Sleep(1) to prevent saturation.
                qSleep(1);
        }

        // Program page
        dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
        err = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
        // B6 01 03 = Saturation (Wrong Data Number) = -1103
        // B6 02 03 = Saturation + No Page = -2103
        // B6 01 02 = Wrong Page (Saturation always have priority on Wrong Page) = -1102
        // C6 00 00 = OK
        // -10 = timeout
        if (err != 0)
        {
            SendLog("DFU SendAndCheck err: failLoadPage=" + QString::number(failLoadPage));
            if (failLoadPage < 2)
            {
                switch (err)
                {
                case -1103:     // Saturation on data reception
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;

                case -2103:
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;

                case -1102:
                    dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
                    err2 = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
                    if (err2 != 0)
                    {
                        failLoadPage++;
                        _ii--;  // Reload current page
                    }
                    else
                        failLoadPage = 0;
                    break;

                case -10:
                    dfuDev.sendAndCheck(MIDI_SETPAGENUMBER, (0x7F - _ii), _ii);
                    err2 = dfuDev.sendAndCheck(MIDI_STARTFLASHING, 0, 0x7F);
                    if (err2 != 0)
                    {
                        failLoadPage++;
                        _ii--;  // Reload current page
                    }
                    else
                        failLoadPage = 0;
                    break;

                default:
                    failLoadPage++;
                    _ii--;  // Reload current page
                    break;
                }
            }
            else
                return err;
        }
        else
            failLoadPage = 0;   // Reset error when a page is correctly programmed

        // Update Status
        setStatus(tr("Upgrading Firmware... ") + QString::number(2 * (_ii + 1)) + tr("KB"));
        setFlashText(tr("Upgrading Firmware... ") + QString::number(2 * (_ii + 1)) + tr("KB out of ") + QString::number(countPage * 2) + tr("KB"));
        QCoreApplication::processEvents();
    }

    // Send message for End Of Prog
    err = dfuDev.sendAndCheck(MIDI_ENDOFPROG);                                              // Send End Of File here
    if (err != 0)
    {
        err2 = dfuDev.sendAndCheck(MIDI_ENDOFPROG);     // 2nd try
        if (err2 != 0)
            return (100 * err) + err2;
    }

    SendLog("Firmware Update Successful");
    return 0;   // SUCCESS
}

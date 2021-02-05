
/*
 * =================================================
 * =============== Harp Interface V2 ===============
 *
 * ** Main **
 *
 * Created by Thomas AVISSE
 * Lightdiction SAS
 *
 * Does not do many things
 * - Load main window
 * - Declare device vars
 * - Declare MIDI vars
 * - Enable DPI Scaling
 *
 * =================================================
 */

#include "../inc/mainwindow.h"
#include <QApplication>
#include <QTranslator>

#include "../inc/comhw.h"

MidiDevIn harpIn;
MidiDevOut harpOut;
MidiDevIn extIn;
MidiDevOut extOut;

ComHwKb2d kbDev;
ComHwDfu dfuDev;

bool changeLanguage = false;

int main(int argc, char *argv[])
{
    //HDC hScreen = GetDC(NULL);

    //float pxDen = GetDeviceCaps(hScreen, LOGPIXELSX);
    //pxDen = 0;
    //SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    //qputenv("QT_SCREEN_SCALE_FACTORS", "1.5");
    //qputenv("QT_SCALE_FACTOR", "1.5");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // Needs QT version updated


    int appReturn = 1;
    do
    {
        changeLanguage = false;
        QApplication a(argc, argv);

        QSettings globQSettings(".kbsession", QSettings::IniFormat);
        QString langTr = globQSettings.value("lang", (QLocale::system().name().section('_', 0, 0))).toString();
        QTranslator translator;
        translator.load(QString("kb2dinterface_") + langTr);
        a.installTranslator(&translator);

        MainWindow w;

        w.show();
        w.updateMidiPortsList();

        appReturn = a.exec();
    } while((appReturn == 0) && changeLanguage);

    return appReturn;
}

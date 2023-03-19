
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
#include <QStandardPaths>

#include "../inc/comhw.h"

MidiDevIn harpIn;
MidiDevOut harpOut;
MidiDevIn extIn;
MidiDevOut extOut;
MidiDevIn throughIn;
MidiDevOut throughOut;

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

    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // Needs QT version updated


    int appReturn = 1;
    QApplication a(argc, argv);
#ifdef MAC_PLATFORM
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists())
        dir.mkpath(".");
    QDir::setCurrent(dir.absolutePath());
#else
    QDir::setCurrent(qApp->applicationDirPath());
#endif
    do
    {
        changeLanguage = false;

        QSettings globQSettings(".kbsession", QSettings::IniFormat);
        QString langTr = globQSettings.value("lang", (QLocale::system().name().section('_', 0, 0))).toString();
        QTranslator translator;
        (void)translator.load(qApp->applicationDirPath() + "/" + QString("kb2dinterface_") + langTr);
        a.installTranslator(&translator);

        MainWindow w;

        w.show();

        appReturn = a.exec();
        a.exit(appReturn);
    } while((appReturn == 0) && changeLanguage);

    return appReturn;
}

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTextStream>
#include <QIODevice>
#include <QProcess>
#include <QDebug>
#include <QQuickView>
#include <QQmlContext>
#include <QString>
#include <QObject>
#include <spawn.h>
#include <alsa/asoundlib.h>


#include "Instrument.h"
#include "instrumentexplorer.h"
#include "urawmidi.h"
#include "midithread.h"


// Channel 1 is left

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    RawMidi rawMidi;
    //rawMidi.jackOpenClient();
//    rawMidi.openDevice("hw:2,1");
//    rawMidi.selectInstrument(0, 0, 0);
//    rawMidi.selectInstrument(0, 0, 1);
//    rawMidi.selectInstrument(0, 0, 2);
//    rawMidi.selectInstrument(0, 0, 3);


    //MidiController *midiControler = new MidiController();

    /*****************************************************************/
    Spawn ombl;
    QStringList tmp;
    ombl.init("/home/pi/ombl/ombl", tmp, "/home/pi/ombl/");
    ombl.start();
    /********************************************************************/

    InstrumentExplorer instruExplorer;
    instruExplorer.loadAllVoices();

    //rawMidi.openDevice("hw:2,1");
    //rawMidi.openDevice("hw:1,0");
     rawMidi.openDevice("virtual");
     //rawMidi.selectInstrument(4, 1, 3);

//   rawMidi.selectInstrument(0, 20, 1);
//    rawMidi.selectInstrument(0, 20, 2);
//    rawMidi.selectInstrument(0, 20, 3);



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("instruExplorer", &instruExplorer);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("ombl", &ombl);


    QObject::connect(&instruExplorer, SIGNAL(requestInstrumentLoading(uint8_t, uint8_t, uint8_t)), &rawMidi, SLOT(selectInstrument(uint8_t, uint8_t,uint8_t)) );


//    QQuickView view;
//    view.rootContext()->setContextProperty("ombl", &ombl);
//    view.setSource(QUrl::fromLocalFile("main.qml"));
//    view.show();

    return app.exec();
}

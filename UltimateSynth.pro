TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    spawn.cpp \
    testclass.cpp \
    patchparser.cpp \
    Instrument.cpp \
    instrumentexplorer.cpp \
    urawmidi.cpp \
    midithread.cpp \
    csvparser.cpp

RESOURCES += qml.qrc


LIBS += -lasound -ljack
# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/ombl
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    testclass.h \
    spawn.h \
    patchparser.h \
    Instrument.h \
    instrumentexplorer.h \
    urawmidi.h \
    midithread.h \
    csvparser.h

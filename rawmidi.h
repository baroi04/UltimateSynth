#ifndef RAWMIDI_H
#define RAWMIDI_H

#include <QObject>

class RawMidi : public QObject
{
    Q_OBJECT
public:
    explicit RawMidi(QObject *parent = 0);

signals:

public slots:
};

#endif // RAWMIDI_H
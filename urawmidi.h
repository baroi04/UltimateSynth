#ifndef U_RAWMIDI_H
#define U_RAWMIDI_H

#include <alsa/asoundlib.h>

#include <QObject>
#include <QString>


class RawMidi : public QObject
{
    Q_OBJECT
public:
    explicit RawMidi(QObject *parent = 0);

    void openDevice(QString device_out_name);

    void jackOpenClient();


signals:

private:
    QString m_device_out;
    snd_rawmidi_t *m_handle_out;

public slots:
        void selectInstrument(uint8_t bank, uint8_t program, uint8_t channel);
};

#endif // RAWMIDI_H

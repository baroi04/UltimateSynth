#ifndef MIDITHREAD_H
#define MIDITHREAD_H

#include <QObject>
#include <QThread>
#include <alsa/asoundlib.h>
#include <QString>
#include <QDebug>

class MidiController;

class MidiThread : public QObject
{
    Q_OBJECT
public:
    explicit MidiThread(QObject *parent = 0);

public slots:

    void doWork(const QString &parameter)
    {
        QString result;
        /* ... here is the expensive or blocking operation ... */

        int err = 0;

        uint8_t channel = 0;
        uint8_t bank = 0;
        uint8_t program = 0;

        unsigned char ch;

        snd_rawmidi_open(&m_handle_in_virtual, &m_handle_out_virtual, "virtual", SND_RAWMIDI_APPEND );

        m_device_out = "hw:1,0,0";
        err = snd_rawmidi_open(NULL, &m_handle_out, m_device_out.toUtf8(), 0);
        //err = snd_rawmidi_open(NULL, &m_handle_out, "m_device_out.toUtf8()", 0);
        if (err) {
            //fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",device_out_name,err);
            qDebug() << "snd_rawmidi_open " << m_device_out << "failed: " << err;
        }

        if (m_handle_out) {
            unsigned char ch;
            ch = MIDI_CMD_CONTROL | channel; snd_rawmidi_write(m_handle_out, &ch,1);
            ch = MIDI_CTL_MSB_BANK;   snd_rawmidi_write(m_handle_out,&ch,1);
            ch = bank;   snd_rawmidi_write(m_handle_out,&ch,1);
            ch = MIDI_CMD_PGM_CHANGE | channel;  snd_rawmidi_write(m_handle_out,&ch,1);
            ch = program;  snd_rawmidi_write(m_handle_out,&ch,1);
            snd_rawmidi_drain(m_handle_out);
            qDebug() << "Instrument selected !";

        }

        m_device_in = "hw:1,0,0";
        err = snd_rawmidi_open(&m_handle_in, NULL, m_device_in.toUtf8(), 0);
        //err = snd_rawmidi_open(NULL, &m_handle_out, "m_device_out.toUtf8()", 0);
        if (err) {
            //fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",device_out_name,err);
            qDebug() << "snd_rawmidi_open " << m_device_in << "failed: " << err;
        }


//        while(1)
//        {
//            snd_rawmidi_read(m_handle_in,&ch,1);
//            snd_rawmidi_write(m_handle_out,&ch,1);
//            snd_rawmidi_drain(m_handle_out);

//            snd_rawmidi_write(m_handle_in, &ch,1);
//            snd_rawmidi_drain(m_handle_in);
//        }

        emit resultReady(result);
    }

private:
    QString m_device_out;
    QString m_device_in;
    snd_rawmidi_t *m_handle_out;
    snd_rawmidi_t *m_handle_in;

    snd_rawmidi_t *m_handle_out_virtual;
    snd_rawmidi_t *m_handle_in_virtual;
signals:
    void resultReady(const QString &result);
};


class MidiController : public QObject
{
    Q_OBJECT
    QThread m_workerThread;
public:
    MidiController() {
        qDebug() << "Starting thread";
        MidiThread *worker = new MidiThread;
        worker->moveToThread(&m_workerThread);
        connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &MidiController::operate, worker, &MidiThread::doWork);
        connect(worker, &MidiThread::resultReady, this, &MidiController::handleResults);

        m_workerThread.start();
        emit operate("");
    }
    ~MidiController() {
        m_workerThread.quit();
        m_workerThread.wait();
    }
public slots:
    void handleResults(const QString &){

    }

signals:
    void operate(const QString &);
};

#endif // MIDITHREAD_H

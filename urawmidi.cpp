#include "urawmidi.h"

#include <alsa/asoundlib.h>
#include <alsa/rawmidi.h>
#include <QString>
#include <QDebug>
#include <jack/jack.h>

RawMidi::RawMidi(QObject *parent) : QObject(parent)
{

}

void RawMidi::openDevice(QString device_out_name)
{

    int err = 0;
    m_device_out = device_out_name;
    err = snd_rawmidi_open(NULL, &m_handle_out, m_device_out.toUtf8(), SND_RAWMIDI_NONBLOCK);
    //err = snd_rawmidi_open(NULL, &m_handle_out, "m_device_out.toUtf8()", 0);
    if (err) {
        //fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",device_out_name,err);
        qDebug() << "snd_rawmidi_open " << device_out_name << "failed: " << err;
    }

}


void RawMidi::selectInstrument(uint8_t bank, uint8_t program, uint8_t channel)
{
    qDebug() << "RawMidi Selecting instrument" << ", bank: " << bank << ", programm:" << program << ", channel:" << channel;
    if (m_handle_out) {
        unsigned char ch;
        ch = MIDI_CMD_CONTROL | channel; snd_rawmidi_write(m_handle_out, &ch,1);

//        ch = MIDI_CTL_MSB_BANK;   snd_rawmidi_write(m_handle_out,&ch,1);
//        ch = bank;   snd_rawmidi_write(m_handle_out,&ch,1);

        ch = MIDI_CTL_LSB_BANK;   snd_rawmidi_write(m_handle_out,&ch,1);
        ch = bank;   snd_rawmidi_write(m_handle_out,&ch,1);

        ch = MIDI_CMD_PGM_CHANGE | channel;  snd_rawmidi_write(m_handle_out,&ch,1);
        ch = program;  snd_rawmidi_write(m_handle_out,&ch,1);
        snd_rawmidi_drain(m_handle_out);
        qDebug() << "Instrument selected !";

    }

}

void RawMidi::jackOpenClient()
{

    jack_options_t options = JackNullOption;

    jack_status_t status;

    jack_client_t* jackClient;

    jackClient = jack_client_new ("jackInQt");

    qDebug() << "status " << (int)status;

    if(jackClient !=  NULL){
        qDebug() << "Jack client opened !";
    }else{
        qDebug() << "Jack client not opened !";
    }

    jack_port_t *input_port = jack_port_register (jackClient, "input",
                         JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

    snd_rawmidi_t *m_handle_out_virtual;
    snd_rawmidi_t *m_handle_in_virtual;
    snd_rawmidi_open(&m_handle_in_virtual, &m_handle_out_virtual, "virtual", SND_RAWMIDI_APPEND );
}


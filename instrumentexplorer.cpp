#include "instrumentexplorer.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

#include "Instrument.h"
#include <csvparser.h>

InstrumentExplorer::InstrumentExplorer(QObject *parent) : QObject(parent)
{

}

void InstrumentExplorer::loadAllVoices()
{
    TSE3::Ins::CakewalkInstrumentFile instrus("/home/pi/ombl/KetronSD2.ins");

    std::list<std::string> instruList = instrus.instruments();
    // Iterate and print values of the list
    qDebug() << "There is " << instruList.size() << " instruments";
    for (std::string n : instruList) {
        qDebug() << QString::fromStdString(n);
    }


    TSE3::Ins::Instrument *instrumentSD2 = instrus.instrument("Ketron SD2");
    qDebug() << "There is " << instrumentSD2->numBanks() << " banks in Ketron SD2 instruments";

    qDebug() << "\n";
    TSE3::Ins::PatchData *patch = instrumentSD2->patchForBank(1);
    for(int i = 0; i < instrumentSD2->numBanks(); i++){
        patch = instrumentSD2->patch(i);
        qDebug() << "Bank adress " << instrumentSD2->bank(i);
        qDebug() << "Bank title " << QString::fromStdString(patch->title());
        qDebug() << "There is " << patch->size() << " voices in this patch";
        qDebug() << "\n";

    }

    InstrumentExplorer::voice voice;
    int banksToLoad[3] = {2, 3, 4};

    for(int i = 0; i < 3; i++)
    {
        patch = instrumentSD2->patch(banksToLoad[i]);

        //qDebug() <<  QString::fromStdString(patch->title()) << "voices:";

        //fileBnk.setFileName(QString::fromStdString(patch->title()).replace(" ", "_") + ".csv");

        //qDebug() << QString::fromStdString(patch->title()).replace(" ", "_") + ".csv";

        QString filePath = QString::fromStdString(patch->title()).replace(" ", "_") + ".csv";

        CsvParser csvParser(filePath, ',', 0);

        for (int j = 0; j < patch->size(); j ++){
            voice.bankAdress = instrumentSD2->bank(banksToLoad[i]);
            voice.patchNum = j+1;
            voice.name = QString::fromStdString(patch->name(j));
            //voice.typeOfInstrus =  instru_type::ACCORD_HARMO;
            voice.typeOfInstrus = csvParser.getField(j, 2).simplified();
            //qDebug() << csvParser.getField(j, 2);
            m_voices.append(voice);
            //qDebug() << "voice.name" << voice.name << ;

            m_categories.append(csvParser.getField(j, 2).simplified());
        }

        //qDebug() << "\n";

    }


    m_categories.removeDuplicates();
}


QStringList InstrumentExplorer::getIntrumentCategories(void)
{
    //qDebug() << m_categories;
    return m_categories;
}

QStringList InstrumentExplorer::getIntrumentListFromCategory(QString cat)
{

    QStringList instruList;

    //qDebug() << cat;

    for (int i = 0; i <  m_voices.length(); i++)
    {
        if (m_voices.at(i).typeOfInstrus == cat)
        {
            instruList.append(m_voices.at(i).name);
        }
    }

    return instruList;
}

void InstrumentExplorer::loadIntrument(QString instruToLoad, quint8 channel)
{
    for (int i = 0; i <  m_voices.length(); i++)
    {
        if (m_voices.at(i).name == instruToLoad)
        {
            qDebug() << i << " User wants to load " << m_voices.at(i).name << ", bank: " << m_voices.at(i).bankAdress << ", programm:" << m_voices.at(i).patchNum;
//            requestInstrumentLoading(m_voices.at(i).bankAdress, m_voices.at(i).patchNum, 1);
//            requestInstrumentLoading(m_voices.at(i).bankAdress, m_voices.at(i).patchNum, 2);
//            requestInstrumentLoading(m_voices.at(i).bankAdress, m_voices.at(i).patchNum, 3);
            requestInstrumentLoading(m_voices.at(i).bankAdress, m_voices.at(i).patchNum, channel);
        }
    }
}

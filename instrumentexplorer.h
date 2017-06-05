#ifndef INSTRUMENTEXPLORER_H
#define INSTRUMENTEXPLORER_H

#include <QObject>
#include <QVector>

class InstrumentExplorer : public QObject
{
    Q_OBJECT
public:
    explicit InstrumentExplorer(QObject *parent = 0);

    enum instru_type{
        PIANO,
        ORGAN,
        GUITAR_BASS,
        ACCORD_HARMO,
        STRING_CHOIR,
        BRASS,
        WOODWIND,
        DRUMS_PERCU
    } ;

    struct voice{
        QString name;
        int patchNum;
        int bankAdress;
        QString typeOfInstrus;
    };

    struct bankPatch{
        QString name;

        struct instru{
            int programChange;
            QString name;
            QString typeOfInstrus;
        };
    };

    void loadAllVoices();

    void setTypeOfInstru(int indexBegin, int indexEnd);

    Q_INVOKABLE QStringList getIntrumentCategories(void);
    Q_INVOKABLE QStringList getIntrumentListFromCategory(QString cat);
    Q_INVOKABLE void loadIntrument(QString instruToLoad, quint8 channel);



signals:
    void requestInstrumentLoading(uint8_t bank, uint8_t program, uint8_t channel);

public slots:

private:
    QVector<InstrumentExplorer::voice> m_voices;
    QStringList m_categories;
};

#endif // INSTRUMENTEXPLORER_H

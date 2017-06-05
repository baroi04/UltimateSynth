#ifndef PATCHPARSER_H
#define PATCHPARSER_H

#include <QObject>

class PatchParser : public QObject
{
    Q_OBJECT
public:
    explicit PatchParser(QObject *parent = 0);

    void openPatch(QString path);

    // getInstrumentAdress(QString intrumentName)

signals:

public slots:

private:
    QStringList m_InstrumentsTable[4]; // 0: Name, 1: Bank, 2: Program, 3: category
};

#endif // PATCHPARSER_H


// Cette classe ouvre le fichier de patch
// Elle fournit la liste de tous les instruments à l'interface QML
// Lorsque l'utilisateur choisi un intrument dans l'interface QML il appelle la fonction getInstrumentAdress
// LOrsque l'utilisateur a a sa diposition l'adresse de l'instrument il peut faire appel a la fonction selectInstrument de la classe ramidi

#ifndef PATCHPARSER_H
#define PATCHPARSER_H

#include <QObject>

class PatchParser : public QObject
{
    Q_OBJECT
public:
    explicit PatchParser(QObject *parent = 0);

signals:

public slots:
};

#endif // PATCHPARSER_H
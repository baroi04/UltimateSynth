#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class testCLASS : public QObject
{
    Q_OBJECT
public:
    explicit testCLASS(QObject *parent = 0);

signals:

public slots:
};

#endif // TESTCLASS_H
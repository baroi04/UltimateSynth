#ifndef SPAWN_H
#define SPAWN_H


#include <QObject>
#include <QProcess>

class Spawn : public QObject
{
    Q_OBJECT
public:
    explicit Spawn(QObject *parent = 0);

    void init(QString program, QStringList arguments, QString workdir = "");

    void start();

    Q_INVOKABLE void writeToStdin(QString string);

signals:

public slots:
    void stdOutHandler();
    void processtHandler();

private:
    QString m_programPath;
    QStringList m_argument;
    QString m_workDir;
    QProcess m_process;


};

#endif // SPAWN_H

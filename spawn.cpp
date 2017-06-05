#include <spawn.h>
#include <QDebug>
#include <QString>
#include <QStringList>

Spawn::Spawn(QObject *parent) : QObject(parent)
{
    m_programPath = "";
    m_argument = QStringList();
    m_workDir = "";

}

void Spawn::init(QString program, QStringList argument, QString workdir)
{
    m_programPath = program;
    m_argument = argument;
    m_workDir = workdir;
    m_process.setWorkingDirectory(m_workDir);

    connect(&m_process, SIGNAL(started()), this, SLOT(processtHandler()) );
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(stdOutHandler()) );

}

void Spawn::start()
{
    if(m_programPath != ""){
       m_process.start(m_programPath, m_argument);
        //m_process.startDetached(m_programPath, m_argument);
    }else
    {
        qDebug() << "ERROR: Spawn::start. Object not initialised. Call Spawn::init first";
    }


}

void Spawn::processtHandler()
{
     qDebug() << "Process state changed";
}

void Spawn::writeToStdin(QString string)
{
    m_process.write((string + "\n").toLocal8Bit());
}


void Spawn::stdOutHandler()
{
    QStringList strLines = QString(m_process.readAllStandardOutput()).split("\n");
    for (int i = 0; i < strLines.size(); i++){
        qDebug() << strLines.at(i);
    }

}

//QString program = "/home/pi/ombl/ombl";
//QStringList arguments;
//QString result;
//QProcess myProcess;
//myProcess.setWorkingDirectory("/home/pi/ombl/");
//myProcess.start(program);

//myProcess.waitForStarted();
//qDebug() << myProcess.state();

////myProcess.write("Hello\n");

//myProcess.waitForReadyRead();

//QStringList strLines = QString(myProcess.readAllStandardOutput()).split("\n");
//for (int i = 0; i < strLines.size(); i++){
//    qDebug() << strLines.at(i);
//}


//myProcess.write("Main A\n");
//myProcess.waitForReadyRead();

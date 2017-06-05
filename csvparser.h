#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QString>
#include <QList>
#include <QStringList>

class CsvParser
{
public:
    CsvParser();
    CsvParser(QString filePath, char delimiter, int firstLineIsHeader);

    QString getField(int rowNumber, int colNumber);


    // Public
//    const CsvRow getHeader();
//    CsvRow * getRow();
//    int getNumFields(const CsvRow *csvRow);
//    const char ** getFields(const CsvRow *csvRow);
//    QString getErrorMessage();

private:
    // Private
//    CsvRow *priv_getRow();
//    int delimiterIsAccepted(const char *delimiter);
//    void setErrorMessage(QString message);

//    QString m_filePath;
//    char m_delimiter;
//    int m_firstLineIsHeader;
//    QString m_errMsg;
//    CsvRow *m_header;
//    FILE *m_fileHandler;
//    int m_fromString;
//    char *m_csvString;
//    int m_csvStringIter;

    QList< QStringList> m_csvContent;
};

#endif // CSVPARSER_H

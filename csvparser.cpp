#include "csvparser.h"
#include <QString>
#include <QFile>
#include <QDebug>

CsvParser::CsvParser(QString filePath, char delimiter, int firstLineIsHeader)
{

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }


    while (!file.atEnd()) {
        QString line = QString::fromLocal8Bit(file.readLine());
        m_csvContent.append(line.split(delimiter));
    }

}

QString CsvParser::getField(int rowNumber, int colNumber)
{
    return m_csvContent.at(rowNumber).at(colNumber);
}


//const CsvRow CsvParser::getHeader() {
//    if (! m_firstLineIsHeader) {
//        setErrorMessage("Cannot supply header, as current CsvParser object does not support header");
//        return NULL;
//    }

//    if (m_header == "") {
//        m_header = getRow();
//    }

//    return m_header;
//}

//CsvParser::CsvRow CsvParser::getRow() {
//    if (m_firstLineIsHeader && m_header == "") {
//        m_header = getRow();
//    }
//    return getRow();
//}

//int CsvParser::getNumFields(const CsvRow *csvRow) {
//    return csvRow->numOfFields_;
//}

//const char ** CsvParser::getFields(const CsvRow *csvRow) {
//    return (const char**)csvRow->fields_;
//}


//CsvParser::CsvRow * CsvParser::priv_getRow() {
//    int numRowRealloc = 0;
//    int acceptedFields = 64;
//    int acceptedCharsInField = 64;

//    if (m_filePath == "") {
//        setErrorMessage("Supplied CSV file path is NULL");
//        return NULL;
//    }

//    if (m_delimiter == '\0') {
//        setErrorMessage("Supplied delimiter is not supported");
//        return NULL;
//    }

//    QString errStr;
//    if (m_fileHandler == NULL) {
//        m_fileHandler = fopen(m_filePath.toStdString().c_str(), "r");
//        if (m_fileHandler == NULL) {
//            int errorNum = errno;
//            errStr = QString::fromLocal8Bit(strerror(errorNum));
//            setErrorMessage("Error opening CSV file for reading" + m_filePath + errStr);
//            return NULL;
//        }
//    }

//    CsvRow *csvRow = (CsvRow*)malloc(sizeof(CsvRow));
//    csvRow->fields_ = (char**)malloc(acceptedFields * sizeof(char*));
//    csvRow->numOfFields_ = 0;

//    int fieldIter = 0;
//    char *currField = (char*)malloc(acceptedCharsInField);
//    int inside_complex_field = 0;
//    int currFieldCharIter = 0;
//    int seriesOfQuotesLength = 0;
//    int lastCharIsQuote = 0;
//    int isEndOfFile = 0;
//    while (1) {
//        char currChar = (csvParser->fromString_) ? csvParser->csvString_[csvParser->csvStringIter_] : fgetc(csvParser->fileHandler_);
//        csvParser->csvStringIter_++;
//        int endOfFileIndicator;
//        if (csvParser->fromString_) {
//            endOfFileIndicator = (currChar == '\0');
//        } else {
//            endOfFileIndicator = feof(csvParser->fileHandler_);
//        }
//        if (endOfFileIndicator) {
//            if (currFieldCharIter == 0 && fieldIter == 0) {
//                _CsvParser_setErrorMessage(csvParser, "Reached EOF");
//                free(currField);
//                CsvParser_destroy_row(csvRow);
//                return NULL;
//            }
//            currChar = '\n';
//            isEndOfFile = 1;
//        }
//        if (currChar == '\r') {
//            continue;
//        }
//        if (currFieldCharIter == 0  && ! lastCharIsQuote) {
//            if (currChar == '\"') {
//                inside_complex_field = 1;
//                lastCharIsQuote = 1;
//                continue;
//            }
//        } else if (currChar == '\"') {
//            seriesOfQuotesLength++;
//            inside_complex_field = (seriesOfQuotesLength % 2 == 0);
//            if (inside_complex_field) {
//                currFieldCharIter--;
//            }
//        } else {
//            seriesOfQuotesLength = 0;
//        }
//        if (isEndOfFile || ((currChar == csvParser->delimiter_ || currChar == '\n') && ! inside_complex_field) ){
//            currField[lastCharIsQuote ? currFieldCharIter - 1 : currFieldCharIter] = '\0';
//            csvRow->fields_[fieldIter] = (char*)malloc(currFieldCharIter + 1);
//            strcpy(csvRow->fields_[fieldIter], currField);
//            free(currField);
//            csvRow->numOfFields_++;
//            if (currChar == '\n') {
//                return csvRow;
//            }
//            if (csvRow->numOfFields_ != 0 && csvRow->numOfFields_ % acceptedFields == 0) {
//                csvRow->fields_ = (char**)realloc(csvRow->fields_, ((numRowRealloc + 2) * acceptedFields) * sizeof(char*));
//                numRowRealloc++;
//            }
//            acceptedCharsInField = 64;
//            currField = (char*)malloc(acceptedCharsInField);
//            currFieldCharIter = 0;
//            fieldIter++;
//            inside_complex_field = 0;
//        } else {
//            currField[currFieldCharIter] = currChar;
//            currFieldCharIter++;
//            if (currFieldCharIter == acceptedCharsInField - 1) {
//                acceptedCharsInField *= 2;
//                currField = (char*)realloc(currField, acceptedCharsInField);
//            }
//        }
//        lastCharIsQuote = (currChar == '\"') ? 1 : 0;
//    }
//}

//int CsvParser::delimiterIsAccepted(const char *delimiter) {
//    char actualDelimiter = *delimiter;
//    if (actualDelimiter == '\n' || actualDelimiter == '\r' || actualDelimiter == '\0' ||
//            actualDelimiter == '\"') {
//        return 0;
//    }
//    return 1;
//}

//void CsvParser::setErrorMessage(CsvParser *csvParser, const char *errorMessage) {
//    if (csvParser->errMsg_ != NULL) {
//        free(csvParser->errMsg_);
//    }
//    int errMsgLen = strlen(errorMessage);
//    m_errMsg = (char*)malloc(errMsgLen + 1);
//    strcpy(csvParser->errMsg_, errorMessage);
//}

//QString CsvParser::getErrorMessage() {
//    return m_errMsg;
//}

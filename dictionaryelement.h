#ifndef DICTIONARYELEMENT_H
#define DICTIONARYELEMENT_H


#include <QString>
#include <QtSql/qsql.h>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#define NATIONAL_TABLE QString("nativeLanguage")
#define FOREIGN_TABLE QString("foreignLanguage")

class DictionaryElement
{
public:

    DictionaryElement(QList<QString> *nationalWord, QList<QString> *foreignWord, QList<QString> *transcription, QList<QString> *soundPath);
    DictionaryElement();
    ~DictionaryElement();


    QList<QString> *nationalWord;
    QList<QString> *foreignWord;
    QList<QString> *transcription;
    QList<QString> *soundPath;
};

#endif // DICTIONARYELEMENT_H

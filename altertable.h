#ifndef ALTERTABLE_H
#define ALTERTABLE_H

#include <QDialog>
#include <QRegExp>
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

namespace Ui {
class AlterTable;
}

class AlterTable : public QDialog
{
    Q_OBJECT

public:
    explicit AlterTable(QWidget *parent = 0);
    AlterTable(bool show);
    ~AlterTable();
    void createTranslationInDB(QString foreignWord, QStringList translationWordsList, QString transcription);

public slots:
    void createTranslation();

private:
    Ui::AlterTable *ui;
    QSqlDatabase DataBase;
    QSqlQueryModel *query;
    QSqlQuery *changeQuery;
    bool validation();

};

#endif // ALTERTABLE_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QPluginLoader>

#include "choosetest.h"
#include "altertable.h"



#define HOST "localhost"
#define DATABASE_NAME "spain"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "vjnjwbrk2000"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectDatabase();
    QSqlDatabase *getDataBase() const;
    void setDataBase(QSqlDatabase *value);

    QSqlQueryModel *getQuery() const;
    void setQuery(QSqlQueryModel *value);

public slots:
    void startTests();
    void alterTable();

private:
    Ui::MainWindow *ui;
    ChooseTest *chooseTestWindow;
    AlterTable *alterTableWindow;
    QSqlDatabase *DataBase;
    QSqlQueryModel *query;

};

#endif // MAINWINDOW_H

#ifndef TESTS_H
#define TESTS_H

#include <QDialog>
#include <QList>
#include <QShortcut>
#include <time.h>
#include "dictionaryelement.h"


#define FROM_NATIONAL 1
#define FROM_FOREIGN 2
#define ALL_RANDOM 3

namespace Ui {
class Tests;
}

class Tests : public QDialog
{
    Q_OBJECT

public:
    int nationalWordsCount;
    int foreignWordsCount;
    explicit Tests(QWidget *parent = 0);
    ~Tests();
    void setTest(int testVersion, int numOfTests);
public slots:
    void check();
    void next();
    void enter();

private:

    int testVersion = 3;
    int numOfTests = 20;
    QSqlDatabase DataBase;
    int rightAnswers;
    int completedTests;
    int testVersionLocal;
    bool checkOrNext = true;

    Ui::Tests *ui;
    QSqlQueryModel *query;
    DictionaryElement *dictionaryElement;
    QList<int> *foreignIds;
    QList<int> *nationalIds;


    void confirmForeignIds();
    void confirmNationalIds();
    DictionaryElement * randomElement();


};

#endif // TESTS_H

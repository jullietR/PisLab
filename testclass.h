#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <mainwindow.h>
#include <choosetest.h>
#include <altertable.h>
#include <dictionaryelement.h>


class TestClass
{
public:
    TestClass();
    bool test(MainWindow * mainWindow);

private:
    int numOfTests = 0;
    int numOfWrongTests = 0;
    QString answer = "";
    void assertEqual();
    void assertTrue(bool check);
};

#endif // TESTCLASS_H

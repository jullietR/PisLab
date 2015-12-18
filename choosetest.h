#ifndef CHOOSETEST_H
#define CHOOSETEST_H

#include <QDialog>

#include "tests.h"

namespace Ui {
class ChooseTest;
}

class ChooseTest : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseTest(QWidget *parent = 0);
    ~ChooseTest();

    void setNationalSize(int nationalSize);
    void setForeignSize(int foreignSize);


public slots:
    void fromNational();
    void fromForeign();
    void allRandom();
    void editCheck(int testVersion);

private:
    Ui::ChooseTest *ui;
    Tests *testWindow;

};

#endif // CHOOSETEST_H

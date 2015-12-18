#include "testclass.h"

TestClass::TestClass()
{

}

/**
 * @brief TestClass::test
 * \n test for mainWiondow
 * @param mainWindow
 * \n our mainWindow we want to test
 * @return
 * \n return true if all tests have been completed normally
 * \n return false otherwise
 */
bool TestClass::test(MainWindow *mainWindow)
{
    assertTrue(mainWindow->getDataBase()->isOpen());//1st test проверяет открыта ли база данных
    mainWindow->getQuery()->setQuery(QString("SELECT COUNT(*) FROM %1").arg(FOREIGN_TABLE),*mainWindow->getDataBase());
    assertTrue(mainWindow->getQuery()->data(mainWindow->getQuery()->index(0, 0)).toInt() > 0);//2nd test проверяет есть ли хоть одна запись в БД

    qDebug() << "\n\n" << "Tests complete\n\n" << "tests: " << numOfTests << ", errors: " << numOfWrongTests << "\n" << answer << "\n\n";
    mainWindow->close();
    delete mainWindow;
    if(numOfWrongTests == 0)
    {
        return true;
    }
    return false;
}

/**
 * @brief TestClass::assertTrue
 * \n our test function
 * \n if check is true, test is succesfull, another way we have error
 * @param check
 */
void TestClass::assertTrue(bool check)
{
    ++numOfTests;
    if(!check)
    {
        ++numOfWrongTests;
        answer += QString("Error in %1 test.").arg(QString::number(numOfTests));
    }
}


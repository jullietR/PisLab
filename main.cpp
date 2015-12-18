#include <testclass.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestClass tests;
    if(tests.test(new MainWindow()))
    {
    MainWindow w;
    w.show();



    return a.exec();
    }
    return 0;
}

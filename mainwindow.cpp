#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * \n standart constructor for out MainWindow class
 * \n set all dependencies
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connectDatabase();
    query = new QSqlQueryModel();
    ui->setupUi(this);
    QObject::connect(ui->testButton,SIGNAL(clicked()),this,SLOT(startTests()));
    QObject::connect(ui->atlerDataBaseButton,SIGNAL(clicked()),this,SLOT(alterTable()));
    QObject::connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(close()));
}

/**
 * @brief MainWindow::~MainWindow
 * \n destructor for our MainWindow class
 */
MainWindow::~MainWindow()
{
    delete ui;

}

/**
 * @brief MainWindow::startTests
 * \n create test window and set all dependencies
 */
void MainWindow::startTests()
{
    chooseTestWindow = new ChooseTest();
    query->setQuery(QString("SELECT COUNT(*) FROM %1").arg(FOREIGN_TABLE),*DataBase);
    chooseTestWindow->setNationalSize(query->data(query->index(0, 0)).toInt());
    query->setQuery(QString("SELECT COUNT(*) FROM %1").arg(NATIONAL_TABLE),*DataBase);
    chooseTestWindow->setForeignSize(query->data(query->index(0, 0)).toInt());
    chooseTestWindow->show();
}

/**
 * @brief MainWindow::alterTable
 * \n create alter window and set all dependencies
 */
void MainWindow::alterTable()
{
    alterTableWindow = new AlterTable();
    alterTableWindow->show();
}

/**
 * @brief MainWindow::getQuery
 * @return query
 */
QSqlQueryModel *MainWindow::getQuery() const
{
    return query;
}

/**
 * @brief MainWindow::setQuery
 * \n set query we need for connection for databases
 * @param value
 * \n query we want to use in this class
 */
void MainWindow::setQuery(QSqlQueryModel *value)
{
    query = value;
}

/**
 * @brief MainWindow::getDataBase
 * @return
 * \n return DataBase
 */
QSqlDatabase *MainWindow::getDataBase() const
{
    return DataBase;
}

/**
 * @brief MainWindow::setDataBase
 * \n set database we need for connection
 * @param value
 * \n database we want to use in this class
 */
void MainWindow::setDataBase(QSqlDatabase *value)
{
    DataBase = value;
}

/**
 * @brief MainWindow::connectDatabase
 * \n create database connection
 */
void MainWindow::connectDatabase()
{
    DataBase = new QSqlDatabase;
    *DataBase = QSqlDatabase::addDatabase("QMYSQL", "mydb");
    DataBase->setHostName(HOST);
    DataBase->setDatabaseName(DATABASE_NAME);
    DataBase->setUserName(DATABASE_USERNAME);
    DataBase->setPassword(DATABASE_PASSWORD);
    if (!DataBase->open())
    {
        qDebug() << DataBase->lastError();
        QMessageBox Message;
        Message.setText("error");
        Message.exec();
    }
}

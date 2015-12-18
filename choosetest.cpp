#include "choosetest.h"
#include "ui_choosetest.h"

/**
 * @brief ChooseTest::ChooseTest
 * \n standart constructor for out ChooseTest class
 * \n set all dependencies
 * @param parent
 */
ChooseTest::ChooseTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTest)
{
    ui->setupUi(this);
    testWindow = new Tests();
    QObject::connect(ui->nationalButton,SIGNAL(clicked()),this,SLOT(fromNational()));
    QObject::connect(ui->foreignButton,SIGNAL(clicked()),this,SLOT(fromForeign()));
    QObject::connect(ui->randomButton,SIGNAL(clicked()),this,SLOT(allRandom()));
}

/**
 * @brief ChooseTest::~ChooseTest
 * \n destructor for our class
 */
ChooseTest::~ChooseTest()
{
    delete ui;
}

/**
 * @brief ChooseTest::setNationalSize
 * \n set value for maximum national words
 * @param nationalSize
 * \n maximum national words
 */
void ChooseTest::setNationalSize(int nationalSize)
{
    ui->maxNationalSizeLabel->setText(QString::number(nationalSize));
}

/**
 * @brief ChooseTest::setForeignSize
 * \n set value for maximum foreign words
 * @param foreignSize
 * \n maximum foreign words
 */
void ChooseTest::setForeignSize(int foreignSize)
{
    ui->maxForeignSizeLabel->setText(QString::number(foreignSize));
}

/**
 * @brief ChooseTest::fromNational
 * \n set test variation from national language to foreign
 */
void ChooseTest::fromNational()
{
    editCheck(FROM_NATIONAL);
}

/**
 * @brief ChooseTest::fromForeign
 * \n set test variation from foreign language to national
 */
void ChooseTest::fromForeign()
{
    editCheck(FROM_FOREIGN);
}

/**
 * @brief ChooseTest::allRandom
 * \n set test variation to random
 * \n this means that every test you will have random translarion
 * \n fromForeign() or :fromNational()
 */
void ChooseTest::allRandom()
{
    editCheck(ALL_RANDOM);
}

/**
 * @brief ChooseTest::editCheck
 * \n check if number of test you want is integer
 * \n if this value is not integer you will get warning on GUI
 * \n if number of tests is more than maximum num of tests
 * \n number of tests will be set to maximum
 * @param testVersion
 */
void ChooseTest::editCheck(int testVersion)
{
    if(int numOfTest = ui->numOfTestEdit->text().toInt())
    {
        delete testWindow;
        testWindow = new Tests();
        testWindow->setTest(testVersion, numOfTest);
        testWindow->next();
        testWindow->show();
        this->close();
    }
    else
    {
        ui->errorLabel->setText("Wrong number!");
        ui->numOfTestEdit->setText("15");
    }
}

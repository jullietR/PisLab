#include "tests.h"
#include "ui_tests.h"

/**
 * @brief Tests::Tests
 * \n standart constructor for out Tests class
 * \n set all dependencies
 * @param parent
 */
Tests::Tests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tests)
{
    ui->setupUi(this);
    nationalWordsCount = 0;
    foreignWordsCount = 0;
    rightAnswers = 0;
    completedTests = 0;
    DataBase = QSqlDatabase::database("mydb");
    query = new QSqlQueryModel();
    foreignIds = new QList<int>();
    nationalIds = new QList<int>();
    qsrand(time(NULL));
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);

    QObject::connect(shortcut,SIGNAL(activated()),this,SLOT(enter()));
    QObject::connect(ui->nextWordButton,SIGNAL(clicked()), this, SLOT(next()));
    QObject::connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(check()));
}

/**
 * @brief Tests::~Tests
 * \n destructor for our class
 */
Tests::~Tests()
{
    delete query;
    delete foreignIds;
    delete nationalIds;
    delete ui;
}

/**
 * @brief Tests::setTest
 * \n set number of tests you want to complete and also set test version (look ChooseTest class)
 * @param testVersion
 * \n can be ALL_RANDOM (3), FROM_FOREIGN(2), FROM_NATIONAL(1) constants
 * @param numOfTests
 * \n number of tests you want to complete
 */
void Tests::setTest(int testVersion, int numOfTests)
{
    this->testVersion = testVersion;
    confirmForeignIds();
    confirmNationalIds();
    nationalWordsCount = nationalIds->size();
    foreignWordsCount = foreignIds->size();
    if(3 == testVersion)
    {
        testVersion = foreignWordsCount > nationalWordsCount ? 2 : 1;
    }
    switch(testVersion)
    {
    case 1:
        if(numOfTests > foreignWordsCount)
        {
            numOfTests = foreignWordsCount;
        }
        break;
    case 2:
        if(numOfTests > nationalWordsCount)
        {
            numOfTests = nationalWordsCount;
        }
        break;
    default:
        break;
    }
    this->numOfTests = numOfTests;
}

/**
 * @brief Tests::check
 * \n check your answers
 */
void Tests::check()
{
    checkOrNext = false;
    QString str;
    QString answer = ui->answerEdit->text();
    switch (testVersionLocal) {
    case 1:
        if(dictionaryElement->foreignWord->contains(answer))
        {
            ui->correctLabel->setText("Right!!!");
            ++rightAnswers;
        }
        else
        {
            ui->correctLabel->setText("Wrong!!!");
        }
        str = "";
        for(int i = 0, size = dictionaryElement->foreignWord->size(); i < size; ++i)
        {
            str += dictionaryElement->foreignWord->at(i);
            if(i != size - 1)
            {
                str += ", ";
            }
        }
        ui->translationLabel->setText(str);
        break;
    case 2:
        if(dictionaryElement->nationalWord->contains(answer))
        {
            ui->correctLabel->setText("Right!!!");
            ++rightAnswers;
        }
        else
        {
            ui->correctLabel->setText("Wrong!!!");
        }
        str = "";
        for(int i = 0, size = dictionaryElement->nationalWord->size(); i < size; ++i)
        {
            str += dictionaryElement->nationalWord->at(i);
            if(i != size - 1)
            {
                str += ", ";
            }
        }
        ui->translationLabel->setText(str);
        ui->transcriptionLabel->setText(dictionaryElement->transcription->at(0));
        break;
    default:
        break;
    }
    if(completedTests == numOfTests)
    {
        QMessageBox box;
        box.setText(QString("Test completed. Your mark(0 to 10): %1(%2/%3)").arg((int)(10 * rightAnswers / numOfTests)).arg(rightAnswers).arg(numOfTests));
        box.exec();
        this->close();
        delete this;
    }
}

/**
 * @brief Tests::next
 * \n give you next task on GUI
 */
void Tests::next()
{
    checkOrNext = true;
    ++completedTests;
    testVersionLocal = testVersion;
    if(testVersionLocal == 3)
    {
        testVersionLocal = qrand() % 2 + 1;
    }
    QString str = "";
    switch (testVersionLocal) {
    case 1:
        dictionaryElement = randomElement();
        for(int i = 0, size = dictionaryElement->nationalWord->size(); i < size; ++i)
        {
            str += dictionaryElement->nationalWord->at(i);

            if(i != (size - 1))
            {
                str += ", ";
            }
        }
        break;
    case 2:
        dictionaryElement = randomElement();
        for(int i = 0, size = dictionaryElement->foreignWord->size(); i < size; ++i)
        {
            str += dictionaryElement->foreignWord->at(i);
            if(i != size - 1);
            {
                str += ", ";
            }
        }
        break;
    default:
        break;
    }
    ui->taskLabel->setText(str);
    ui->correctLabel->clear();
    ui->transcriptionLabel->setText(QString::number(this->numOfTests));
    ui->translationLabel->clear();
    ui->answerEdit->clear();
}

/**
 * @brief Tests::enter
 * \n slot for quick enter
 * \n firts time you used it, it will start check() function
 * \n second time you used it, it will start next() function
 */
void Tests::enter()
{
    if(checkOrNext)
    {
        check();

    }
    else
    {
        next();
    }

}

/**
 * @brief Tests::randomElement
 * @return
 * \n random Dictionary element for your test
 * \n and remove it from list of aviable elements for this test
 */
DictionaryElement *Tests::randomElement()
{
    confirmForeignIds();
    confirmNationalIds();
    nationalWordsCount = nationalIds->size();
    foreignWordsCount = foreignIds->size();
    int id;
    QList<QString> *nationalWords = new QList<QString>();
    QList<QString> *foreignWords = new QList<QString>();
    QList<QString> *transcriptions = new QList<QString>();
    QList<QString> *soundPaths = new QList<QString>();
    switch (testVersionLocal) {
    case 1:
        id = foreignIds->takeAt(qrand() % foreignWordsCount);
        query->setQuery((QString("SELECT word, transcription, soundPath FROM foreignLanguage WHERE id = %1")).arg(id), DataBase);
        if(query->rowCount())
        {
            foreignWords->append(query->data(query->index(0,0)).toString());
            transcriptions->append(query->data(query->index(0,1)).toString());
            soundPaths->append(query->data(query->index(0,2)).toString());
            query->setQuery(QString("SELECT idNative FROM translation WHERE idForeign = %1").arg(id), DataBase);
            int rowCount = query->rowCount();
            int *nationalIdArray = new int[rowCount];
            for(int i = 0; i < rowCount; ++i)
            {
                nationalIdArray[i] = query->data(query->index(i, 0)).toInt();
            }
            QString str = "SELECT word FROM nativeLanguage WHERE id IN(";
            for(int i = 0; i < rowCount; ++i)
            {
                str += QString::number(nationalIdArray[i]);
                if(i != rowCount - 1)
                {
                    str+=",";
                }

            }
            str +=")";
            query->setQuery(str, DataBase);
            rowCount = query->rowCount();
            for(int i = 0; i < rowCount; ++i)
            {
                nationalWords->append(query->data(query->index(i, 0)).toString());
            }

        }
        else
        {
            QMessageBox *messageBox = new QMessageBox();
            messageBox->setText("ERROROOORORO");
            messageBox->exec();
        }


        break;
    case 2:
        id = nationalIds->takeAt(qrand() % nationalWordsCount);
        query->setQuery(QString("SELECT word FROM nativeLanguage WHERE id = %1").arg(id), DataBase);
        if(query->rowCount())
        {

            nationalWords->append(query->data(query->index(0,0)).toString());
            query->setQuery(QString("SELECT idForeign FROM translation WHERE idNative = %1").arg(id), DataBase);
            int * foreignIdArray = new int[query->rowCount()];
            for(int i = 0, size = query->rowCount(); i < size; ++i)
            {
                foreignIdArray[i] = query->data(query->index(i, 0)).toInt();
            }
            QString str = "SELECT word FROM foreignLanguage WHERE id IN(";
            for(int i = 0, size = query->rowCount(); i < size; ++i)
            {
                str += QString::number(foreignIdArray[i]);
                if(i != size - 1)
                {
                    str+=",";
                }

            }
            str +=")";
            query->setQuery(str, DataBase);
            int rowCount = query->rowCount();
            for(int i = 0; i < rowCount; ++i)
            {
                foreignWords->append(query->data(query->index(i, 0)).toString());
            }
        }
        else
        {
            QMessageBox *messageBox = new QMessageBox();
            messageBox->setText("ERROROOORORO");
            messageBox->exec();
        }

        break;

    default:
        break;
    }
    DictionaryElement *dE = new DictionaryElement(nationalWords,foreignWords,transcriptions,soundPaths);
    return dE;
}



/**
 * @brief Tests::confirmForeignIds
 * \n create list of ids in DB of foreign words
 */
void Tests::confirmForeignIds()
{
    if(foreignIds->isEmpty())
    {
        query->setQuery("SELECT id FROM foreignLanguage", DataBase);
        for(int i = 0, rowCount = query->rowCount(); i< rowCount; ++i)
        {
            foreignIds->append(query->data(query->index(i, 0)).toInt());
        }
    }
}

/**
 * @brief Tests::confirmNationalIds
 * \n create list of ids in DB of national words
 */
void Tests::confirmNationalIds()
{
    if(nationalIds->isEmpty())
    {
        query->setQuery("SELECT id FROM nativeLanguage", DataBase);
        for(int i = 0, rowCount = query->rowCount(); i< rowCount; ++i)
        {
            nationalIds->append(query->data(query->index(i, 0)).toInt());
        }
    }
}


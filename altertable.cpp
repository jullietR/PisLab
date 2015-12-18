#include "altertable.h"
#include "ui_altertable.h"

/**
 * @brief AlterTable::AlterTable
 * \n standart constructor for out AlterTable class
 * \n set all dependencies
 * @param parent
 */
AlterTable::AlterTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterTable)
{
    ui->setupUi(this);
    ui->errorLabel->setText("");
    DataBase = QSqlDatabase::database("mydb");
    query = new QSqlQueryModel();
    changeQuery = new QSqlQuery(DataBase);

    QObject::connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(createTranslation()));
}

/**
 * @brief AlterTable::AlterTable
 * \n this class(AlterTable) can be used for not GUI operations
 * \n for this you need to desable GUI
 * @param show
 * \n true to show GUI
 * \n false to hide GUI
 */
AlterTable::AlterTable(bool show)
{
    AlterTable();
    this->setVisible(show);
}

/**
 * @brief AlterTable::~AlterTable
 * \n destructor for our class
 */
AlterTable::~AlterTable()
{
    delete ui;
}

/**
 * @brief AlterTable::createTranslationInDB
 * \n create foreign word with transcription in DB
 * \n also create translations in DB
 * \n create dependencies in DB between foreign words and translations
 * \n if foreign word or translations have been allready created
 * \n we don't add them again
 * \n we only add dependencies
 * @param foreignWord
 * @param translationWordsList
 * \n one foreign word can have several translations
 * @param transcription
 */
void AlterTable::createTranslationInDB(QString foreignWord, QStringList translationWordsList, QString transcription)
{
    changeQuery->exec(QString("INSERT INTO foreignLanguage (word, transcription) VALUES('%1','%2')").arg(foreignWord).arg(transcription));
    qDebug() << changeQuery->lastError();
    query->setQuery(QString("SELECT id FROM foreignLanguage WHERE word = '%1'").arg(foreignWord),DataBase);
    int foreignWordId = query->data(query->index(0,0)).toInt();
    for(int i = 0, size = translationWordsList.size(); i < size; ++i)
    {
        changeQuery->exec(QString("INSERT INTO nativeLanguage (word) VALUES('%1')").arg(translationWordsList[i]));
    }
    QString str = "SELECT id FROM nativeLanguage WHERE word IN (";
    for(int i = 0, size = translationWordsList.size(); i < size; ++i)
    {
        str += "'" + translationWordsList[i] + "'";
        if(i != size - 1)
        {
            str += ",";
        }
    }
    str += ")";
    query->setQuery(str,DataBase);
    int * nationalWordIds = new int[query->rowCount()];
    for(int i = 0, size = query->rowCount(); i < size; ++i)
    {
        nationalWordIds[i] = query->data(query->index(i, 0)).toInt();
    }
    for(int i = 0, size = query->rowCount(); i < size; ++i)
    {
        changeQuery->exec(QString("INSERT INTO translation VALUES(%1,%2)").arg(nationalWordIds[i]).arg(foreignWordId));

    }
}

/**
 * @brief AlterTable::createTranslation
 * \n if input data from GUI has gone throught validation
 * \n it put input foreign word and transcription
 * \n into QString
 * \n input translations will be separated and put into QStringLists
 * \n than all information will be given to createTranslationInDB(QString foreignWord, QStringList translationWordsList, QString transcription) function
 */

void AlterTable::createTranslation()
{
    if(validation())
    {
        QString foreignWord = ui->foreignWordEdit->text().trimmed();
        QStringList translationWordsList = ui->translateWordEdit->text().split(",");
        QString transcription = ui->transcriptionEdit->text().trimmed();
        createTranslationInDB(foreignWord, translationWordsList, transcription);
        ui->foreignWordEdit->clear();
        ui->transcriptionEdit->clear();
        ui->translateWordEdit->clear();

    }

}

/**
 * @brief AlterTable::validation
 * \n check if the input information is ok for future work
 * @return
 * \n true if input is OK
 * \n false if input is not OK
 */

bool AlterTable::validation()
{
    QRegExp regExpTranslation("([\\w ,`-]+)");
    QRegExp regExp("([\\w `-]+)");
    if(regExpTranslation.exactMatch(ui->translateWordEdit->text()) &&
            regExp.exactMatch(ui->transcriptionEdit->text()) &&
            regExp.exactMatch(ui->foreignWordEdit->text()))
    {
        ui->errorLabel->clear();
        return true;
    }
    else
    {
        QString errorMassage = "Wrong ";
        if(!regExpTranslation.exactMatch(ui->translateWordEdit->text()))
        {
            errorMassage += "in translate ";
        }
        if(!regExp.exactMatch(ui->transcriptionEdit->text()))
        {
            errorMassage += "in transcription ";
        }

        if(!regExp.exactMatch(ui->foreignWordEdit->text()))
        {
           errorMassage += "in word ";
        }
        ui->errorLabel->setText(errorMassage);
        return false;
    }

}

#include "dictionaryelement.h"


/**
 * @brief DictionaryElement::DictionaryElement
 * \n standart constructo for our class
 * \n allmost not used
 */
DictionaryElement::DictionaryElement()
{
}

/**
 * @brief DictionaryElement::DictionaryElement
 * \n create DictionaryElement with start parametrs
 * @param nationalWord
 * @param foreignWord
 * @param transcription
 * @param soundPath
 */
DictionaryElement::DictionaryElement(QList<QString> *nationalWord, QList<QString> *foreignWord, QList<QString> *transcription, QList<QString> *soundPath)
{
    this->nationalWord = nationalWord;
    this->foreignWord = foreignWord;
    this->transcription = transcription;
    this->soundPath = soundPath;
}

/**
 * @brief DictionaryElement::~DictionaryElement
 * \n destructor for our class
 */
DictionaryElement::~DictionaryElement()
{
    delete nationalWord;
    delete foreignWord;
    delete transcription;
    delete soundPath;
}

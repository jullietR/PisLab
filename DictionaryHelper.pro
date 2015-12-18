#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T19:07:24
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DictionaryHelper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tests.cpp \
    choosetest.cpp \
    dictionaryelement.cpp \
    altertable.cpp \
    testclass.cpp

HEADERS  += mainwindow.h \
    tests.h \
    choosetest.h \
    dictionaryelement.h \
    altertable.h \
    testclass.h

FORMS    += mainwindow.ui \
    tests.ui \
    choosetest.ui \
    altertable.ui

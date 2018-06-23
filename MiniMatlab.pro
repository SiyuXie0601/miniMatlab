#-------------------------------------------------
#
# Project created by QtCreator 2018-05-10T11:29:05
#
#-------------------------------------------------

QT       += core gui\
            printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniMatlab
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Matrix.cpp \
    SortingSolution.cpp \
    EquationSolution.cpp \
    IntergrationSolution.cpp \
    interpreter.cpp \
    Real.cpp \
    modeldata.cpp \
    share.cpp \
    function1.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    Matrix.h \
    SortingSolution.h \
    EquationSolution.h \
    IntergrationSolution.h \
    interpreter.h \
    Real.h \
    modeldata.h \
    share.h \
    myexceptions.h \
    function1.h \
    qcustomplot.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

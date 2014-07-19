#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T21:43:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FYD_Project
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    src/wireless_communicator.cpp \
    src/FYD_Client.cpp \
    src/functions.cpp \
    src/conio.cpp \
    src/accelerometers.cpp \
    src/main.cpp \
    src/flexiforce.cpp \
    src/loadcell.cpp




HEADERS  += mainwindow.h \
    src/wireless_communicator.h \
    src/functions.h \
    src/conio.h \
    src/accelerometers.h \
    src/globals.h \
    src/flexiforce.h \
    src/loadcell.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lopencv_core -lopencv_highgui -lphidget21

#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T15:36:54
#
#-------------------------------------------------

QT       += core gui network sql positioning location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        myparentobject.cpp\
        rowdata.cpp

HEADERS += \
        mainwindow.h \
        myparentobject.h\
        enumtables.h \
        rowdata.h \
        PropertyHelper.h


FORMS += \
        mainwindow.ui

# set exe to bin directory and others file to tmp
OBJECTS_DIR = tmp
MOC_DIR = tmp
DESTDIR = bin

# my auto deploy on release mode
CONFIG(release, debug|release ) {
    # on release mode
        win32{
            TARGET_EXT = .exe
            DEPLOY_COMMAND = windeployqt
            DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/$${DESTDIR}/$${TARGET}$${TARGET_EXT}))

        #warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})
                QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
        }
}

#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T16:26:09
#
#-------------------------------------------------

QT       += widgets declarative opengl script scripttools xml xmlpatterns multimedia

CONFIG   += console
CONFIG   -= app_bundle
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = ExtraGuiQtLib
TEMPLATE = lib

DEFINES += EXTRAGUIQTLIB_LIBRARY

SOURCES += ExtraGuiQtLib.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    RootHelpers.cpp \
    FastClustering.cpp

HEADERS += ExtraGuiQtLib.h\
        extraguiqtlib_global.h \
    mainwindow.h \
    newPoint.h \
    qcustomplot.h \
    RootHelpers.h \
    FastClustering.h \
    Parameters.h

unix {
    target.path = ./
    INSTALLS += target
}

FORMS += \
    mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += alibava-soap


QT += widgets
QT += gui declarative
QMAKE_CXXFLAGS += `root-config --cflags --libs`
QMAKE_LIBS     += `root-config --libs`
QMAKE_CXXFLAGS +=  -std=c++11

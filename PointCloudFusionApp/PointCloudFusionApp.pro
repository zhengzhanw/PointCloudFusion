#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T15:49:35
#
#-------------------------------------------------

QT       += core gui


TARGET = PointCloudFusionApp
TEMPLATE = lib


CONFIG -= debug_and_release
CONFIG -= c++11
CONFIG += c++98

macx{
    QMAKE_CXXFLAGS -= -stdlib=libc++
    QMAKE_CXXFLAGS += -stdlib=libstdc++
    QMAKE_LFLAGS -= -stdlib=libc++
    QMAKE_LFLAGS += -stdlib=libstdc++
}

DESTDIR = ../lib
DLLDESTDIR = ../bin
OBJECTS_DIR = ../obj

DEFINES += POINTCLOUDFUSIONAPP_LIBRARY

SOURCES += \
    ReadFile.cpp
        

HEADERS  +=  \
    export.h \
    ReadFile.h
    

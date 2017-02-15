#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T15:49:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PointCloudFusion
TEMPLATE = app

CONFIG -= c++98
CONFIG += c++11
CONFIG -= debug_and_release

macx{
    QMAKE_CXXFLAGS -= -stdlib=libc++
    QMAKE_CXXFLAGS += -stdlib=libstdc++
    QMAKE_LFLAGS -= -stdlib=libc++
    QMAKE_LFLAGS += -stdlib=libstdc++
}

DESTDIR = ../bin
OBJECTS_DIR = ../obj
MOC_DIR = ./moc
RCC_DIR = ./rcc
UI_DIR = ./ui

win32{
    #win32
    INCLUDEPATH += ../ \

    LIBS += \
        -L$$OUT_PWD/../lib \

}else:unix{
    macx{
        #macx
    }else{
        #linux
    }
}

#Debug
CONFIG(debug,debug|release){
    win32{
        LIBS += \
        -lPointCloudFusionApp \
    }else:unix{
        macx{
            #macx
        }else{
            #linux
        }
    }
}

#release
CONFIG(release,debug|release){
    win32{
        LIBS += \
        -lPointCloudFusionApp \
    }else:unix{
        macx{
            #macx
        }else{
            #linux
        }
    }
}


SOURCES += main.cpp\
        mainwindow.cpp \
        zPCFWidget.cpp

HEADERS  += mainwindow.h \
        zPCFWidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

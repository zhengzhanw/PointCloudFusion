#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T15:49:35
#
#-------------------------------------------------

QT       += core gui

QT +=opengl

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

DEFINES += OSG_LIBRARY_STATIC
DEFINES += POINTCLOUDFUSIONAPP_LIBRARY

message($$(WIN_SYS_LIB))

INCLUDEPATH += ../ \
    F:/OpenSceneGraph3.2.3/include \
    F:/OpenSceneGraph3.2.3/3rdParty_msvc2013/include \
    E:/Root/opencv/opencv/build/include \

LIBS += \
    -L$$OUT_PWD/../lib \
    -L$$(WIN_SYS_LIB)/Lib \
    -LF:/OpenSceneGraph3.2.3/lib \
    -LF:/OpenSceneGraph3.2.3/lib/osgPlugins-3.2.3 \
    -LF:/OpenSceneGraph3.2.3/3rdParty_msvc2013/lib \
    -LE:/Root/opencv/opencv/build/x86/vc12/lib \
    -LE:/Root/opencv/opencv/build/x86/vc12/staticlib \

LIBS += \
    -lshell32 \
    -lOpengl32 \


CONFIG(debug,debug|release){

    LIBS += \
        -lopengl32d \
        -lopenThreadsd \
        -losgd \
        -losgDBd \
        -losgGAd \
        -losgParticled \
        -losgQtd \
        -losgUtild \
        -losgViewerd \
        -losgVolumed \
        -losgTextd \
        -losgdb_bmpd \
        -losgdb_deprecated_osgd \
        -losgdb_jpegd \
        -losgdb_pngd \
        -losgdb_rgbd \
        -losgdb_ss2d \
        -losgdb_serializers_osgd \
        -losgdb_ss2d \
        -lopencv_ml2410d \
        -lopencv_calib3d2410d \
        -lopencv_contrib2410d \
        -lopencv_core2410d \
        -lopencv_features2d2410d \
        -lopencv_flann2410d \
        -lopencv_gpu2410d \
        -lopencv_highgui2410d \
        -lopencv_imgproc2410d \
        -lopencv_legacy2410d \
        -lopencv_objdetect2410d \
        -lopencv_ts2410d \
        -lopencv_video2410d \
        -lopencv_nonfree2410d \
        -lopencv_ocl2410d \
        -lopencv_photo2410d \
        -lopencv_stitching2410d \
        -lopencv_superres2410d \
        -lopencv_videostab2410d \
}

CONFIG(release,debug|release){

    LIBS += \
        -lopengl32 \
        -lpenThreads \
        -losg \
        -losgDB \
        -losgGA \
        -losgParticle \
        -losgQt \
        -losgUtil \
        -losgViewer \
        -losgVolume \
        -losgTextd \
        -losgdb_bmp \
        -losgdb_deprecated_osg \
        -losgdb_jpeg \
        -losgdb_png \
        -losgdb_rgb \
        -losgdb_ss2 \
        -losgdb_serializers_osg \
        -losgdb_ss2 \
}


SOURCES += \
    ReadFile.cpp
        

HEADERS  +=  \
    export.h \
    ReadFile.h
    

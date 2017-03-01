#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T15:49:35
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PointCloudFusion
TEMPLATE = app

CONFIG -= c++98
CONFIG += c++11
CONFIG -= debug_and_release
CONFIG += gif
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
#        "E:/Program Files/PCL 1.8.0/include" \

    LIBS += \
        -L$$OUT_PWD/../lib \
        -L$$(WIN_SYS_LIB)/Lib \

    LIBS += \
        -lshell32 \


}else:unix{
    macx{
        #macx
    }else{
        #linux
    }
}

INCLUDEPATH += $$quote(E:/Program Files/PCL 1.8.0/3rdParty/OpenNI2/Include) \
    $$quote(E:/Program Files/PCL 1.8.0/include/pcl-1.8/pcl) \
    $$quote(E:/Program Files/PCL 1.8.0/include/pcl-1.8) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/Boost/include/boost-1_59) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/Eigen/eigen3) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/FLANN/include) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/FLANN/include/flann) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/Qhull/include) \
    $$quote(E:/Program Files/PCL 1.8.0/3rdParty/VTK/include/vtk-7.0) \


#LIBS += -L D:\OpenNI2\Lib\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/lib\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/3rdParty\Boost\lib\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/3rdParty\Eigen\eigen3\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/3rdParty\FLANN\lib\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/3rdParty\Qhull\lib\

#LIBS += -L $$quote(E:/Program Files/PCL 1.8.0/3rdParty\VTK\lib
LIBS += $$quote(E:/Program Files/PCL 1.8.0/3rdParty/VTK/lib/*.lib)

LIBS += \
    -L$$quote(E:/Program Files/PCL 1.8.0/lib) \
    -L$$quote(E:/Program Files/PCL 1.8.0/3rdParty/Boost/lib) \
    -L$$quote(E:/Program Files/PCL 1.8.0/3rdParty/FLANN/lib) \
    -L$$quote(E:/Program Files/PCL 1.8.0/3rdParty/Qhull/lib) \
    -L$$quote(E:/Program Files/PCL 1.8.0/3rdParty/VTK/lib) \
    -L$$quote(E:/Program Files/PCL 1.8.0/3rdParty/OpenNI2/Lib) \

CONFIG(debug,debug|release){

LIBS += -lpcl_common_debug \
        -lpcl_features_debug \
        -lpcl_filters_debug \
        -lpcl_io_debug \
        -lpcl_io_ply_debug \
        -lpcl_kdtree_debug \
        -lpcl_keypoints_debug \
        -lpcl_octree_debug \
        -lpcl_outofcore_debug \
        -lpcl_people_debug \
        -lpcl_recognition_debug \
        -lpcl_registration_debug \
        -lpcl_sample_consensus_debug \
        -lpcl_search_debug \
        -lpcl_segmentation_debug \
        -lpcl_surface_debug \
        -lpcl_tracking_debug \
        -lpcl_visualization_debug \
#        -llibboost_atomic-vc120-mt-gd-1_57 \
#        -llibboost_chrono-vc120-mt-gd-1_57 \
#        -llibboost_container-vc120-mt-gd-1_57 \
#        -llibboost_context-vc120-mt-gd-1_57 \
#        -llibboost_coroutine-vc120-mt-gd-1_57 \
#        -llibboost_date_time-vc120-mt-gd-1_57 \
#        -llibboost_exception-vc120-mt-gd-1_57 \
#        -llibboost_filesystem-vc120-mt-gd-1_57 \
#        -llibboost_graph-vc120-mt-gd-1_57 \
#        -llibboost_iostreams-vc120-mt-gd-1_57 \
#        -llibboost_locale-vc120-mt-gd-1_57 \
#        -llibboost_log-vc120-mt-gd-1_57 \
#        -llibboost_log_setup-vc120-mt-gd-1_57 \
#        -llibboost_math_c99-vc120-mt-gd-1_57 \
#        -llibboost_math_c99f-vc120-mt-gd-1_57 \
#        -llibboost_math_c99l-vc120-mt-gd-1_57 \
#        -llibboost_math_tr1-vc120-mt-gd-1_57 \
#        -llibboost_math_tr1f-vc120-mt-gd-1_57 \
#        -llibboost_math_tr1l-vc120-mt-gd-1_57 \
#        -llibboost_mpi-vc120-mt-gd-1_57 \
#        -llibboost_prg_exec_monitor-vc120-mt-gd-1_57 \
#        -llibboost_program_options-vc120-mt-gd-1_57 \
#        -llibboost_random-vc120-mt-gd-1_57 \
#        -llibboost_regex-vc120-mt-gd-1_57 \
#        -llibboost_serialization-vc120-mt-gd-1_57 \
#        -llibboost_signals-vc120-mt-gd-1_57 \
#        -llibboost_system-vc120-mt-gd-1_57 \
#        -llibboost_test_exec_monitor-vc120-mt-gd-1_57 \
#        -llibboost_thread-vc120-mt-gd-1_57 \
#        -llibboost_thread-vc120-mt-gd-1_59 \
#        -llibboost_timer-vc120-mt-gd-1_57 \
#        -llibboost_unit_test_framework-vc120-mt-gd-1_57 \
#        -llibboost_wave-vc120-mt-gd-1_57 \
#        -llibboost_wserialization-vc120-mt-gd-1_57 \
        -lflann_cpp_s-gd \
#        -lqhullstatic_d \
#        -lvtkalglib-6.2-gd \
#        -lvtkChartsCore-6.2-gd \
#        -lvtkCommonColor-6.2-gd \
#        -lvtkCommonComputationalGeometry-6.2-gd \
#        -lvtkCommonCore-6.2-gd \
#        -lvtkCommonDataModel-6.2-gd \
#        -lvtkCommonExecutionModel-6.2-gd \
#        -lvtkCommonMath-6.2-gd \
#        -lvtkCommonMisc-6.2-gd \
#        -lvtkCommonSystem-6.2-gd \
#        -lvtkCommonTransforms-6.2-gd \
#        -lvtkDICOMParser-6.2-gd \
#        -lvtkDomainsChemistry-6.2-gd \
#        -lvtkexoIIc-6.2-gd \
#        -lvtkexpat-6.2-gd \
#        -lvtkFiltersAMR-6.2-gd \
#        -lvtkFiltersCore-6.2-gd \
#        -lvtkFiltersExtraction-6.2-gd \
#        -lvtkFiltersFlowPaths-6.2-gd \
#        -lvtkFiltersGeneral-6.2-gd \
#        -lvtkFiltersGeneric-6.2-gd \
#        -lvtkFiltersGeometry-6.2-gd \
#        -lvtkFiltersHybrid-6.2-gd \
#        -lvtkFiltersHyperTree-6.2-gd \
#        -lvtkFiltersImaging-6.2-gd \
#        -lvtkFiltersModeling-6.2-gd \
#        -lvtkFiltersParallel-6.2-gd \
#        -lvtkFiltersParallelImaging-6.2-gd \
#        -lvtkFiltersProgrammable-6.2-gd \
#        -lvtkFiltersSelection-6.2-gd \
#        -lvtkFiltersSMP-6.2-gd \
#        -lvtkFiltersSources-6.2-gd \
#        -lvtkFiltersStatistics-6.2-gd \
#        -lvtkFiltersTexture-6.2-gd \
#        -lvtkFiltersVerdict-6.2-gd \
#        -lvtkfreetype-6.2-gd \
#        -lvtkftgl-6.2-gd \
#        -lvtkGeovisCore-6.2-gd \
#        -lvtkgl2ps-6.2-gd \
#        -lvtkhdf5-6.2-gd \
#        -lvtkhdf5_hl-6.2-gd \
#        -lvtkImagingColor-6.2-gd \
#        -lvtkImagingCore-6.2-gd \
#        -lvtkImagingFourier-6.2-gd \
#        -lvtkImagingGeneral-6.2-gd \
#        -lvtkImagingHybrid-6.2-gd \
#        -lvtkImagingMath-6.2-gd \
#        -lvtkImagingMorphological-6.2-gd \
#        -lvtkImagingSources-6.2-gd \
#        -lvtkImagingStatistics-6.2-gd \
#        -lvtkImagingStencil-6.2-gd \
#        -lvtkInfovisCore-6.2-gd \
#        -lvtkInfovisLayout-6.2-gd \
#        -lvtkInteractionImage-6.2-gd \
#        -lvtkInteractionStyle-6.2-gd \
#        -lvtkInteractionWidgets-6.2-gd \
#        -lvtkIOAMR-6.2-gd \
#        -lvtkIOCore-6.2-gd \
#        -lvtkIOEnSight-6.2-gd \
#        -lvtkIOExodus-6.2-gd \
#        -lvtkIOExport-6.2-gd \
#        -lvtkIOGeometry-6.2-gd \
#        -lvtkIOImage-6.2-gd \
#        -lvtkIOImport-6.2-gd \
#        -lvtkIOInfovis-6.2-gd \
#        -lvtkIOLegacy-6.2-gd \
#        -lvtkIOLSDyna-6.2-gd \
#        -lvtkIOMINC-6.2-gd \
#        -lvtkIOMovie-6.2-gd \
#        -lvtkIONetCDF-6.2-gd \
#        -lvtkIOParallel-6.2-gd \
#        -lvtkIOParallelXML-6.2-gd \
#        -lvtkIOPLY-6.2-gd \
#        -lvtkIOSQL-6.2-gd \
#        -lvtkIOVideo-6.2-gd \
#        -lvtkIOXML-6.2-gd \
#        -lvtkIOXMLParser-6.2-gd \
#        -lvtkjpeg-6.2-gd \
#        -lvtkjsoncpp-6.2-gd \
#        -lvtklibxml2-6.2-gd \
#        -lvtkmetaio-6.2-gd \
#        -lvtkNetCDF-6.2-gd \
#        -lvtkNetCDF_cxx-6.2-gd \
#        -lvtkoggtheora-6.2-gd \
#        -lvtkParallelCore-6.2-gd \
#        -lvtkpng-6.2-gd \
#        -lvtkproj4-6.2-gd \
#        -lvtkRenderingAnnotation-6.2-gd \
#        -lvtkRenderingContext2D-6.2-gd \
#        -lvtkRenderingContextOpenGL-6.2-gd \
#        -lvtkRenderingCore-6.2-gd \
#        -lvtkRenderingFreeType-6.2-gd \
#        -lvtkRenderingFreeTypeOpenGL-6.2-gd \
#        -lvtkRenderingGL2PS-6.2-gd \
#        -lvtkRenderingImage-6.2-gd \
#        -lvtkRenderingLabel-6.2-gd \
#        -lvtkRenderingLIC-6.2-gd \
#        -lvtkRenderingLOD-6.2-gd \
#        -lvtkRenderingOpenGL-6.2-gd \
#        -lvtkRenderingVolume-6.2-gd \
#        -lvtkRenderingVolumeOpenGL-6.2-gd \
#        -lvtksqlite-6.2-gd \
#        -lvtksys-6.2-gd \
#        -lvtktiff-6.2-gd \
#        -lvtkverdict-6.2-gd \
#        -lvtkViewsContext2D-6.2-gd \
#        -lvtkViewsCore-6.2-gd \
#        -lvtkViewsInfovis-6.2-gd \
#        -lvtkzlib-6.2-gd \
#        -lflann_s-gd \
#        -lflann-gd \
#        -lqhull_d \
#        -lqhull_p_d \
#        -lqhullcpp_d \
#        -lqhullstatic_p_d \
        -lOpenNI2 \

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
        zPCFWidget.cpp \
    WaitDialog.cpp

HEADERS  += mainwindow.h \
        zPCFWidget.h \
    WaitDialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

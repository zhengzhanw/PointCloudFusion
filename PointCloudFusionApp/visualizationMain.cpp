#pragma once
//#pragma comment(lib, "visualizationMain.lib")
//========================================================
/**
*  @file      visualizationMain.cpp
*
*  项目描述： Visualization System
*  文件描述:  颜色计算类
*  适用平台： Windows98/2000/NT/XP/Win7
*  作    者:
*/
//========================================================
const unsigned int MASK_2D = 0xF0000000;
const unsigned int MASK_3D = 0x0F000000;

//#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "opencv/cv.h"                             //  OpenCV 文件头
#include "opencv/highgui.h"
#include "opencv/cvaux.h"
#include "opencv/cxcore.h"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc.hpp>

//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
/*#include <osgWidget/WindowManager>
#include <osgWidget/ViewerEventHandlers>
#include <osgWidget/Box>
*/

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Vec3>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/PolygonStipple>
#include <osg/TriangleFunctor>
#include <osg/io_utils>

#include <osgDB/WriteFile>

#include <osgGA/TrackballManipulator>
#include <osgUtil/DelaunayTriangulator>

#include <osg/Math>

#include <osg/StateSet>
#include <osg/LineWidth>
#include <osg/Point>

#include <osg/ShapeDrawable>
using namespace cv;
#include "Color.h"
int ShowScene(Mat _img,int _dimFlag,int _colorFlag);
osg::ref_ptr<osg::Node> ShowFrameProcessResult(Mat _img,int _dimFlag,int _colorFlag);
osg::ref_ptr<osg::Node> DrawImage(Mat img,int dimFlag,int colorFlag);

osg::ref_ptr<osg::Node> DrawLineLoop();

/**
* @function main
* @brief Main function
*/
int start(  )
{

    //IplImage* pImg=cvLoadImage("E:\\proj\\testVS\\test\\20160413_092822.jpg",-1);
    //cv::Mat img(pImg,0); //img拿到pImg的data

    Mat img = imread("F:\\常用\\重装系统桌面文件\\bishe\\1.jpg");//imread( "E:\\proj\\testVS\\test\\baboon.jpg" );//argv[1]
    ShowScene(img,3,1);


    return 0;
}

osg::ref_ptr<osg::Node> DrawLineLoop()
{
    //CColor color;
    //color.SetColor(1,1,1);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> pointCloudGeom= new osg::Geometry();

    //int sizeVec=pointCloudVec.size();
    //color.SetHeightRange(0,sizeVec);//?
    osg::ref_ptr<osg::Vec3Array> tempPoint=new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> temColor=new osg::Vec4Array();
    osg::ref_ptr<osg::Geometry> temGeom=new osg::Geometry();
    //for(int i=0; i<2; i++)
    {
        tempPoint->push_back(osg::Vec3(1,0,0));//v1pointCloudVec.at(i).GetZ()-
        tempPoint->push_back(osg::Vec3(1,1,0));//v1pointCloudVec.at(i).GetZ()-
        tempPoint->push_back(osg::Vec3(1,0,1));//v1pointCloudVec.at(i).GetZ()-

    }
    temColor->push_back(osg::Vec4(0.2,0.5,0.6,1.0f));
    temColor->push_back(osg::Vec4(0.5,0.2,0.9,1.0f));
    temColor->push_back(osg::Vec4(0.9,0.9,0.6,1.0f));
    pointCloudGeom->setVertexArray(tempPoint);
    pointCloudGeom->setColorArray(temColor);
    pointCloudGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    pointCloudGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS,0,tempPoint->size()));

    geode->addDrawable(pointCloudGeom);

    //设置属性状态，并设置线宽为个像素。
    osg::StateSet *stateGeode=geode->getOrCreateStateSet();

    osg::LineWidth *lw=new osg::LineWidth(2.0);
    osg::Point *pt=new osg::Point(10.0);
    stateGeode->setAttribute(pt);
    //关闭光照
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    return geode;
}

osg::ref_ptr<osg::Node> ShowFrameProcessResult(Mat _img,int _dimFlag,int _colorFlag)
{
    osg::ref_ptr<osg::MatrixTransform> modelview = new osg::MatrixTransform;
    osg::Matrix matrix(osg::Matrix::rotate(osg::PI_2*(-1), 0,0,1)*osg::Matrix::rotate(osg::PI_2, 1,0,0) ); // osg::Matrix::scale(1,1,-1) * osg::Matrix::rotate(osg::PI_2, 0,0,1)* osg::Matrixd::translate(120,10,0)
    modelview->setMatrix(matrix);

    modelview->addChild(DrawImage(_img,_dimFlag,_colorFlag));
    return modelview;
}

int ShowScene(Mat _img,int _dimFlag,int _colorFlag)
{
    osgViewer::Viewer viewer;
/*	osgWidget::WindowManager* wm = new osgWidget::WindowManager(
        &viewer,
        1024.0f,
        768.0f,
        MASK_2D,
        osgWidget::WindowManager::WM_PICK_DEBUG
        );
*/
    osg::Group*  group  = new osg::Group();
//	osg::Camera* camera = osgWidget::createOrthoCamera(1024.0f, 768.0f);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> temGeom = new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> tempPoint = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> temColor = new osg::Vec4Array();

    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet() ));
    //viewer.getCamera()->setPostDrawCallback(new CaptureDrawCallback(image_c.get())) ;
    //modelPoint->setNodeMask(MASK_3D);
//	camera->addChild(wm);

//	group->addChild(camera);
    //group->addChild(ShowTest());
    group->addChild(ShowFrameProcessResult(_img,_dimFlag,_colorFlag));
    //osgDB::Registry::instance()->writeNode(ShowFrameProcessResult(),"filename.ive",osgDB::Registry::instance()->getOptions());

    viewer.setUpViewInWindow(100,100, 800, 600);
    viewer.setSceneData(group);


    return viewer.run();
}

//以2D和3D的形式绘制一幅图像
//dimFlag: 2,3;
//colorFlag: 0表示用图像自身的颜色,其它则为计算的颜色
osg::ref_ptr<osg::Node> DrawImage(Mat img,int dimFlag,int colorFlag)
{
    CColor color;

    float pointAll=img.rows*img.cols;

    color.SetHeightRange(0,255);//
    int channels = img.channels();

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> temGeom=new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> tempPoint = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> temColor = new osg::Vec4Array();


    for (int i=0; i<img.rows; i++)
    {
        for (int j=0; j<img.cols; j++)
        {
            //三维可视化
            if(dimFlag==3)
            {
                if(colorFlag==0)
                {
                    ///255.0,osg的颜色值小于1
                    if(channels==1)
                    {
                        color.SetColor((float)img.at<uchar>(i,j)/255.0,(float)img.at<uchar>(i,j)/255.0,(float)img.at<uchar>(i,j)/255.0);//image.at<cv::Vec3b>(j,i)[0]
                    }
                    else
                    {
                        color.SetColor((float)img.at<cv::Vec3b>(i,j)[0]/255.0,(float)img.at<cv::Vec3b>(i,j)[1]/255.0,(float)img.at<cv::Vec3b>(i,j)[2]/255.0);//image.at<cv::Vec3b>(j,i)[0]
                    }
                }
                else if(colorFlag==1)
                {
                    if(channels==1)
                    {
                        color.CalculateColor((float)img.at<uchar>(i,j));
                    }
                    else
                    {
                        color.CalculateColor(((float)img.at<cv::Vec3b>(i,j)[0]+(float)img.at<cv::Vec3b>(i,j)[1]+(float)img.at<cv::Vec3b>(i,j)[2])/3.0);
                    }
                }
                else
                {
                    color.CalculateColor(i*img.cols+j);
                }

                temColor->push_back(osg::Vec4(color.GetColorR(),color.GetColorG(),color.GetColorB(),1.0f));

                if(dimFlag==3)
                {
                    float f_pointZ;
                    if(channels==1)
                    {
                        f_pointZ=img.at<uchar>(i,j);
                    }
                    else
                    {
                        f_pointZ=(((float)img.at<cv::Vec3b>(i,j)[0]+(float)img.at<cv::Vec3b>(i,j)[1]+(float)img.at<cv::Vec3b>(i,j)[2])/3.0);
                    }
                    tempPoint->push_back(osg::Vec3((float)i,(float)j,f_pointZ));//v1
                }
                else
                {
                    tempPoint->push_back(osg::Vec3((float)i,(float)j,0));//v1
                }

            }
            else//二维可视化处理整个图像
            {
                if(colorFlag==0)
                {
                    ///255.0,osg的颜色值小于1
                    if(channels==1)
                    {
                        color.SetColor((float)img.at<uchar>(i,j)/255.0,(float)img.at<uchar>(i,j)/255.0,(float)img.at<uchar>(i,j)/255.0);//image.at<cv::Vec3b>(j,i)[0]
                    }
                    else
                    {
                        color.SetColor((float)img.at<cv::Vec3b>(i,j)[0]/255.0,(float)img.at<cv::Vec3b>(i,j)[1]/255.0,(float)img.at<cv::Vec3b>(i,j)[2]/255.0);//image.at<cv::Vec3b>(j,i)[0]
                    }
                }
                else if(colorFlag==1)
                {
                    if(channels==1)
                    {
                        color.CalculateColor((float)img.at<uchar>(i,j));
                    }
                    else
                    {
                        color.CalculateColor(((float)img.at<cv::Vec3b>(i,j)[0]+(float)img.at<cv::Vec3b>(i,j)[1]+(float)img.at<cv::Vec3b>(i,j)[2])/3.0);
                    }
                }
                else
                {
                    color.CalculateColor(i*img.cols+j);
                }

                temColor->push_back(osg::Vec4(color.GetColorR(),color.GetColorG(),color.GetColorB(),1.0f));

                if(dimFlag==3)
                {
                    float f_pointZ;
                    if(channels==1)
                    {
                        f_pointZ=img.at<uchar>(i,j);
                    }
                    else
                    {
                        f_pointZ=(((float)img.at<cv::Vec3b>(i,j)[0]+(float)img.at<cv::Vec3b>(i,j)[1]+(float)img.at<cv::Vec3b>(i,j)[2])/3.0);
                    }
                    tempPoint->push_back(osg::Vec3((float)i,(float)j,f_pointZ));//v1
                }
                else
                {
                    tempPoint->push_back(osg::Vec3((float)i,(float)j,0));//v1
                }
            }
        }
    }
    temGeom->setVertexArray(tempPoint);
    temGeom->setColorArray(temColor);
    temGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    temGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS,0,tempPoint->size()));

    geode->addDrawable(temGeom);
    //设置属性状态，并设置线宽为个像素。
    osg::StateSet *stateGeode=geode->getOrCreateStateSet();
    osg::Point *ptr=new osg::Point(8);
    stateGeode->setAttribute(ptr);
    //关闭光照
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    return geode;
}

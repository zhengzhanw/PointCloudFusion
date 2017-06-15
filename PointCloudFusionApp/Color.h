#pragma once
//========================================================
/**
*  @file      color.h
*
*  项目描述： Visualization System
*  文件描述:  颜色计算类
*  适用平台： Windows98/2000/NT/XP/Win7
*  作    者:
*/
//========================================================
#include <osg/Vec3>
#include <osg/Vec4>

class CColor
{
public:
    CColor(void);
    ~CColor(void);
private:
    // 红色分量
    float colorR;
    // 绿色分量
    float colorG;
    // 蓝色分量
    float colorB;

    double min_H;
    double max_H;

    double blue_H;
    double green_H;
    double yellow_H;
    double red_H;
public:
    //
    osg::Vec4 GetColor(void);
    // 返回红色分量值
    float GetColorR(void);
    // 返回绿色分量值
    float GetColorG(void);
    // 返回蓝色分量值
    float GetColorB(void);
        void SetColor(float f_r,float f_g,float f_b);
    // 返回红色分量值
    void SetColorR(float f_r);
    // 返回绿色分量值
    void SetColorG(float f_g);
    // 返回蓝色分量值
    void SetColorB(float f_b);
    // 设置高程的最小值与最大值 ，以及各个颜色段的高程值
    // 对于激光高度计的数据可以采用minH=1.73036e+006,maxH=1.74258e+006
    void SetHeightRange(double minH, double maxH);
    void SetHeightRange(double minH, double maxH, double HBlue, double HGreen, double HYellow, double HRed);
    // 计算颜色值
    void  CalculateColor(double H);
};


#include "Color.h"

CColor::CColor(void)
: colorR(0)
, colorG(0)
, colorB(0)
,min_H(0)
,max_H(0)
,blue_H(0)
,green_H(0)
,yellow_H(0)
,red_H(0)
{
}

CColor::~CColor(void)
{
}

// 返回红色分量值
float CColor::GetColorR(void)
{
    return colorR;
}

// 返回绿色分量值
float CColor::GetColorG(void)
{
    return colorG;
}

// 返回蓝色分量值
float CColor::GetColorB(void)
{
    return colorB;
}
void CColor::SetColor(float f_r,float f_g,float f_b)
{
    colorR=f_r;
    colorG=f_g;
    colorB=f_b;

}
// 返回红色分量值
void CColor::SetColorR(float f_r)
{
    colorR=f_r;

}
// 返回绿色分量值
void CColor::SetColorG(float f_g)
{

    colorG=f_g;

}
// 返回蓝色分量值
void CColor::SetColorB(float f_b)
{

    colorB=f_b;
}
// 设置高程的最小值与最大值
void CColor::SetHeightRange(double minH, double maxH)
{
    min_H=minH;
    max_H=maxH;
    double remainH=0.06;
    double stepH=(max_H-min_H-2*remainH)/3;
    blue_H=min_H+remainH;
    green_H=blue_H+stepH;
    yellow_H=green_H+stepH;
    red_H=max_H-remainH;;


}
// 设置高程的最小值与最大值 ，以及各个颜色段的高程值
void CColor::SetHeightRange(double minH, double maxH, double HBlue, double HGreen, double HYellow, double HRed)
{
    min_H=minH;
    max_H=maxH;
    blue_H=HBlue;
    green_H=HGreen;
    yellow_H=HYellow;
    red_H=HRed;
}

// 计算颜色值
void CColor::CalculateColor(double H)
{

    if (H<=blue_H)
    {
        colorR=0.0;colorG=0;colorB=1.0;
    };
    if (H>blue_H&&H<=green_H)
    {
        colorR=0.0;
        colorG=(H-blue_H)/(green_H-blue_H);
        colorB=1.0-(H-blue_H)/(green_H-blue_H);
    };
    if (H>green_H&&H<=yellow_H)
    {
        colorR=(H-green_H)/(yellow_H-green_H);
        colorG=1.0;
        colorB=0;
    };
    if (H>yellow_H&&H<=red_H)
    {
        colorR=1.0;
        colorG=1.0-(H-yellow_H)/(red_H-yellow_H);
        colorB=0.0;
    };
    if (H>red_H)
    {
        colorR=1.0;colorG=0;colorB=0.0;
    };

}
osg::Vec4 CColor::GetColor(void)
{
    osg::Vec4 colors;
    colors.set(GetColorR(),GetColorG(),GetColorB(),1);
    return colors;
}

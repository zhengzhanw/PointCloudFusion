#include "zPCFWidget.h"
#include <QPushButton>
#include <QBoxLayout>
#include <PointCloudFusionApp/ReadFile.h>
#include <QDebug>

zPCFWidget::zPCFWidget(QWidget *parent):QWidget(parent)
{
    ReadFile readfile;
    readfile.open("e:/test.txt",ReadFile::IOS_IN);
    char a[30];
    while(readfile.read(a,30))
       std::cout<<a;
    readfile.close();
}

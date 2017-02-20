#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream> //标准输入输出流
#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件
#include "PointCloudFusionApp/ReadFile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readPCL(std::string pcd_Path)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); // 创建点云（指针）

      if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_Path, *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
      {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
        return ;
      }
      qDebug() << "Loaded "
                << cloud->width * cloud->height
                << " data points from test_file.pcd with the following fields: ";
      //for (size_t i = 0; i < cloud->points.size (); ++i) //显示所有的点

        for (size_t i = 0; i < 5; ++i) // 为了方便观察，只显示前5个点
        std::cout << "    " << cloud->points[i].x
                  << " "    << cloud->points[i].y
                  << " "    << cloud->points[i].z << std::endl;

}

void MainWindow::on_readFile_action_triggered()
{
    QStringList filePath = QFileDialog::getOpenFileNames(this,
        tr("Open File"),
        "f:/Bibased",
        tr("Files (*.pcd *.txt *.jpg *.png *.jpg)"),
        0);
    if(!filePath.empty()){
//        for(int i=0;i<filePath.length();i++)
//        {
//            ReadFile readfile;
//            if(readfile.open(filePath.at(i).toStdString(),ReadFile::IOS_IN)){
//                char a[30];
//                while(readfile.read(a,30))
//                {
//                   ui->textEdit->append(a);
//                   qDebug()<<a;
//                }
//                readfile.close();
//            }
//        }
        readPCL(filePath.at(0).toStdString());
    }

}

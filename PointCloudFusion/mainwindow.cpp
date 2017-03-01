#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream> //标准输入输出流

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>
#include "QVTKWidget.h"
#include "WaitDialog.h"

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
//    WaitDialog wait;
//    wait.open();
    QLabel *label = new QLabel();
    QMovie *movie = new QMovie(":/images/loading0.gif");
    label->setMovie(movie);
    movie->start();
    label->show();
    if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_Path, *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
    {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
        return ;
    }
    //wait.close();
    qDebug() << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_file.pcd with the following fields: ";
    //for (size_t i = 0; i < cloud->points.size (); ++i) //显示所有的点

    //        for (size_t i = 0; i < 5; ++i) // 为了方便观察，只显示前5个点
    //        std::cout << "    " << cloud->points[i].x
    //                  << " "    << cloud->points[i].y
    //                  << " "    << cloud->points[i].z << std::endl;
    //        pcl::visualization::CloudViewer viewer("Cloud Viewer1");
    //        viewer.showCloud(cloud);

    //Set up the QVTK window
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer",false));
    ui->centralWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->centralWidget->GetInteractor(),ui->centralWidget->GetRenderWindow());
    ui->centralWidget->update();

    viewer->addPointCloud(cloud,"cloud");
    viewer->resetCamera();
    ui->centralWidget->update();

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

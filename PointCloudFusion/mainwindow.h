#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zPCFWidget.h"
#include "WaitDialog.h"
#include "PointCloudFusionApp/ReadFile.h"

#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readPCL(std::string pcd_Path);

private slots:
    void displayViewer();
    void on_readFile_action_triggered();

    void on_delete_action_triggered();

protected:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    //PointCloudT::Ptr cloud;

private:
    Ui::MainWindow *ui;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    WaitDialog *wait;
    std::string fileName;
//    zPCFWidget *pcfWidget;
};

#endif // MAINWINDOW_H

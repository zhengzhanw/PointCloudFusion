#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>
#include "zPCFWidget.h"
#include "WaitDialog.h"
#include "ICPBlend.h"
#include "PointCloudFusionApp/ReadFile.h"

#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/console/time.h>   // TicToc

//typedef PointT PointT;
//typedef pcl::PointCloud<PointT> PointCloudT;


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

    void viewIterator();
    //virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void displayViewer();
    void on_readFile_action_triggered();

    void on_delete_action_triggered();

    void on_execute_action_triggered();

    void on_exportFile_action_triggered();

    void on_mulFusion_action_triggered();

    void on_exit_action_triggered();

    void on_fullScreen_action_triggered();

    void on_about_action_triggered();

    void on_transform_action_triggered();

    void on_osgExport_action_triggered();

protected:

    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent* size);

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> source_viewer;
    //PointCloudT::Ptr cloud;

private:
    Ui::MainWindow *ui;
    pcl::PointCloud<PointT>::Ptr cloud;
    std::vector<pcl::PointCloud<PointT>::Ptr> clouds_vector;
    WaitDialog *wait;
    std::string fileName;

    pcl::console::TicToc time;
//    zPCFWidget *pcfWidget;
};

#endif // MAINWINDOW_H

#ifndef ZTHREAD_H
#define ZTHREAD_H

#include <QObject>
#include <QThread>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件

class zThread : public QThread
{
    Q_OBJECT
public:
    explicit zThread(pcl::PointCloud<pcl::PointXYZ>::Ptr p_cloud,std::string p_Path,QThread *parent = NULL);
    virtual void run() override;
private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    std::string pcd_Path;
};

#endif // ZTHREAD_H

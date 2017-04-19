#include "zThread.h"
#include <QDebug>
zThread::zThread(pcl::PointCloud<pcl::PointXYZ>::Ptr p_cloud,std::string p_Path,QThread *parent)
    :QThread(parent),cloud(p_cloud),pcd_Path(p_Path)
{

}

void zThread::run()
{
    if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_Path, *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
    {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
        return ;
    }
}

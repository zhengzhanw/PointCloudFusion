#include "zThread.h"
#include <QDebug>
zThread::zThread(pcl::PointCloud<PointT>::Ptr p_cloud,std::string p_Path,zThread::IOType p_type ,QThread *parent)
    :QThread(parent),cloud(p_cloud),pcd_Path(p_Path),type(p_type)
{

}

void zThread::run()
{
    if(type == zThread::READ){
        if (pcl::io::loadPCDFile<PointT> (pcd_Path, *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
        {
            PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
            return ;
        }
    }else if(type == zThread::WRITE){
        pcl::io::savePCDFileASCII<PointT> (pcd_Path, *cloud); //将点云保存到PCD文件中
        std::cerr << "Saved " << cloud->points.size () << " data points to test_pcd.pcd." << std::endl;
        return ;
    }else{
        return;
    }
}

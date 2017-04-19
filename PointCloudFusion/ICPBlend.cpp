#include "ICPBlend.h"
#include <boost/make_shared.hpp> //共享指针
//点/点云
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
//pcd文件输入/输出
#include <pcl/io/pcd_io.h>
//滤波
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/filter.h>
//特征
#include <pcl/features/normal_3d.h>
//配准
#include <pcl/registration/icp.h> //ICP方法
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/transforms.h>
//可视化
#include <pcl/visualization/pcl_visualizer.h>
//命名空间
using pcl::visualization::PointCloudColorHandlerGenericField;
using pcl::visualization::PointCloudColorHandlerCustom;

//定义类型的别名
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;
typedef pcl::PointNormal PointNormalT;
typedef pcl::PointCloud<PointNormalT> PointCloudWithNormals;

ICPBlend::ICPBlend()
{

}

ICPBlend::ICPBlend(pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_source , pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_target)
{
    source  = p_source;
    target = p_target;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr ICPBlend::blend(pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_source , pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_target)
{
    return blendMain(p_source,p_target);
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr ICPBlend::blend(pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_source, std::string p_targetPath)
{

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_target (new pcl::PointCloud<pcl::PointXYZRGB>);

    // load pcd file

    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>(p_targetPath , *p_target)==-1) {
        std::cout << "load target failed!" << std::endl;
        return NULL;
    }
    std::cout << "target loaded!" << std::endl;

    return blendMain(p_source,p_target);
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr ICPBlend::blend(std::string p_sourcePath, std::string p_targetPath)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_source (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_target (new pcl::PointCloud<pcl::PointXYZRGB>);

    // load pcd file
    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>(p_sourcePath, *p_source)==-1) {
        std::cout << "load source failed!" << std::endl;
        return NULL;
    }
    std::cout << "source loaded!" << std::endl;

    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>(p_targetPath, *p_target)==-1) {
        std::cout << "load target failed!" << std::endl;
        return NULL;
    }
    std::cout << "target loaded!" << std::endl;

    return blendMain(p_source,p_target);
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr ICPBlend::blendMain(pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_source, pcl::PointCloud<pcl::PointXYZRGB>::Ptr p_target)
{

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_source_registration (new pcl::PointCloud<pcl::PointXYZRGB>);
    // ICP
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> icp;
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree1 (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree1->setInputCloud(p_source);
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree2->setInputCloud(p_target);
    icp.setSearchMethodSource(tree1);
    icp.setSearchMethodTarget(tree2);
    icp.setInputSource(p_source);
    icp.setInputTarget(p_target);
    icp.setMaxCorrespondenceDistance(0.1);//1.5
    icp.setTransformationEpsilon(1e-6);//-10
    icp.setEuclideanFitnessEpsilon(0.01);//0.01
    icp.setMaximumIterations(100);//100
    icp.align(*cloud_source_registration);
    //Eigen::Matrix4f transformation = icp.getFinalTransformation();
    //std::cout << transformation << std::endl;

    return cloud_source_registration;

//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr output;

//    Eigen::Matrix4f final_transform;
//    //下采样
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr src (new pcl::PointCloud<pcl::PointXYZRGB>);         //存储滤波后的源点云
//      pcl::PointCloud<pcl::PointXYZRGB>::Ptr tgt (new pcl::PointCloud<pcl::PointXYZRGB>);       //存储滤波后的目标点云
//      pcl::VoxelGrid grid;                 //滤波处理对象
//    /*if (downsample)
//      {
//        grid.setLeafSize (0.05, 0.05, 0.05);      //设置滤波处理时采用的体素大小
//        grid.setInputCloud (cloud_src);
//        grid.filter (*src);
//        grid.setInputCloud (cloud_tgt);
//        grid.filter (*tgt);
//      }
//    else
//      {*/
//    src = *p_source;
//    tgt = *p_target;
//     // }
//    //计算点云法线
//      PointCloudWithNormals::Ptr points_with_normals_src (new PointCloudWithNormals);
//      PointCloudWithNormals::Ptr points_with_normals_tgt (new PointCloudWithNormals);
//      pcl::NormalEstimation norm_est; //点云法线估计对象
//      pcl::search::KdTree::Ptr tree (new pcl::search::KdTree ());
//      norm_est.setSearchMethod (tree);                        //设置估计对象采用的搜索对象
//      norm_est.setKSearch (30);                                //设置估计时进行搜索用的k数
//      norm_est.setInputCloud (src);
//      norm_est.compute (*points_with_normals_src);           //下面分别估计源和目标点云法线
//      pcl::copyPointCloud (*src, *points_with_normals_src);
//      norm_est.setInputCloud (tgt);
//      norm_est.compute (*points_with_normals_tgt);
//      pcl::copyPointCloud (*tgt, *points_with_normals_tgt);

//      // 配准
//        pcl::IterativeClosestPointNonLinear<PointNormalT, PointNormalT> reg; //配准对象
//        reg.setTransformationEpsilon (1e-6);//设置收敛判断条件，越小精度越大，收敛也越慢
//      //将两个点云中的对应点对之间的(src<->tgt)最大距离设置为10厘米，大于此值的点对不考虑。
//      //注意：根据你的数据集大小来调整
//        reg.setMaxCorrespondenceDistance (0.1);
//      //设置点表示
//        reg.setPointRepresentation (boost::make_shared<const MyPointRepresentation> (point_representation));
//        reg.setInputCloud (points_with_normals_src);    //设置源点云
//        reg.setInputTarget (points_with_normals_tgt);   //设置目标点云

//        reg.setMaximumIterations (2);                     //设置最大迭代次数

//        targetToSource = Ti.inverse();// 得到目标点云到源点云的变换
//        //把目标点云变换到源点云坐标系下
//          pcl::transformPointCloud (*cloud_tgt, *output, targetToSource);
////        *output +=*p_source;
////        final_transform = targetToSource;
//          return output;
}

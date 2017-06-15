#ifndef ICPBLEND_H
#define ICPBLEND_H

#include <QObject>
#include <pcl/filters/filter.h>
#include <pcl/registration/icp.h>
#include <pcl/console/time.h>   // TicToc
#include "plugin.h"
#define ITERATION 25

//typedef pcl::PointXYZRGB PointT;
//typedef pcl::PointCloud<PointT> PointCloudT;


class ICPBlend
{
public:
    ICPBlend();
    ICPBlend(pcl::PointCloud<PointT>::Ptr p_source,pcl::PointCloud<PointT>::Ptr p_target);

    pcl::PointCloud<PointT>::Ptr blend(pcl::PointCloud<PointT>::Ptr cloud_icp,pcl::PointCloud<PointT>::Ptr cloud_in);

    void blendMain();

private:
    pcl::PointCloud<PointT>::Ptr source;
    pcl::PointCloud<PointT>::Ptr target;
    pcl::console::TicToc time;
    int iterations;
};

#endif // ICPBLEND_H

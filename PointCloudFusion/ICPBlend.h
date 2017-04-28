#ifndef ICPBLEND_H
#define ICPBLEND_H

#include <QObject>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class ICPBlend
{
public:
    ICPBlend();
    ICPBlend(pcl::PointCloud<pcl::PointXYZ>::Ptr p_source,pcl::PointCloud<pcl::PointXYZ>::Ptr p_target);

    void blend();

private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr source;
    pcl::PointCloud<pcl::PointXYZ>::Ptr target;
};

#endif // ICPBLEND_H

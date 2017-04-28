#include "ICPBlend.h"

ICPBlend::ICPBlend():
    source(NULL),target(NULL)
{

}

ICPBlend::ICPBlend(pcl::PointCloud<pcl::PointXYZ>::Ptr p_source, pcl::PointCloud<pcl::PointXYZ>::Ptr p_target):
    source(p_source),target(p_target)
{

}

void ICPBlend::blend()
{

}

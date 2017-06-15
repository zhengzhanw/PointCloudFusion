#include "ICPBlend.h"

void print4x4Matrix(const Eigen::Matrix4d & matrix)
{
    printf("Rotation matrix :\n");
    printf("    | %6.3f %6.3f %6.3f | \n", matrix(0, 0), matrix(0, 1), matrix(0, 2));
    printf("R = | %6.3f %6.3f %6.3f | \n", matrix(1, 0), matrix(1, 1), matrix(1, 2));
    printf("    | %6.3f %6.3f %6.3f | \n", matrix(2, 0), matrix(2, 1), matrix(2, 2));
    printf("Translation vector :\n");
    printf("t = < %6.3f, %6.3f, %6.3f >\n\n", matrix(0, 3), matrix(1, 3), matrix(2, 3));
}

ICPBlend::ICPBlend():
    source(NULL),target(NULL),iterations(ITERATION)
{

}

ICPBlend::ICPBlend(pcl::PointCloud<PointT>::Ptr p_source, pcl::PointCloud<PointT>::Ptr p_target):
    source(p_source),target(p_target),iterations(ITERATION)
{

}

pcl::PointCloud<PointT>::Ptr ICPBlend::blend(pcl::PointCloud<PointT>::Ptr cloud_icp, pcl::PointCloud<PointT>::Ptr cloud_in)
{
    Eigen::Matrix4d transformation_matrix = Eigen::Matrix4d::Identity();
    std::vector<int> mapping;
    pcl::removeNaNFromPointCloud(*cloud_in, *cloud_in, mapping);
    // The Iterative Closest Point algorithm
    time.tic();
    pcl::IterativeClosestPoint<PointT, PointT> icp;
    icp.setMaximumIterations(iterations);
    icp.setInputSource(cloud_icp);
    icp.setInputTarget(cloud_in);
    icp.align(*cloud_icp);
    icp.setMaximumIterations(1);  // We set this variable to 1 for the next time we will call .align () function
    std::cout << "Applied " << iterations << " ICP iteration(s) in " << time.toc() << " ms" << std::endl;

    if (icp.hasConverged())
    {
        std::cout << "\nICP has converged, score is " << icp.getFitnessScore() << std::endl;
        std::cout << "\nICP transformation " << iterations << " : cloud_icp -> cloud_in" << std::endl;
        transformation_matrix = icp.getFinalTransformation().cast<double>();
        print4x4Matrix(transformation_matrix);
    }
    else
    {
        PCL_ERROR("\nICP has not converged.\n");
        //return (-1);
    }
    return cloud_icp;
}

void ICPBlend::blendMain()
{

}



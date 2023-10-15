 #include <iostream>
 #include <pcl/io/pcd_io.h>
 #include <pcl/point_types.h>
 #include <pcl/filters/voxel_grid.h>
 #include <pcl/visualization/cloud_viewer.h>

 int main ()
 {
    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
    pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());

    // Fill in the cloud data
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file
    reader.read ("../table_scene_lms400.pcd", *cloud); // Remember to download the file first!
  
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
         << " data points (" << pcl::getFieldsList (*cloud) << ")." << std::endl;
  
    // Create the filtering object
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloud_filtered);
  
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
         << " data points (" << pcl::getFieldsList (*cloud_filtered) << ")." << std::endl;
  
    pcl::PCDWriter writer;
    writer.write ("../table_scene_lms400_downsampled.pcd", *cloud_filtered, 
           Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false);
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../table_scene_lms400.pcd", *cloud_);
    pcl::visualization::CloudViewer viewer("demo viewer");
    viewer.showCloud(cloud_);
    viewer.runOnVisualizationThreadOnce([](pcl::visualization::PCLVisualizer& viewer) {
        viewer.setBackgroundColor(.0, .0, .0);
    });
    system("read -p 'Press Enter to continue...' var");
    return (0);
  }
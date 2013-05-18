#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud_xyz;
  pcl::PointCloud<pcl::PointXYZRGBA> cloud_xyzrgba;

  //std::cerr << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << "\n" << std::endl;
  
  double xx[640*480];
  double yy[648*480];
  uint16_t zz[640*480];
  FILE *fpx = NULL;
  FILE *fpy = NULL;
  FILE *fpz = NULL;
  fpx = fopen(argv[1], "r");
  fpy = fopen(argv[2], "r");
  fpz = fopen(argv[3], "r");
  fread(xx, sizeof(double), 640*480, fpx);
  fread(yy, sizeof(double), 640*480, fpy);
  fread(zz, sizeof(uint16_t), 640*480, fpz);
  fclose(fpx);
  fclose(fpy);
  fclose(fpz);
  
  // Fill in the cloud data
  cloud_xyzrgba.width    = 640;
  cloud_xyzrgba.height   = 480;
  cloud_xyzrgba.points.resize (cloud_xyzrgba.width * cloud_xyzrgba.height);
  
  for (size_t i = 0; i < cloud_xyzrgba.points.size (); ++i)
    {
      cloud_xyzrgba.points[i].x = xx[i]/1E3;
      cloud_xyzrgba.points[i].y = yy[i]/1E3;
      cloud_xyzrgba.points[i].z = zz[i]/1E3;
      cloud_xyzrgba.points[i].rgba = 0;
    }
  pcl::io::savePCDFileBinaryCompressed (argv[4], cloud_xyzrgba );
  
  return (0);
}

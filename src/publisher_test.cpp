#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include "Scanning.h"

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/*Diminue la qualité d'une image.*/
int main( int argc, char** argv )
{
	ros::init(argc,argv, "publisher_test");
	ros::NodeHandle n;
	image_transport::ImageTransport it(n);
	image_transport::Publisher pub = it.advertise("image_test", 1);

	if(argc < 3){
		cout << "Not enough parameters" << endl;
	}
	int divideWith;
	stringstream s;
	s << argv[2];
	s >> divideWith;

	uchar table[256];
	for (int i = 0; i < 256; ++i){
		table[i] = divideWith * (i/divideWith);
	}

	Mat imageTraitee;
	Mat imageInitiale = imread(argv[1], CV_LOAD_IMAGE_COLOR);


	Scanning scan = Scanning();

	//imageTraitee = scan.ScanImageAndReduceIterator(imageInitiale,table);
	//imageTraitee = scan.ScanImageAndRemoveNoise(imageInitiale);
	imageTraitee = scan.KeepEdges(imageInitiale);	

	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", imageTraitee).toImageMsg();

	ros::Rate loop_rate(5);
  while (n.ok()) {
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}

	

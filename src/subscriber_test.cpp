#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace std;

void imageCallBack(const sensor_msgs::ImageConstPtr& msg)
{
	try
	{
		cv::imshow("view",cv_bridge::toCvShare(msg, "mono8")->image);
		cv::waitKey(30);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Fuck you");
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subscriber_test");
	ros::NodeHandle n;
	cv::namedWindow("view");
	cv::startWindowThread();
	image_transport::ImageTransport it(n);
	image_transport::Subscriber sub = it.subscribe("image_test", 1, imageCallBack);
	ros::spin();
	cv::destroyWindow("view");
}

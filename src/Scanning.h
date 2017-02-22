/*
 * Scanning.h
 *
 *  Created on: 4 janv. 2017
 *      Author: eric
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#ifndef SRC_SCANNING_H_
#define SRC_SCANNING_H_

/*Programme pour diminuer la qualité de l'image, afin de la rendre plus légère et plus facile pour travailler dessus*/

class Scanning {
public:
	Scanning();
	virtual ~Scanning();
	Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table);
	Mat& ScanImageAndRemoveNoise(Mat& image);
	Mat KeepEdges(Mat& image);
};

#endif /* SRC_SCANNING_H_ */

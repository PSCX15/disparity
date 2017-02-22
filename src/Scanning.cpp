/*
 * Scanning.cpp
 *
 *  Created on: 4 janv. 2017
 *      Author: eric
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "Scanning.h"

using namespace cv;
using namespace std;

Mat& Scanning::ScanImageAndReduceIterator(Mat& I, const uchar* const table){
	 // accept only char type matrices
	    CV_Assert(I.depth() != sizeof(uchar));

	    const int channels = I.channels();
	    switch(channels)
	    {
	    case 1:
	        {
	            MatIterator_<uchar> it, end;
	            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
	                *it = table[*it];
	            break;
	        }
	    case 3:
	        {
	            MatIterator_<Vec3b> it, end;
	            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
	            {
	                (*it)[0] = table[(*it)[0]];
	                (*it)[1] = table[(*it)[1]];
	                (*it)[2] = table[(*it)[2]];
	            }
	        }
	    }

	    return I;
}

Mat& Scanning::ScanImageAndRemoveNoise(Mat& image){
	MatIterator_<uchar> it, end;
	for( it = image.begin<uchar>(), end = image.end<uchar>(); it!=end;++it){
		if(*it<20){
			*it=0;
		}
	}
	return image;
}

Mat Scanning::KeepEdges(Mat& image){
	///Paramètre du filtre de Laplace
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	///Image utilisée dans la fonction
	Mat image_gray, image_contour, dst;
	/// Remove noise by blurring with a Gaussian filter
	//GaussianBlur( image, image, Size(3,3), 0, 0, BORDER_DEFAULT );
	/// Convert the image to grayscale
	cvtColor( image, image_gray, CV_BGR2GRAY );
	///Laplace apply
	Laplacian( image_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( dst, image_contour );
	return image_contour;
}



Scanning::Scanning() {
	// TODO Auto-generated constructor stub

}

Scanning::~Scanning() {
	// TODO Auto-generated destructor stub
}


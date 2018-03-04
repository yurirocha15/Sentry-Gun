/*
 * RedTarget.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: yuri
 */

#include "../Includes/RedTarget.h"

RedTarget::RedTarget() : iLowH1(56), iLowS1(162), iLowV1(142), iHighH1(144), iHighS1(209), iHighV1(194), iLowH2(171), iLowS2(161), iLowV2(76), iHighH2(189), iHighS2(255), iHighV2(255)
{
	namedWindow("HSV", CV_WINDOW_AUTOSIZE | CV_GUI_EXPANDED);
}

RedTarget::RedTarget(int lowh, int lows, int lowv, int highh, int highs, int highv) : iLowH1(lowh), iLowS1(lows), iLowV1(lowv), iHighH1(highh), iHighS1(highs), iHighV1(highv), iLowH2(lowh), iLowS2(lows), iLowV2(lowv), iHighH2(highh), iHighS2(highs), iHighV2(highv)
{
	namedWindow("HSV", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL);
}

RedTarget::~RedTarget()
{
	destroyWindow("HSV");
}

void RedTarget::SetHSVRange2(int lowh, int lows, int lowv, int highh, int highs, int highv)
{
	iLowH2 = lowh;
	iLowS2 = lows;
	iLowV2 = lowv;
	iHighH2 = highh;
	iHighS2 = highs;
	iHighV2 = highv;
}

Mat RedTarget::FindColor(Mat frame)
{
	Mat hsv_frame;		//result image of the BGR2HSV conversion
	Mat hsv_frame_tmp;
	cvtColor(frame,hsv_frame,COLOR_BGR2Lab);
	GaussianBlur(hsv_frame,hsv_frame,Size(3,3),1.5,1.5);
	hsv_frame.copyTo(hsv_frame_tmp);

	//Check if the array of elements lie between the elements of the two other arrays
	inRange(hsv_frame,Scalar(iLowH1,iLowS1,iLowV1),Scalar(iHighH1,iHighS1,iHighV1), hsv_frame);
	//Orange color has two channels, so there are 2 hsv values
	inRange(hsv_frame_tmp,Scalar(iLowH2,iLowS2,iLowV2),Scalar(iHighH2,iHighS2,iHighV2), hsv_frame_tmp);
	//Add both images
	bitwise_or(hsv_frame, hsv_frame_tmp, hsv_frame);

	//morphological opening (removes small objects from the foreground)
	erode(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (removes small holes from the foreground)
	dilate(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(10,10)));
	erode(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(10,10)));

	//Just For Testing Purposes
	imshow("HSV", hsv_frame);

	return hsv_frame;
}

void RedTarget::FindDistance()
{
	//y = -0,0003*x³ + 0,0681*x² - 5,3769*x+172
	distance = -0.0003 * pow(radius,3) + 0.0681 * radius * radius - 5.3769 * radius + 172;
}


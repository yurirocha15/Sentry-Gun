/*
 * BlueTarget.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: yuri
 */

#include "../Includes/BlueTarget.h"

/*iLowH(55), iLowS(108), iLowV(47), iHighH(226), iHighS(160), iHighV(104)*/

BlueTarget::BlueTarget() : iLowH(101), iLowS(125), iLowV(86), iHighH(127), iHighS(255), iHighV(255)
{
	namedWindow("HSV Blue", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL);
}

BlueTarget::BlueTarget(int lowh, int lows, int lowv, int highh, int highs, int highv) : iLowH(lowh), iLowS(lows), iLowV(lowv), iHighH(highh), iHighS(highs), iHighV(highv)
{
	namedWindow("HSV Blue", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL);
}

BlueTarget::~BlueTarget()
{
	destroyWindow("HSV Blue");
}

void BlueTarget::SetHSVRange(int lowh, int lows, int lowv, int highh, int highs, int highv)
{
	iLowH = lowh;
	iLowS = lows;
	iLowV = lowv;
	iHighH = highh;
	iHighS = highs;
	iHighV = highv;
}

Mat BlueTarget::FindColor(Mat frame)
{
	Mat hsv_frame;		//result image of the BGR2HSV conversion
	cvtColor(frame,hsv_frame,COLOR_BGR2HSV);
	GaussianBlur(hsv_frame,hsv_frame,Size(3,3),1.5,1.5);

	//Check if the array of elements lie between the elements of the two other arrays
	inRange(hsv_frame,Scalar(iLowH,iLowS,iLowV),Scalar(iHighH,iHighS,iHighV), hsv_frame);

	//morphological opening (removes small objects from the foreground)
	erode(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (removes small holes from the foreground)
	dilate(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(10,10)));
	erode(hsv_frame, hsv_frame, getStructuringElement(MORPH_ELLIPSE, Size(10,10)));

	//Just For Testing Purposes
	imshow("HSV Blue", hsv_frame);

	return hsv_frame;
}

void BlueTarget::FindDistance()
{
	//y = -0,0003*x³ + 0,0681*x² - 5,3769*x+172
	distance = -0.0003 * pow(radius,3) + 0.0681 * radius * radius - 5.3769 * radius + 172;
}


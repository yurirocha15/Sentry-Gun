/*
 * Target.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: yuri
 */

#include "../Includes/Target.h"

Target::Target() : x(0), y(0), radius(0), distance(0), targetFound(false), counter(0), radiusAvg(0), i(0)
{
	namedWindow("Circle", CV_WINDOW_AUTOSIZE | CV_GUI_EXPANDED);
	radiusBuffer.clear();
}

Target::~Target()
{
	destroyWindow("Circle");
	radiusBuffer.clear();
}

int Target::GetX()
{
	return x;
}

int Target::GetY()
{
	return y;
}

void Target::SetX(int x)
{
	this->x = x;
}

void Target::SetY(int y)
{
	this->y = y;
}

int Target::GetRadius()
{
	return radius;
}

int Target::GetDistance()
{
	return distance;
}

void Target::FindTarget(Mat frame)
{
	Mat hsv_frame = this->FindColor(frame);
	vector<Vec3f> circles = this->FindCircles(hsv_frame);
	int radius = 0;
	if(circles.empty())
	{
		this->targetFound = false;
	}
	else
	{
		this->targetFound = true;
		vector<Vec3f>::iterator it;
		//Get only the biggest circle
		for(it = circles.begin(); it != circles.end(); ++it)
		{
			if((*it)[2] > radius)
			{
				this->x = (*it)[0];
				this->y = (*it)[1];
				radius = (*it)[2];
			}

		}
		if(radius != 0)
		{
			radiusBuffer.push_front(radius);
			if(radiusBuffer.size() > 20)
				radiusBuffer.pop_back();
		}



		/*if(counter >= 10)
		{
			for(it2 = radiusBuffer.begin(); it2 != radiusBuffer.end(); it2++, i++)
			{
				radiusAvg += *it2;
			}
			radiusAvg /= i;
			for(it2 = radiusBuffer.begin(); it2 != radiusBuffer.end(); it2++)
			{
				if(*it2 > 1.1 * radiusAvg || *it2 < 0.9 * radiusAvg)
					it2 = radiusBuffer.erase(it2);
			}
			for(it2 = radiusBuffer.begin(), i = 0, radiusAvg = 0; it2 != radiusBuffer.end(); it2++, i++)
			{
				radiusAvg += *it2;
			}
			radiusAvg /= i;
			counter = 0;
		}
		else
			counter++;
		this->radius = radiusAvg;*/
		this->radius = radius;
		circle(frame, Point(x,y), 2, CV_RGB(255,0,0), -1, 8, 0); //center
		circle(frame, Point(x,y), this->radius, CV_RGB(0,255,0), 2, 8, 0);	//circle
		this->FindDistance();
	}
	//Just for testing purposes
	imshow("Circle", frame);
}

bool Target::TargetFound()
{
	return targetFound;
}

void Target::FindDistance()
{
}

vector<Vec3f> Target::FindCircles(Mat frame)
{
	//Variables to the Hough Transform
	Mat result_frame;				//Input image
	vector<Vec3f> circles; 			//A vector that stores sets of 3 values: x_{c}, y_{c}, r for each detected circle.
									//CV_HOUGH_GRADIENT: Define the detection method. Currently this is the only one available in OpenCV
	int dp = 2; 					//The inverse ratio of resolution
	int min_dist = frame.rows/4; 	//Minimum distance between detected centers
	int param_1 = 200; 				//Upper threshold for the internal Canny edge detector
	int param_2 = 50; 				//Threshold for center detection.
	int min_radius = 10; 			//Minimum radio to be detected. If unknown, put zero as default.
	int max_radius = 200; 			//Maximum radius to be detected. If unknown, put zero as default

	//reduce the noise to avoid false detections
	//GaussianBlur(frame,result_frame,Size(9,9),2,2);
	frame.copyTo(result_frame);

	//apply the Hough Transform to detect circles
	HoughCircles(result_frame,circles,CV_HOUGH_GRADIENT,dp,min_dist,param_1,param_2,min_radius,max_radius);

	return circles;
}

Mat Target::FindColor(Mat frame)
{
	return frame;
}




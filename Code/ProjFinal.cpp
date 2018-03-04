/*
 * ProjFinal.cpp
 *
 *  Created on: 10/07/2013
 *      Author: yuri
 */

#include <iostream>
//OpenCV libraries
#include "opencv2/core/core.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

//Classes
#include "../Includes/Controler.h"

using namespace std;
using namespace cv;

int main()
{
	try
	{
		VideoCapture cap(0);
		if (!cap.isOpened())
			throw "Webcam opening Error.";
		Controler controler(cap);

	}
	catch (const char *msg)
	{
		cout << msg << endl;
		return 0;
	}
	return 0;
}





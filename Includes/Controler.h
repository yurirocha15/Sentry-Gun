/*
 * Controler.h
 *
 *  Created on: 11/07/2013
 *      Author: yuri
 */

#ifndef CONTROLER_H_
#define CONTROLER_H_

#include <iostream>
#include <fstream>
#include <list>

//OpenCV libraries
#include "opencv2/core/core.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

//Classes
#include "Template.h"
#include "RedTarget.h"
#include "BlueTarget.h"

//Sounds
//#include "SDL/SDL.h"
//#include "SDL/SDL_mixer.h"

//namespaces
using namespace std;
using namespace cv;

class Controler {
private:
	Mat  frame;
	VideoCapture capture;
	ofstream arduino_com;
	Target *target;
	void MainLoop();
	void GenerateTemplate(vector<Rect>);
	bool CheckTemplate(Template*);
	void MatchTemplate(Mat);
public:
	Controler(VideoCapture);
	virtual ~Controler();
};

#endif /* CONTROLER_H_ */

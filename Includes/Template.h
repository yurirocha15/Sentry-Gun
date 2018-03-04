/*
 * Template.h
 *
 *  Created on: 02/07/2013
 *      Author: yuri
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include<list>
#include<iostream>
#include <sstream>

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Template {
private:
	int x;
	int y;
	int width;
	int height;
	Mat *tpl;
	int updateCounter;
	bool templateFound;

public:
	Template();
	Template(int, int, int, int);
	virtual ~Template();
	void setTemplate(Mat);
	Template* getTemplate();
	Mat getImage();
	int getHeight();
	void setHeight(int);
	int getWidth();
	void setWidth(int width);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	bool ThereIsTemplate();
	bool MatchTemplate(Mat);
};

#endif /* TEMPLATE_H_ */

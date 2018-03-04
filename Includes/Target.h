/*
 * Target.h
 *
 *  Created on: Dec 5, 2014
 *      Author: yuri
 */

#ifndef TARGET_H_
#define TARGET_H_

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <list>
#include <math.h>

using namespace std;
using namespace cv;

class Target {
public:
	Target();
	virtual ~Target();
	int GetX();
	int GetY();
	void SetX(int);
	void SetY(int);
	int GetRadius();
	int GetDistance();
	void FindTarget(Mat);
	bool TargetFound();

protected:
	vector<Vec3f> FindCircles(Mat);
	virtual Mat FindColor(Mat);
	virtual void FindDistance();
	int x;
	int y;
	float radius;
	int distance;
	bool targetFound;
	list<float> radiusBuffer;
	list<float>::iterator it2;
	int counter;
	float radiusAvg;
	int i;

};

#endif /* TARGET_H_ */

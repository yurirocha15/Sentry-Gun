/*
 * BlueTarget.h
 *
 *  Created on: Dec 12, 2014
 *      Author: yuri
 */

#ifndef CODE_BLUETARGET_H_
#define CODE_BLUETARGET_H_

#include "Target.h"

class BlueTarget: public Target {
public:
	BlueTarget();
	BlueTarget(int,int,int,int,int,int);
	virtual ~BlueTarget();
	void SetHSVRange(int,int,int,int,int,int);
	Mat FindColor(Mat);
	void FindDistance();
private:
	int iLowH;
	int iLowS;
	int iLowV;
	int iHighH;
	int iHighS;
	int iHighV;
};

#endif /* CODE_BLUETARGET_H_ */

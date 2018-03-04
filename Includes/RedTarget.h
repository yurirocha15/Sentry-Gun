/*
 * RedTarget.h
 *
 *  Created on: Dec 5, 2014
 *      Author: yuri
 */

#include "Target.h"

#ifndef CODE_REDTARGET_H_
#define CODE_REDTARGET_H_

class RedTarget: public Target {
public:
	RedTarget();
	RedTarget(int,int,int,int,int,int);
	virtual ~RedTarget();
	void SetHSVRange2(int,int,int,int,int,int);
	Mat FindColor(Mat);
	void FindDistance();
private:
	int iLowH1;
	int iLowS1;
	int iLowV1;
	int iHighH1;
	int iHighS1;
	int iHighV1;
	int iLowH2;
	int iLowS2;
	int iLowV2;
	int iHighH2;
	int iHighS2;
	int iHighV2;

};

#endif /* CODE_REDTARGET_H_ */

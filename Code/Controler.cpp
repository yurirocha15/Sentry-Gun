/*
 * Controler.cpp
 *
 *  Created on: 11/07/2013
 *      Author: yuri
 */

#include "../Includes/Controler.h"

//Button Functions
bool flagShoot = false;
int flagColor = -1;

void callbackButtonRed(int state,void* userdata)
{
    flagColor=0;
}

void callbackButtonBlue(int state,void* userdata)
{
    flagColor=1;
}

void callbackButtonShoot(int state,void* userdata)
{
    flagShoot = true;
}

Controler::Controler(VideoCapture cap) : capture(cap)
{
	namedWindow("SentryGun", CV_WINDOW_AUTOSIZE | CV_GUI_EXPANDED);
	createButton("Blue",callbackButtonBlue,NULL,CV_RADIOBOX); // Button Blue
	createButton("Red",callbackButtonRed,NULL,CV_RADIOBOX); // Button Red
	while(1)
	{
		if(flagColor == 0)
		{
			target = new RedTarget;
			break;
		}
		else if(flagColor == 1)
		{
			target = new BlueTarget;
			break;
		}
		waitKey(1);
	}

	createButton("Shoot",callbackButtonShoot,NULL,CV_PUSH_BUTTON); // Button Shoot

	try
    {
		arduino_com.open("/dev/ttyUSB1");
		if(!arduino_com.is_open())
			throw "Serial Port Opening ERROR.";
    }
	catch (const char *msg)
	{
		cout << msg << endl;
	}
	switch(flagShoot)
	{
	case(0):
			MainLoop();
			break;
	case(1): break;
	}

}

Controler::~Controler() {
	destroyAllWindows();
	arduino_com.close();
	frame.release();
}

void Controler::MainLoop() {
	const int KEY_SPACE  = 32;
	const int KEY_ESC    = 27;
	char key;
	Template tplt;

	do
	{
		capture >> frame;
		if(frame.empty())
			break;

		Mat frameTpl;
		frame.copyTo(frameTpl);

		target->FindTarget(frameTpl);
		cout << "DISTANCE " << target->GetDistance() << endl << "RADIUS " << target->GetRadius() << endl;
		arduino_com << "update " <<  target->GetX() << " " << target->GetY() << endl << "distance " << target->GetDistance() << " ";

		(target->TargetFound()) ? arduino_com << 1 << endl : arduino_com << 0 << endl;

		key = waitKey(1000/30);

	    if(key == KEY_SPACE)
	    	key = waitKey(0);

	    if(key == KEY_ESC)
	    	break;
	    imshow("SentryGun", frame);
	  }while(1);
}


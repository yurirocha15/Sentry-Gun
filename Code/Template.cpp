/*
 * Template.cpp
 *
 *  Created on: 02/07/2013
 *      Author: yuri
 */

#include "../Includes/Template.h"

Template::Template() : x(0), y(0), width(100), height(100), tpl(NULL), updateCounter(0), templateFound(false)
{
	namedWindow("TEMPLATE", CV_GUI_NORMAL);
}

Template::Template(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), tpl(NULL), updateCounter(0), templateFound(false)
{
}

Template::~Template()
{
	delete(tpl);
	tpl = NULL;
}

void Template::setTemplate(Mat frame) {
	cout << "SET TEMPLATE " << "x " << x << "y " << y << "w " << width << "h " << height << endl;
	tpl = new Mat(frame, Rect(x, y, width, height));
	imwrite("storedtpl.jpg", *tpl);
	templateFound = true;
}

Template* Template::getTemplate() {
	return this;
}

Mat Template::getImage() {
	return *tpl;
}

int Template::getHeight() {
	return height;
}

void Template::setHeight(int h) {
	this->height = h;
}

int Template::getWidth() {
	return width;
}

void Template::setWidth(int w) {
	this->width = w;
}

int Template::getX() {
	return x;
}

void Template::setX(int x) {
	this->x = x;
}

int Template::getY() {
	return y;
}

void Template::setY(int y) {
	this->y = y;
}

bool Template::ThereIsTemplate()
{
	return templateFound;
}

bool Template::MatchTemplate(Mat frame) {
	if(frame.empty() || tpl == NULL)
	{
		templateFound = false;
		return false;
	}
	int WINDOW_WIDTH = frame.cols * 0.8;
	int WINDOW_HEIGHT = frame.rows * 0.8;

    Point minloc, maxloc;
    double  minval, maxval;
    cout << "Setup" << endl;
    /* setup position of search window */
    int win_x0 = this->x - ((WINDOW_WIDTH - this->width) / 2 );
    if(WINDOW_WIDTH > frame.cols)
    	WINDOW_WIDTH = frame.cols;
    int win_y0 = this->y - ((WINDOW_HEIGHT - this->height) / 2 );
    if(WINDOW_HEIGHT > frame.rows)
    	WINDOW_HEIGHT = frame.rows;

    	if(win_x0 < 0){
    		win_x0 = 0;
    	}
    	if(win_x0 + WINDOW_WIDTH > frame.cols){
    		win_x0 = frame.cols - WINDOW_WIDTH;
    	}
    	if(win_y0 < 0){
    		win_y0 = 0;
    	}
    	if(win_y0 + WINDOW_HEIGHT > frame.rows){
    		win_y0 = frame.rows - WINDOW_HEIGHT;
    	}
    /* search object in search window */
    Mat tm (frame,
    		Rect(	win_x0,
    				win_y0,
    				WINDOW_WIDTH,
    				WINDOW_HEIGHT));

    int result_cols =  tm.cols + tpl->cols - 1;
    int result_rows = tm.rows + tpl->rows - 1;
    Mat result;
    imwrite("tpl.jpg",*tpl);
    imwrite("tm.jpg", tm);
    result.create( result_rows, result_cols, CV_32FC1 );
    //cvtColor(tm,tm,CV_8UC1);  //channels need to match template
    //cvtColor(*tpl,*tpl,CV_8UC1);  //channels need to match template
    cout << "Match" << endl;
    matchTemplate( tm, *tpl, result, CV_TM_CCORR_NORMED );
    cout << "thresh" << endl;
    threshold(result, result, 0.94, 1., CV_THRESH_TOZERO);
    cout << "minmax" << endl;
    minMaxLoc( result, &minval, &maxval, &minloc, &maxloc);
    /* if object found... */

    if( maxval > 0.94) {
        //cout<<maxval<<endl<<maxloc.x<<" "<<maxloc.y<<endl;
        /* save object's current location */
        this->x = win_x0 +
        		  maxloc.x;
        this->y = win_y0 +
        		  maxloc.y;
        if(x < 0)
        	x = 0;
        if(y < 0)
        	y = 0;
        if(x > frame.cols - width)
        	x = frame.cols - width;
        if(y > frame.rows - height)
            x = frame.rows - height;
        templateFound = true;
        if(updateCounter >= 5)
        {
        	cout << "update" << endl;
        	this->setTemplate(frame);
        	updateCounter = 0;
        }
        else
        	updateCounter++;

        //TODO: ERASE THIS JUST FOR TESTING
        cout << "printing" << endl;
        Mat tmp;
        frame.copyTo(tmp);
        rectangle(tmp, Point(x, y), Point(x + width, y + height), CV_RGB(255, 0, 0),8, 0);
        imshow("TEMPLATE", tmp);
        return true;
    }
    delete(tpl);
    tpl = NULL;
    templateFound = false;
    return false;
}


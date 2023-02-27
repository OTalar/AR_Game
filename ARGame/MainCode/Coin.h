#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>        
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;

class Coin
{
private:

	int random1;
	int random2;
	bool randomChange;
	Mat img;
	Mat coin;
	int maxRangeX;
	int maxRangeY;
	Point points;

	int y;
	int x;

	

public:
	void randomGenerator();
	void setX(int number);
	void setY(int number);
	
	int getY();
	int getX();

	Point getCoinTopLeft();
	Point getCoinBotRight();

	Mat updateLocation(Mat image);


};


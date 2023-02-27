#include "Coin.h"


//generates random coordinates for the coin
void Coin::randomGenerator()
{

	//generates a random seed
	if (randomChange)
	{
		srand(time(0) + x);
	}
	else
	{
		srand(time(0) + y);
	}

	x = (rand() % maxRangeX) + 1;
	y = (rand() % maxRangeY) + 1;
	random1 = x;
	random2 = y;
}

void Coin::setX(int number)
{
	maxRangeX = number;
}

void Coin::setY(int number)
{
	maxRangeY = number;
}

int Coin::getY()
{
	return y;
}

int Coin::getX()
{
	return x;
}
// marks the coin border coordinates 
Point Coin::getCoinTopLeft()
{
	Point tempNumber;
	tempNumber.x = x;
	tempNumber.y = y;
	return tempNumber;
}
// marks the coin border coordinates 
Point Coin::getCoinBotRight()
{
	Point tempNumber;
	tempNumber.x = x + 50;
	tempNumber.y = y - 50;
	return tempNumber;
}


//displays the coin in main img
Mat Coin::updateLocation(Mat image)
{


	coin = imread("data/coin.png");
	resize(coin, coin, Size(50, 50));
	img = image;
	coin.copyTo(img(cv::Rect(x, y, coin.cols, coin.rows)));
	//rectangle(img, { x, y,50,50 }, Scalar(0, 255, 0));

	return img;
}

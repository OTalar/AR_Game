#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>        
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>

#include <chrono>
#include <iostream>

using namespace std;
using namespace cv;



class Camera
{

private:
	bool blinking;
	VideoCapture mainCamera;
	Mat img;
	Mat imgGray;
	Mat imgGame;
	Mat faceImg;
	string test;
	int score;
	vector<Rect> faces;
	vector<Rect> eyes;

	Point faceTopLeft;
	Point faceBotRight;
public:
	void updateScoreText();
	void updateScore(int number);

	Camera(int number);
	void setCamera(int number);
	void updateImg();
	void display();
	void faceDetection();
	void setImg(Mat img);
	Mat getImg();
	Point getFaceTopLeft();
	Point getFaceBotRight();
	bool getBlinking();
};



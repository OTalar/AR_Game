#include "Camera.h"





void Camera::updateScoreText()
{
	String text = "Coins: "+to_string(score);
	putText(imgGame, text, { 10,50 }, FONT_HERSHEY_DUPLEX, 1, { 0,0,0 });
}

void Camera::updateScore(int number)
{
	score = number;
}


Camera::Camera(int number)
{
	setCamera(number);
}

void Camera::setCamera(int number)
{
	mainCamera.open(number);
}

void Camera::updateImg()
{
	imgGame = imread("data/GameImgs/Background.jpg");
	mainCamera.read(img);
	resize(imgGame, imgGame, img.size());
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
}

void Camera::display()
{
	flip(img,img,1);
	flip(imgGame, imgGame, 1);

	updateScoreText();





	imshow("Game", imgGame);
	//imshow("gray", imgGray);
	imshow("Video", img);
}


void Camera::faceDetection()
{
	CascadeClassifier object;
	

	faceImg = imread("data/GameImgs/bag2.png");
	resize(faceImg, faceImg, Size(50, 50));
	// down scale gray img to improve frame rate
	const int scale = 2;
	Mat resizedImgGray(cvRound(imgGray.rows / scale), cvRound(imgGray.cols / scale), CV_8UC1);
	resize(imgGray, resizedImgGray, resizedImgGray.size());


	// face detection
	object.load("data/haarcascades/lbpcascade_frontalface_improved.xml");
	object.detectMultiScale(resizedImgGray, faces,1.1,3, 0 | CASCADE_SCALE_IMAGE),Size(100,100);


	for (int i = 0; i < faces.size(); i++)
	{
		faces[i].x = faces[i].x * scale;
		faces[i].y = faces[i].y * scale;
		faces[i].height = faces[i].height * scale;
		faces[i].width = faces[i].width * scale;




		if (i == 0)
		{
			
			// marks the faces border coordinates 
			faceTopLeft = { faces[0].x,faces[0].y };
			//faceBotRight = { faces[0].x + faces[0].width,faces[0].y - faces[0].height };
			faceBotRight = { faces[0].x + 50,faces[0].y - 50 };
		}
		rectangle(img, faces[i], Scalar(255, 255, 0));


		
		faceImg.copyTo(imgGame(cv::Rect(faces[i].x, faces[i].y, faceImg.cols, faceImg.rows)));


			// eye detection
			object.load("data/haarcascades/haarcascade_eye.xml");
			object.detectMultiScale(resizedImgGray, eyes, 1.1, 3, 0 | CASCADE_SCALE_IMAGE),Size(15,15);

			for (int x = 0; x < eyes.size(); x++)
			{
				eyes[x].x = eyes[x].x * scale;
				eyes[x].y = eyes[x].y * scale;

				if (eyes.size() > 1)
				{
					if (blinking)
					{
						cout << "Blink" << endl;
						blinking = false;
					}


					//// looks for left eye
					//if (x == 0 && eyes[0].x > eyes[1].x || x == 1 && eyes[1].x > eyes[0].x)
					//{
					//	circle(img, { eyes[x].x + 30,eyes[x].y + 25 }, 15, Scalar(255, 0, 255));
					//
					//}
					////// do nothing if more then 2 eyes have been detected 
					//if (eyes.size() > 2)
					//{

					//}
					//// display the right eye
					//else
					//{
						circle(img, { eyes[x].x + 30,eyes[x].y + 25 }, 15, Scalar(0, 0, 255));
					//	
					/*}*/
				}
				else
				{
					// display one eye
					circle(img, { eyes[x].x + 30,eyes[x].y + 25 }, 15, Scalar(0, 0, 255));

					if (!blinking)
					{
						blinking = true;
					}
				}
			}
	}

}

void Camera::setImg(Mat image)
{
	imgGame = image;
}

Mat Camera::getImg()
{
	return imgGame;
}

Point Camera::getFaceTopLeft()
{
	return faceTopLeft;
}

Point Camera::getFaceBotRight()
{

	return faceBotRight;
}

bool Camera::getBlinking()
{
	return blinking;
}






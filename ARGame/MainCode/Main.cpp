#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "Camera.h"
#include "Coin.h"
#include <thread>

using namespace cv;
using namespace std;



bool coinOverLap(Point leftTop1, Point rightBot1, Point leftTop2, Point rightBot2)
{



    if (leftTop1.x == rightBot1.x || leftTop1.y == rightBot1.y || leftTop2.x == rightBot2.x
        || leftTop2.y == rightBot2.y) {
        return false;
    }

    if (leftTop1.x >= rightBot2.x || leftTop2.x >= rightBot1.x)
        return false;

    if (rightBot1.y >= leftTop2.y || rightBot2.y >= leftTop1.y)
        return false;

    return true;
}



void main() {
    const int maxCoinCap = 5;
    int score = 0;
    int buyDelay = 0;
    Camera mainCamera(0);
    Coin coin1[maxCoinCap];
    int currenCoinCap = 1;
    bool start = true;


    for (int i = 0; i < 6; i++)
    {
        // set coin spawn limit
        coin1[i].setX(450);
        coin1[i].setY(350);
    }
	while (true) {
        
        if (score >= 100)
        {
            break;
        }



        mainCamera.updateImg();
        //generate coordinates for coin at start
        if (start)
        {
            coin1[0].randomGenerator();
            start = false;
        }

        mainCamera.faceDetection();
        // change coin coordinates on ovelapn and increase score
        for (int i = 0; i < currenCoinCap; i++)
        {
            if (coinOverLap(mainCamera.getFaceTopLeft(), mainCamera.getFaceBotRight(), coin1[i].getCoinTopLeft(), coin1[i].getCoinBotRight()))
            {
                score = score + 1;
                cout << "you gained score "<< score << endl;
                coin1[i].randomGenerator();
            }
            mainCamera.setImg(coin1[i].updateLocation(mainCamera.getImg()));
        }
        //cout << mainCamera.getBlinking() << endl;

        // check if blinking
        if (mainCamera.getBlinking())
        {
            
            if (buyDelay < 1)
            {
                // check if reached coin cap
                if (currenCoinCap == maxCoinCap)
                {
                    cout << "too many coins" << endl;
                }
                // buy coin if you have enough money;
                else if (score >= 10)
                { 
                    cout << "upgrade bought" << endl;
                    currenCoinCap = currenCoinCap + 1;
                    coin1[currenCoinCap -1].randomGenerator();
                    score = score - 10;
                }

                buyDelay = 10;
            }
        }
        if (buyDelay >= 1)
        {
           // cout << buyDelay << endl;
            buyDelay = buyDelay - 1;
        }
        
        mainCamera.updateScore(score);
        mainCamera.display();
        waitKey(1);






	}
}
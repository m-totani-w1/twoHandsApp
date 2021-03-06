#include "Leap.h"
#include "Header.h"
#include "SampleListener.h"

using namespace Leap;
/***********LeapMotionの処理***************/

void SampleListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    /* 使用するジェスチャーをセットする */
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
    std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    Frame frame = controller.frame();// 最新のFrameを取得する
    HandList handList = frame.hands();// 全ての手の情報を取得する
    FingerList allFingerList = frame.fingers();// 全ての指の情報を取得する
    GestureList gesturesInFrame = frame.gestures();// 全てのジェスチャーの情報を取得する

    if (handList.count() != 0) {

        //それぞれの個数を表示する
        printf("\n\n\nhands:%d, fingers:%2d, gestures:%d\n",
            handList.count(), allFingerList.count(), gesturesInFrame.count());

        int i, j;

        Vector tmpSwipeV;
        float tmpSwipeS;



        //手と指の処理
        for (i = 0; i < handList.count(); i++) {
            Hand hand = handList[i];
            Vector handCenter = hand.palmPosition();
            FingerList fingerList = hand.fingers();// handの指の情報を取得する

            Vector posi0, posi1;
            Vector tmpCenter = { 0,0,0 };


            //個別の手の情報を出力する
            printf("  hand[%d] (%6.1f,%6.1f,%6.1f), fingers:%d\n",
                i, handCenter.x, handCenter.y, handCenter.z, fingerList.count());
            for (j = 0; j < fingerList.count(); j++) {
                Finger finger = fingerList[j];
                Vector currentPosition = finger.tipPosition();

                if (j == 0) {
                    posi0 = currentPosition;
                }
                else if (j == 1) {
                    posi1 = currentPosition;
                    tmpSwipeV = finger.tipVelocity();
                    tmpSwipeS = tmpSwipeV.magnitude();
                }

                //個別の指の情報を出力する
                printf("    finger[%d] (%6.1f,%6.1f,%6.1f)\n",
                    j, currentPosition.x, currentPosition.y, currentPosition.z);

            }
            if (hand.isLeft()) {
                double dist = posi0.distanceTo(posi1);
                tmpCenter = (posi0 + posi1) / 2;
                lengthL = dist / 20;
                printf("left cube : %f\n", lengthL);
            }
            else {
                if (tmpSwipeS > 500) {
                    if (flag) {
                        flag = false;
                        swipeVector = tmpSwipeV;
                        swipeCenter = tmpCenter - posi1;
                        swipeCenter.z = -swipeCenter.z;
                    }
                    swipeSpead = tmpSwipeS / 200;

                    printf("sV x:%f y:%f z:%f \n", swipeVector.x, swipeVector.y, swipeVector.z);
                }
                else if(tmpSwipeS < 50) {
                    if (!flag) {
                        flag = true;

                    }


                }

                printf("%f\n", swipeSpead);

                double dist = posi0.distanceTo(posi1);
                lengthR = dist / 15;
                //printf("right cube : %f\n", lengthR);

            }


        }

        //ジェスチャーの処理
        GestureList gestures = frame.gestures();
        for (i = 0; i < gestures.count(); i++) {
            Gesture gesture = gestures[i];

            //ジェスチャーの種類の出力
            printf("  gesture[%d] ", i);
            switch (gesture.type()) {
            case Gesture::TYPE_CIRCLE:
                printf("CIRCLE\n");
                break;
            case Gesture::TYPE_SWIPE:

                printf("SWIPE\n");
                break;
            case Gesture::TYPE_KEY_TAP:
                printf("KEY_TAP\n");
                break;
            case Gesture::TYPE_SCREEN_TAP:
                printf("SCREEN_TAP\n");
                break;
            default:
                printf("unknown\n");
                break;
            }
        }

    }

}

void SampleListener::onFocusGained(const Controller& controller) {
}

void SampleListener::onFocusLost(const Controller& controller) {
}


void CleanupExit() {
    controller.removeListener(listener);
    exit(1);
}
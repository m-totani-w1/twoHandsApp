/* --------------------------------------------------------------------
 * gls02.c
 * OpenGL を使って立方体を回転させる
 * -------------------------------------------------------------------- */

 /* ヘッダファイル */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "Leap.h"
#include "SampleListener.h"
#include "freeglut.h"

using namespace std;
using namespace Leap;


/* グローバル変数 */
int   xBegin = 0;               /* マウスドラッグの始点X座標 */
int   yBegin = 0;               /* マウスドラッグの始点Y座標 */
int   PressButton = 0;          /* 現在押されているマウスボタン（1:左,2:中,3:右） */
float CameraAzimuth = 90.0;   /* カメラの位置（方位角） */
float CameraElevation = 0.0;    /* カメラの位置（仰角） */
float CameraDistance = 5.0;    /* カメラの位置（原点からの距離） */
float CameraX = 0.0;            /* カメラの位置（X座標） */
float CameraY = 0.0;            /* カメラの位置（Y座標） */
float CameraZ = 10.0;            /* カメラの位置（Z座標） */
float BoxRotate = 0.0;          /* 箱の回転角 */

float lengthL = 1;       /* 左の一辺の長さ */
float lengthR = 1;        /* 右の一辺の長さ */
float swipeSpead = 1;           /* 人差し指のスワイプの速さ */
Vector swipeVector = { 0,0,1 };          /* 右手の人差し指のスワイプの速度 */
Vector swipeCenter = { 1,1,0 };         /* 回転体の中心方向を指すベクトル*/
bool flag = true;

//必要だろうか。。。？
Controller controller;
SampleListener listener;
Screen screen;


/***********************************************************
|  関数：main()
|  説明：メイン関数
|  引数：int argc       実行時引数の数
|  引数：char** argv    実行時引数の内容（文字列配列）
|  戻値：int            0:正常終了
***********************************************************/
int main(int argc, char** argv)
{
    SampleListener listener;
    Controller controller;
    controller.addListener(listener);

    /* 初期化 */
    glutInit(&argc, argv);  /* OpenGL の初期化 */
    myInit(argv[0]);        /* ウインドウ表示と描画設定の初期化 */

    /* イベント処理ループ */
    glutMainLoop();

    /* プログラム終了 */
    return(0);
}
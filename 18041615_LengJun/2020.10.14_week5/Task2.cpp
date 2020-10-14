#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void threshold_adapt(int , void* data);//回调函数声明

string window_adapt = "adaptive";      //窗口名
int lowC = 0, maxC = 50;               //常数C范围
int lowSize = 25, maxSize = 200;       //blocksize范围

void threshold_adapt(int , void* data) //回调函数定义，用于自适应二值化
{
	Mat src = *(Mat*)(data);           //取灰度图数据
	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY, lowSize!=0 ? lowSize*2+1 :3, lowC);   //二值化

	imshow(window_adapt, dst);         //显示二值图
}


int main()
{
	Mat srcMat, gryMat,dst;
	srcMat = imread("F:\\Test_Image\\2.jpg");
	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY); //RGB转灰度

	threshold(gryMat, dst, 120, 255, THRESH_OTSU);//大津法
	imshow("OSTU", dst);

	namedWindow(window_adapt);                      //创建窗口
	createTrackbar("blocksize", window_adapt, &lowSize, maxSize, threshold_adapt, &gryMat); 
	createTrackbar("const_C", window_adapt, &lowC, maxC, threshold_adapt, &gryMat);         //创建blocksize和常数C的滑动条

	waitKey(0);
	return 0;
}


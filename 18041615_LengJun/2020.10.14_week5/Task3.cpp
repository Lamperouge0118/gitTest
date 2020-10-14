#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string window_name = "binaryMat";      //窗口名

void threshod_Mat(int th, void* data); //声明回调函数

void threshod_Mat(int th, void* data)  //回调函数定义
{
	Mat src = *(Mat*)(data);           //取灰度图数据
	Mat dst;
	threshold(src, dst, th, 255, 0);   //二值化
	 
	imshow(window_name, dst);          //显示二值图
}

int main()
{
	Mat srcMat,gryMat;
	int lowTh = 30;
	int maxTh = 255;//设定阈值范围，也即滑动条的范围

	srcMat = imread("F:\\Test_Image\\2.jpg");     //检查图像是否成功加载
	if (!srcMat.data)
	{
		cout << "图像载入失败" << endl;
		return 0;
	}

	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);    //BGR转灰度图
	imshow(window_name, gryMat);                 //显示灰度图
	createTrackbar("threshold", window_name, &lowTh, maxTh, threshod_Mat, &gryMat); //创建滑动条，依附于"binaryMat"窗口

	waitKey(0);
	return 0;
}
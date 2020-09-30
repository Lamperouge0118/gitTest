#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("F:\\Test_Image\\Blank_R.png");
	Point pt,pt1,pt2;      //定义圆心，两个点

	pt.x = 750;            //圆心坐标
	pt.y = 450;
	circle(img, pt, 150, CV_RGB(255, 0, 255), 1, 8, 0);   //以pt为圆心，150像素为半径画圆，紫色

	pt1.x = 300;           //端点坐标
	pt1.y = 0;
	pt2.x = 1200;
	pt2.y = 900;
	line(img, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);     //以pt1,pt2为端点画线，红色

	Rect rect;                                           //定义矩形
	rect.x = 600;                                        //矩形左上端点
	rect.y = 300;
	rect.width = 300;                                    //矩形长宽
	rect.height = 300;
	rectangle(img, rect, CV_RGB(0, 0, 0), 1, 8, 0);      //画黑色矩形框

	imshow("img", img);                                  //显示
	waitKey(0);

	return 0;
}
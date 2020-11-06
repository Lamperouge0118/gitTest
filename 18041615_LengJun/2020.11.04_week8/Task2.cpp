/***********************************************************练习2 旋转及缩放****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

#define pi 3.1415926

using namespace cv;
using namespace std;

Mat srcImg, out, rot;         //原图，结果图，变换矩阵
double scale;                 //缩放倍数
int angle = 10;               //旋转角度
Point2f center;               //旋转中心
double l;                     //旋转后外接矩形的长度
double h;                     //旋转后外接矩形的宽度

double tmp = 1 / 180.0 * pi;  //角度转弧度因子


void affine_matrix(int, void*)
{
	//根据旋转角度计算外接矩形的长和宽
	if ((angle >= 0) && (angle <= 90))
	{

		l = srcImg.rows * cos(angle * tmp) + srcImg.cols * sin(angle * tmp);
		h = srcImg.rows * sin(angle * tmp) + srcImg.cols * cos(angle * tmp);
	}
	else
	{
		if ((angle > 90) && (angle <= 180))
		{
			l = srcImg.rows * cos((180-angle) * tmp) + srcImg.cols * sin((180-angle) * tmp);
			h = srcImg.rows * sin((180-angle) * tmp) + srcImg.cols * cos((180-angle) * tmp);
		}
		else
		{
			if ((angle > 180) && (angle <= 270))
			{
				l = srcImg.rows * cos((angle-180) * tmp) + srcImg.cols * sin((angle-180) * tmp);
				h = srcImg.rows * sin((angle-180) * tmp) + srcImg.cols * cos((angle-180) * tmp);
			}

			else
			{
				l = srcImg.rows * cos((360-angle) * tmp) + srcImg.cols * sin((360-angle) * tmp);
				h = srcImg.rows * sin((360-angle) * tmp) + srcImg.cols * cos((360-angle) * tmp);
			}
		}
	}

	scale = srcImg.rows/l;                             //计算缩放因子,只适用于正方形图像
	rot = getRotationMatrix2D(center, angle, scale);   //取得变换矩阵

	warpAffine(srcImg, out, rot, srcImg.size());       //进行仿射变换

	imshow("结果", out);                               //显示结果
}

int main()
{


	srcImg = imread("E:\\Test_Image\\17.jpg");        //读取图片
	if (srcImg.empty())
	{
		cout << "不能打开图像" << endl;
		destroyAllWindows();
		return -1;
	}

	center = Point2f(srcImg.cols / 2, srcImg.rows / 2);         //求旋转中心
	imshow("原图", srcImg);                                     //显示原图

	createTrackbar("旋转角度","原图", &angle, 360, affine_matrix);      //创建滑动条
	affine_matrix(0,0);                                                //调用回调函数

	waitKey(0);
	return 0;

}
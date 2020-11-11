/***********************************************************练习1 旋转及缩放****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

#define pi 3.1415926

using namespace cv;
using namespace std;

Mat srcImg, out, rot;         //原图，结果图，变换矩阵
int scale = 5;                //缩放倍数
int angle = 10;               //旋转角度
Point2f center;               //旋转中心

void affine_matrix(int, void*)
{
	rot = getRotationMatrix2D(center, angle, 1);                        //取得变换矩阵
	Rect bbox = RotatedRect(center, srcImg.size(),angle).boundingRect();//获取外界四边形
	//调整仿射矩阵
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	warpAffine(srcImg, out, rot, bbox.size());       //进行仿射变换

	float s = scale ? scale/5.0 : 1;                 //转换缩放比例
	Size ResSize = Size(out.cols * s, out.rows * s); //定义尺寸，即缩放后的尺寸
	resize(out, out, ResSize, INTER_LINEAR);         //缩放
	imshow("结果", out);                             //显示结果
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

	createTrackbar("旋转角度", "原图", &angle, 360, affine_matrix);      //创建滑动条
	createTrackbar("缩放倍数", "原图", &scale, 10, affine_matrix);
	affine_matrix(0, 0);                                                //调用回调函数

	waitKey(0);
	return 0;

}
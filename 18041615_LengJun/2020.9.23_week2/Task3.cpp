#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("F:/Test_Image/47621790_p0.jpg");//读取图片

	cout << "原图：" << endl;   //显示原图
	imshow("origin", srcImage);
	waitKey(0);

	int height = srcImage.rows;  //获取图片长度
	int width = srcImage.cols;   //获取图片宽度
	uchar average;
	uchar threshold = 100;       //设定阈值

/********************************************分通道处理像素值***********************************************************/
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			average = (srcImage.at<Vec3b>(i,j)[0] + srcImage.at<Vec3b>(i,j)[1] + srcImage.at<Vec3b>(i,j)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			srcImage.at<Vec3b>(i,j)[0] = average;
			srcImage.at<Vec3b>(i,j)[1] = average;
			srcImage.at<Vec3b>(i,j)[2] = average;
		}
	}

	cout << "二值图像：" << endl;//显示二值图像
	imshow("Binary", srcImage);
	waitKey(0);
	return 0;

}


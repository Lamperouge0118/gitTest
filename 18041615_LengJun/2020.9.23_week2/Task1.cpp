#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("F:/Test_Image/47621790_p0.jpg");//读取图片
	int height = srcImage.rows; //获取图片长度
	int width = srcImage.cols;  //获取图片宽度
	uchar average;

	cout << "原图：" <<endl;     //显示原图
	imshow("origin", srcImage);
	waitKey(0);

	/********************************************分通道处理像素值***********************************************************/
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			average = (srcImage.at<Vec3b>(i,j)[0] + srcImage.at<Vec3b>(i,j)[1] + srcImage.at<Vec3b>(i,j)[2]) / 3;
			srcImage.at<Vec3b>(i,j)[0] = average;
			srcImage.at<Vec3b>(i,j)[1] = average;
			srcImage.at<Vec3b>(i,j)[2] = average;
		}
	}

	cout << "灰度图：" << endl;//显示处理后的灰度图
	imshow("Gray", srcImage);
	waitKey(0);
	return 0;

}

 
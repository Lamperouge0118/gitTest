#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcM = imread("F:/Test_Image/47621790_p0.jpg");//读取图片
	Mat deepMat,shallowMat;

	srcM.copyTo(deepMat);//深复制
	shallowMat = srcM;   //浅复制

	cout << "原始的deepMat和shallowMat：" << endl;//显示原始的deepMat和shallowMat图像
	imshow("original deepMat", deepMat);
	imshow("original shallowMat", shallowMat);
	waitKey(0);


	int height = srcM.rows;//获取图片长度
	int width = srcM.cols; //获取图片宽度
	uchar average;
	uchar threshold=100;   //设定阈值
						   
/********************************************分通道处理像素值***********************************************************/
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			average = (srcM.at<Vec3b>(i, j)[0] + srcM.at<Vec3b>(i, j)[1] + srcM.at<Vec3b>(i, j)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			srcM.at<Vec3b>(i, j)[0] = average;
			srcM.at<Vec3b>(i, j)[1] = average;
			srcM.at<Vec3b>(i, j)[2] = average;
		}
	}

	cout << "变化后的deepMat和shallowMat：" << endl;//显示变化后的deepMat和shallowMat图像
	imshow("changed deepMat", deepMat);
	imshow("changed shallowMat", shallowMat);
	waitKey(0);
	return 0;

}


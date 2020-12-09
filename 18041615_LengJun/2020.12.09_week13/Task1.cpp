/********************************************************************练习一**********************************************************************************/
//实现gamma矫正
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


void MyGammaCorrection_A(Mat src, Mat& dst, float r);//伽马校正函数声明
void MyGammaCorrection_B(Mat src, Mat& dst, float r);

int main()
{
	Mat srcImg, dst1, dst2;
	
	srcImg = imread("E:\\Test_Image\\26.jpg");
	if (srcImg.empty())
	{
		cout << "无法打开该图像" << endl;
		destroyAllWindows();
		return -1;
	}

	MyGammaCorrection_A(srcImg, dst1, 1 / 2.2);
	MyGammaCorrection_B(srcImg, dst2, 1 / 2.2);

	imshow("src", srcImg);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey(0);
	return 0;
}


void MyGammaCorrection_A(Mat src, Mat& dst, float r)
{
	//归一化
	src.convertTo(src, CV_32F);
	normalize(src, src, 1.0, 0.0, NORM_MINMAX);
	//计算像素值
	int width = src.cols * src.channels();
	int height = src.rows;
	for (int i = 0; i < height; i++)
	{
		float* data = src.ptr<float>(i);
		for (int j = 0; j < width; j++)
		{
				data[j] = saturate_cast<uchar>(pow(data[j], r) * 255);
		}
	}
	if (src.channels() == 1)
		src.convertTo(dst, CV_8UC1);
	else
		src.convertTo(dst, CV_8UC3);
}

/*
查表法：建立查询表数组Table，size == 256遍历[0，255]
1.下标值归一化到[0, 1]之间
2.Output = Input^r
3.Lut[i] = Output * 255
调用LUT函数，
遍历所有像素像素值作为下表，直接从Table中读出变化后的像素值
*/
void MyGammaCorrection_B(Mat src, Mat& dst, float r)
{
	Mat Table(1, 256, CV_8U);
	uchar* p = Table.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = saturate_cast<uchar>(pow((float)(i / 255.0), r) * 255);
	}
	LUT(src, Table, dst);

}
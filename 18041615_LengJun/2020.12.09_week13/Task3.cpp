/*******************************************************************练习三**************************************************************************************/
//原图中有一些字，由于曝光不足无法观察到，请使用gamma矫正，并设置合适参数，找出隐藏的信息

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


void MyGammaCorrection_A(Mat src, Mat& dst, float r);//伽马校正函数声明
void MyGammaCorrection_B(Mat src, Mat& dst, float r);
void on_gamma(int, void* userdata);                  //伽马指数回调函数


Mat dst1, dst2;                             
int gamma1 = 0.35 * 100 , gamma2 = 0.35 * 100;      //伽马指数初值
int max_r = 1 * 100;                                //伽马指数最大值

int main()
{
	Mat srcImg;

	srcImg = imread("E:\\Test_Image\\28.jpg");
	if (srcImg.empty())
	{
		cout << "无法打开该图像" << endl;
		destroyAllWindows();
		return -1;
	}
	imshow("src", srcImg);
	createTrackbar("gamma1", "src", &gamma1, max_r, on_gamma, &srcImg);
	createTrackbar("gamma2", "src", &gamma2, max_r, on_gamma, &srcImg);
	on_gamma(0, &srcImg);

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

void on_gamma(int, void* userdata)
{
	float r1 = gamma1 ? gamma1 / 100.0 : 0.01;
	float r2 = gamma2 ? gamma2 / 100.0 : 0.01;
	Mat src = *(Mat*)userdata;

	MyGammaCorrection_A(src, dst1, r1);
	MyGammaCorrection_B(src, dst2, r2);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
}


#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>
#include <typeinfo>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImg = imread("F:\\Test_Image\\4.png");
	float histgram[3][256];                                   //定义二维数组，分通道存取概率
	//float (*histgram)[256] = new float[3][256];
	memset(histgram, 0, sizeof(histgram));                    //初始化数组

	int width,height,pixel;                                    //定义宽，长，像素量
	width = srcImg.cols;
	height = srcImg.rows;
	pixel = width * height;

	vector<Mat> channels;                                     //定义Mat型的vecto容器
	split(srcImg, channels);                                  //分离通道

	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	for (int i = 0; i < height; i++)                          //分通道计算像素值出现次数，并存入数组
	{
		for (int j = 0; j < width; j++)
		{
			histgram[0][R.at<uchar>(i, j)] += 1;
			histgram[1][G.at<uchar>(i, j)] += 1;
			histgram[2][B.at<uchar>(i, j)] += 1;
		}
	}
	
	int cnt = 3 * 256;                                        //计算像素值出现的概率，更新数组
	for (int k = 0; k < cnt; k++)
	{
		*(histgram[0] + k) /= pixel;
	}

	
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src_color = imread("F:\\Test_Image\\4.png");
	vector<Mat> channels;       //Mat型的vecto容器
	split(src_color, channels); //通道分离

	Mat B = channels.at(0);     //分通道存储
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	imshow("Red", R);          //显示
	imshow("Green", G);
	imshow("Blue", B);
	imshow("original Mat", src_color);

	waitKey(0);
	return 0;
}


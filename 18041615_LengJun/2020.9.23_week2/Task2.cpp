#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("F:/Test_Image/47621790_p0.jpg",0);//读取图片，并直接转为灰度图
	cout << "灰度图" << endl; //显示图片
	imshow("Gray", srcImage);
	waitKey(0);
	return 0;

}


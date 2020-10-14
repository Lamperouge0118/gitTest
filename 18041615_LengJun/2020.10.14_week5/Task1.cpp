#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	double scale = 0.5;//缩放倍数


	//定义HSV各自的范围
	//[0,180]
	//肤色
	double i_minH = 0;
	double i_maxH = 20;
	//[0,255]
	double i_minS = 43;
	double i_maxS = 255;
	//[0,255]
	double i_minV = 55;
	double i_maxV = 255;

	while (true)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;
		Size ResImgSize = Size(frame.cols * scale, frame.rows * scale);//定义尺寸，即所得帧缩放后的尺寸
		Mat rFrame = Mat(ResImgSize, frame.type());//以尺寸ResImgSize，frame的数据类型创建Mat
		resize(frame, rFrame, ResImgSize, INTER_LINEAR);//把frame按ResImgSize尺寸缩放，结果存入rFrame

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);//将rFrame转为HSV格式，结果存入hsvMat

		rFrame.copyTo(detectMat);//拷贝原图

		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//二值化，阈值内像素值为255，否则为0

		imshow("while: in the range", detectMat);
		imshow("frame", rFrame);

		waitKey(30);
	}
}
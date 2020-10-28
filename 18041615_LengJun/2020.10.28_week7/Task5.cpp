/*******************************************************************练习三，磨皮程序**********************************************************************************/
//使用已经学过的算法，实现一个简单的磨皮程序，即人物皮肤的部分显得光滑。（mask，卷积，HSV范围限制）

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void Ksize(int, void*);			   //滤波Ksize回调函数
void FrameSize(int, void*);        //帧尺寸回调函数

Mat frame, rFrame;                 //原帧,尺寸改变后的原帧
Mat detectMat, edge;               //提取皮肤的二值图，detectMat滤波后得到的掩膜edge
int KsizeValue = 0;                //Ksize滑动条初始位置
int scale = 0;                     //帧尺寸滑动条初始位置


void Ksize(int, void*)            //滤波Ksize回调函数
{
	//双边滤波
	//bilateralFilter(detectMat, edge,KsizeValue, KsizeValue*2, KsizeValue/2);

	//中值滤波
	medianBlur(detectMat, edge, KsizeValue > 0 ? KsizeValue * 2 + 1 : 3);

	//高斯滤波
	//int length = KsizeValue * 2 + 1;
	//GaussianBlur(detectMat, edge, Size(length, length), 0, 0);
	//均值滤波
	//blur(detectMat, edge, Size(length, length));
	imshow("edge", edge);
}

void FrameSize(int, void*)        //帧尺寸回调函数
{
	double s;
	if (!scale)                   //排除0值
	{
		s = 1.0;
	}
	else
	{
		s = (scale >= 1) && (scale <= 5) ? scale / 5.0 : (scale - 3.0) * 0.5;//缩小倍率步长为0.2，增大倍率步长为0.5
	}

	Size ResSize = Size(frame.cols * s, frame.rows * s);//定义尺寸，即平滑帧缩放后的尺寸
	resize(frame, rFrame, ResSize, INTER_LINEAR); //把frame按ResSize尺寸缩放，结果存入rFrame
}

int main()
{
	Mat hsvMat, dst;       //HSV类型，磨皮输出
	
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

	VideoCapture cap(0);                        //打开摄像头

	while (true)
	{
		cap >> frame;                           //读取帧

		if (frame.empty())
		{
			cout << "不能从视频文件中读取帧!" << endl;
			destroyAllWindows();
			return -1;
		}

		imshow("原帧", frame);

		//创建滑动条，调节帧尺寸
		createTrackbar("帧大小", "原帧", &scale, 10, FrameSize);
		FrameSize(scale, 0);                             //调用回调函数

		//转HSV，并提取皮肤
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);         //将rFrame转为HSV格式，结果存入hsvMat
		rFrame.copyTo(detectMat);                        //拷贝rFrame
		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//二值化，阈值内像素值为255，否则为0，取皮肤像素
		imshow("mask", detectMat);

		//创建滑动条，滤波
		createTrackbar("内核尺寸", "原帧", &KsizeValue, 50, Ksize); //创建滑动条
		Ksize(KsizeValue, 0);                                      //调用回调函数

		dst = Scalar::all(0);
		rFrame.copyTo(dst, edge);
		imshow("磨皮", dst);

		//等待键盘相应，按下ESC键退出
		if (waitKey(30) == 27)
		{
			destroyAllWindows();
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
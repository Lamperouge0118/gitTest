/*******************************************************************练习二，均值滤波**********************************************************************************/
//读取摄像头图像，并对摄像头图像进行均值滤波

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void Blur_Ksize(int, void*);      //均值滤波Ksize回调函数
void FrameSize(int, void*);       //帧尺寸回调函数
Mat frame, dst, rFrame;           //原帧，平滑帧，尺寸改变后的原帧
int KsizeValue = 0;               //Ksize滑动条初始位置
int scale = 0;                    //帧尺寸滑动条初始位置


void Blur_Ksize(int, void*)       //均值滤波Ksize回调函数
{
	int length = KsizeValue*2 + 1;
	blur(rFrame, dst, Size(length,length));
	imshow("平滑帧", dst);
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
	resize(frame, rFrame, ResSize, INTER_LINEAR);     //把frame按ResSize尺寸缩放，结果存入rFrame
}

int main()
{
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

		createTrackbar("内核尺寸", "原帧", &KsizeValue, 15, Blur_Ksize); //创建滑动条
		createTrackbar("平滑帧大小", "原帧", &scale, 10, FrameSize);
		FrameSize(scale, 0);                                            //调用回调函数
		Blur_Ksize(KsizeValue, 0);                                      
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
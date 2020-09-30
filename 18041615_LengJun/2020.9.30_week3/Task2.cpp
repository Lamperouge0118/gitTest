#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;	

int main()
{
	VideoCapture cap;    

	cap.open(0);           //打开本机第一个摄像头

	if (!cap.isOpened())   //检查视频是否成功开启
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}

	double FPS = cap.get(CAP_PROP_FPS);  //获取视频的FPS
	cout << "FPS" << FPS << endl;

	while (true)
	{
		Mat frame;
		bool read_Sucess = cap.read(frame);  //获取视频当前帧

		if (!read_Sucess)                    //检查是否成功获取当前帧
		{
			cout << "不能从视频文件中读取帧" << endl;  
			break;
		}
		else
		{
			imshow("frame", frame);         //显示当前帧
		}
		waitKey(30);
	}

	return 0;
}
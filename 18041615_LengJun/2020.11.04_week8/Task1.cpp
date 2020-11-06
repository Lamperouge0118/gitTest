/*****************************************************练习1 canny算子***************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void threshold(int, void*);        //阈值回调函数
void Ksize(int, void*);            //结构算子尺寸回调函数

Mat grd_x, grd_y;                  //x,y的边缘
Mat gray;                          //灰度图
Mat edge1, edge2;                  //canny结果


int KsizeValue = 3;                //Ksize滑动条初始位置
int th1 = 20;

void threshold(int, void*)         //阈值回调函数
{
	Canny(grd_x, grd_y, edge1, th1, th1*3);
	Canny(gray, edge2, th1, th1*3, 3);
	imshow("edge1", edge1);        //显示canny计算的边缘
	imshow("edge2", edge2);
}

void Ksize(int, void*)            //滤波Ksize回调函数
{
	//双边滤波
	//bilateralFilter(gray, gray,KsizeValue, KsizeValue*2, KsizeValue/2);

	//中值滤波
	//medianBlur(gray, gray, KsizeValue > 0 ? KsizeValue * 2 + 1 : 3);

	//高斯滤波
	int length = KsizeValue * 2 + 1;
	GaussianBlur(gray, gray, Size(length, length), 0, 0);
	//均值滤波
	//blur(gray, gray, Size(length, length));
}

int main()
{
	Mat frame;
	Mat dst1, dst2;          //掩膜结果


	VideoCapture cap(0);     //打开摄像头

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

		createTrackbar("第一阈值", "原帧", &th1, 100, threshold);   //创建滑动条
		createTrackbar("内核尺寸", "原帧", & KsizeValue, 50, Ksize);

		cvtColor(frame, gray, COLOR_BGR2GRAY);                     //转灰度
		Ksize(KsizeValue, 0);                                      //滤波
	
		Sobel(frame,grd_x, CV_16S, 1, 0, 3);                       //计算X方向梯度
		Sobel(frame,grd_y, CV_16S, 0, 1, 3);                       //计算Y方向梯度

		threshold(th1,0);                                          //canny计算边缘

		dst1 = Scalar::all(0);
		dst2 = Scalar::all(0);
		frame.copyTo(dst1, edge1);                                 //掩膜结果
		frame.copyTo(dst2, edge2);
		imshow("dst1", dst1);                                      //显示掩膜结果
		imshow("dst2", dst2);

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
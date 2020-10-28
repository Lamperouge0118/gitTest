/*******************************************************************练习四，边缘提取**********************************************************************************/
//读取摄像头图像，并对摄像头图像进行边缘提取，分别提取x，y方向上的边缘，观察结果有何区别。

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat grd_x, grd_y;
	Mat AbsGrdX, AbsGrdY;
	Mat frame, gray, dst;

	VideoCapture cap(0);           //打开摄像头                  
	
	while (true)
	{
		cap >> frame;              //读取帧

		if (frame.empty())
		{
			cout << "不能从视频文件中读取帧!" << endl;
			destroyAllWindows();
			return -1;
		}

		cvtColor(frame, gray, COLOR_BGR2GRAY);  //转灰度
		Sobel(gray, grd_x, CV_16SC1, 1, 0, 3);  //计算X方向梯度
		Sobel(gray, grd_y, CV_16SC1, 0, 1, 3);  //计算Y方向梯度

		convertScaleAbs(grd_x, AbsGrdX);        //计算绝对值，并把结果转换为8位
		convertScaleAbs(grd_y, AbsGrdY);

		addWeighted(AbsGrdX, 0.5, AbsGrdY, 0.5, 0, dst); //按比例合并梯度

		imshow("原帧", frame);                     //显示原帧
		imshow("X边缘", AbsGrdX);                  //显示两个方向的梯度的幅值
		imshow("Y边缘", AbsGrdY);

		imshow("sobel边缘检测",dst);


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
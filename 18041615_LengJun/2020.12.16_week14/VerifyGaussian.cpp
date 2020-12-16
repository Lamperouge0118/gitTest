/*********************************************************验证视频中的像素变换是否符合高斯分布规律*****************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int EVENT, int x, int y, int flags, void* userdata);//鼠标响应，选取像素
void draw_histogram(float* histogram, Mat& histoMat, int binwidth, int binheight);//画直方图
Point Sp;//选取的像素坐标

int main()
{
	VideoCapture cap(0);//打开摄像头
	if (!cap.isOpened())
	{
		cout << "不能打开视频" << endl;
		return -1;
		destroyAllWindows();
	}

	Mat frame;
	float histogram[256] = {0};//直方图数组
	int bin_width =  4;        //柱形宽度
	int bin_height = 500;      //柱形的最大高度
	Mat histoMat(bin_height, bin_width*256, CV_8UC3, Scalar(255, 255 ,255));//直方图画布
	int cnt = 0;               //计数值


	while (1)
	{
		cap >> frame;
		if (frame.empty())
		{
			cout << "不能读取视频帧" << endl;
			return -1;
			destroyAllWindows();
		}

		//从第一帧选取像素
		if (!cnt)
		{
			Mat SelectMat;           //辅助Mat
			SelectMat = frame.clone();
			namedWindow("SelectMat");
			imshow("SelectMat", SelectMat);
			setMouseCallback("SelectMat", onMouse, &SelectMat);//创建鼠标响应
			waitKey(0);
			destroyAllWindows();
		}

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		

		int value = frame.at<uchar>(Sp);                      //取灰度值
		histogram[value] ++;                                  //直方图累加
		draw_histogram(histogram, histoMat, bin_width, bin_height);//画直方图
		drawMarker(frame, Sp, Scalar(0, 0, 255));             //在当前帧绘出所选像素
		imshow("frame", frame);                               //显示当前帧
		imshow("histogram", histoMat);                        //显示直方图
		//延时30ms
		//等待键盘相应，按下ESC键退出
		if (waitKey(30) == 27) 
		{
			destroyAllWindows();
			break;
		}
		cnt ++;
	}
	return 0;
}

//鼠标响应，选取像素
void onMouse (int EVENT, int x, int y, int flags, void* userdata)
{
	Mat disp = *(Mat*)userdata;
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN://当左键按下
	{	
		Sp.x = x;          //返回所选像素坐标
		Sp.y = y;
		drawMarker(disp, Sp, Scalar(0, 0, 255));//绘出坐标位置
		imshow("SelectMat", disp);
	}
	break;
	}
}

//画直方图
void draw_histogram(float* histogram, Mat& histoMat, int binwidth, int binheight)
{
	histoMat = Scalar(255, 255, 255);//清除画布
	//取直方图最大值，便于归一化
	float maxValue = *max_element(histogram, histogram + 256);
	for (int i = 0; i < 256; i++)
	{
		Rect bin, edge;//柱形，柱形外轮廓

		edge.x = (binwidth-1) * i;//每个柱形的左上角x坐标
		float height = histogram[i] / maxValue * binheight;//归一化柱形高度
		edge.width = binwidth;    //柱形宽度
		edge.height = height;
		edge.y = binheight - edge.height;//每个柱形的左上角y坐标

		bin.x = edge.x + 1, bin.y = edge.y + 1;
		bin.width = edge.width - 2, bin.height = edge.height - 1;
		rectangle(histoMat, edge, Scalar(0), 0);
		rectangle(histoMat, bin, Scalar(255, 255, 0), -1);
	}
}
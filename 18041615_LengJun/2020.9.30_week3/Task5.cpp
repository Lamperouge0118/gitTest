#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>

using namespace cv;
using namespace std;

//typedef float(*rt)[256];

float* data_histg(void);                              //函数声明，计算直方图 
float max(float s[],int n);                           //函数声明，求数组元素最大值

float* data_histg()
{
	Mat srcImg = imread("F:\\Test_Image\\1.jpg");
	float(*histgram)[256] = new float[3][256]{};      //定义二维数组，分通道存取概率,并初始化
	//memset(histgram, 0, sizeof(histgram)*3*256);    

	int width, height, pixel;                         //定义宽，长，像素量
	height = srcImg.rows;               
	width = srcImg.cols;
	pixel = width * height;

	vector<Mat> channels;                             //定义Mat型的vecto容器
	split(srcImg, channels);                          //分离通道

	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	for (int i = 0; i < height; i++)                 //分通道计算像素值出现次数，并存入数组
	{
		for (int j = 0; j < width; j++)
		{
			histgram[0][R.at<uchar>(i, j)] += 1;    //hisgram中依次存放R,G,B三个通道
			histgram[1][G.at<uchar>(i, j)] += 1;
			histgram[2][B.at<uchar>(i, j)] += 1;
		}
	}

	int cnt = 256*3;                                //计算像素值出现的概率，更新数组
	for (int k = 0; k < cnt; k++)
	{
		*(histgram[0] + k) /= pixel;
	}

	imshow("Red", R);                                        //分通道显示
	imshow("Green", G);
	imshow("Blue", B);

	return histgram[0];                             //返回数组中第一个元素的指针
}

float max(float s[], int n)                         //计算数组元素最大值
{
	float tmp;
	if (n == 1)
		return s[0];

	tmp = max(s, n - 1);
	if (tmp > s[n - 1])
		return tmp;
	return s[n - 1];
}

int main()                                              //画直方图
{
	Mat img[3];
	img[0] = imread("F:\\Test_Image\\Blank_R.png");
	img[1] = imread("F:\\Test_Image\\Blank_G.png");
	img[2] = imread("F:\\Test_Image\\Blank_B.png");

	Point pt0,ptx,pty;     //定义坐标轴的端点

	pt0.x = 0;      //坐标轴原点

	ptx.x = 1500;   //坐标轴x轴端点

	pty.x = 0;     //坐标轴y轴端点
	pty.y = 0;

	int width,height;
	cout << "请输入直方图的宽度（单位为像素,例如输入1280,则每个矩形的宽度为5像素)：" << endl;
	cin >> width;
	cout << "请输入直方图的长度（单位为像素,长度是指归一化后单位1的长度)：" << endl;
	cin >> height;

	Rect rect;
	rect.width = width/256;       //计算每一个小矩形的宽度

	float* p= data_histg();       //取直方图数据的首地址
	
	for (int n = 0; n<3 ;n++)     //分通道画直方图
	{
		rect.x = 5;               //直方图起始点横坐标
		int N = (n + 1) * 256;    //各个通道的元素地址偏移量极限
		int i = 256 * n;          //各个通道的起始元素地址偏移量
		float max_height = max(p+i, 256) * height;   //调用max函数,计算各通道出现概率最大的像素值所对应的矩形长度

		for (;i < N; i++)         //对于特定通道，画出其直方图
		{
			rect.y = 50;          //重置矩形端点的纵坐标
			pt0.y = ptx.y = max_height + rect.y + 5;   //计算坐标轴
			line(img[n], pt0, ptx, CV_RGB(255, 0, 0), 1, 8, 0);     //绘出坐标轴
			line(img[n], pt0, pty, CV_RGB(255, 0, 0), 1, 8, 0);

			rect.height = *(p + i) * height;             //计算各像素值对应的矩形长度
			rect.y += (max_height - rect.height);                   //矩形端点坐标的重定位
			rectangle(img[n], rect, CV_RGB(0, 0, 0), 1, 8, 0);      //绘出小矩形
			rect.x += rect.width;                                   //横坐标平移，准备绘出下一个矩形
		}
	}
	
	imshow("img_R", img[0]);                                        //分通道绘出直方图
	imshow("img_G", img[1]);
	imshow("img_B", img[2]);
	waitKey(0);
	return 0;
}
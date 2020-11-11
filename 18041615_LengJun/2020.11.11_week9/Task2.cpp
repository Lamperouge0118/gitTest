/*******************************************************练习2********************************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

void threshold(int, void*);
Mat srcImg;               //原图
Mat edge;                 //边缘
Mat gray;                 //灰度图

int th = 100 , th1 = 150; //霍夫累加阈值，Canny第一阈值

void threshold(int, void*)
{
	Mat dst = srcImg.clone();                   //把原图拷贝到输出
	Canny(gray, edge, th1, (double)th1 * 3, 3); //计算边缘
	imshow("edge", edge);                       //显示边缘

	//vector<Vec2f> lines;                        //点的向量
	//HoughLines(edge, lines, 1, CV_PI / 180, th);//霍夫变换
	//for (size_t i = 0; i < lines.size(); i++)   //画线
	//{
	//	float rho = lines[i][0];                           //取极径
	//	float theta = lines[i][1];                         //取极角
	//	Point pt1, pt2;
	//	double c = cos(theta);                             //极角的正余弦
	//	double s = sin(theta);
	//	double x0 = rho * c, y0 = rho * s;
	//	pt1.x = saturate_cast<int>(x0 + 1000 * (-s));      //计算线段的端点坐标
	//	pt1.y = saturate_cast<int>(y0 + 1000 * (c));
	//	pt2.x = saturate_cast<int>(x0 - 1000 * (-s));
	//	pt2.y = saturate_cast<int>(y0 - 1000 * (c));
	//	line(dst, pt1, pt2, Scalar(255, 255, 0), 1, LINE_AA);//画线
	//}

	Mat lineMat;                                  //点的Mat
	HoughLines(edge, lineMat, 1, CV_PI / 180, th);//霍夫变换
	int height = lineMat.rows;
	for (int i = 0; i < height; i++)              //画线
	{
		float rho = lineMat.at<Vec2f>(i,0)[0];             //取极径
		float theta = lineMat.at<Vec2f>(i,0)[1];           //取极角
		Point pt1, pt2;
		double c = cos(theta);                             //极角的正余弦
		double s = sin(theta);
		double x0 = rho * c, y0 = rho * s;
		pt1.x = saturate_cast<int>(x0 + 1000 * (-s));      //计算线段的端点坐标
		pt1.y = saturate_cast<int>(y0 + 1000 * (c));
		pt2.x = saturate_cast<int>(x0 - 1000 * (-s));
		pt2.y = saturate_cast<int>(y0 - 1000 * (c));
		line(dst, pt1, pt2, Scalar(255, 255, 0), 1, LINE_AA);//画线
	}
	imshow("dst", dst);                          //显示结果
}

int main()
{
	srcImg = imread("E:\\Test_Image\\18.jpg");   //读取原图
	if (srcImg.empty())
	{
		cout << "不能打开图像" << endl;
		destroyAllWindows();
		return -1;
	}
	cvtColor(srcImg,gray,COLOR_BGR2GRAY);        //转灰度

	namedWindow("edge");
	namedWindow("dst");
	createTrackbar("Canny阈值1", "edge", &th1, 300, threshold);//创建滑动条
	createTrackbar("霍夫累加阈值","dst", &th, 300, threshold);

	threshold(0, 0);                                          //调用回调函数
	waitKey(0);
	return 0;
}
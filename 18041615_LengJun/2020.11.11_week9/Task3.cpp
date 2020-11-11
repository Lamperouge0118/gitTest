/*******************************************************练习3********************************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

void threshold(int, void*);
Mat srcImg;               //原图
Mat edge;                 //边缘
Mat gray;                 //灰度图

int th = 20, th1 = 150; //霍夫累加阈值，Canny第一阈值
int LineLength = 0, LineGap = 30;

void threshold(int, void*)
{
	Mat dst = srcImg.clone();                   //把原图拷贝到输出
	Canny(gray, edge, th1, (double)th1 * 3, 3); //计算边缘
	imshow("edge", edge);                       //显示边缘

	vector<Vec4i> lines;                                                //点的向量
	HoughLinesP(edge, lines, 1, CV_PI / 180, th, LineLength, LineGap);//累计概率霍夫变换
	for (size_t i = 0; i < lines.size(); i++)   //画线
	{
		Point pt1, pt2;
		pt1.x = lines[i][0];                    //计算线段的端点坐标
		pt1.y = lines[i][1];
		pt2.x = lines[i][2];
		pt2.y = lines[i][3];
		line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);//画线
	}

	//Mat lineMat;                                                         //点的Mat
	//HoughLinesP(edge, lineMat, 1, CV_PI / 180, th, LineLength, LineGap);//累计概率霍夫变换
	//int height = lineMat.rows;
	//for (int i = 0; i < height; i++)            //画线
	//{
	//	Point pt1, pt2;
	//	pt1.x = lineMat.at<Vec4i>(i, 0)[0];       //计算线段的端点坐标
	//	pt1.y = lineMat.at<Vec4i>(i, 0)[1];
	//	pt2.x = lineMat.at<Vec4i>(i, 0)[2];
	//	pt2.y = lineMat.at<Vec4i>(i, 0)[3];
	//	line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);//画线
	//}
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
	cvtColor(srcImg, gray, COLOR_BGR2GRAY);        //转灰度

	namedWindow("edge");
	namedWindow("dst");
	createTrackbar("Canny阈值1", "edge", &th1, 300, threshold);//创建滑动条
	createTrackbar("霍夫累加阈值", "dst", &th, 300, threshold);
	createTrackbar("LineLength", "dst", &LineLength, 100, threshold);
	createTrackbar("LineGap", "dst", &LineGap, 100, threshold);

	threshold(0, 0);                                          //调用回调函数
	waitKey(0);
	return 0;
}
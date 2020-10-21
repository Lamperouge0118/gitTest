/***********************************************************************练习三************************************************************/
//使用大津法分割PCB板图，并对其进行连通域标记，
//利用图像形态学中所学的知识实现自动计算原点个数。


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImag, gryImag, binImag,bst;//原图，灰度图，二值图，反转二值图
	srcImag = imread("F:\\Test_Image\\11.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);				//RGB转灰度
	threshold(gryImag, binImag, 0, 255, THRESH_OTSU);		//二值化
	bitwise_not(binImag, bst);								//颜色反转，也可用binImag = 255 - binImag
	imshow("二值图", bst);

	Mat line_elemt = getStructuringElement(MORPH_RECT, Size(21, 21));  //定义结构尺寸
	Mat circ_elemt = getStructuringElement(MORPH_ELLIPSE, Size(9, 9)); //定义结构尺寸

	Mat ero_Imag, open_Imag;                               //腐蚀结果，开运算结果
	erode(bst, ero_Imag, line_elemt);                      //先腐蚀
	imshow("腐蚀结果", ero_Imag);

	dilate(ero_Imag, open_Imag, circ_elemt,Point(-1,-1),3);//再膨胀
	imshow("开运算结果", open_Imag);

	Mat labels, stats, centroids;                      //连通域标记
	int num = connectedComponentsWithStats(open_Imag,  //二值图像
										   labels,     //和原图一样大的标记图
										   stats,      //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
										   centroids   //nccomps×2的矩阵 表示每个连通区域的质心
										  );

	Rect rect;                                         //绘制矩形框
	int height = stats.rows;

	for (int i = 1; i < height; i++)
	{
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);

		rectangle(srcImag, rect, CV_RGB(255, 0, 0), 1, 8);
	}

	imshow("矩形框", srcImag);
	cout << "原点个数：" << num-1 << endl;

	waitKey(0);
	return 0;
}
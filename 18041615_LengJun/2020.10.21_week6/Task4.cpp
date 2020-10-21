/**************************************************************************练习四**************************************************************/
//对回形针图片进行自动计数。


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImag, gryImag, binImag, bst;//原图，灰度图，二值图，反转二值图
	srcImag = imread("F:\\Test_Image\\10.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);        //RGB转灰度
	threshold(gryImag, binImag, 0, 255, THRESH_OTSU);  //二值化
	bitwise_not(binImag, bst);                         //颜色反转，也可用binImag = 255 - binImag

	Rect dvide(10,0,bst.cols-10,bst.rows);             //定义裁剪区域
	bst = bst(dvide);                                  //裁剪图像，把左边缘裁剪掉
	imshow("二值图", bst);

	Mat line_elemt = getStructuringElement(MORPH_RECT, Size(3, 3)); //定义结构尺寸

	Mat ero_Imag;                                      //腐蚀结果
	erode(bst, ero_Imag, line_elemt);                  //腐蚀，把小斑点给腐蚀掉
	imshow("腐蚀结果", ero_Imag);

	Mat labels, stats, centroids;                      //连通域标记
	int num = connectedComponentsWithStats(ero_Imag,   //二值图像
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
	cout << "回形针个数：" << num - 1 << endl;
	cout << "状态矩阵：\n";
	cout << stats << endl;
	


	waitKey(0);
	return 0;
}
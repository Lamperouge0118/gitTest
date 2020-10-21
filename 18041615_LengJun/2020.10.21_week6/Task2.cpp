/**************************************************************************练习二**************************************************************/
//对硬币图先进行二值化，然后进行连通域标记，并绘制出每个连通域的外接四边形（bounding box）
//并使用 cout << ，将硬币的个数 输出至状态栏。

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImag, gryImag, binImag;				//原图，灰度图，二值图
	srcImag = imread("F:\\Test_Image\\9.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);			//RGB转灰度
	threshold(gryImag, binImag, 87, 255, THRESH_BINARY);//二值化

	Mat labels, stats, centroids;                       //连通域标记
	int num = connectedComponentsWithStats(binImag,		//二值图像
										   labels,		//和原图一样大的标记图
										   stats,	    //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
										   centroids	//nccomps×2的矩阵 表示每个连通区域的质心
										   );

	Rect rect;                            //绘制矩形框
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
	imshow("binImag", binImag);
	cout << "硬币的个数：" << num-1 << endl;
	cout << "状态矩阵：\n";
	cout << stats << endl;

	waitKey(0);
	return 0;
}

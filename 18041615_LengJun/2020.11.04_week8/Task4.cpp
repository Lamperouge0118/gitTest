/***********************************************************练习4 投影变换****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat srcImg, out, rot;                           //原图，结果图，变换矩阵
	srcImg = imread("E:\\Test_Image\\17.jpg");      //读取图片
	if (srcImg.empty())
	{
		cout << "不能打开图像" << endl;
		destroyAllWindows();
		return -1;
	}

	//设置原图和目标图上的四组点计算变换矩阵
	Point2f src_pt[4] = {
							Point2f(150,150),
							Point2f(150,300),
							Point2f(350,300),
							Point2f(350,150)
	};

	Point2f dst_pt[4] = {
							Point2f(200,150),
							Point2f(300,300),
							Point2f(340,270),
							Point2f(340,180)
	};

	rot = getPerspectiveTransform(src_pt, dst_pt);       //求变换矩阵
	warpPerspective(srcImg, out, rot, srcImg.size());

	imshow("原图", srcImg);
	imshow("结果", out);


	waitKey(0);
	return 0;

}
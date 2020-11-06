/***********************************************************练习3 仿射变换****************************************************************************************************/

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

	//设置原图和目标图上的三组点计算仿射矩阵
	Point2f src_pt[3] = {                            
							Point2f(200,200),
							Point2f(250,200),
							Point2f(200,100)
						};

	Point2f dst_pt[3] = {
							Point2f(300,100),
							Point2f(300,50),
							Point2f(200,100)
						};

	rot = getAffineTransform(src_pt,dst_pt);       //求仿射矩阵
	warpAffine(srcImg,out,rot,srcImg.size());

	imshow("原图", srcImg);
	imshow("结果", out);


	waitKey(0);
	return 0;

}
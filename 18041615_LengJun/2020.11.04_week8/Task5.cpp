/***********************************************************练习5 图像矫正****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat srcImg, gray;                  //原图，灰度图
	Mat edge, rot, dst;                //边缘，变换矩阵，结果

	Point2f src_pt[3];                 //原图的目标点


	srcImg = imread("E:\\Test_Image\\16.jpg"); //读取图片
	if (srcImg.empty())
	{
		cout << "不能打开图像" << endl;
		destroyAllWindows();
		return -1;
	}
	
	//结果图的目标点
	Point2f dst_pt[3] = {
							Point2f(srcImg.cols - 1,0),
							Point2f(0,srcImg.rows - 1),
							Point2f(srcImg.cols - 1,srcImg.rows - 1)
						};
	

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);    //转灰度
	Canny(gray, edge, 100, 200, 3);            //计算边缘

	int width = edge.cols;                     //图片的长和宽
	int height = edge.rows;

	for (int i = 0; i < height; i++)  //取右上角目标点的坐标
	{
		if (edge.at<uchar>(i, width - 1) != 0)
		{
			src_pt[0] = Point2f(width - 1, i);
			break;
		}

	}

	for (int j = height - 1; j > 0; j--)//左下角目标点的坐标
	{
		if (edge.at<uchar>(j, 0) != 0)
		{
			src_pt[1] = Point2f(0, j);
			break;
		}
	}

	for (int k = width - 1; k > 0; k--)//右下角目标点的坐标
	{
		if(edge.at<uchar>(height - 1, k) != 0)
		{
			src_pt[2] = Point2f(k, height - 1);
			break;
		}
	}
		
	  
	rot = getAffineTransform(src_pt, dst_pt);       //求变换矩阵
	warpAffine(srcImg, dst, rot, srcImg.size());    //求仿射结果

	imshow("原图", srcImg);                          //显示
	imshow("结果", dst);

	waitKey(0);
	return 0;
}
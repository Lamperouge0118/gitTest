/************************************************************************************练习三****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat hsvMat, detectMat;           //hsv，二值图
	vector<vector<Point>> contours;  //轮廓向量

    //定义HSV各自的范围
	//红色
	//[0,180]
	double i_minH = 0;
	double i_maxH = 180;
	//[0,255]
	double i_minS = 100;
	double i_maxS = 255;
	//[0,255]
	double i_minV = 46;
	double i_maxV = 255;

	Mat srcImg = imread("E:\\Test_Image\\25.jpg");         //读取原图
	if (srcImg.empty())
	{
		cout << "不能打开该图像" << endl;
		destroyAllWindows();
		return -1;

	}

	namedWindow("src", 0);
	namedWindow("out", 0);

	imshow("src", srcImg);                                  //显示原图

	cvtColor(srcImg, hsvMat, COLOR_BGR2HSV);                //BGR转HSSV
	inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//二值化，阈值内像素值为255，否则为0

	findContours(detectMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //寻找轮廓
	Mat drawing = srcImg.clone();                                                 //定义画板
	for (int i = 0; i < contours.size(); i++)                                     //画出轮廓
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //寻找轮廓的带旋转属性最小外接矩形
		Point2f vertex[4];                                                        //矩形顶角向量
		rbox.points(vertex);
		float area = rbox.size.area();                                            //外接矩形的面积
		if (area > 200 * 200)
		{
			drawContours(drawing, contours, i, Scalar(0, 255, 0), 3);             //画出轮廓
			for (int j = 0; j < 4; j++)
			{
				line(drawing, vertex[j], vertex[(j + 1) % 4], Scalar(0, 0, 255), 3, LINE_AA);          //画出外接矩形
			}
		}
	}
	imshow("out", drawing);                                                      //显示结果

	waitKey(0);
	return 0;
}
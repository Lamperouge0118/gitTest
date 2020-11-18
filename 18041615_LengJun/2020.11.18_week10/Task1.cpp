/************************************************************************************练习一****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat binImag, bst;   //二值图，反色二值图
	Mat gray;           //灰度图
	vector<vector<Point>> contours;                        //轮廓向量


	Mat srcImg = imread("E:\\Test_Image\\23.png");         //读取原图
	if (srcImg.empty())
	{
		cout << "不能打开该图像" << endl;
		destroyAllWindows();
		return -1;

	}
	imshow("src",srcImg);                                   //显示原图

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);                 //转灰度
	threshold(gray, binImag, 0, 255, THRESH_OTSU);		    //二值化
	bitwise_not(binImag, bst);								//颜色反转，也可用binImag = 255 - binImag

	Mat circ_elemt = getStructuringElement(MORPH_ELLIPSE, Size(3,3)); //定义结构尺寸
	Mat open_Imag;                                                    //开运算结果
	morphologyEx(bst, open_Imag, MORPH_OPEN, circ_elemt);             //开运算

	findContours(open_Imag, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //寻找轮廓
	Mat drawing = srcImg.clone();                                                 //定义画板
	for (int i = 0; i < contours.size(); i++)                                     //画出轮廓
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //寻找轮廓的带旋转属性最小外接矩形
		float area = rbox.size.area();                                            //外接矩形的面积
		if (area>43*43 && area<90*90)                     
		{
			drawContours(drawing, contours, i, Scalar(255,255,0), -1);            //画出轮廓
		}
	}
	imshow("out", drawing);                                                       //显示结果

	waitKey(0);
	return 0;
}
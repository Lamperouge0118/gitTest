/************************************************************************************练习二****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat binImag;   //二值图
	Mat gray;      //灰度图
	vector<vector<Point>> contours;                        //轮廓向量


	Mat srcImg = imread("E:\\Test_Image\\24.jpg");         //读取原图
	if (srcImg.empty())
	{
		cout << "不能打开该图像" << endl;
		destroyAllWindows();
		return -1;

	}
	imshow("src", srcImg);                                  //显示原图

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);                 //转灰度
	threshold(gray, binImag, 0, 255, THRESH_OTSU);		    //二值化

	Mat rect_elemt = getStructuringElement(MORPH_RECT, Size(5, 5));   //定义结构尺寸
	Mat open_Imag;                                                    //开运算结果
	morphologyEx(binImag, open_Imag, MORPH_OPEN, rect_elemt);         //开运算

	findContours(open_Imag, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //寻找轮廓
	Mat drawing = srcImg.clone();                                                 //定义画板
	for (int i = 0; i < contours.size(); i++)                                     //画出轮廓
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //寻找轮廓的带旋转属性最小外接矩形
		Point2f vertex[4];                                                        //矩形顶角向量
		rbox.points(vertex);
		float area = rbox.size.area();                                            //外接矩形的面积
		if (area > 50*50 )
		{
			drawContours(drawing, contours, i, Scalar(0, 0, 255), 1);             //画出轮廓
			for (int j = 0; j < 4; j++)
			{
				line(drawing, vertex[j], vertex[(j + 1) % 4], Scalar(255, 255, 0), 1, LINE_AA);          //画出外接矩形
			}
		}
	}
	imshow("out", drawing);                                                      //显示结果

	waitKey(0);
	return 0;
}
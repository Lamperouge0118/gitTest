/**************************************************************************练习一**************************************************************/
//对硬币图先进行二值化，然后分别进行腐蚀、膨胀、开运算和闭运算。


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat binImag,display;                                    //二值图，效果图
int MORPH_Num = 0;                                      //0：腐蚀；1：膨胀；2：开运算；3：闭运算
int ElementSize = 3,StructElement = 3;                  //结构单元尺寸

void ErodeDilate(int, void*);                           //回调函数，腐蚀，膨胀
void Change(int, void*);                                //回调函数，基于morphologyEx



int main()
{
	Mat srcImag, gryImag;                               //原图，灰度图
	srcImag = imread("F:\\Test_Image\\9.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);         //RGB转灰度
	threshold(gryImag, binImag, 87, 255, THRESH_BINARY);//二值化
	imshow("二值图", binImag);                           //显示二值图

	namedWindow("【腐蚀/膨胀】");
	namedWindow("效果图");

	//创建滑动条
	createTrackbar("腐蚀/膨胀", "【腐蚀/膨胀】", &MORPH_Num, 1, ErodeDilate);       //腐蚀/膨胀切换
	createTrackbar("结构尺寸", "【腐蚀/膨胀】", &ElementSize, 21, ErodeDilate);   //结构单元尺寸调节

	createTrackbar("腐蚀/膨胀/开/闭", "效果图", &MORPH_Num, 3, Change);             //腐蚀/膨胀/开/闭切换
	createTrackbar("结构尺寸", "效果图", &StructElement,21, Change);               //结构单元尺寸调节

	waitKey(0);
	return 0;
}


void ErodeDilate(int, void*)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * ElementSize + 1, 2 * ElementSize + 1)); //定义结构尺寸
	if (!MORPH_Num)
	{
		erode(binImag, display, element);//腐蚀
	}
	else
	{
		dilate(binImag, display, element);//膨胀/
	}

	imshow("【腐蚀/膨胀】", display);
}


void Change(int, void*)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * StructElement + 1, 2 * StructElement + 1)); //定义结构尺寸
	morphologyEx(binImag, display, MORPH_Num, element);
	imshow("效果图", display);
}

/**************************************************************************��ϰһ**************************************************************/
//��Ӳ��ͼ�Ƚ��ж�ֵ����Ȼ��ֱ���и�ʴ�����͡�������ͱ����㡣


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat binImag,display;                                    //��ֵͼ��Ч��ͼ
int MORPH_Num = 0;                                      //0����ʴ��1�����ͣ�2�������㣻3��������
int ElementSize = 3,StructElement = 3;                  //�ṹ��Ԫ�ߴ�

void ErodeDilate(int, void*);                           //�ص���������ʴ������
void Change(int, void*);                                //�ص�����������morphologyEx



int main()
{
	Mat srcImag, gryImag;                               //ԭͼ���Ҷ�ͼ
	srcImag = imread("F:\\Test_Image\\9.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);         //RGBת�Ҷ�
	threshold(gryImag, binImag, 87, 255, THRESH_BINARY);//��ֵ��
	imshow("��ֵͼ", binImag);                           //��ʾ��ֵͼ

	namedWindow("����ʴ/���͡�");
	namedWindow("Ч��ͼ");

	//����������
	createTrackbar("��ʴ/����", "����ʴ/���͡�", &MORPH_Num, 1, ErodeDilate);       //��ʴ/�����л�
	createTrackbar("�ṹ�ߴ�", "����ʴ/���͡�", &ElementSize, 21, ErodeDilate);   //�ṹ��Ԫ�ߴ����

	createTrackbar("��ʴ/����/��/��", "Ч��ͼ", &MORPH_Num, 3, Change);             //��ʴ/����/��/���л�
	createTrackbar("�ṹ�ߴ�", "Ч��ͼ", &StructElement,21, Change);               //�ṹ��Ԫ�ߴ����

	waitKey(0);
	return 0;
}


void ErodeDilate(int, void*)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * ElementSize + 1, 2 * ElementSize + 1)); //����ṹ�ߴ�
	if (!MORPH_Num)
	{
		erode(binImag, display, element);//��ʴ
	}
	else
	{
		dilate(binImag, display, element);//����/
	}

	imshow("����ʴ/���͡�", display);
}


void Change(int, void*)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * StructElement + 1, 2 * StructElement + 1)); //����ṹ�ߴ�
	morphologyEx(binImag, display, MORPH_Num, element);
	imshow("Ч��ͼ", display);
}

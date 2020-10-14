#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void threshold_adapt(int , void* data);//�ص���������

string window_adapt = "adaptive";      //������
int lowC = 0, maxC = 50;               //����C��Χ
int lowSize = 25, maxSize = 200;       //blocksize��Χ

void threshold_adapt(int , void* data) //�ص��������壬��������Ӧ��ֵ��
{
	Mat src = *(Mat*)(data);           //ȡ�Ҷ�ͼ����
	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY, lowSize!=0 ? lowSize*2+1 :3, lowC);   //��ֵ��

	imshow(window_adapt, dst);         //��ʾ��ֵͼ
}


int main()
{
	Mat srcMat, gryMat,dst;
	srcMat = imread("F:\\Test_Image\\2.jpg");
	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY); //RGBת�Ҷ�

	threshold(gryMat, dst, 120, 255, THRESH_OTSU);//���
	imshow("OSTU", dst);

	namedWindow(window_adapt);                      //��������
	createTrackbar("blocksize", window_adapt, &lowSize, maxSize, threshold_adapt, &gryMat); 
	createTrackbar("const_C", window_adapt, &lowC, maxC, threshold_adapt, &gryMat);         //����blocksize�ͳ���C�Ļ�����

	waitKey(0);
	return 0;
}


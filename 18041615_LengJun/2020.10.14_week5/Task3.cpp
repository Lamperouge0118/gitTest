#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string window_name = "binaryMat";      //������

void threshod_Mat(int th, void* data); //�����ص�����

void threshod_Mat(int th, void* data)  //�ص���������
{
	Mat src = *(Mat*)(data);           //ȡ�Ҷ�ͼ����
	Mat dst;
	threshold(src, dst, th, 255, 0);   //��ֵ��
	 
	imshow(window_name, dst);          //��ʾ��ֵͼ
}

int main()
{
	Mat srcMat,gryMat;
	int lowTh = 30;
	int maxTh = 255;//�趨��ֵ��Χ��Ҳ���������ķ�Χ

	srcMat = imread("F:\\Test_Image\\2.jpg");     //���ͼ���Ƿ�ɹ�����
	if (!srcMat.data)
	{
		cout << "ͼ������ʧ��" << endl;
		return 0;
	}

	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);    //BGRת�Ҷ�ͼ
	imshow(window_name, gryMat);                 //��ʾ�Ҷ�ͼ
	createTrackbar("threshold", window_name, &lowTh, maxTh, threshod_Mat, &gryMat); //������������������"binaryMat"����

	waitKey(0);
	return 0;
}
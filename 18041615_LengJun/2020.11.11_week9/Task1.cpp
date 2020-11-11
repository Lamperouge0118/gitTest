/***********************************************************��ϰ1 ��ת������****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

#define pi 3.1415926

using namespace cv;
using namespace std;

Mat srcImg, out, rot;         //ԭͼ�����ͼ���任����
int scale = 5;                //���ű���
int angle = 10;               //��ת�Ƕ�
Point2f center;               //��ת����

void affine_matrix(int, void*)
{
	rot = getRotationMatrix2D(center, angle, 1);                        //ȡ�ñ任����
	Rect bbox = RotatedRect(center, srcImg.size(),angle).boundingRect();//��ȡ����ı���
	//�����������
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	warpAffine(srcImg, out, rot, bbox.size());       //���з���任

	float s = scale ? scale/5.0 : 1;                 //ת�����ű���
	Size ResSize = Size(out.cols * s, out.rows * s); //����ߴ磬�����ź�ĳߴ�
	resize(out, out, ResSize, INTER_LINEAR);         //����
	imshow("���", out);                             //��ʾ���
}

int main()
{


	srcImg = imread("E:\\Test_Image\\17.jpg");        //��ȡͼƬ
	if (srcImg.empty())
	{
		cout << "���ܴ�ͼ��" << endl;
		destroyAllWindows();
		return -1;
	}

	center = Point2f(srcImg.cols / 2, srcImg.rows / 2);         //����ת����
	imshow("ԭͼ", srcImg);                                     //��ʾԭͼ

	createTrackbar("��ת�Ƕ�", "ԭͼ", &angle, 360, affine_matrix);      //����������
	createTrackbar("���ű���", "ԭͼ", &scale, 10, affine_matrix);
	affine_matrix(0, 0);                                                //���ûص�����

	waitKey(0);
	return 0;

}
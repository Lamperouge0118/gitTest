#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcM = imread("F:/Test_Image/47621790_p0.jpg");//��ȡͼƬ
	Mat deepMat,shallowMat;

	srcM.copyTo(deepMat);//���
	shallowMat = srcM;   //ǳ����

	cout << "ԭʼ��deepMat��shallowMat��" << endl;//��ʾԭʼ��deepMat��shallowMatͼ��
	imshow("original deepMat", deepMat);
	imshow("original shallowMat", shallowMat);
	waitKey(0);


	int height = srcM.rows;//��ȡͼƬ����
	int width = srcM.cols; //��ȡͼƬ���
	uchar average;
	uchar threshold=100;   //�趨��ֵ
						   
/********************************************��ͨ����������ֵ***********************************************************/
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			average = (srcM.at<Vec3b>(i, j)[0] + srcM.at<Vec3b>(i, j)[1] + srcM.at<Vec3b>(i, j)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			srcM.at<Vec3b>(i, j)[0] = average;
			srcM.at<Vec3b>(i, j)[1] = average;
			srcM.at<Vec3b>(i, j)[2] = average;
		}
	}

	cout << "�仯���deepMat��shallowMat��" << endl;//��ʾ�仯���deepMat��shallowMatͼ��
	imshow("changed deepMat", deepMat);
	imshow("changed shallowMat", shallowMat);
	waitKey(0);
	return 0;

}


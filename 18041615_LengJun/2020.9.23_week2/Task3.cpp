#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("F:/Test_Image/47621790_p0.jpg");//��ȡͼƬ

	cout << "ԭͼ��" << endl;   //��ʾԭͼ
	imshow("origin", srcImage);
	waitKey(0);

	int height = srcImage.rows;  //��ȡͼƬ����
	int width = srcImage.cols;   //��ȡͼƬ���
	uchar average;
	uchar threshold = 100;       //�趨��ֵ

/********************************************��ͨ����������ֵ***********************************************************/
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			average = (srcImage.at<Vec3b>(i,j)[0] + srcImage.at<Vec3b>(i,j)[1] + srcImage.at<Vec3b>(i,j)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			srcImage.at<Vec3b>(i,j)[0] = average;
			srcImage.at<Vec3b>(i,j)[1] = average;
			srcImage.at<Vec3b>(i,j)[2] = average;
		}
	}

	cout << "��ֵͼ��" << endl;//��ʾ��ֵͼ��
	imshow("Binary", srcImage);
	waitKey(0);
	return 0;

}


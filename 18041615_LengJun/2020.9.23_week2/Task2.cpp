#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("F:/Test_Image/47621790_p0.jpg",0);//��ȡͼƬ����ֱ��תΪ�Ҷ�ͼ
	cout << "�Ҷ�ͼ" << endl; //��ʾͼƬ
	imshow("Gray", srcImage);
	waitKey(0);
	return 0;

}


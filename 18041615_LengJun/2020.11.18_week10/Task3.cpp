/************************************************************************************��ϰ��****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat hsvMat, detectMat;           //hsv����ֵͼ
	vector<vector<Point>> contours;  //��������

    //����HSV���Եķ�Χ
	//��ɫ
	//[0,180]
	double i_minH = 0;
	double i_maxH = 180;
	//[0,255]
	double i_minS = 100;
	double i_maxS = 255;
	//[0,255]
	double i_minV = 46;
	double i_maxV = 255;

	Mat srcImg = imread("E:\\Test_Image\\25.jpg");         //��ȡԭͼ
	if (srcImg.empty())
	{
		cout << "���ܴ򿪸�ͼ��" << endl;
		destroyAllWindows();
		return -1;

	}

	namedWindow("src", 0);
	namedWindow("out", 0);

	imshow("src", srcImg);                                  //��ʾԭͼ

	cvtColor(srcImg, hsvMat, COLOR_BGR2HSV);                //BGRתHSSV
	inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//��ֵ������ֵ������ֵΪ255������Ϊ0

	findContours(detectMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //Ѱ������
	Mat drawing = srcImg.clone();                                                 //���廭��
	for (int i = 0; i < contours.size(); i++)                                     //��������
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //Ѱ�������Ĵ���ת������С��Ӿ���
		Point2f vertex[4];                                                        //���ζ�������
		rbox.points(vertex);
		float area = rbox.size.area();                                            //��Ӿ��ε����
		if (area > 200 * 200)
		{
			drawContours(drawing, contours, i, Scalar(0, 255, 0), 3);             //��������
			for (int j = 0; j < 4; j++)
			{
				line(drawing, vertex[j], vertex[(j + 1) % 4], Scalar(0, 0, 255), 3, LINE_AA);          //������Ӿ���
			}
		}
	}
	imshow("out", drawing);                                                      //��ʾ���

	waitKey(0);
	return 0;
}
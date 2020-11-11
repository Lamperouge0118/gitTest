/*******************************************************��ϰ3********************************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

void threshold(int, void*);
Mat srcImg;               //ԭͼ
Mat edge;                 //��Ե
Mat gray;                 //�Ҷ�ͼ

int th = 20, th1 = 150; //�����ۼ���ֵ��Canny��һ��ֵ
int LineLength = 0, LineGap = 30;

void threshold(int, void*)
{
	Mat dst = srcImg.clone();                   //��ԭͼ���������
	Canny(gray, edge, th1, (double)th1 * 3, 3); //�����Ե
	imshow("edge", edge);                       //��ʾ��Ե

	vector<Vec4i> lines;                                                //�������
	HoughLinesP(edge, lines, 1, CV_PI / 180, th, LineLength, LineGap);//�ۼƸ��ʻ���任
	for (size_t i = 0; i < lines.size(); i++)   //����
	{
		Point pt1, pt2;
		pt1.x = lines[i][0];                    //�����߶εĶ˵�����
		pt1.y = lines[i][1];
		pt2.x = lines[i][2];
		pt2.y = lines[i][3];
		line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);//����
	}

	//Mat lineMat;                                                         //���Mat
	//HoughLinesP(edge, lineMat, 1, CV_PI / 180, th, LineLength, LineGap);//�ۼƸ��ʻ���任
	//int height = lineMat.rows;
	//for (int i = 0; i < height; i++)            //����
	//{
	//	Point pt1, pt2;
	//	pt1.x = lineMat.at<Vec4i>(i, 0)[0];       //�����߶εĶ˵�����
	//	pt1.y = lineMat.at<Vec4i>(i, 0)[1];
	//	pt2.x = lineMat.at<Vec4i>(i, 0)[2];
	//	pt2.y = lineMat.at<Vec4i>(i, 0)[3];
	//	line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);//����
	//}
	imshow("dst", dst);                          //��ʾ���
}

int main()
{
	srcImg = imread("E:\\Test_Image\\18.jpg");   //��ȡԭͼ
	if (srcImg.empty())
	{
		cout << "���ܴ�ͼ��" << endl;
		destroyAllWindows();
		return -1;
	}
	cvtColor(srcImg, gray, COLOR_BGR2GRAY);        //ת�Ҷ�

	namedWindow("edge");
	namedWindow("dst");
	createTrackbar("Canny��ֵ1", "edge", &th1, 300, threshold);//����������
	createTrackbar("�����ۼ���ֵ", "dst", &th, 300, threshold);
	createTrackbar("LineLength", "dst", &LineLength, 100, threshold);
	createTrackbar("LineGap", "dst", &LineGap, 100, threshold);

	threshold(0, 0);                                          //���ûص�����
	waitKey(0);
	return 0;
}
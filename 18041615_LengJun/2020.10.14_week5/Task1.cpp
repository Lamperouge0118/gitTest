#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	double scale = 0.5;//���ű���


	//����HSV���Եķ�Χ
	//[0,180]
	//��ɫ
	double i_minH = 0;
	double i_maxH = 20;
	//[0,255]
	double i_minS = 43;
	double i_maxS = 255;
	//[0,255]
	double i_minV = 55;
	double i_maxV = 255;

	while (true)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;
		Size ResImgSize = Size(frame.cols * scale, frame.rows * scale);//����ߴ磬������֡���ź�ĳߴ�
		Mat rFrame = Mat(ResImgSize, frame.type());//�Գߴ�ResImgSize��frame���������ʹ���Mat
		resize(frame, rFrame, ResImgSize, INTER_LINEAR);//��frame��ResImgSize�ߴ����ţ��������rFrame

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);//��rFrameתΪHSV��ʽ���������hsvMat

		rFrame.copyTo(detectMat);//����ԭͼ

		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//��ֵ������ֵ������ֵΪ255������Ϊ0

		imshow("while: in the range", detectMat);
		imshow("frame", rFrame);

		waitKey(30);
	}
}
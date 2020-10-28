/*******************************************************************��ϰ����ĥƤ����**********************************************************************************/
//ʹ���Ѿ�ѧ�����㷨��ʵ��һ���򵥵�ĥƤ���򣬼�����Ƥ���Ĳ����Եù⻬����mask�������HSV��Χ���ƣ�

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void Ksize(int, void*);			   //�˲�Ksize�ص�����
void FrameSize(int, void*);        //֡�ߴ�ص�����

Mat frame, rFrame;                 //ԭ֡,�ߴ�ı���ԭ֡
Mat detectMat, edge;               //��ȡƤ���Ķ�ֵͼ��detectMat�˲���õ�����Ĥedge
int KsizeValue = 0;                //Ksize��������ʼλ��
int scale = 0;                     //֡�ߴ绬������ʼλ��


void Ksize(int, void*)            //�˲�Ksize�ص�����
{
	//˫���˲�
	//bilateralFilter(detectMat, edge,KsizeValue, KsizeValue*2, KsizeValue/2);

	//��ֵ�˲�
	medianBlur(detectMat, edge, KsizeValue > 0 ? KsizeValue * 2 + 1 : 3);

	//��˹�˲�
	//int length = KsizeValue * 2 + 1;
	//GaussianBlur(detectMat, edge, Size(length, length), 0, 0);
	//��ֵ�˲�
	//blur(detectMat, edge, Size(length, length));
	imshow("edge", edge);
}

void FrameSize(int, void*)        //֡�ߴ�ص�����
{
	double s;
	if (!scale)                   //�ų�0ֵ
	{
		s = 1.0;
	}
	else
	{
		s = (scale >= 1) && (scale <= 5) ? scale / 5.0 : (scale - 3.0) * 0.5;//��С���ʲ���Ϊ0.2�������ʲ���Ϊ0.5
	}

	Size ResSize = Size(frame.cols * s, frame.rows * s);//����ߴ磬��ƽ��֡���ź�ĳߴ�
	resize(frame, rFrame, ResSize, INTER_LINEAR); //��frame��ResSize�ߴ����ţ��������rFrame
}

int main()
{
	Mat hsvMat, dst;       //HSV���ͣ�ĥƤ���
	
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

	VideoCapture cap(0);                        //������ͷ

	while (true)
	{
		cap >> frame;                           //��ȡ֡

		if (frame.empty())
		{
			cout << "���ܴ���Ƶ�ļ��ж�ȡ֡!" << endl;
			destroyAllWindows();
			return -1;
		}

		imshow("ԭ֡", frame);

		//����������������֡�ߴ�
		createTrackbar("֡��С", "ԭ֡", &scale, 10, FrameSize);
		FrameSize(scale, 0);                             //���ûص�����

		//תHSV������ȡƤ��
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);         //��rFrameתΪHSV��ʽ���������hsvMat
		rFrame.copyTo(detectMat);                        //����rFrame
		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//��ֵ������ֵ������ֵΪ255������Ϊ0��ȡƤ������
		imshow("mask", detectMat);

		//�������������˲�
		createTrackbar("�ں˳ߴ�", "ԭ֡", &KsizeValue, 50, Ksize); //����������
		Ksize(KsizeValue, 0);                                      //���ûص�����

		dst = Scalar::all(0);
		rFrame.copyTo(dst, edge);
		imshow("ĥƤ", dst);

		//�ȴ�������Ӧ������ESC���˳�
		if (waitKey(30) == 27)
		{
			destroyAllWindows();
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
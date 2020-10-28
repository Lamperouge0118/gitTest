/*******************************************************************��ϰһ����ֵ�˲�**********************************************************************************/
//��ȡ����ͷͼ�񣬲�������ͷͼ�������ֵ�˲�
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void MedinBlur_Ksize(int, void*); //��ֵ�˲�Ksize�ص�����
void FrameSize(int, void*);       //֡�ߴ�ص�����
Mat frame, dst, rFrame;           //ԭ֡��ƽ��֡���ߴ�ı���ԭ֡
int KsizeValue = 0;               //Ksize��������ʼλ��
int scale = 0;                    //֡�ߴ绬������ʼλ��


void MedinBlur_Ksize(int, void*)  //��ֵ�˲�Ksize�ص�����
{
	medianBlur(rFrame, dst, KsizeValue>0? KsizeValue*2+1: 3);
	imshow("ƽ��֡", dst);
}

void FrameSize(int , void*)       //֡�ߴ�ص�����
{
	double s;
	if (!scale)                   //�ų�0ֵ
	{
		s = 1.0;
	}
	else
	{
		s = (scale >= 1) && (scale <= 5) ? scale/5.0 : (scale-3.0)*0.5;//��С���ʲ���Ϊ0.2�������ʲ���Ϊ0.5
	}

	Size ResSize = Size(frame.cols*s, frame.rows*s);//����ߴ磬��ƽ��֡���ź�ĳߴ�
	resize(frame, rFrame, ResSize, INTER_LINEAR); //��frame��ResSize�ߴ����ţ��������rFrame	 
}

int main()
{ 
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

		createTrackbar("�׾��ߴ�", "ԭ֡", &KsizeValue, 25, MedinBlur_Ksize); //����������
		createTrackbar("ƽ��֡��С", "ԭ֡", &scale, 10, FrameSize);   
		FrameSize(scale, 0);                                                 //���ûص�����
		MedinBlur_Ksize(KsizeValue, 0);                                     
		
	
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
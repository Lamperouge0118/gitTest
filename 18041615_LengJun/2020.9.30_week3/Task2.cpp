#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;	

int main()
{
	VideoCapture cap;    

	cap.open(0);           //�򿪱�����һ������ͷ

	if (!cap.isOpened())   //�����Ƶ�Ƿ�ɹ�����
	{
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return -1;
	}

	double FPS = cap.get(CAP_PROP_FPS);  //��ȡ��Ƶ��FPS
	cout << "FPS" << FPS << endl;

	while (true)
	{
		Mat frame;
		bool read_Sucess = cap.read(frame);  //��ȡ��Ƶ��ǰ֡

		if (!read_Sucess)                    //����Ƿ�ɹ���ȡ��ǰ֡
		{
			cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << endl;  
			break;
		}
		else
		{
			imshow("frame", frame);         //��ʾ��ǰ֡
		}
		waitKey(30);
	}

	return 0;
}
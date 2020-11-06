/*****************************************************��ϰ1 canny����***************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void threshold(int, void*);        //��ֵ�ص�����
void Ksize(int, void*);            //�ṹ���ӳߴ�ص�����

Mat grd_x, grd_y;                  //x,y�ı�Ե
Mat gray;                          //�Ҷ�ͼ
Mat edge1, edge2;                  //canny���


int KsizeValue = 3;                //Ksize��������ʼλ��
int th1 = 20;

void threshold(int, void*)         //��ֵ�ص�����
{
	Canny(grd_x, grd_y, edge1, th1, th1*3);
	Canny(gray, edge2, th1, th1*3, 3);
	imshow("edge1", edge1);        //��ʾcanny����ı�Ե
	imshow("edge2", edge2);
}

void Ksize(int, void*)            //�˲�Ksize�ص�����
{
	//˫���˲�
	//bilateralFilter(gray, gray,KsizeValue, KsizeValue*2, KsizeValue/2);

	//��ֵ�˲�
	//medianBlur(gray, gray, KsizeValue > 0 ? KsizeValue * 2 + 1 : 3);

	//��˹�˲�
	int length = KsizeValue * 2 + 1;
	GaussianBlur(gray, gray, Size(length, length), 0, 0);
	//��ֵ�˲�
	//blur(gray, gray, Size(length, length));
}

int main()
{
	Mat frame;
	Mat dst1, dst2;          //��Ĥ���


	VideoCapture cap(0);     //������ͷ

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

		createTrackbar("��һ��ֵ", "ԭ֡", &th1, 100, threshold);   //����������
		createTrackbar("�ں˳ߴ�", "ԭ֡", & KsizeValue, 50, Ksize);

		cvtColor(frame, gray, COLOR_BGR2GRAY);                     //ת�Ҷ�
		Ksize(KsizeValue, 0);                                      //�˲�
	
		Sobel(frame,grd_x, CV_16S, 1, 0, 3);                       //����X�����ݶ�
		Sobel(frame,grd_y, CV_16S, 0, 1, 3);                       //����Y�����ݶ�

		threshold(th1,0);                                          //canny�����Ե

		dst1 = Scalar::all(0);
		dst2 = Scalar::all(0);
		frame.copyTo(dst1, edge1);                                 //��Ĥ���
		frame.copyTo(dst2, edge2);
		imshow("dst1", dst1);                                      //��ʾ��Ĥ���
		imshow("dst2", dst2);

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
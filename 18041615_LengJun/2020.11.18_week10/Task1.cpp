/************************************************************************************��ϰһ****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat binImag, bst;   //��ֵͼ����ɫ��ֵͼ
	Mat gray;           //�Ҷ�ͼ
	vector<vector<Point>> contours;                        //��������


	Mat srcImg = imread("E:\\Test_Image\\23.png");         //��ȡԭͼ
	if (srcImg.empty())
	{
		cout << "���ܴ򿪸�ͼ��" << endl;
		destroyAllWindows();
		return -1;

	}
	imshow("src",srcImg);                                   //��ʾԭͼ

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);                 //ת�Ҷ�
	threshold(gray, binImag, 0, 255, THRESH_OTSU);		    //��ֵ��
	bitwise_not(binImag, bst);								//��ɫ��ת��Ҳ����binImag = 255 - binImag

	Mat circ_elemt = getStructuringElement(MORPH_ELLIPSE, Size(3,3)); //����ṹ�ߴ�
	Mat open_Imag;                                                    //��������
	morphologyEx(bst, open_Imag, MORPH_OPEN, circ_elemt);             //������

	findContours(open_Imag, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //Ѱ������
	Mat drawing = srcImg.clone();                                                 //���廭��
	for (int i = 0; i < contours.size(); i++)                                     //��������
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //Ѱ�������Ĵ���ת������С��Ӿ���
		float area = rbox.size.area();                                            //��Ӿ��ε����
		if (area>43*43 && area<90*90)                     
		{
			drawContours(drawing, contours, i, Scalar(255,255,0), -1);            //��������
		}
	}
	imshow("out", drawing);                                                       //��ʾ���

	waitKey(0);
	return 0;
}
/************************************************************************************��ϰ��****************************************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat binImag;   //��ֵͼ
	Mat gray;      //�Ҷ�ͼ
	vector<vector<Point>> contours;                        //��������


	Mat srcImg = imread("E:\\Test_Image\\24.jpg");         //��ȡԭͼ
	if (srcImg.empty())
	{
		cout << "���ܴ򿪸�ͼ��" << endl;
		destroyAllWindows();
		return -1;

	}
	imshow("src", srcImg);                                  //��ʾԭͼ

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);                 //ת�Ҷ�
	threshold(gray, binImag, 0, 255, THRESH_OTSU);		    //��ֵ��

	Mat rect_elemt = getStructuringElement(MORPH_RECT, Size(5, 5));   //����ṹ�ߴ�
	Mat open_Imag;                                                    //��������
	morphologyEx(binImag, open_Imag, MORPH_OPEN, rect_elemt);         //������

	findContours(open_Imag, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);          //Ѱ������
	Mat drawing = srcImg.clone();                                                 //���廭��
	for (int i = 0; i < contours.size(); i++)                                     //��������
	{
		RotatedRect rbox = minAreaRect(contours[i]);                              //Ѱ�������Ĵ���ת������С��Ӿ���
		Point2f vertex[4];                                                        //���ζ�������
		rbox.points(vertex);
		float area = rbox.size.area();                                            //��Ӿ��ε����
		if (area > 50*50 )
		{
			drawContours(drawing, contours, i, Scalar(0, 0, 255), 1);             //��������
			for (int j = 0; j < 4; j++)
			{
				line(drawing, vertex[j], vertex[(j + 1) % 4], Scalar(255, 255, 0), 1, LINE_AA);          //������Ӿ���
			}
		}
	}
	imshow("out", drawing);                                                      //��ʾ���

	waitKey(0);
	return 0;
}
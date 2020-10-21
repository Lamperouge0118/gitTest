/**************************************************************************��ϰ��**************************************************************/
//�Ի�����ͼƬ�����Զ�������


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImag, gryImag, binImag, bst;//ԭͼ���Ҷ�ͼ����ֵͼ����ת��ֵͼ
	srcImag = imread("F:\\Test_Image\\10.jpg");

	cvtColor(srcImag, gryImag, COLOR_BGR2GRAY);        //RGBת�Ҷ�
	threshold(gryImag, binImag, 0, 255, THRESH_OTSU);  //��ֵ��
	bitwise_not(binImag, bst);                         //��ɫ��ת��Ҳ����binImag = 255 - binImag

	Rect dvide(10,0,bst.cols-10,bst.rows);             //����ü�����
	bst = bst(dvide);                                  //�ü�ͼ�񣬰����Ե�ü���
	imshow("��ֵͼ", bst);

	Mat line_elemt = getStructuringElement(MORPH_RECT, Size(3, 3)); //����ṹ�ߴ�

	Mat ero_Imag;                                      //��ʴ���
	erode(bst, ero_Imag, line_elemt);                  //��ʴ����С�ߵ����ʴ��
	imshow("��ʴ���", ero_Imag);

	Mat labels, stats, centroids;                      //��ͨ����
	int num = connectedComponentsWithStats(ero_Imag,   //��ֵͼ��
										   labels,     //��ԭͼһ����ı��ͼ
										   stats,      //nccomps��5�ľ��� ��ʾÿ����ͨ�������Ӿ��κ������pixel��
										   centroids   //nccomps��2�ľ��� ��ʾÿ����ͨ���������
										  );

	Rect rect;                                         //���ƾ��ο�
	int height = stats.rows;

	for (int i = 1; i < height; i++)
	{
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);

		rectangle(srcImag, rect, CV_RGB(255, 0, 0), 1, 8);
	}

	imshow("���ο�", srcImag);
	cout << "�����������" << num - 1 << endl;
	cout << "״̬����\n";
	cout << stats << endl;
	


	waitKey(0);
	return 0;
}
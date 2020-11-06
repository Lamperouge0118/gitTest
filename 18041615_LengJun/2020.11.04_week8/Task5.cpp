/***********************************************************��ϰ5 ͼ�����****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat srcImg, gray;                  //ԭͼ���Ҷ�ͼ
	Mat edge, rot, dst;                //��Ե���任���󣬽��

	Point2f src_pt[3];                 //ԭͼ��Ŀ���


	srcImg = imread("E:\\Test_Image\\16.jpg"); //��ȡͼƬ
	if (srcImg.empty())
	{
		cout << "���ܴ�ͼ��" << endl;
		destroyAllWindows();
		return -1;
	}
	
	//���ͼ��Ŀ���
	Point2f dst_pt[3] = {
							Point2f(srcImg.cols - 1,0),
							Point2f(0,srcImg.rows - 1),
							Point2f(srcImg.cols - 1,srcImg.rows - 1)
						};
	

	cvtColor(srcImg, gray, COLOR_BGR2GRAY);    //ת�Ҷ�
	Canny(gray, edge, 100, 200, 3);            //�����Ե

	int width = edge.cols;                     //ͼƬ�ĳ��Ϳ�
	int height = edge.rows;

	for (int i = 0; i < height; i++)  //ȡ���Ͻ�Ŀ��������
	{
		if (edge.at<uchar>(i, width - 1) != 0)
		{
			src_pt[0] = Point2f(width - 1, i);
			break;
		}

	}

	for (int j = height - 1; j > 0; j--)//���½�Ŀ��������
	{
		if (edge.at<uchar>(j, 0) != 0)
		{
			src_pt[1] = Point2f(0, j);
			break;
		}
	}

	for (int k = width - 1; k > 0; k--)//���½�Ŀ��������
	{
		if(edge.at<uchar>(height - 1, k) != 0)
		{
			src_pt[2] = Point2f(k, height - 1);
			break;
		}
	}
		
	  
	rot = getAffineTransform(src_pt, dst_pt);       //��任����
	warpAffine(srcImg, dst, rot, srcImg.size());    //�������

	imshow("ԭͼ", srcImg);                          //��ʾ
	imshow("���", dst);

	waitKey(0);
	return 0;
}
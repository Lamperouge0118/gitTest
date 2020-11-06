/***********************************************************��ϰ3 ����任****************************************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat srcImg, out, rot;                           //ԭͼ�����ͼ���任����
	srcImg = imread("E:\\Test_Image\\17.jpg");      //��ȡͼƬ
	if (srcImg.empty())
	{
		cout << "���ܴ�ͼ��" << endl;
		destroyAllWindows();
		return -1;
	}

	//����ԭͼ��Ŀ��ͼ�ϵ���������������
	Point2f src_pt[3] = {                            
							Point2f(200,200),
							Point2f(250,200),
							Point2f(200,100)
						};

	Point2f dst_pt[3] = {
							Point2f(300,100),
							Point2f(300,50),
							Point2f(200,100)
						};

	rot = getAffineTransform(src_pt,dst_pt);       //��������
	warpAffine(srcImg,out,rot,srcImg.size());

	imshow("ԭͼ", srcImg);
	imshow("���", out);


	waitKey(0);
	return 0;

}
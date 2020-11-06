/***********************************************************��ϰ4 ͶӰ�任****************************************************************************************************/

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

	//����ԭͼ��Ŀ��ͼ�ϵ���������任����
	Point2f src_pt[4] = {
							Point2f(150,150),
							Point2f(150,300),
							Point2f(350,300),
							Point2f(350,150)
	};

	Point2f dst_pt[4] = {
							Point2f(200,150),
							Point2f(300,300),
							Point2f(340,270),
							Point2f(340,180)
	};

	rot = getPerspectiveTransform(src_pt, dst_pt);       //��任����
	warpPerspective(srcImg, out, rot, srcImg.size());

	imshow("ԭͼ", srcImg);
	imshow("���", out);


	waitKey(0);
	return 0;

}
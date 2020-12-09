/*******************************************************************��ϰ��**************************************************************************************/
//ԭͼ����һЩ�֣������عⲻ���޷��۲쵽����ʹ��gamma�����������ú��ʲ������ҳ����ص���Ϣ

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


void MyGammaCorrection_A(Mat src, Mat& dst, float r);//٤��У����������
void MyGammaCorrection_B(Mat src, Mat& dst, float r);
void on_gamma(int, void* userdata);                  //٤��ָ���ص�����


Mat dst1, dst2;                             
int gamma1 = 0.35 * 100 , gamma2 = 0.35 * 100;      //٤��ָ����ֵ
int max_r = 1 * 100;                                //٤��ָ�����ֵ

int main()
{
	Mat srcImg;

	srcImg = imread("E:\\Test_Image\\28.jpg");
	if (srcImg.empty())
	{
		cout << "�޷��򿪸�ͼ��" << endl;
		destroyAllWindows();
		return -1;
	}
	imshow("src", srcImg);
	createTrackbar("gamma1", "src", &gamma1, max_r, on_gamma, &srcImg);
	createTrackbar("gamma2", "src", &gamma2, max_r, on_gamma, &srcImg);
	on_gamma(0, &srcImg);

	waitKey(0);
	return 0;
}


void MyGammaCorrection_A(Mat src, Mat& dst, float r)
{
	//��һ��
	src.convertTo(src, CV_32F);
	normalize(src, src, 1.0, 0.0, NORM_MINMAX);
	//��������ֵ
	int width = src.cols * src.channels();
	int height = src.rows;
	for (int i = 0; i < height; i++)
	{
		float* data = src.ptr<float>(i);
		for (int j = 0; j < width; j++)
		{
			data[j] = saturate_cast<uchar>(pow(data[j], r) * 255);
		}
	}
	if (src.channels() == 1)
		src.convertTo(dst, CV_8UC1);
	else
		src.convertTo(dst, CV_8UC3);
}

/*
�����������ѯ������Table��size == 256����[0��255]
1.�±�ֵ��һ����[0, 1]֮��
2.Output = Input^r
3.Lut[i] = Output * 255
����LUT������
����������������ֵ��Ϊ�±�ֱ�Ӵ�Table�ж����仯�������ֵ
*/
void MyGammaCorrection_B(Mat src, Mat& dst, float r)
{
	Mat Table(1, 256, CV_8U);
	uchar* p = Table.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = saturate_cast<uchar>(pow((float)(i / 255.0), r) * 255);
	}
	LUT(src, Table, dst);

}

void on_gamma(int, void* userdata)
{
	float r1 = gamma1 ? gamma1 / 100.0 : 0.01;
	float r2 = gamma2 ? gamma2 / 100.0 : 0.01;
	Mat src = *(Mat*)userdata;

	MyGammaCorrection_A(src, dst1, r1);
	MyGammaCorrection_B(src, dst2, r2);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
}


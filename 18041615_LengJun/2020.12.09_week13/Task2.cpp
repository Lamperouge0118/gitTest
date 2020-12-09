/****************************************************************练习二**************************************************************************************************/
//调用直方图均衡函数，进行直方图均衡处理，opencv原函数只能对单通道图像进行直方图均衡，要求实现可以对3通道图像进行直方图均衡

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

void equalize(Mat src, Mat& dst);
int main()
{
	Mat srcImg, dst;
	srcImg = imread("E:\\Test_Image\\27.jpg");
	if (srcImg.empty())
	{
		cout << "无法打开该图像" << endl;
		destroyAllWindows();
		return -1;
	}

	equalize(srcImg, dst);
	imshow("src", srcImg);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}

void equalize(Mat src, Mat& dst)
{
	Mat B, G, R;
	vector<Mat> channels;

	int chnel = src.channels();
	switch (chnel)
	{
	case 1:
		equalizeHist(src, dst);
		break;

	case 3:
		split(src, channels);
		B = channels[0];
		G = channels[1];
		R = channels[2];

		equalizeHist(B, B);
		equalizeHist(G, G);
		equalizeHist(R, R);
		merge(channels, dst);
		break;

	default:
		break;
	}

}
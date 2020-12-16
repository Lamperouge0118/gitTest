/*********************************************************��֤��Ƶ�е����ر任�Ƿ���ϸ�˹�ֲ�����*****************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int EVENT, int x, int y, int flags, void* userdata);//�����Ӧ��ѡȡ����
void draw_histogram(float* histogram, Mat& histoMat, int binwidth, int binheight);//��ֱ��ͼ
Point Sp;//ѡȡ����������

int main()
{
	VideoCapture cap(0);//������ͷ
	if (!cap.isOpened())
	{
		cout << "���ܴ���Ƶ" << endl;
		return -1;
		destroyAllWindows();
	}

	Mat frame;
	float histogram[256] = {0};//ֱ��ͼ����
	int bin_width =  4;        //���ο��
	int bin_height = 500;      //���ε����߶�
	Mat histoMat(bin_height, bin_width*256, CV_8UC3, Scalar(255, 255 ,255));//ֱ��ͼ����
	int cnt = 0;               //����ֵ


	while (1)
	{
		cap >> frame;
		if (frame.empty())
		{
			cout << "���ܶ�ȡ��Ƶ֡" << endl;
			return -1;
			destroyAllWindows();
		}

		//�ӵ�һ֡ѡȡ����
		if (!cnt)
		{
			Mat SelectMat;           //����Mat
			SelectMat = frame.clone();
			namedWindow("SelectMat");
			imshow("SelectMat", SelectMat);
			setMouseCallback("SelectMat", onMouse, &SelectMat);//���������Ӧ
			waitKey(0);
			destroyAllWindows();
		}

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		

		int value = frame.at<uchar>(Sp);                      //ȡ�Ҷ�ֵ
		histogram[value] ++;                                  //ֱ��ͼ�ۼ�
		draw_histogram(histogram, histoMat, bin_width, bin_height);//��ֱ��ͼ
		drawMarker(frame, Sp, Scalar(0, 0, 255));             //�ڵ�ǰ֡�����ѡ����
		imshow("frame", frame);                               //��ʾ��ǰ֡
		imshow("histogram", histoMat);                        //��ʾֱ��ͼ
		//��ʱ30ms
		//�ȴ�������Ӧ������ESC���˳�
		if (waitKey(30) == 27) 
		{
			destroyAllWindows();
			break;
		}
		cnt ++;
	}
	return 0;
}

//�����Ӧ��ѡȡ����
void onMouse (int EVENT, int x, int y, int flags, void* userdata)
{
	Mat disp = *(Mat*)userdata;
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN://���������
	{	
		Sp.x = x;          //������ѡ��������
		Sp.y = y;
		drawMarker(disp, Sp, Scalar(0, 0, 255));//�������λ��
		imshow("SelectMat", disp);
	}
	break;
	}
}

//��ֱ��ͼ
void draw_histogram(float* histogram, Mat& histoMat, int binwidth, int binheight)
{
	histoMat = Scalar(255, 255, 255);//�������
	//ȡֱ��ͼ���ֵ�����ڹ�һ��
	float maxValue = *max_element(histogram, histogram + 256);
	for (int i = 0; i < 256; i++)
	{
		Rect bin, edge;//���Σ�����������

		edge.x = (binwidth-1) * i;//ÿ�����ε����Ͻ�x����
		float height = histogram[i] / maxValue * binheight;//��һ�����θ߶�
		edge.width = binwidth;    //���ο��
		edge.height = height;
		edge.y = binheight - edge.height;//ÿ�����ε����Ͻ�y����

		bin.x = edge.x + 1, bin.y = edge.y + 1;
		bin.width = edge.width - 2, bin.height = edge.height - 1;
		rectangle(histoMat, edge, Scalar(0), 0);
		rectangle(histoMat, bin, Scalar(255, 255, 0), -1);
	}
}
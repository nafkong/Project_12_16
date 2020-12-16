#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() 
{
	VideoCapture cap(0);
	int cnt = 0;
	int N = 20;
	Mat frame, dstMat, ave_Mat, deata_Mat;
	vector<Mat> channels;
	while (1) {
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt < N) 
		{
			channels.push_back(frame);
			if (cnt == 0) {
				std::cout << "reading frame " << std::endl;
			}
		}
		else if (cnt == N) 
		{
			ave_Mat.create(frame.size(), CV_8UC1);
			deata_Mat.create(frame.size(), CV_32FC1);
			int rows = channels[0].rows;
			int cols = channels[0].cols;
			int size = channels.size();
			for (int i = 0; i < rows; i++) 
			{
				for (int j = 0; j < cols; j++) 
				{
					int sum = 0;
					float deata = 0;

					for (int n = 0; n < size; n++) {
						sum += channels[n].at<uchar>(i, j);
					}
					ave_Mat.at<uchar>(i, j) = sum / size;

					for (int n = 0; n < size; n++) {
						deata += pow((channels[n].at<uchar>(i, j) - ave_Mat.at<uchar>(i, j)), 2);
					}
					deata_Mat.at<float>(i, j) = deata / size;
				}
			}
		}
		else 
		{
			dstMat.create(frame.size(), CV_8UC1);
			int rows = frame.rows;
			int cols = frame.cols;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					int srcI;
					int meanI;
					int weight = 1.25;
					srcI = frame.at<uchar>(i, j);
					meanI = ave_Mat.at<uchar>(i, j);
					int dif = abs(srcI - meanI);
					int th = weight * deata_Mat.at<float>(i, j);

					if (dif > th) 
					{
						dstMat.at<uchar>(i, j) = 255;
					}
					else 
					{
						dstMat.at<uchar>(i, j) = 0;
					}
				}
			}
			imshow("result", dstMat);
			imshow("frame", frame);
			waitKey(30);
		}
		cnt++;
	}
}
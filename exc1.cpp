#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

VideoCapture cap(0);
Mat frame,bgMat,subMat,bny_subMat;
int cnt=0;
int main()
{
	while (1) {
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			frame.copyTo(bgMat);
		}
		else {
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 100, 255, CV_THRESH_BINARY);
			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			imshow("bgMat", bgMat);
		}
		cnt++;
		waitKey(0);
	}
}
// 单目测距.cpp: 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// 单位像素宽/高(cm/pixel)
#define UNIT_PIXEL_W 0.0008234375
#define UNIT_PIXEL_H 0.000825

using namespace std;
using namespace cv;
int main(void)
{
	Mat frame;
	VideoCapture capture(0);

	const double f = 0.35;  // 焦距
	const double w = 8.5;   // 被测物体宽度
	const double h = 5.6;   // 被测物体高度

	if (!capture.isOpened()) {
		printf("The camera is not opened.\n");
		return EXIT_FAILURE;
	}

	while(1) {
		//capture >> frame;等价
		capture.read(frame);
		if (frame.empty()) {
			printf("The frame is empty.\n");
			break;
		}
		medianBlur(frame, frame, 3);//中值滤波 卷积核3

		Mat grayImage;
		cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);
		// otsu 可以换用动态阈值
		threshold(grayImage, grayImage, NULL, 255,THRESH_BINARY |THRESH_OTSU);

		vector<vector<Point>> contours;
		vector<Point> maxAreaContour;

		findContours(grayImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//cv::drawContours(frame, contours, -1, cv::Scalar(0, 0, 255), 2, 8);

		// 提取面积最大轮廓
		double maxArea = 0;
		for (size_t i = 0; i < contours.size(); i++) {
			double area = fabs(cv::contourArea(contours[i]));
			if (area > maxArea) {
				maxArea = area;
				maxAreaContour = contours[i];
			}
		}
		// 轮廓外包正矩形
		Rect rect = boundingRect(maxAreaContour);
		rectangle(frame, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height),Scalar(255, 0, 0), 2, 8);

		// 计算成像宽/高
		double width = rect.width * UNIT_PIXEL_W;
		double height = rect.height * UNIT_PIXEL_H;
		// 分别以宽/高为标准计算距离
		double distanceW = w * f / width;
		double distanceH = h * f / height;

		char disW[50], disH[50];
		sprintf_s(disW, "DistanceW : %.2fcm", distanceW);
		sprintf_s(disH, "DistanceH : %.2fcm", distanceH);
		putText(frame, disW, cv::Point(5, 20), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 1, 8);
		putText(frame, disH, cv::Point(5, 40), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 0), 1, 8);

		imshow("Frame", frame);
		imshow("Gray", grayImage);
		if ((waitKey(10) & 0XFF) == 27) break;
	}
	cv::destroyAllWindows();
	capture.release();

	return EXIT_SUCCESS;
}

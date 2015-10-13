#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include "ImageRecognition.h"
#include "PrintWindow.h"
#include <vector>
#include "ImageData.h"

#include "SendMove.h"
#include "Vec2D.h"

void TouhouAILogic::ImageRecognition::test()
{
	WindowPrint wp;
	
	cv::Mat img = wp.HBITMAPToMat();
	
	std::map<std::string, cv::Mat> image = ImageData::Instance().ImageMap();

	std::vector<cv::Mat> planes;

	cv::split(img, planes);
	/*

	for (auto xy : image) {
		cv::Mat result;

		if (xy.first[xy.first.size() - 1] == 'R') {
			cv::matchTemplate(planes[2], xy.second, result, cv::TM_CCOEFF_NORMED);
		}
		else if (xy.first[xy.first.size() - 1] == 'G') {
			cv::matchTemplate(planes[1], xy.second, result, cv::TM_CCOEFF_NORMED);
		}

		else if (xy.first[xy.first.size() - 1] == 'B') {
			cv::matchTemplate(planes[0], xy.second, result, cv::TM_CCOEFF_NORMED);
		}
		
		std::vector<cv::Point> maxpt;

		float threshold = 0.65f;
		for (int y = 0; y < result.rows; ++y) {
			for (int x = 0; x < result.cols; ++x) {
				if (result.at<float>(y, x) > threshold) {
					maxpt.emplace_back(x, y);
				}
			}
		}
		for (auto x : maxpt) {
			cv::rectangle(img, x, cv::Point(x.x + xy.second.cols, x.y + xy.second.rows), cv::Scalar(0, 255, 255), 2, 8, 0);
		}

	}
	*/

	Vec2D a(0, 1);
	SendMove b;
	b.MovePlayer(a);
	
	cv::imshow("matching", img);
}

void TouhouAILogic::ImageRecognition::TemplateMatch()
{
	/*
	cv::Mat img = cv::imread("capture.bmp");
	cv::Mat img2 = cv::imread("capture2.png");
	
	std::vector<cv::Mat> planes;
	std::vector<cv::Mat> planes2;

	cv::split(img, planes);
	cv::split(img2, planes2);


	cv::Mat result;
	cv::matchTemplate(planes[2], planes2[2], result, cv::TM_CCOEFF_NORMED);

	std::vector<cv::Point> maxpt;

	float threshold = 0.55f;
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.emplace_back(x, y);
			}
		}
	}

	for (auto x : maxpt) {
		cv::rectangle(img, x, cv::Point(x.x + img2.cols, x.y + img2.rows), cv::Scalar(0, 255, 255), 2, 8, 0);
	}

	cv::imshow("matching", img);
	cv::imshow("result", result);
	cv::waitKey(0);
	cv::destroyAllWindows();
	*/

	cv::waitKey(0);
	cv::destroyAllWindows();
}

std::vector<cv::Point> TouhouAILogic::ImageRecognition::Mach()
{


	return std::vector<cv::Point>();
}

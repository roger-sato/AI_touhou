#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include "ImageRecognition.h"
#include "PrintWindow.h"
#include <vector>


void TouhouAILogic::ImageRecognition::test(System::IntPtr hw)
{
	WindowPrint wp;
	//wp.Print(hw);

	cv::Mat img = wp.HBITMAPToMat(hw);
}

void TouhouAILogic::ImageRecognition::TemplateMatch()
{
	//cv::Mat temp_img = cv::imread("capture3.bmp",cv::IMREAD_GRAYSCALE);
	cv::Mat img = cv::imread("capture.bmp");
	cv::Mat img2 = cv::imread("capture2.bmp");


	/*
	cv::Mat bin_img2;
	cv::cvtColor(img2, bin_img2, CV_BGR2GRAY);
	cv::Mat result;
	cv::matchTemplate(img2,temp_img,result, cv::TM_CCORR_NORMED);

	
	std::vector<cv::Point> maxpt;
	float threshold = 0.95f;
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.emplace_back(x,y);
			}
		}
	}
	
	for (auto x : maxpt) {
		cv::rectangle(img2, x, cv::Point(x.x + temp_img.cols, x.y + temp_img.rows), cv::Scalar(0, 255, 255), 2, 8, 0);
	}
	

	cv::imshow("matching", img2);
	cv::waitKey(0);
	cv::destroyAllWindows();
	*/



	
	cv::initModule_nonfree();
	cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("SURF");
	std::vector<cv::KeyPoint> keypoint, keypoint2;

	detector->detect(img, keypoint);
	detector->detect(img2, keypoint2);
	

	cv::Ptr<cv::DescriptorExtractor> extractor = cv::DescriptorExtractor::create("SURF");
	cv::Mat descriptor1, descriptor2;
	extractor->compute(img, keypoint, descriptor1);
	extractor->compute(img2, keypoint2, descriptor2);

	// マッチング
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-SL2");
	std::vector<cv::DMatch> dmatch;
	matcher->match(descriptor1, descriptor2, dmatch);

	/*
	std::vector<cv::DMatch> match12, match21;
	matcher->match(descriptor1, descriptor2, match12);
	matcher->match(descriptor2, descriptor1, match21);
	for (size_t i = 0; i < match12.size(); i++)
	{
	cv::DMatch forward = match12[i];
	cv::DMatch backward = match21[forward.trainIdx];
	if (backward.trainIdx == forward.queryIdx)
	dmatch.push_back(forward);
	}
	*/

	// マッチング結果の表示


	cv::Mat out;
	cv::drawMatches(img, keypoint, img2, keypoint2, dmatch, out);
	cv::imshow("matching", out);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
}
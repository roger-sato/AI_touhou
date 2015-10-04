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
	//cv::Mat img = wp.HBITMAPToMat(hw);

	cv::Mat img = cv::imread("capture.bmp");
	cv::Mat img2 = cv::imread("capture2.bmp");


	
	cv::initModule_nonfree();
	cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("SURF");
	std::vector<cv::KeyPoint> keypoint,keypoint2;
	
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

	// マッチング結果の表示
	
	cv::Mat out;
	cv::drawMatches(img, keypoint, img2, keypoint2, dmatch, out);
	cv::imshow("matching", out);
	cv::waitKey(0);
	cv::destroyAllWindows();

	/*
	//window作成
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);
	cv::imshow("red", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
	*/
}

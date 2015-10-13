
#include "Stdafx.h"
#include "ImageData.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>



void TouhouAILogic::ImageData::Init()
{
	AddImage("bullet_1" , "R");
	AddImage("bullet_2" , "R");
	AddImage("bullet_3" , "R");
	AddImage("enemy_1" , "G");
	AddImage("player_1" , "G");

}


cv::Mat TouhouAILogic::ImageData::Image(std::string file)
{
	return image_data[file];
}

std::map<std::string, cv::Mat> TouhouAILogic::ImageData::ImageMap()
{
	return image_data;
}

void TouhouAILogic::ImageData::AddImage(std::string name,std::string rgb)
{
	std::string filename = "./template/" + name + ".bmp";
	cv::Mat img = cv::imread(filename);
	std::vector<cv::Mat> planes;

	cv::split(img, planes);

	if (rgb == "R") {
		image_data[name + "_R"] = planes[2];
	}
	else if (rgb == "G") {
		image_data[name + "_G"] = planes[1];
	}
	else if (rgb == "B") {
		image_data[name + "_B"] = planes[0];
	}
}

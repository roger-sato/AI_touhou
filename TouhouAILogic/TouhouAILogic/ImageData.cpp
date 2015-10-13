
#include "Stdafx.h"
#include "ImageData.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>



void TouhouAILogic::ImageData::Init()
{
	AddImage("bullet","bullet_1" , "R");
	AddImage("bullet","bullet_2" , "R");
	AddImage("bullet","bullet_3" , "R");
	AddImage("enemy","enemy_1" , "G");
	AddImage("player","player_1" , "G");
	AddImage("player","player_2", "G");
	AddImage("player","player_3", "G");

}


cv::Mat TouhouAILogic::ImageData::Image(std::string type,std::string file)
{
	if (type == "enemy") {
		return enemy_data[file];
	}
	else if (type == "bullet") {
		return bullet_data[file];
	}
	else if (type == "player") {
		return player_data[file];
	}
	return cv::Mat();
}

std::map<std::string, cv::Mat> TouhouAILogic::ImageData::ImageMap(std::string type)
{
	if (type == "enemy") {
		return enemy_data;
	}
	else if (type == "bullet") {
		return bullet_data;
	}
	else if (type == "player") {
		return player_data;
	}
	return std::map<std::string, cv::Mat>();
}

void TouhouAILogic::ImageData::AddImage(std::string type,std::string name,std::string rgb)
{
	std::string filename = "./template/" + name + ".bmp";
	cv::Mat img = cv::imread(filename);
	std::vector<cv::Mat> planes;

	cv::split(img, planes);

	if (type == "enemy") {
		if (rgb == "R") {
			enemy_data[name + "_R"] = planes[2];
		}
		else if (rgb == "G") {
			enemy_data[name + "_G"] = planes[1];
		}
		else if (rgb == "B") {
			enemy_data[name + "_B"] = planes[0];
		}
	}
	else if (type == "bullet") {
		if (rgb == "R") {
			bullet_data[name + "_R"] = planes[2];
		}
		else if (rgb == "G") {
			bullet_data[name + "_G"] = planes[1];
		}
		else if (rgb == "B") {
			bullet_data[name + "_B"] = planes[0];
		}
	}
	else if (type == "player") {
		if (rgb == "R") {
			player_data[name + "_R"] = planes[2];
		}
		else if (rgb == "G") {
			player_data[name + "_G"] = planes[1];
		}
		else if (rgb == "B") {
			player_data[name + "_B"] = planes[0];
		}
	}
}

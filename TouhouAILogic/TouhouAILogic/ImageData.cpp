
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
	

	AddImage("bullet", "bullet_4", "R");
	AddImage("bullet", "bullet_5", "G");
	AddImage("bullet", "bullet_6", "G");
	AddImage("bullet", "bullet_7", "G");
	AddImage("bullet", "bullet_8", "G");


	//AddImage("enemy","enemy_1" , "G");

	AddImage("player", "player_1", "G");
	AddImage("player", "player_2", "G");
	AddImage("player", "player_3", "G");

	AddImage("player", "player_4", "G");
	AddImage("player", "player_5", "G");
	AddImage("player", "player_6", "G");

	AddImage("player", "player_7", "G");
	AddImage("player", "player_8", "G");
	AddImage("player", "player_9", "G");

	AddImage("player", "player_10", "MG");
	AddImage("player", "player_11", "MG");
	AddImage("player", "player_12", "MG");

	AddImage("player", "player_13", "MG");
	AddImage("player", "player_14", "MG");
	AddImage("player", "player_15", "MG");

	AddImage("player", "player_16", "MG");
	AddImage("player", "player_17", "MG");
	AddImage("player", "player_18", "MG");

	AddImage("player", "player_19", "MG");
	//AddImage("player", "player_20", "MG");
	//AddImage("player", "player_21", "MG");
	
}

void TouhouAILogic::ImageData::ImageMap(std::string type, std::vector<std::pair<cv::Mat,std::string>>& get_img)
{
	if (type == "enemy") {
		get_img = enemy_data;
	}
	else if (type == "bullet") {
		get_img = bullet_data;
	}
	else if (type == "player") {
		get_img = player_data;
	}
	else if (type == "move_player") {
		get_img = player_data_move;
	}
}

void TouhouAILogic::ImageData::AddImage(std::string type,std::string name,std::string rgb)
{
	std::string filename = "./template/" + name + ".bmp";
	cv::Mat img = cv::imread(filename);
	std::vector<cv::Mat> planes;

	cv::split(img, planes);

	if (type == "enemy") {
		if (rgb == "R") {
			enemy_data.push_back(std::pair<cv::Mat,std::string>(planes[2],"R"));
		}
		else if (rgb == "G") {
			enemy_data.push_back(std::pair<cv::Mat, std::string>(planes[1],"G"));
		}
		else if (rgb == "B") {
			enemy_data.push_back(std::pair<cv::Mat, std::string>(planes[0],"B"));
		}
	}
	else if (type == "bullet") {
		if (rgb == "R") {
			bullet_data.push_back(std::pair<cv::Mat, std::string>(planes[2],"R"));
		}
		else if (rgb == "G") {
			bullet_data.push_back(std::pair<cv::Mat, std::string>(planes[1],"G"));
		}
		else if (rgb == "B") {
			bullet_data.push_back(std::pair<cv::Mat, std::string>(planes[0],"B"));
		}
	}
	else if (type == "player") {
		if (rgb == "R") {
			player_data.push_back(std::pair<cv::Mat, std::string>(planes[2],"R"));
		}
		else if (rgb == "G") {
			player_data.push_back(std::pair<cv::Mat, std::string>(planes[1],"G"));
		}
		else if (rgb == "MG") {
			player_data_move.push_back(std::pair<cv::Mat, std::string>(planes[1], "G"));
		}
		else if (rgb == "B") {
			player_data.push_back(std::pair<cv::Mat, std::string>(planes[0],"B"));
		}
	}
}

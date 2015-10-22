#pragma once

#include <string>
#include <map>
#include <opencv2/core/core.hpp>

namespace TouhouAILogic {

	public class ImageData{
		std::vector<std::pair<cv::Mat,std::string>> enemy_data;
		std::vector<std::pair<cv::Mat, std::string>> bullet_data;
		std::vector<std::pair<cv::Mat, std::string>> player_data;


	public:
		static ImageData& Instance()
		{
			static ImageData instance;
			return instance;
		}

		void Init();
		void ImageMap(std::string type, std::vector<std::pair<cv::Mat,std::string>>& get_img);

	private:
		void AddImage(std::string type,std::string,std::string);

		ImageData() {}
		ImageData(const ImageData &other) {}
		ImageData &operator=(const ImageData &other) {}
	};
}
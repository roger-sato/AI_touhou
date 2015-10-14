#pragma once

#include <string>
#include <map>
#include <opencv2/core/core.hpp>

namespace TouhouAILogic {

	public class ImageData{
		std::map<std::string, cv::Mat> enemy_data;
		std::map<std::string, cv::Mat> bullet_data;
		std::map<std::string, cv::Mat> player_data;

	public:
		static ImageData& Instance()
		{
			static ImageData instance;
			return instance;
		}

		void Init();
		cv::Mat Image(std::string type,std::string file);
		void ImageMap(std::string type, std::map<std::string, cv::Mat>& get_img);

	private:
		void AddImage(std::string type,std::string,std::string);

		ImageData() {}
		ImageData(const ImageData &other) {}
		ImageData &operator=(const ImageData &other) {}
	};
}
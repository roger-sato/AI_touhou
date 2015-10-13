#pragma once

#include <string>
#include <map>
#include <opencv2/core/core.hpp>

namespace TouhouAILogic {

	public class ImageData{
		std::map<std::string, cv::Mat> image_data;

	public:
		static ImageData& Instance()
		{
			static ImageData instance;
			return instance;
		}

		void Init();
		cv::Mat Image(std::string file);
		std::map<std::string, cv::Mat> ImageMap();

	private:
		void AddImage(std::string,std::string);

		ImageData() {}
		ImageData(const ImageData &other) {}
		ImageData &operator=(const ImageData &other) {}
	};
}
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

// Yeesh, i need to figure this out ngl
#define ROOT_PATH "../../../"
#define ASSET_PATH "../../../assets/"
#define DESTINATION_PATH "../../../include/generated_assets"

/*
* This is not part of the game itself, image exporter is a tool to turn images into files that can be embedded into the game.
*/

const std::string GetAssetPath(const char* imageName) {
	const std::string assetPath = ASSET_PATH;
	return assetPath + imageName;
}
void ExportImage(const char* imageName) {
	const std::string imagePath = GetAssetPath(imageName);
	Image img = LoadImage(imagePath.c_str());

	std::string genImageName = imageName;
	auto stripLoc = genImageName.find(".");
	genImageName.resize(stripLoc);
	genImageName += "_Image.h";
	std::cout << GetWorkingDirectory() << "\n";

	
	std::string fileDestinationPath = DESTINATION_PATH + std::string("/") + genImageName;
	std::cout << fileDestinationPath.c_str() << "\n";
	ExportImageAsCode(img, fileDestinationPath.c_str());
}

int main() {
	std::cout << "Running ImageExporter!\n";
	std::vector<const char*> filePaths = {
		"Food.png"
	};

	for (const char* path : filePaths) {
		ExportImage(path);
	}


}

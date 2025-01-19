#include "Assets.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Assets::load()
{
	std::ifstream file(_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open assets file: " << _filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string config_type;
		if (iss >> config_type) {
			if (config_type == "Sound") {
				std::string name;
				std::string path;
				iss >> name >> path;
				path = _prefix + path;
				Sound sound = LoadSound(path.c_str());
				_sounds[name] = sound;
			}
			else if (config_type == "Texture") {
				std::string name;
				std::string path;
				iss >> name >> path;
				path = _prefix + path;
				Texture2D texture = LoadTexture(path.c_str());
				_textures[name] = texture;
			}
		}
    }

	file.close();
}
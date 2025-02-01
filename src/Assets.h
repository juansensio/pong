#pragma once

#include <map>
#include <string>
#include "raylib.h"

class Assets
{
	std::string 						_filename;
	std::string 						_prefix;
	std::map<std::string, Sound> 		_sounds;
	std::map<std::string, Texture2D> 	_textures;

public:
	Assets(): _filename("assets.txt"), _prefix("assets/") {}
	Assets(const std::string& filename): _filename(filename), _prefix("assets/") {}

	void load();

	const Sound& getSound(const std::string& name) const { return _sounds.at(name); }
	const Texture2D& getTexture(const std::string& name) const { return _textures.at(name); }
};
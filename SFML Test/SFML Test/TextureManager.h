#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include <string>

using std::unordered_map;
using std::string;
using namespace std;

class TextureManager {
public:
	static unordered_map<string, sf::Texture> textures;
	static void loadTexture(string filename);
	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};



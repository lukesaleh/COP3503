#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;
void TextureManager::loadTexture(string filename) {
	string filePath = "images/";
	filePath += filename + ".png";
	textures[filename].loadFromFile(filePath);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end()) {
		loadTexture(textureName);
	}
	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}
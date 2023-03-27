#include <string>
#include <vector>
#include "ImageData.h"
using namespace std;

ImageData::ImageData(const ImageData& d) {
	this->h = d.h;
	pixels.clear();
	for (unsigned int i = 0; i < d.pixels.size(); i++) {
		pixels.push_back(d.pixels[i]);
	}
}

ImageData::ImageData() {
	this->h = Header(); 
	this->pixels = {};
}

 ImageData::Header::Header() {
	 this->idLength = ' ';
	 this->colorMapType = ' ';
	 this->dataTypeCode = ' ';
	 this->colorMapOrigin = 0;
	 this->colorMapLength = 0;
	 this->colorMapDepth = ' ';
	 this->xOrigin = 0;
	 this->yOrigin = 0;
	 this->width = 0;
	 this->height = 0;
	 this->bitsPerPixel = ' ';
	 this->imageDescriptor = ' ';
 }
ImageData::ImageData(Header head, vector<ColorData> &pixelList) {
	h = head; 
	pixels.clear();
	for (unsigned int i = 0; i < pixelList.size(); i++) {
		pixels.push_back(pixelList[i]); 
	}
}
ImageData::ColorData::ColorData() {
	this->blue = 0;
	this->green = 0;
	this->red = 0;
}
ImageData::ColorData::ColorData(unsigned char blue, unsigned char green, unsigned char red) {
	this->blue = blue;
	this->green = green;
	this->red = red;
}
ImageData::Header ImageData::getHeader() {
	return this->h; 
}
vector<ImageData::ColorData> ImageData::getPixels() {
	return this->pixels; 
}
unsigned char ImageData::ColorData::getRed(){
	return this->red;
}
unsigned char ImageData::ColorData::getBlue() {
	return this->blue;
}
unsigned char ImageData::ColorData::getGreen() {
	return this->green;
}



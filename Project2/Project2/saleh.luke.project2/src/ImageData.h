#pragma once
#include <string>
#include <vector> 
using namespace std;
class ImageData {
public:
	struct Header {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
		Header();
	};
	struct ColorData {
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		ColorData();
		ColorData(unsigned char blue, unsigned char green, unsigned char red); 
		unsigned char getRed();
		unsigned char getGreen();
		unsigned char getBlue();
	};
	ImageData(Header head, vector<ColorData> &pixelList);
	ImageData();
	ImageData(const ImageData& d);
	Header getHeader(); 
	vector<ColorData> getPixels();
private:
	Header h;
	vector<ColorData> pixels;
};
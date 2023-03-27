#include "ImageData.h"
#include <vector>
#include <iostream>
#include <string> 
#include <fstream>
using namespace std;
bool testCase(ImageData output, ImageData example);
void testPrint(bool b, int num);
ImageData readTGA(string filename);
void writeTGA(ImageData data, string filename);
ImageData multiply(ImageData base, ImageData layer);
ImageData subtract(ImageData base, ImageData layer);
ImageData screen(ImageData base, ImageData layer);
ImageData overlay(ImageData background, ImageData foreground);
int main() {
	string filename = "input/layer1.tga";
	string outputname = "output/part1.tga";
	string examplename = "Examples/EXAMPLE_part1.tga";
	ImageData image1 = readTGA(filename); 
	ImageData example = readTGA(examplename);
	filename = "input/pattern1.tga";
	ImageData image2 = readTGA(filename); 
	ImageData task = multiply(image1, image2);
	writeTGA(task, outputname);
	bool taskTest = testCase(task, example);
	testPrint(taskTest, 1);

	filename = "input/car.tga";
	examplename = "Examples/EXAMPLE_part2.tga";
	outputname = "output/part2.tga";
	image1 = readTGA(filename);
	example = readTGA(examplename);
	filename = "input/layer2.tga";
	image2 = readTGA(filename);
	task = subtract(image1, image2);
	writeTGA(task, outputname);
	taskTest = testCase(task, example);
	testPrint(taskTest, 2);

	examplename = "Examples/EXAMPLE_part3.tga";
	outputname = "output/part3.tga";
	filename = "input/layer1.tga";
	example = readTGA(examplename);
	image1 = readTGA(filename);
	filename = "input/pattern2.tga";
	image2 = readTGA(filename);
	ImageData multiplyImage = multiply(image1, image2);
	filename = "input/text.tga";
	ImageData image3 = readTGA(filename);
	task = screen(multiplyImage, image3);
	writeTGA(task, outputname);
	taskTest = testCase(task, example);
	testPrint(taskTest, 3);

	examplename = "Examples/EXAMPLE_part4.tga";
	outputname = "output/part4.tga";
	filename = "input/layer2.tga";
	example = readTGA(examplename);
	image1 = readTGA(filename);
	filename = "input/circles.tga";
	image2 = readTGA(filename);
	multiplyImage = multiply(image1, image2);
	filename = "input/pattern2.tga";
	image3 = readTGA(filename);
	task = subtract(multiplyImage, image3);
	writeTGA(task, outputname);
	taskTest = testCase(task, example);
	testPrint(taskTest, 4);

	examplename = "Examples/EXAMPLE_part5.tga";
	outputname = "output/part5.tga";
	filename = "input/layer1.tga";
	example = readTGA(examplename);
	image1 = readTGA(filename); 
	filename = "input/pattern1.tga";
	image2 = readTGA(filename);
	task = overlay(image2, image1);
	writeTGA(task, outputname);
	taskTest = testCase(task, example);
	testPrint(taskTest, 5);

	examplename = "Examples/EXAMPLE_part6.tga";
	outputname = "output/part6.tga";
	filename = "input/car.tga";
	example = readTGA(examplename);
	image1 = readTGA(filename);
	vector<ImageData::ColorData> image1List = image1.getPixels();
	float green;
	for (unsigned int i = 0; i < image1List.size(); i++) {
		green = (float)(image1List[i].getGreen()); 
		green += 200;
		if (green > 255) {
			green = 255;
		}
		unsigned char greenChar = (char)(green + 0.5f);
		ImageData::ColorData pixel(image1List[i].getBlue(), greenChar, image1List[i].getRed());
		image1List[i] = pixel;
	}
	ImageData output6(image1.getHeader(), image1List); 
	writeTGA(output6, outputname);
	taskTest = testCase(output6, example);
	testPrint(taskTest, 6);

	examplename = "Examples/EXAMPLE_part7.tga";
	outputname = "output/part7.tga";
	filename = "input/car.tga";
	example = readTGA(examplename);
	image1 = readTGA(filename);
	image1List = image1.getPixels();
	float red;
	float blue;
	for (unsigned int i = 0; i < image1List.size(); i++) {
		red = (float)(image1List[i].getRed());
		red *= 4;
		blue = (float)(image1List[i].getBlue());
		blue *= 0;
		if (red > 255) {
			red = 255;
		}
		unsigned char redChar = (char)(red + 0.5f);
		unsigned char blueChar = (char)(blue);
		ImageData::ColorData pixel(blueChar, image1List[i].getGreen(), redChar);
		image1List[i] = pixel;
	}
	ImageData output7(image1.getHeader(), image1List);
	writeTGA(output7, outputname);
	taskTest = testCase(output7, example); 
	testPrint(taskTest, 7);

	string exampleR = "Examples/EXAMPLE_part8_r.tga";
	string exampleG = "Examples/EXAMPLE_part8_g.tga";
	string exampleB = "Examples/EXAMPLE_part8_b.tga";
	filename = "input/car.tga";
	ImageData exampleDataR = readTGA(exampleR);
	ImageData exampleDataG = readTGA(exampleG);
	ImageData exampleDataB = readTGA(exampleB);
	vector<ImageData::ColorData> redList;
	vector<ImageData::ColorData> greenList;
	vector<ImageData::ColorData> blueList;
	image1 = readTGA(filename);
	image1List = image1.getPixels();
	for (unsigned int i = 0; i < image1List.size(); i++) {
		red = (image1List[i].getRed());
		green = (image1List[i].getGreen());
		blue = (image1List[i].getBlue());
		ImageData::ColorData pixelRed(red, red, red);
		ImageData::ColorData pixelGreen(green, green, green);
		ImageData::ColorData pixelBlue(blue, blue, blue);
		redList.push_back(pixelRed);
		greenList.push_back(pixelGreen);
		blueList.push_back(pixelBlue);
	}
	ImageData redChannel(image1.getHeader(), redList);
	ImageData greenChannel(image1.getHeader(), greenList);
	ImageData blueChannel(image1.getHeader(), blueList);
	writeTGA(redChannel, "output/part8_r.tga");
	writeTGA(greenChannel, "output/part8_g.tga");
	writeTGA(blueChannel, "output/part8_b.tga");
	cout << "Task 8 tests: " << endl;
	cout << "Red channel: "<<endl;
	bool redTest = testCase(redChannel, exampleDataR);
	testPrint(redTest, 8);
	cout << "Green channel: "<<endl;
	bool greenTest = testCase(greenChannel, exampleDataG);
	testPrint(greenTest, 8);
	cout << "Blue channel: "<<endl;
	bool blueTest = testCase(blueChannel, exampleDataB);
	testPrint(blueTest, 8);

	examplename = "Examples/EXAMPLE_part9.tga";
	example = readTGA(examplename); 
	outputname = "output/part9.tga";
	string filenameR = "input/layer_red.tga";
	string filenameG = "input/layer_green.tga";
	string filenameB = "input/layer_blue.tga";
	ImageData inputRed = readTGA(filenameR);
	ImageData inputGreen = readTGA(filenameG);
	ImageData inputBlue = readTGA(filenameB);
	redList = inputRed.getPixels();
	greenList = inputGreen.getPixels();
	blueList = inputBlue.getPixels(); 
	vector<ImageData::ColorData> outputList; 
	for (unsigned int i = 0; i < redList.size(); i++) {
		red = redList[i].getRed();
		green = greenList[i].getGreen();
		blue = blueList[i].getBlue();
		ImageData::ColorData pixels(blue, green, red); 
		outputList.push_back(pixels);
	}
	ImageData task9(inputRed.getHeader(), outputList);
	writeTGA(task9, outputname);
	taskTest = testCase(task9, example);
	testPrint(taskTest, 9);

	examplename = "Examples/EXAMPLE_part10.tga";
	example = readTGA(examplename);
	outputname = "output/part10.tga";
	filename = "input/text2.tga";
	image1 = readTGA(filename);
	image1List = image1.getPixels();
	for (unsigned int i = 0; i < (image1List.size()) / 2; i++) {
		ImageData::ColorData temp = image1List[i];
		image1List[i] = image1List[image1List.size() - 1 - i];
		image1List[image1List.size() - 1 - i] = temp; 
	}
	ImageData flipped(image1.getHeader(), image1List);
	writeTGA(flipped, outputname);
	taskTest = testCase(flipped, example); 
	testPrint(taskTest, 10);

	examplename = "Examples/EXAMPLE_extracredit.tga";
	example = readTGA(examplename);
	outputname = "output/extracredit.tga"; 
	filename = "input/car.tga";
	ImageData car = readTGA(filename);
	vector<ImageData::ColorData> carList = car.getPixels();
	filename = "input/circles.tga";
	ImageData circles = readTGA(filename); 
	vector<ImageData::ColorData> circlesList = circles.getPixels(); 
	filename = "input/text.tga";
	ImageData textImage = readTGA(filename);
	vector<ImageData::ColorData> textList = textImage.getPixels(); 
	filename = "input/pattern1.tga";
	ImageData pattern1 = readTGA(filename);
	vector<ImageData::ColorData> pattern1List = pattern1.getPixels();
	int counterx = 0;
	int countery = 0;
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int index4 = 0;
	vector<ImageData::ColorData> pixels;
	for (int i = 0; i < (1024 * 1024); i++) {
		if (counterx == 1024) {
			counterx = 0;
		}
		if (counterx < 512 && countery >= 524288) {
			pixels.push_back(carList[index1]);
			index1++;
		}
		else if (counterx >= 512 && countery >= 524288) {
			pixels.push_back(circlesList[index2]);  
			index2++;
		}
		else if (counterx < 512 && countery < 524288) {
			pixels.push_back(textList[index3]);
			index3++;
		}
		else if (counterx >= 512 && countery < 524288) {
			pixels.push_back(pattern1List[index4]);
			index4++; 
		}
		counterx++; 
		countery++; 
	}
	ImageData::Header h = car.getHeader(); 
	h.height = 1024; 
	h.width = 1024; 
	ImageData extraImage(h, pixels);
	writeTGA(extraImage, outputname);
	taskTest = testCase(extraImage, example);
	testPrint(taskTest, 11);
	return 0;
}

ImageData readTGA(string filename) {
	vector<ImageData::ColorData> pixels;
	ifstream file(filename, ios_base::binary);
	ImageData::Header head;
	file.read(&head.idLength, sizeof(head.idLength));
	file.read(&head.colorMapType, sizeof(head.colorMapType));
	file.read(&head.dataTypeCode, sizeof(head.dataTypeCode));
	file.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
	file.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
	file.read(&head.colorMapDepth, sizeof(head.colorMapDepth));
	file.read((char*)&head.xOrigin, sizeof(head.xOrigin));
	file.read((char*)&head.yOrigin, sizeof(head.yOrigin));
	file.read((char*)&head.width, sizeof(head.width));
	file.read((char*)&head.height, sizeof(head.height));
	file.read(&head.bitsPerPixel, sizeof(head.bitsPerPixel));
	file.read(&head.imageDescriptor, sizeof(head.imageDescriptor));
	for (int i = 0; i < (head.width * head.height); i++) {
		unsigned char red;
		unsigned char blue;
		unsigned char green;
		file.read((char*)&blue, sizeof(blue));
		file.read((char*)&green, sizeof(green));
		file.read((char*)&red, sizeof(red));
		ImageData::ColorData data(blue, green, red);
		pixels.push_back(data);
	}
	ImageData image(head, pixels); 
	vector<ImageData::ColorData> pixelList = image.getPixels();
	file.close();
	return image;
}
void writeTGA(ImageData data, string filename) {
	ImageData::Header head = data.getHeader();
	vector<ImageData::ColorData> pixels = data.getPixels();
	ofstream outfile(filename, ios_base::binary);
	outfile.write(&head.idLength, sizeof(head.idLength));
	outfile.write(&head.colorMapType, sizeof(head.colorMapType));
	outfile.write(&head.dataTypeCode, sizeof(head.dataTypeCode));
	outfile.write((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
	outfile.write((char*)&head.colorMapLength, sizeof(head.colorMapLength));
	outfile.write(&head.colorMapDepth, sizeof(head.colorMapDepth));
	outfile.write((char*)&head.xOrigin, sizeof(head.xOrigin));
	outfile.write((char*)&head.yOrigin, sizeof(head.yOrigin));
	outfile.write((char*)&head.width, sizeof(head.width));
	outfile.write((char*)&head.height, sizeof(head.height));
	outfile.write(&head.bitsPerPixel, sizeof(head.bitsPerPixel));
	outfile.write(&head.imageDescriptor, sizeof(head.imageDescriptor));
	for (unsigned int i = 0; i < pixels.size(); i++) {
		unsigned char red = pixels[i].getRed();
		unsigned char blue = pixels[i].getBlue();
		unsigned char green = pixels[i].getGreen();
		outfile.write((char*)&blue, sizeof(blue));
		outfile.write((char*)&green, sizeof(green));
		outfile.write((char*)&red, sizeof(red));
	}
	outfile.close();
}
ImageData multiply(ImageData base, ImageData layer) { 
	vector<ImageData::ColorData> data1List = base.getPixels();
	vector<ImageData::ColorData> data2List = layer.getPixels();
	vector<ImageData::ColorData> dataList;
	float f = 255.0;
	for (unsigned int i = 0; i < data1List.size(); i++) {
		float red = (float)(data1List[i].getRed()) * (float)(data2List[i].getRed());
		
		float green = (float)(data1List[i].getGreen()) * (float)(data2List[i].getGreen());
		
		float blue = (float)(data1List[i].getBlue()) * (float)(data2List[i].getBlue());
		
		red = red / 255;
		blue = blue / 255;
		green = green / 255;
		unsigned char blueChar = (char)(blue + 0.5f);
		unsigned char redChar = (char)(red + 0.5f);
		unsigned char greenChar = (char)(green + 0.5f);
		ImageData::ColorData color(blueChar, greenChar, redChar);
		dataList.push_back(color);
	}
	ImageData data(base.getHeader(), dataList);
	return data;
}
bool testCase(ImageData output, ImageData example) {
	if (output.getPixels().size() != example.getPixels().size()) {
		cout << "Failed size" << endl;
		return false;
	}
	else if (output.getHeader().idLength != example.getHeader().idLength) {
		return false;
	}
	else if (output.getHeader().colorMapType != example.getHeader().colorMapType) {
		return false;
	}
	else if (output.getHeader().dataTypeCode != example.getHeader().dataTypeCode) {
		return false;
	}
	else if (output.getHeader().colorMapOrigin != example.getHeader().colorMapOrigin) {
		return false;
	}
	else if (output.getHeader().colorMapLength != example.getHeader().colorMapLength) {
		return false;
	}
	else if (output.getHeader().colorMapDepth != example.getHeader().colorMapDepth) {
		return false;
	}
	else if (output.getHeader().xOrigin != example.getHeader().xOrigin) {
		return false;
	}
	else if (output.getHeader().yOrigin != example.getHeader().yOrigin) {
		return false;
	}
	else if (output.getHeader().width != example.getHeader().width) {
		return false;
	}
	else if (output.getHeader().bitsPerPixel != example.getHeader().bitsPerPixel) {
		return false;
	}
	else if (output.getHeader().imageDescriptor != example.getHeader().imageDescriptor) {
		return false;
	}
	else {
		vector<ImageData::ColorData> outputlist = output.getPixels();
		vector<ImageData::ColorData> examplelist = example.getPixels();
		for (unsigned int i = 0; i < outputlist.size(); i++) {
			if (outputlist[i].getBlue() != examplelist[i].getBlue()) {
				cout << i << endl;
				cout << "Blue output: " << (float)outputlist[i].getBlue() << ", blue example: " << (float)examplelist[i].getBlue()<<endl;
				return false;
			}
			else if (outputlist[i].getRed() != examplelist[i].getRed()) {
				cout << i << endl;
				cout << "Red output: " << (float)outputlist[i].getRed() << ", red example: " << (float)examplelist[i].getRed()<<endl;
				return false;
			}
			else if (outputlist[i].getGreen() != examplelist[i].getGreen()) {
				cout << i << endl;
				cout << "Green output: " << (float)outputlist[i].getGreen() << ", green example: " << (float)examplelist[i].getGreen()<<endl;
				return false;
			}
		}
	}
	return true;
}
void testPrint(bool b, int num) {
	if (b == true) {
		cout << "Test case "<<num<<": passed!" << endl;
	}
	else {
		cout << "Test case " << num << ": failed!" << endl;
	}
}
ImageData subtract(ImageData base, ImageData layer) {
	vector<ImageData::ColorData> data1List = base.getPixels();
	vector<ImageData::ColorData> data2List = layer.getPixels();
	vector<ImageData::ColorData> dataList;
	for (unsigned int i = 0; i < data1List.size(); i++) {
		float red = (float)(data1List[i].getRed()) - (float)(data2List[i].getRed()); 
		float blue = (float)(data1List[i].getBlue()) - (float)(data2List[i].getBlue());
		float green = (float)(data1List[i].getGreen()) - (float)(data2List[i].getGreen());
		if (red < 0) {
			red = 0;
		}
		if (blue < 0) {
			blue = 0;
		}
		if (green < 0) {
			green = 0;
		}
		unsigned char redChar = (char)(red +0.5f);
		unsigned char blueChar = (char)(blue +0.5f);
		unsigned char greenChar = (char)(green +0.5f);
		ImageData::ColorData color(blueChar, greenChar, redChar);
		dataList.push_back(color); 
	}
	ImageData data(base.getHeader(), dataList);
	return data;
}
ImageData screen(ImageData base, ImageData layer) {
	vector<ImageData::ColorData> onePixels;
	float red = 255.f;
	float green = 255.f;
	float blue = 255.f;
	vector<ImageData::ColorData> baseList = base.getPixels();
	unsigned char redChar = (char)(red);
	unsigned char greenChar = (char)(green);
	unsigned char blueChar = (char)(blue);
	for (unsigned int i = 0; i < baseList.size(); i++) { 
		ImageData::ColorData color(blueChar, greenChar, redChar);
		onePixels.push_back(color); 
	}
	ImageData oneImage(base.getHeader(), onePixels);
	ImageData termA = subtract(oneImage, base);
	ImageData termB = subtract(oneImage, layer);
	ImageData multiplyTerm = multiply(termA, termB);
	ImageData output = subtract(oneImage, multiplyTerm); 
	return output; 
}
ImageData overlay(ImageData background, ImageData foreground) {
	float red; 
	float green;
	float blue;
	float redB;
	float greenB;
	float blueB;
	float redF;
	float greenF;
	float blueF;
	unsigned char redChar;
	unsigned char greenChar;
	unsigned char blueChar;
	vector<ImageData::ColorData> backgroundList = background.getPixels();
	vector<ImageData::ColorData> foregroundList = foreground.getPixels();
	vector<ImageData::ColorData> outputList;
	for (unsigned int i = 0; i < backgroundList.size(); i++) {
		redB = (float)backgroundList[i].getRed();
		redB = redB / 255.f;
		greenB = (float)backgroundList[i].getGreen();
		greenB = greenB / 255.f;
		blueB = (float)backgroundList[i].getBlue();
		blueB = blueB / 255.f;
		redF = (float)foregroundList[i].getRed();
		redF = redF / 255.f;
		greenF = (float)foregroundList[i].getGreen();
		greenF = greenF / 255.f;
		blueF = (float)foregroundList[i].getBlue();
		blueF = blueF / 255.f;
		if (redB <= 0.5) {
			red = (2 * redB * redF);
			red = red * 255;
		}
		else {
			red = 2 * (1 - redB) * (1 - redF);
			red = 1 - red;
			red = red *255;
		}
		if (greenB <= 0.5) {
			green = (2 * greenB * greenF);
			green = green * 255;
		}
		else {
			green = 2 * (1 - greenB) * (1 - greenF);
			green = 1 - green;
			green = green * 255; 
		}
		if (blueB <= 0.5) {
			blue = (2 * blueB * blueF);
			blue = blue * 255;
		}
		else {
			blue = 2 * (1 - blueB) * (1 - blueF);
			blue = 1 - blue;
			blue = blue * 255;
		}
		unsigned char blueChar = (char)(blue + 0.5f);
		unsigned char redChar = (char)(red + 0.5f);
		unsigned char greenChar = (char)(green + 0.5f);
		ImageData::ColorData pixel(blueChar, greenChar, redChar);
		outputList.push_back(pixel);
	}
	ImageData output(background.getHeader(), outputList);
	return output;
}
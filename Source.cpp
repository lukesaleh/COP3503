#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

bool errorCheck(string input);
string substringExtractor(string input);
int commaPosition(string input);

int main() {
	//Creating variables for later use to store title, column headers, etc.
	string title;
	string header1;
	string header2;
	string inputData;
	string dataString;
	int dataInt;
	vector<string> strVector;
	vector<int> intVector;
	bool run = true;

	cout << "Enter a title for the data:" << endl;
	getline(cin, title);
	cout << "You entered: " << title << endl;

	cout << "Enter the column 1 header:" << endl;
	getline(cin, header1);
	cout << "You entered: " << header1 << endl;

	cout << "Enter the column 2 header:" << endl;
	getline(cin, header2);
	cout << "You entered: " << header2 << endl;

	while (run) {
		cout << "Enter a data point (-1 to stop input):" << endl;
		getline(cin, inputData);
		if (inputData == "-1") {
			run = false;
			break;
		}
		else if (!errorCheck(inputData)) {
			continue;
		}
		else {
			dataInt = stoi(inputData.substr(inputData.find(',') + 1)); 
			dataString = substringExtractor(inputData);
			strVector.push_back(dataString);
			intVector.push_back(dataInt);
			cout << "Data string: " << dataString << endl;
			cout << "Data integer: " << dataInt << endl;
		}
	}

	cout << "" << endl;
	cout << right << setw(33) << title << endl;
	cout << left << setw(20) << header1 << "|" << right << setw(23) << header2 << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < strVector.size(); i++) {
		cout << left << setw(20) << strVector[i] << "|" << right << setw(23) << intVector[i] << endl;
	}

	cout << "" << endl;
	for (int i = 0; i < strVector.size(); i++) {
		cout << right << setw(20) << strVector[i]<<" ";
		for (int j = 0; j < intVector[i]; j++) {
			cout << "*";
		}
		cout << endl;
	}
	return 0;
}
bool errorCheck(string input) {
	try {
		int count = 0;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == ',') {
				count++;
			}
		}
		if (count >= 2) {
			throw 'c';
		}
		else if (count == 0) {
			throw 505;
		}
		string numbers = input.substr(input.find(',') + 1);
		try {
			stoi(numbers);
		}
		catch (invalid_argument) {
			cout << "Error: Comma not followed by an integer." << endl;
			return false;
		}
			return true;
	}
	catch (char c) {
		cout << "Error: Too many commas in input." << endl;
		return false;
	}
	catch (int num) {
		cout << "Error: No comma in string." << endl;
		return false;
	}
}

string substringExtractor(string input) {
	int pos = commaPosition(input);
	string s = input.substr(0, pos);
	return s;
}

int commaPosition(string input) {
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ',') {
			return i;
		}
	} 
}
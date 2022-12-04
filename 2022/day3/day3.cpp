#include <iostream>
#include <unordered_set>
#include <fstream>
using namespace std;

unordered_set <char> charSet;


/*
65 - A
90 - Z

97 - a
122 - z

mapping char to array index and priority
a-z is 1-26
A-Z is 27-52
*/


unsigned int char2ArrayIdx(unsigned int charInt) {
	unsigned int res;
	if (charInt >= 97) { // a-z
		res = charInt - 96;
	}
	else {  // A-Z
		res = charInt - 38;
	}

	return res;

}

void part2() {

	string line;
	ifstream file("day3.txt");
	unsigned int idx;
	unsigned int totalPriority = 0;
	unsigned int occuranceMap[73] = {0};  // index 0 is dummy
	int lineNo = 0;
	while(getline(file, line)){
		if (lineNo == 0) {
			// populate occuranceMap
			for (int i=0; i<line.length(); i++){
				idx = char2ArrayIdx(line[i]);
				occuranceMap[idx] = 1;
			}
		}
		else if (lineNo == 1) {

			for (int i=0; i<line.length(); i++){
				idx = char2ArrayIdx(line[i]);
				if (occuranceMap[idx] == 1) {
					occuranceMap[idx] = 2;
				}
			}
		}
		else {
			for (int i=0; i < line.length(); i++) {
				idx = char2ArrayIdx(line[i]);
				if (occuranceMap[idx] == 2) {
					totalPriority += idx;
					// flush buffer for next 3 lines
					for (auto &eachItem: occuranceMap) {
						eachItem = 0;
					}
					break;
				}
			}
		}	
		lineNo += 1;
		lineNo = lineNo % 3;

	}
	cout << totalPriority << endl;
}


void part1() {

	string line;
	ifstream file("day3.txt");
	unsigned int idx;
	unsigned int totalPriority = 0;
	unsigned int occuranceMap[73] = {0};  // index 0 is dummy
	
	while(getline(file, line)){
		// init to 0
		for (auto &eachItem: occuranceMap) {
			eachItem = 0;
		}
		for (int i=0; i< line.length() / 2; i++){
			idx = char2ArrayIdx(line[i]);
			occuranceMap[idx] = 1;
		}
		for (int i=line.length() / 2; i< line.length(); i++) {
			idx = char2ArrayIdx(line[i]);
			if (occuranceMap[idx] == 1) {
				totalPriority += idx;
				break;
			}
		}
	}
	cout << totalPriority << endl;
}


int main() {
	part2();
}

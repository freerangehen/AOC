#include "TopThree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;
 




void part1() {
	typedef unordered_map<int, int> ElfCalMap;

	string str;
	ifstream file("day1a.txt");

	ElfCalMap elfCalMap;
	int elfNum = 0;
    int elfCal = 0;
    int maxCal = 0;
	while(getline(file, str)){
		if (str.empty()) {
			if (elfCal > maxCal) {
				maxCal = elfCal;
			}
			elfCalMap[elfNum] = elfCal;
			elfCal = 0;
			elfNum += 1;
			continue;
		}
		elfCal += stoi(str); 
	}
	cout << maxCal << endl;
}


void part2() {

	TopThree topThreeCals;

	string str;
	ifstream file("day1a.txt");

    int elfCal = 0;
    int maxCal = 0;
	while(getline(file, str)){
		if (str.empty()) {
			topThreeCals.update(elfCal);
			elfCal = 0;
			continue;
		}
		elfCal += stoi(str); 
	}
	cout << topThreeCals.sum() << endl;
}


int main(){
	part2();
}



































#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;
 

const string xyzPAPER = "Y";
const string xyzROCK = "X";
const string xyzSCISSORS = "Z";

const string abcPAPER = "B";
const string abcROCK = "A";
const string abcSCISSORS = "C";

const string DRAW = "Y";
const string WIN = "Z";
const string LOSE = "X";


int getPoints2(string you, string opponent) {

    int competeScore;
    if (you == DRAW){
        competeScore = 3;
		if (opponent == abcPAPER) { return competeScore + 2; }
		if (opponent == abcSCISSORS) { return competeScore + 3; }
		if (opponent == abcROCK) { return competeScore + 1; }
	}
    else if (you == WIN){
        competeScore = 6;
		if (opponent == abcPAPER) { return competeScore + 3; }
		if (opponent == abcSCISSORS) { return competeScore + 1; }
		if (opponent == abcROCK) { return competeScore + 2; }
    }
    else {
        competeScore = 0;
		if (opponent == abcPAPER) { return competeScore + 1; }
		if (opponent == abcSCISSORS) { return competeScore + 2; }
		if (opponent == abcROCK) { return competeScore + 3; }
    }
	return 0;
}

int getPoints1(string you, string opponent) {

    int shapeScore;
    int result;
    if (you == xyzPAPER){
        shapeScore = 2;
    }
    else if (you == xyzROCK){
        shapeScore = 1;
    }
    else {
        shapeScore = 3;
    }

    if ((you == xyzPAPER && opponent == abcPAPER) || (you == xyzROCK && opponent == abcROCK) || (you == xyzSCISSORS && opponent == abcSCISSORS)){
        cout << 3 + shapeScore << endl;
        return  3 + shapeScore;
    }
    if ((you == xyzPAPER && opponent == abcROCK) || (you == xyzROCK && opponent == abcSCISSORS) || (you == xyzSCISSORS && opponent == abcPAPER)) {
        cout << 6 + shapeScore << endl;
        return  6 + shapeScore;
    }

    cout << shapeScore << endl;
    return shapeScore;
}


void part1() {

	string line;
	ifstream file("day2.txt");
    vector<string> splitLine;

    int points = 0;

	while(getline(file, line)){
        boost::split(splitLine, line, boost::is_any_of(" "));
        if (!splitLine[0].empty() && !splitLine[1].empty()) {
            points += getPoints1(splitLine[1], splitLine[0]);
        }
    }
    cout << points << endl;
}


void part2() {
	string line;
	ifstream file("day2.txt");
    vector<string> splitLine;

    int points = 0;

	while(getline(file, line)){
		cout << line[0] << endl;
        boost::split(splitLine, line, boost::is_any_of(" "));
        if (!splitLine[0].empty() && !splitLine[1].empty()) {
            points += getPoints2(splitLine[1], splitLine[0]);
        }
    }
    cout << points << endl;
}


int main(){
	part2();
}



































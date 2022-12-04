#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;


bool included(int start1, int end1, int start2, int end2) {
    return (((start2 >= start1) && (end2 <= end1)) || ((start1 >= start2) && (end2 >= end1)));
}

bool overlap(int start1, int end1, int start2, int end2){
    return !((start2 > end1) || (start1 > end2));
}

tuple<int, int, int, int> line2ranges(string line){
        vector<string> splitLine;
        int start1, start2, end1, end2;
        string range1, range2;

        cout << "<-- " << line << endl;
        boost::split(splitLine, line, boost::is_any_of(","));
        range1 = splitLine[0];
        range2 = splitLine[1];
        cout << range1 << " " << range2 << endl;

        boost::split(splitLine, range1, boost::is_any_of("-"));
        start1 = stoi(splitLine[0]);
        end1 = stoi(splitLine[1]);
        cout << start1 << "," << end1 << endl;

        boost::split(splitLine, range2, boost::is_any_of("-"));
        start2 = stoi(splitLine[0]);
        end2 = stoi(splitLine[1]);
        cout << start2 << "," << end2 << endl;
        return make_tuple(start1, end1, start2, end2);
}


void part2(){
    int start1, start2, end1, end2;
    string line;
    int overlapCount = 0;

    ifstream file("day4.txt");
    while (getline(file, line)) {
        tie(start1, end1, start2, end2) = line2ranges(line);
        if (overlap(start1, end1, start2, end2)) {
            overlapCount += 1;
        }

    }

    cout << overlapCount << endl;

}


void part1(){
    int start1, start2, end1, end2;
    string line;
    int includeCount = 0;

    ifstream file("day4.txt");
    while (getline(file, line)) {
        tie(start1, end1, start2, end2) = line2ranges(line);
        if (included(start1, end1, start2, end2)) {
            includeCount += 1;
        }

    }

    cout << includeCount << endl;

}
int main(){
    part2();
}


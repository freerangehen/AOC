#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

// unordersed_set<setElementType, hashFunctionReturnType>

bool cycleCondition(int cycle, vector<string> splitLine, int X)
{
    /*
    cout << "cycle=" << cycle << ", X=" << X;
    for (const auto& item: splitLine) {cout << item;}
    cout << endl;
    */
    return ((cycle == 20) || (cycle == 60) || (cycle == 100) || (cycle == 140) || (cycle == 180) || (cycle == 220));
}

void plot(int cycle, int X)
{
    // cycle starts at 1
    int screenLocation = (cycle - 1) % 40;
    char pixel;
    if ((screenLocation >= X - 1) && (screenLocation <= X + 1))
    {
        pixel = '#';
    }else
    {
        pixel = '.';
    }

    if (screenLocation == 0) 
    {
        //cout << "screenLocation=" << screenLocation << ", cycle=" << cycle << ", X=" << X << endl;
        cout << endl;
    }
    cout << pixel;
}

void part2(string filename){
    string line, instruction, stringArgument;
	vector<string> splitLine;
    unordered_map<string, int> instructionCode;

    const int noop = 0;
    const int addx = 1;
    instructionCode["noop"] = noop; 
    instructionCode["addx"] = addx; 

    int intArgument;
    int cycle = 1;
    int X = 1;

    plot(cycle, X);
    ifstream file(filename);
    while (getline(file, line))
    {
        boost::split(splitLine, line, boost::is_any_of(" "));
        instruction = splitLine[0];
        switch (instructionCode[instruction]){
            case noop:
                // do nothing
                cycle += 1;
                plot(cycle, X);
                break;
            case addx:
                intArgument = stoi(splitLine[1]);
                cycle += 1;
                plot(cycle, X);

                X += intArgument;
                cycle += 1;
                plot(cycle, X);
                break;
        }
    }

}


void part1(string filename){
    string line, instruction, stringArgument;
	vector<string> splitLine;
    unordered_map<string, int> instructionCode;

    const int noop = 0;
    const int addx = 1;
    instructionCode["noop"] = noop; 
    instructionCode["addx"] = addx; 

    int intArgument;
    int cycle = 1;
    int X = 1;
    int sum;

    ifstream file(filename);
    while (getline(file, line))
    {
        boost::split(splitLine, line, boost::is_any_of(" "));
        instruction = splitLine[0];
        switch (instructionCode[instruction]){
            case noop:
                // do nothing
                cycle += 1;
                if (cycleCondition(cycle, splitLine, X)){cout << cycle << "*" << X << " = " << cycle * X << endl; sum += cycle*X;}
                break;
            case addx:
                intArgument = stoi(splitLine[1]);

                cycle += 1;
                if (cycleCondition(cycle, splitLine, X)){cout << cycle << "*" << X << " = " << cycle * X << endl; sum += cycle*X;}

                X += intArgument;

                cycle += 1;
                if (cycleCondition(cycle, splitLine, X)){cout << cycle << "*" << X << " = " << cycle * X << endl; sum += cycle*X;}
                
                break;
        }
    }

    cout << "total sum = " << sum << endl;
}


int main(){
    part2("day10.txt");
    // part1("day10.txt");
}


#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;



tuple<int, int, int> parseInstruction(string line) {
    int numCrates=0, src=0, dest=0;
    int _startNumCrates, _endNumCrates, _startSrc, _endSrc, _startDest, _endDest;

    _startNumCrates = 5;
    _endNumCrates = line.find(" from");
    _startSrc = line.find("from ") + 5;
    _endSrc =line.find(" to");
    _startDest = line.find("to ") + 3;
    _endDest = line.length();
    // cout << line << endl;
    // cout << _startNumCrates << ", " << _endNumCrates << ", " << _startSrc << ", " << _endSrc << ", " << _startDest << ", " << _endDest << endl;
    numCrates = stoi(line.substr(_startNumCrates, _endNumCrates - _startNumCrates));
    src = stoi(line.substr(_startSrc, _endSrc - _startSrc));
    dest = stoi(line.substr(_startDest, _endDest - _startDest));

    cout << line << endl;
    cout << numCrates << ", " << src << ", " << dest << endl;

    return make_tuple(numCrates, src, dest);
}

int getNumStacks(string filename){
    string line;
    vector<string> splitLine;

    ifstream file(filename);
    while (getline(file, line)){
        if (line.length() > 2) {
            if (line.substr(0, 2) == " 1"){ // somehow == "1" does not work
                boost::split(splitLine, line, boost::is_any_of(" "));
                file.close();
                return stoi(splitLine[splitLine.size() - 2]);
            }
        }
    }
    return -1;
}

void loadStacks(string line, vector<string> stacks[]) {
    // location of crates are at 1, 5, 9, 12, ...
    int stackIdx;
    string item;
    cout << line << endl;
    for (int i=1; i<line.length(); i+=4){
        stackIdx = (i - 1) / 4;
        item = line.substr(i, 1);
        if (item != " "){
            stacks[stackIdx].insert(stacks[stackIdx].begin(), item);
        }
    }
} 


void moveCrates(vector<string> stacks[], int src, int dest, int numCrates){
    src -= 1;
    dest -= 1;
    // part1
    /*
    for (int n=0; n<numCrates; n++){
        stacks[dest].push_back(stacks[src].back());
        stacks[src].pop_back();
    }
    */
    // part2
    vector<string> toMove;
    for (int n=0; n<numCrates; n++){
        toMove.push_back(stacks[src].back());
        stacks[src].pop_back();
    }

    for (int n=0; n<numCrates; n++){
        stacks[dest].push_back(toMove.back());
        toMove.pop_back();
    }
}

void part1(string filename){
    // 1, 5, 9, 13, 17, ... 
    string line;
    int numCrates, src, dest, numStacks;
    vector<string> splitLine;

    // first get number of stacks
    numStacks = getNumStacks(filename);
    cout << "number of stacks = " << numStacks << endl;

    // array of vector stacks
    vector<string> stacks[numStacks];
    
    ifstream file(filename);
    while (getline(file, line)) {
        if (line.substr(0, 2) == " 1") {
            cout << "end of stacks, assemble" << endl;
            for (const auto &item: stacks) {
                for (int n=0; n<item.size(); n++){
                    cout << item[n];
                }
                cout << endl;
            }
            continue;
            // end of initial stacks layout
        }else if (line.substr(0, 1) != "m") {
            loadStacks(line, stacks);
        }else if (line.length() > 0) {
            tie(numCrates, src, dest) = parseInstruction(line);
            moveCrates(stacks, src, dest, numCrates);
            cout << "moved creates:" << endl;
            for (const auto &item: stacks) {
                for (int n=0; n<item.size(); n++){
                    cout << item[n];
                }
                cout << endl;
            }
        }

    }

    cout << " *** results *** " << endl;
    for (const auto &item: stacks) {
        cout << item.back();
    }
    cout << endl;

}
int main(){
    part1("day5.txt");
}


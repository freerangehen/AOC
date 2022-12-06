#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

using namespace std;

void part1(string filename){
    string line;
    unordered_set<char> distinctChars;
    vector<char> last4;
    
    ifstream file(filename);
    getline(file, line);
    cout << line << endl;
    for (int n=0; n<line.length(); n++){
        if (n >= 4){
            distinctChars.erase(last4.back());
            last4.pop_back();
        }
        last4.insert(last4.begin(), line[n]);
        distinctChars.insert(line[n]);
        for (const auto &item:distinctChars){
            cout << item;
        }
        cout << endl;
        if (distinctChars.size() >= 4) {
            cout << n << endl;
            break;
        }
    }
}


void part2(string filename){
    /* part1 is buggy, it deletes characters in the unique buffer that is inserted after
     * last of the buffer "falls off". here we do a unique computation on the buffer
     * of last 14 characteres instead */
    string line;

    unordered_set<char> distinctChars;
    vector<char> last14;
    
    ifstream file(filename);
    getline(file, line);
    cout << line << endl;
    for (int n=0; n<line.length(); n++){
        if (n >= 14) {
            last14.pop_back();
        }
        last14.insert(last14.begin(), line[n]);

        distinctChars.clear();
        for (const auto &item: last14) {
            distinctChars.insert(item);
        }
        if (distinctChars.size() >= 14) {
            cout << n+1 << endl;
            break;
        }
    }
}


int main(){
    part2("day6Test3.txt");  // 29
    part2("day6Test2.txt");  // 23
    part2("day6Test4.txt");  // 26
    part2("day6.txt");  // ???
}


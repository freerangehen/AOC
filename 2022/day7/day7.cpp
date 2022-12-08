#include <iostream>
#include <ctype.h>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "FileTree.hpp"

using namespace std;

bool greaterThan(int a, int b) {return a<b;}

void part1(string filename){
    string line;
    unordered_set<char> distinctChars;
    vector<string> splitLine;
    FileTree* root = new FileTree("/", 0, nullptr);
    FileTree* currentNode = root;
    string op, arg, fileNodeName;
    int fileSize, requiredSpace;

    vector<int> allSizes;

    ifstream file(filename);
    while (getline(file, line))
    {
        if (line.length() > 0)
        {
            if (isdigit(*line.begin()))
            {  // isdigit(line.substr(0, 1)) does not work ?!
                boost::split(splitLine, line.substr(0, line.length()), boost::is_any_of(" "));
                fileNodeName = splitLine[1];
                fileSize = stoi(splitLine[0]);
                cout << "file " << fileNodeName << " with size " << fileSize << endl;
                currentNode->subfolders.push_back(new FileTree(fileNodeName, fileSize, currentNode));
            } else if (line.substr(0, 1) == "$")
            {
                boost::split(splitLine, line.substr(2, line.length() - 2), boost::is_any_of(" "));
                op = splitLine[0];
                if (op == "cd")
                {
                    arg = splitLine[1];
                    if (arg == "..")
                    {
                        cout << "cd .. back to " << currentNode->parent->name << endl;
                        currentNode = currentNode->parent;
                    } else if (arg == ".")
                    {
                        cout << "cd . do nothing" << endl;
                        // cd . do nothing
                    } else if (arg == "/")
                    {
                        cout << "cd /, we're in " << currentNode->name << endl;
                        // do nothing, keep current node as /
                    }
                    else
                    {// assuming we always ls before cd, and at ls we build the structure
                        cout << "cd into subfolder: " << currentNode->getSubfolder(arg)->name << endl;
                        currentNode = currentNode->getSubfolder(arg);
                    }
                } else if (op == "ls") {
                    cout << "ls: " << line << endl;
                    // do nothing, loop will carry on to ls content
                }
            } else if (line.substr(0, 3) == "dir")
            {
                cout << "found folder " << line << ": ";
                fileNodeName = line.substr(4, line.length() - 4);
                currentNode->subfolders.insert(currentNode->subfolders.begin(), new FileTree(fileNodeName, 0, currentNode));
                cout << fileNodeName << endl;
            }
        }
    }

    cout << root->updateSize() << endl;
    cout << root->calcAllFolderSum(100000) << endl;

    requiredSpace = 30000000 - (70000000 - root->size);
    cout << "required to delete " << requiredSpace << endl;

    allSizes = root->getAllFolderSizes();
    sort(allSizes.begin(), allSizes.end(), greaterThan);
    for (const auto &item:allSizes) {cout << item << ", ";}; cout << endl;

    for (const auto &item:allSizes) 
    {
        if (item > requiredSpace)
        {

            cout << "minimum abouve threshold " << requiredSpace << " is " << item << endl;
            break;
        }
    }
}



int main(){
    // part1("day7Test.txt");
    part1("day7.txt");
}


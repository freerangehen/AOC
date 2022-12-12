#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Location
{
    int x;
    int y;
};

Location makeLocation(int x, int y)
{
    Location location;
    location.x = x;
    location.y = y;
    return location;
}

bool canMove(int srcX, int srcY, int destX, int destY, vector<vector<int>> elevation)
{
    bool result;
    if ((destX >= elevation[0].size()) || (destX < 0) || (destY >= elevation.size()) || (destY <0))
    {
        result = false;
    } else
    {
        result = elevation[srcY][srcX] + 1 >= elevation[destY][destX];
    }

    return result;

}


void printElevation(vector<vector<int>> elevation)
{
    for (int i=0; i < elevation.size(); i++)
    {
        for (int j=0; j< elevation[i].size(); j++)
        {
            if (elevation[i][j] < 10)
            {
                cout << elevation[i][j] << "  ";
            }
            else 
            {
                cout << elevation[i][j] << " ";
            }
        }
        cout << endl;
    }
}


int findMinSteps(int startX, int startY, int endX, int endY, vector<vector<int>> elevation)
{
    vector<Location> currentQueue;
    vector<vector<bool>> visitedArray;

    for (const auto& row: elevation)
    {
        vector<bool> visitedRow(row.size(), false);
        visitedArray.push_back(visitedRow);
    }

    Location location = makeLocation(startX, startY);

    int currentStep = 0;
    currentQueue.push_back(location);
    currentStep += 1;

    while (currentStep < elevation[0].size() * elevation.size())
    {
        vector<Location> nextQueue;
        for (const auto& item: currentQueue)
        {
            if (canMove(item.x, item.y, item.x + 1, item.y, elevation) && (!visitedArray[item.y][item.x + 1]))
            {
                if (((item.x + 1) == endX) && (item.y == endY)) { return currentStep;} //cout << "took " << currentStep << " steps" << endl; return currentStep; }
                nextQueue.push_back(makeLocation(item.x + 1, item.y));
                visitedArray[item.y][item.x + 1] = true;
            }
            if (canMove(item.x, item.y, item.x - 1, item.y, elevation) && (!visitedArray[item.y][item.x - 1]))
            {
                if (((item.x - 1) == endX) && (item.y == endY)) { return currentStep;} //cout << "took " << currentStep << " steps" << endl; return currentStep; }
                nextQueue.push_back(makeLocation(item.x - 1, item.y));
                visitedArray[item.y][item.x - 1] = true;;
            }
            if (canMove(item.x, item.y, item.x, item.y + 1, elevation) && (!visitedArray[item.y+1][item.x]))
            {
                if ((item.x == endX) && ((item.y + 1) == endY)) { return currentStep;} // cout << "took " << currentStep << " steps" << endl; return currentStep; }
                nextQueue.push_back(makeLocation(item.x, item.y + 1));
                visitedArray[item.y + 1][item.x] = true;
            }
            if (canMove(item.x, item.y, item.x, item.y - 1, elevation) && (!visitedArray[item.y-1][item.x]))
            {
                if ((item.x == endX) && ((item.y - 1) == endY)) { return currentStep;} // cout << "took " << currentStep << " steps" << endl; return currentStep; }
                nextQueue.push_back(makeLocation(item.x, item.y - 1));
                visitedArray[item.y - 1][item.x] = true;
            }

        }
        currentStep += 1;
        currentQueue = nextQueue;
        // cout << "finished step " << currentStep << " with " << currentQueue.size() << " in queue" << endl;
        if (currentQueue.size() == 0) {currentStep;}
    }
    return INT_MAX;
}

void part1(string filename){
    string line, instruction, stringArgument;
	vector<vector<int>> elevation;

    int startX, startY, endX, endY;
    char eleChar;
    int lineCount = 0;

    ifstream file(filename);
    while (getline(file, line))
    {
        vector<int> row(line.length(), -1);
        for (int i=0; i<line.length(); i++)
        {
            eleChar = line[i];
            if (eleChar == 'S')
            {
                startX = i;
                startY = lineCount;
                eleChar = 'a';
            }
            if (eleChar == 'E')
            {
                endX = i;
                endY = lineCount;
                eleChar = 'z';
            }
            row[i] = ((int) eleChar) - 97;
        } 
        elevation.push_back(row);
        lineCount += 1;
    }

    printElevation(elevation);

    cout << "took " << findMinSteps(startX, startY, endX, endY, elevation) << " steps" << endl;

}


void part2(string filename){
    string line, instruction, stringArgument;
	vector<vector<int>> elevation;
    vector<Location> candidates;

    int endX, endY;
    char eleChar;
    int lineCount = 0;

    ifstream file(filename);
    while (getline(file, line))
    {
        vector<int> row(line.length(), -1);
        for (int i=0; i<line.length(); i++)
        {
            eleChar = line[i];
            if (eleChar == 'S')
            {
                eleChar = 'a';
            }
            if (eleChar == 'E')
            {
                endX = i;
                endY = lineCount;
                eleChar = 'z';
            }
            if (eleChar == 'a')
            {
                candidates.push_back(makeLocation(i, lineCount));
            }
            row[i] = ((int) eleChar) - 97;
        } 
        elevation.push_back(row);
        lineCount += 1;
    }

    printElevation(elevation);

    int minSteps = INT_MAX;
    int tempResult;
    int trialCount = 1;
    cout << candidates.size() << " candidates" << endl;
    for (const auto& item: candidates)
    {
        cout << "trying candidate (" << item.x << "," << item.y << ")" << " trial " << trialCount << "/" << candidates.size() << endl;
        tempResult = findMinSteps(item.x, item.y, endX, endY, elevation);
        if (tempResult < minSteps)
        {
            minSteps = tempResult;
        }
        trialCount += 1;
    } 
    cout << "minSteps = " << minSteps << endl;
}
int main(){
    part2("day12.txt");
}


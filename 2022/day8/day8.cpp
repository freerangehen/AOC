#include <iostream>
#include <ctype.h>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

int countNumTreesInView(vector<vector<int>> matrix, int treeRowNo, int treeColumnNo)
{
    int rightCount = 0;
    int leftCount = 0;
    int upCount = 0;
    int downCount = 0;

    int treeHeight = matrix[treeRowNo][treeColumnNo];
    // search right
    for (int columnNo=treeColumnNo; columnNo<matrix[0].size(); columnNo++)
    {
        if ((columnNo != treeColumnNo) && (treeHeight <= matrix[treeRowNo][columnNo]))
        {
            break;
        }
        if (columnNo != matrix[0].size() - 1)
        {
            rightCount += 1;
        }
    }
    cout << "right count = " << rightCount << endl;
    // search left
    for (int columnNo=treeColumnNo; columnNo>=0; columnNo--)
    {
        if ((columnNo != treeColumnNo) && (treeHeight <= matrix[treeRowNo][columnNo]))
        {
            break;
        }
        if (columnNo != 0)
        {
            leftCount += 1;
        }
    }
    cout << "left count = " << leftCount << endl;

    // search down
    for (int rowNo=treeRowNo; rowNo<matrix.size(); rowNo++)
    {
        if ((rowNo != treeRowNo) && (treeHeight <= matrix[rowNo][treeColumnNo]))
        {
            break;
        }
        if (rowNo != matrix.size() - 1)
        {
            downCount += 1;
        }
    }
    cout << "down count = " << downCount << endl;

    // search up
    for (int rowNo=treeRowNo; rowNo>= 0; rowNo--)
    {
        if ((rowNo != treeRowNo) && (treeHeight <= matrix[rowNo][treeColumnNo]))
        {
            break;
        }
        if (rowNo != 0)
        {
            upCount += 1;
        }
    }
    cout << "up count = " << upCount << endl;

    cout << "scenic score = " << leftCount * rightCount * downCount * upCount << endl;;
    return leftCount * rightCount * downCount * upCount;
}


vector<vector<bool>> setVisibleFromLeft(vector<vector<int>> matrix)
{
    int maxSoFar = -1;
    vector<vector<bool>> visibleIndicatorMatrix;

    for (const auto &row:matrix)
    {
        maxSoFar = -1;
        vector<bool> visibleIndicatorRow(row.size(), false);
        for (int i=0; i<row.size(); i++)
        {
            if (row[i] > maxSoFar)
            {
                visibleIndicatorRow[i] = true;
                maxSoFar = row[i];
            }
        }
        visibleIndicatorMatrix.push_back(visibleIndicatorRow);
    }
    return visibleIndicatorMatrix;
}


vector<vector<bool>> setVisibleFromRight(vector<vector<int>> matrix)
{
    int maxSoFar = -1;
    vector<vector<bool>> visibleIndicatorMatrix;

    for (const auto &row:matrix)
    {
        maxSoFar = -1;
        vector<bool> visibleIndicatorRow(row.size(), false);
        for (int i=row.size() - 1; i>=0; i--)
        {
            if (row[i] > maxSoFar)
            {
                visibleIndicatorRow[i] = true;
                maxSoFar = row[i];
            }
        }
        visibleIndicatorMatrix.push_back(visibleIndicatorRow);
    }
    return visibleIndicatorMatrix;
}


vector<vector<bool>> setVisibleFromUp(vector<vector<int>> matrix)
{
    int maxSoFar = -1;
    vector<vector<bool>> visibleIndicatorMatrix(matrix.size());

    for (int columnNo=0; columnNo<matrix[0].size(); columnNo++)
    {
        maxSoFar = -1;
        vector<bool> visibleIndicatorColumn(matrix.size(), false);
        for (int rowNo=0; rowNo<matrix.size(); rowNo++)
        {
            if (matrix[rowNo][columnNo] > maxSoFar)
            {
                visibleIndicatorColumn[rowNo] = true;
                maxSoFar = matrix[rowNo][columnNo];
            }
        }
        for (int k=0; k<visibleIndicatorColumn.size(); k++)
        {
            visibleIndicatorMatrix[k].push_back(visibleIndicatorColumn[k]);
        }
    }
    return visibleIndicatorMatrix;
}


vector<vector<bool>> setVisibleFromDown(vector<vector<int>> matrix)
{
    int maxSoFar = -1;
    vector<vector<bool>> visibleIndicatorMatrix(matrix.size());

    for (int columnNo=0; columnNo<matrix[0].size(); columnNo++)
    {
        maxSoFar = -1;
        vector<bool> visibleIndicatorColumn(matrix.size(), false);
        for (int rowNo=matrix.size() - 1; rowNo>=0; rowNo--)
        {
            if (matrix[rowNo][columnNo] > maxSoFar)
            {
                visibleIndicatorColumn[rowNo] = true;
                maxSoFar = matrix[rowNo][columnNo];
            }
        }
        for (int k=0; k<visibleIndicatorColumn.size(); k++)
        {
            visibleIndicatorMatrix[k].push_back(visibleIndicatorColumn[k]);
        }
    }
    return visibleIndicatorMatrix;
}


vector<vector<int>> readFile(string filename)
{
    vector<vector<int>> array;
    string line;
    ifstream file(filename);
    while (getline(file, line))
    {
        vector<int> row(line.length(), 0);
        for (int i=0; i<line.length(); i++)
        {
            row[i] = stoi(line.substr(i, 1));
        }
        array.push_back(row);    
    }
    return array; 
}


void part1(string filename){
    vector<vector<int>> array;
    vector<vector<bool>> visibleFromLeft, visibleFromUp, visibleFromRight, visibleFromDown;
    int countTotal = 0;
    int maxScore = 0;
    int treeScore = 0;

    array = readFile(filename);

    for (int i=0; i<array.size(); i++) {for (int j=0; j<array[i].size(); j++) {cout << array[i][j] << " ";} cout << endl;}

    visibleFromLeft = setVisibleFromLeft(array); 
    cout << endl << "from left" << endl;
    for (int i=0; i<visibleFromLeft.size(); i++) {for (int j=0; j<visibleFromLeft[i].size(); j++) {cout << visibleFromLeft[i][j] << " ";} cout << endl;}

    visibleFromRight = setVisibleFromRight(array);
    cout << endl << "from right" << endl;
    for (int i=0; i<visibleFromRight.size(); i++) {for (int j=0; j<visibleFromRight[i].size(); j++) {cout << visibleFromRight[i][j] << " ";} cout << endl;}

    visibleFromUp = setVisibleFromUp(array);
    cout << endl << "from up" << endl;
    for (int i=0; i<visibleFromUp.size(); i++) {for (int j=0; j<visibleFromUp[i].size(); j++) {cout << visibleFromUp[i][j] << " ";} cout << endl;}

    visibleFromDown = setVisibleFromDown(array);
    cout << endl << "from down" << endl;
    for (int i=0; i<visibleFromDown.size(); i++) {for (int j=0; j<visibleFromDown[i].size(); j++) {cout << visibleFromDown[i][j] << " ";} cout << endl;}



    for (int i=0; i<array.size(); i++)
    {
        for (int j=0; j<array[0].size(); j++)
        {
            if (visibleFromLeft[i][j] || visibleFromRight[i][j] || visibleFromUp[i][j] || visibleFromDown[i][j])
            {
                countTotal += 1;
                cout << ">>> [" << i << "]" << "[" << j << "]" << " = " << array[i][j] << endl;
                treeScore = countNumTreesInView(array, i, j);
                if (treeScore >= maxScore){
                    maxScore = treeScore;
                }
            }
        }
    }
    cout << "total visible = " << countTotal << endl;
    cout << "max scenic score = " << maxScore << endl;;

}



int main(){
    //part1("day8Test.txt");
    part1("day8.txt");
}


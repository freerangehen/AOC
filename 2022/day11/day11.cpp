#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cmath>

using namespace std;

// unordersed_set<setElementType, hashFunctionReturnType>

float reduceWorry(float worry, bool part1, int mod)
{
    mod = 17 * 13 * 19 * 23;
    if (part1) 
    { 
        worry = (float) std::floor(worry / 3);
    }else
    {
        worry = (float)((int) worry % mod);
    }
    return worry;
}

void simulate(bool part1){
    int nMonkeys = 8;
    int nRounds;

    if (part1)
    {
        nRounds = 20;
    }else
    {
        nRounds = 10000;
    }

    float worry;
    vector<vector<float>> monkeyItems {
        {98, 70, 75, 80, 84, 89, 55, 98},
        {59},
        {77, 95, 54, 65, 89},
        {71, 64, 75},
        {74, 55, 87, 98},
        {90, 98, 85, 52, 91, 60},
        {99, 51},
        {98, 94, 59, 76, 51, 65, 75}
    };
    int inspectCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int roundNo=1; roundNo <= nRounds; roundNo++)
    {
        cout << "simulate round " << roundNo << endl;
        for (int monkeyNo=0; monkeyNo < nMonkeys; monkeyNo++)
        {
            inspectCount[monkeyNo] += monkeyItems[monkeyNo].size();
            vector<float>::iterator item = monkeyItems[monkeyNo].begin();
            switch(monkeyNo)
            {
                case 0:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item * 2;
                        worry = reduceWorry(worry, part1, 11);
                        if (((int)worry % 11) == 0)
                        {
                            monkeyItems[1].push_back(worry);
                        }else
                        {
                            monkeyItems[4].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 1:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item * *item;
                        worry = reduceWorry(worry, part1, 19);
                        if (((int)worry % 19) == 0)
                        {
                            monkeyItems[7].push_back(worry);
                        }else
                        {
                            monkeyItems[3].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 2:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 6;
                        worry = reduceWorry(worry, part1, 7);
                        if (((int)worry % 7) == 0)
                        {
                            monkeyItems[0].push_back(worry);
                        }else
                        {
                            monkeyItems[5].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 3:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 2;
                        worry = reduceWorry(worry, part1, 17);
                        if (((int)worry % 17) == 0)
                        {
                            monkeyItems[6].push_back(worry);
                        }else
                        {
                            monkeyItems[2].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 4:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item * 11;
                        worry = reduceWorry(worry, part1, 3);
                        if (((int)worry % 3) == 0)
                        {
                            monkeyItems[1].push_back(worry);
                        }else
                        {
                            monkeyItems[7].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 5:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 7;
                        worry = reduceWorry(worry, part1, 5);
                        if (((int)worry % 5) == 0)
                        {
                            monkeyItems[0].push_back(worry);
                        }else
                        {
                            monkeyItems[4].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 6:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 1;
                        worry = reduceWorry(worry, part1, 13);
                        if (((int)worry % 13) == 0)
                        {
                            monkeyItems[5].push_back(worry);
                        }else
                        {
                            monkeyItems[2].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 7:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 5;
                        worry = reduceWorry(worry, part1, 2);
                        if (((int)worry % 2) == 0)
                        {
                            monkeyItems[3].push_back(worry);
                        }else
                        {
                            monkeyItems[6].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
            }
        }
        cout << "after round " << roundNo << endl;
        for (int i=0; i<monkeyItems.size(); i++)
        {
            cout << "monkey[" << i << "] = {";
            for (const auto& monkeyItem: monkeyItems[i]){cout << monkeyItem << ", ";}
            cout << endl;
        }
    }
    cout << "monkey inspection count: " << endl;
    for (const auto& item: inspectCount) { cout << item << ", ";}
    cout << endl;

}


void simulateTest(bool part1){
    int nMonkeys = 4;
    int nRounds;

    int inspectCount[4] = {0, 0, 0, 0};
    if (part1)
    {
        nRounds=20;
    }else
    {
        nRounds=10000;
    }
    nRounds = 20;
    float worry;
    vector<vector<float>> monkeyItems {
        {79, 98},
        {54, 65, 75, 74},
        {79, 60, 97},
        {74}
    };


    for (int roundNo=1; roundNo <= nRounds; roundNo++)
    {
        for (int monkeyNo=0; monkeyNo <= nMonkeys; monkeyNo++)
        {
            inspectCount[monkeyNo] += monkeyItems[monkeyNo].size();
            vector<float>::iterator item = monkeyItems[monkeyNo].begin();
            switch(monkeyNo)
            {
                case 0:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item * 19;
                        worry = reduceWorry(worry, part1, 23);
                        if (((int)worry % 23) == 0)
                        {
                            monkeyItems[2].push_back(worry);
                        }else
                        {
                            monkeyItems[3].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 1:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 6;
                        worry = reduceWorry(worry, part1, 19);
                        if (((int)worry % 19) == 0)
                        {
                            monkeyItems[2].push_back(worry);
                        }else
                        {
                            monkeyItems[0].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 2:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item * *item;
                        worry = reduceWorry(worry, part1, 13);
                        if (((int)worry % 13) == 0)
                        {
                            monkeyItems[1].push_back(worry);
                        }else
                        {
                            monkeyItems[3].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
                case 3:
                    while (item != monkeyItems[monkeyNo].end())
                    {
                        worry = *item + 3;
                        worry = reduceWorry(worry, part1, 17);
                        if (((int)worry % 17) == 0)
                        {
                            monkeyItems[0].push_back(worry);
                        }else
                        {
                            monkeyItems[1].push_back(worry);
                        }
                        monkeyItems[monkeyNo].erase(item);
                    }
                    break;
            }
        }
        if (true) //(roundNo == 1) || (roundNo == 20) || (roundNo == 1000) || (roundNo == 2000))
        {
            cout << "after round " << roundNo << endl;
            /*
            for (int i=0; i<monkeyItems.size(); i++)
            {
                cout << "monkey[" << i << "] = {";
                for (const auto& monkeyItem: monkeyItems[i]){cout << monkeyItem << ", ";}
                cout << endl;
            }
            */
            cout << "monkey inspection count: " << endl;
            for (const auto& item: inspectCount) { cout << item << ", ";}
            cout << endl;
        }
    }
    cout << "monkey inspection count: " << endl;
    for (const auto& item: inspectCount) { cout << item << ", ";}
    cout << endl;
}


int main(){
   //  simulate(false);
   simulateTest(false);
}


#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;


struct Packet
{
    int number = -1;
    vector<Packet> contents;
};

bool isList(Packet packet)
{
    return packet.contents.size() >= 1;
}

bool isInt(Packet packet)
{
    return (packet.number != -1);
}

bool isEmpty(Packet packet)
{
    return ((packet.contents.size()) == 0 && (packet.number == -1));
}


void printPacket(Packet packet)
{
    if (isInt(packet))
    {
        cout << " " << packet.number << " ";
    } else
    {
        for (int i=0; i < packet.contents.size(); i++)
        {
            if (!isInt(packet.contents[i]))
            {
                cout << " [ ";
            }
            printPacket(packet.contents[i]);
            if (!isInt(packet.contents[i]))
            {
                cout << " ] ";
            }
        }
    }
}

char comparePackets(Packet left, Packet right)
{
    // one or both empty, non ints
    if (!isInt(left) && !isList(left) && !isInt(right) && !isList(right)) {return '=';}
    if (!isInt(left) && !isList(left)) {return '<';}
    if (!isInt(right) && !isList(right)) {return '>';}

    // both int
    if ((isInt(left)) && (isInt(right)))
    {
        if (left.number < right.number) {return '<';}
        if (left.number == right.number) {return '=';}
        if (left.number > right.number) {return '>';}
    }

    // both list
    if ((isList(left)) && (isList(right)))
    {
        int limit = min(left.contents.size(), right.contents.size());
        for (int i=0; i<limit; i++)
        {
            char compResult = comparePackets(left.contents[i], right.contents[i]);
            if (compResult != '=')
            {
                return compResult;
            }
        }
        // been always '=' above, consider list size
        if (left.contents.size() == right.contents.size()) {return '=';} 
        if (left.contents.size() < right.contents.size()) {return '<';} 
        if (left.contents.size() > right.contents.size()) {return '>';} 
    }

    // one list, one int
    if ((isList(left)) && (isInt(right)))
    {
        Packet rightList = Packet();
        rightList.contents.push_back(right);
        return comparePackets(left, rightList); 
    }
    if ((isInt(left)) && (isList(right)))
    {
        Packet leftList = Packet();
        leftList.contents.push_back(left);
        return comparePackets(leftList, right); 
    }

}

bool isLessThan(Packet left, Packet right)
{
    return (comparePackets(left, right) == '<');
}

Packet createPacket(string packetString)
{
    vector<Packet> stack;
    Packet currentPacket = Packet();

    int idx = 0;
    while (idx < packetString.length())
    {
        char eachChar = packetString[idx];
        if (eachChar == '[')
        {
            // push current packet to top of stack and start a new packet
            stack.push_back(currentPacket);
            currentPacket = Packet(); 
            idx += 1;
        }
        else if (eachChar == ']')
        {
            // add current packet to contents of top of stack and pop stack to be current packet
            if (stack.size() > 0){
                stack.back().contents.push_back(currentPacket);
                currentPacket = stack.back();
                stack.pop_back();
                idx += 1;
            }
        }
        else if (eachChar == ',')
        {
            idx += 1;
        }
        else
        {
            // a number, or left most digit of a number
            Packet numberPacket = Packet();
            int numberLength = 1;
            for (int i=idx; i<packetString.length(); i++)
            {
                if ((packetString[i] == ']') || (packetString[i] == '[') || (packetString[i] == ',')) {break;}
                numberLength += 1;
            }
            numberPacket.number = stoi(packetString.substr(idx, numberLength));
            currentPacket.contents.push_back(numberPacket);
            idx += 1;
        }

    }
    // cout << "length of stack = " << stack.size() << endl;
    return currentPacket.contents[0];
} 


bool isDivider(Packet packet)
{
    /*
    cout << "inspecting packet.number = " << packet.number << ", packet.contents.size() = " << packet.contents.size() << endl;
    if (packet.contents.size() == 1)
    {
        cout << "single content packet, packet.contents[0].number = " << packet.contents[0].number << endl;
        if (packet.contents[0].contents.size() == 1)
        {
            cout << "single content packet, packet.contents[0].contents[0].number = " << packet.contents[0].contents[0].number << endl;
        }
    }
    */
    if ((isInt(packet)) || (packet.contents.size() == 0)) {return false;}

    if ((packet.contents.size() == 1) && (packet.contents[0].contents.size() == 1) && (packet.contents[0].contents[0].number == 2))
    {
        return true;
    }
    if ((packet.contents.size() == 1) && (packet.contents[0].contents.size() == 1) && (packet.contents[0].contents[0].number == 6))
    {
        return true;
    }

    return false;
}


void part2(string filename){
    string line, instruction, stringArgument;
    int rowCount = 0;

    vector<Packet> allPackets;

    ifstream file(filename);
    while (getline(file, line))
    {
        if (line.length() == 0)
        {
            // empty line
            continue;
        }
        allPackets.push_back(createPacket(line));
    }

    cout << " read " << allPackets.size() << " packets" << endl;

    
    sort(allPackets.begin(), allPackets.end(), isLessThan);
    cout << "afer sorting" << endl;
    for (int i=0; i<allPackets.size(); i++)
    {
        /*
        printPacket(allPackets[i]);
        cout <<  endl;
        */
        if (isDivider(allPackets[i]))
        {
            cout << "divider detected at index " << i + 1 << endl;
        }

    }
}



void part1(string filename){
    string line, instruction, stringArgument;
    vector<vector<Packet>> packetPairs; 
    int rowCount = 0;

    vector<Packet> eachPair;

    ifstream file(filename);
    while (getline(file, line))
    {
        if (line.length() == 0)
        {
            // empty line
            continue;
        }

        if (rowCount % 2 == 0)
        {
            eachPair.push_back(createPacket(line));
        }else
        {
            eachPair.push_back(createPacket(line));
            packetPairs.push_back(eachPair);
            eachPair.clear();
        }
        rowCount += 1;
    }

    cout << " read " << packetPairs.size() << " pairs" << endl;

    int indexSum = 0;
    for (int i=0; i < packetPairs.size(); i++)  //const auto& eachPair: packetPairs)
    {
        vector<Packet> eachPair = packetPairs[i];
        cout << "pair [" << i + 1 << "]" << endl;
        printPacket(eachPair[0]);
        cout << " vs ";
        printPacket(eachPair[1]);
        cout << endl;
        if (comparePackets(eachPair[0], eachPair[1]) == '<')
        {
            indexSum += (i + 1);
            cout << ">>> right order" << endl;
        }
        /*
        cout << "compare results: " ;
        cout << comparePackets(eachPair[0].contents[0], eachPair[1].contents[0]);
        cout << endl;
        cout << endl;
        */
    }
    cout << "index sum = " << indexSum << endl;
    
}


int main(){
    // part1("day13Test.txt");
    part2("day13.txt");
}


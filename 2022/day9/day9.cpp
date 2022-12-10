#include <iostream>
#include <ctype.h>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Coordinate{
	int x;
	int y;

};

// == needed for hashing, cannot be member of Coordinate
bool operator==(Coordinate const& lhs, Coordinate const& rhs)
{
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}


// struct wrapper for type of hash function
struct Hash
{
	size_t operator() (const Coordinate& coordinate) const
	{
		return (std::hash<int>()(coordinate.x) * 63 + std::hash<int>()(coordinate.y));
	}
};

// unordersed_set<setElementType, hashFunctionReturnType>

void moveTail(Coordinate& head, Coordinate& tail)
{
	int xDiff, yDiff;

	xDiff = head.x - tail.x;
	yDiff = head.y - tail.y;

	/* immediately 2 steps away left/right/up/down */
	if (xDiff == 0)
	{
		if (yDiff == 2){ tail.y += 1; return; }
		if (yDiff == -2){ tail.y -= 1; return;}
	}
	if (yDiff == 0)
	{
		if (xDiff == 2) {tail.x += 1; return;}
		if (xDiff == -2){tail.x -= 1; return;}
	}
	/* diagonal 2 steps away */
	if ((xDiff == 2) && (yDiff == 2)) {tail.x += 1; tail.y += 1; return;}
	if ((xDiff == -2) && (yDiff == -2)) {tail.x -= 1; tail.y -= 1; return;}
	if ((xDiff == 2) && (yDiff == -2)) {tail.x += 1; tail.y -= 1; return;}
	if ((xDiff == -2) && (yDiff == 2)) {tail.x -= 1; tail.y += 1; return;}

	/* "knight" moves */
	if ((xDiff == 2) && (yDiff == 1)) {tail.x += 1; tail.y += 1; return;}
	if ((xDiff == 1) && (yDiff == 2)) {tail.x += 1; tail.y += 1; return;}
	if ((xDiff == -2) && (yDiff == -1)) {tail.x -= 1; tail.y -= 1; return;}
	if ((xDiff == -1) && (yDiff == -2)) {tail.x -= 1; tail.y -= 1; return;}
	if ((xDiff == 2) && (yDiff == -1)) {tail.x += 1; tail.y -= 1; return;}
	if ((xDiff == -1) && (yDiff == 2)) {tail.x -= 1; tail.y += 1; return;}
	if ((xDiff == -2) && (yDiff == 1)) {tail.x -= 1; tail.y += 1; return;}
	if ((xDiff == 1) && (yDiff == -2)) {tail.x += 1; tail.y -= 1; return;}
}


void makeMove(Coordinate& input, char direction, int nMoves)
{
	switch (direction) 
	{
		case 'L':
		{
			input.x -= nMoves;
			break;
		};
		case 'R':
		{
			input.x += nMoves;
			break;
		};
		case 'U':
		{
			input.y += nMoves;
			break;
		};
		case 'D':
		{
			input.y -= nMoves;
			break;
		};
	}		
}


void part2(string filename){
    string line;
	char direction;
	int nMoves;

	int TAIL=9;
	int HEAD=0;
	vector<string> splitLine;
	Coordinate coordinates[10]; // [0] is head, [9] is tail
	unordered_set<Coordinate, Hash> visitedCoordinates;

	for (auto& item: coordinates) {item.x=0; item.y=0;}

	visitedCoordinates.insert(coordinates[TAIL]);

    ifstream file(filename);
    while (getline(file, line))
    {
        boost::split(splitLine, line, boost::is_any_of(" "));
		direction = line[0];
		nMoves = stoi(splitLine[1]);

		cout << "move " << direction << " by " << nMoves << endl;
		for (int i=0; i<nMoves; i++)
		{
			makeMove(coordinates[0], direction, 1);
			for (int j=1; j<10; j++)
			{
				moveTail(coordinates[j-1], coordinates[j]);
			}
			visitedCoordinates.insert(coordinates[TAIL]);
		}
    }
	visitedCoordinates.insert(coordinates[TAIL]);
	cout << visitedCoordinates.size() << endl;
}


void part1(string filename){
    string line;
	char direction;
	int nMoves;
	vector<string> splitLine;
	Coordinate head, tail;
	unordered_set<Coordinate, Hash> visitedCoordinates;

	head.x = 0;
	head.y = 0;
	tail.x = 0;
	tail.y = 0;

	visitedCoordinates.insert(tail);

    ifstream file(filename);
    while (getline(file, line))
    {
        boost::split(splitLine, line, boost::is_any_of(" "));
		direction = line[0];
		nMoves = stoi(splitLine[1]);

		cout << "move " << direction << " by " << nMoves << endl;
		for (int i=0; i<nMoves; i++)
		{
			makeMove(head, direction, 1);
			cout << "head is at (" << head.x << ", " << head.y << ")" << " and ";
			moveTail(head, tail);
			visitedCoordinates.insert(tail);
			cout << "tail is at (" << tail.x << ", " << tail.y << ")" << endl;
		}
    }
	visitedCoordinates.insert(tail);
	cout << visitedCoordinates.size() << endl;
}


int main(){
    part2("day9.txt");
}


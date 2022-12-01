#ifndef TopThree_HPP
#define TopThree_HPP

using namespace std;

class TopThree
{
    int topThree[3];
    const int SMALLEST = 0;
    const int LARGEST = 2;

    public:
        TopThree();
        void update(int x);
        int sum();
};


#endif


















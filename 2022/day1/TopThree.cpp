#include "TopThree.hpp"

TopThree::TopThree()
{
    topThree[0] = 0; 
    topThree[1] = 0; 
    topThree[2] = 0; 
}

void TopThree::update(int x)
{
    if (x > topThree[0]) {
        topThree[2] = topThree[1];
        topThree[1] = topThree[0];
        topThree[0] = x;
        return;
    }

    if (x < topThree[0] && x > topThree[1]) {
        topThree[2] = topThree[1];
        topThree[1] = x;
        return;
    }

    if (x > topThree[2]){
        topThree[2] = x;
        return;
    }

}

int TopThree::sum()
{
    return topThree[0] + topThree[1] + topThree[2];
}











































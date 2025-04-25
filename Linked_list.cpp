#include <iostream>
#include "Link_list.h"

int main() {
    DoubleList<int> lst;
    for (int i = 0; i < 6; i++)
    {
        lst.PushBack(i);
    }
    lst.FOut();
    return 0;
}
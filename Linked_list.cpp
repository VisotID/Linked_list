// Высоцкая И.Д.
#include <iostream>
#include "Link_list.h"

int main() {
    test();
    DoubleList<int> lst;
    for (int i = 0; i < 6; i++)
    {
        lst.PushBack(i);
        cout << lst[i];
    }
    
    return 0;
}
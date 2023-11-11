#include <iostream>
#include <vector>
#include <set>


int main()
{
    std::vector<std::set<int>> test (7);
    test[1].insert(5);
    std::cout << test[1].empty();

}
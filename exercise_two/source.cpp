#include <iostream>
#include <string>
#include "PopMap.h"

int main(int argc, char const *argv[])
{
    PopMap<int, std::string> _popMap("C:/Users/jesus/GitHub/Binary-Search-Tree/popSmall.txt");

    std::cout << "Author: Jesus Rodriguez-Luna" << std::endl << std::endl;

    //List all records
    _popMap.print();

    //Search for 6037 and 6000
    std::cout << std::endl;
    _popMap.find(6037);
    _popMap.find(6000);

    //insert
    _popMap.insert(6066, "1, New County, CA");
    _popMap.insert(6065, "2000, Riverside, CA");

    //delete
    _popMap.erase(6999);
    _popMap.erase(6075);
    _popMap.erase(6055);

    //List all records
    std::cout << std::endl;
    _popMap.print();

    return 0;
}

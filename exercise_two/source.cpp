#include <iostream>
#include <string>
#include <fstream>
#include "PopMap.h"

int main(int argc, char const *argv[])
{
    PopMap<int, std::string> _popMap("C:/Users/jesus/Documents/GitHub/Binary-Search-Tree/popSmall.txt");
    
    //Test
    _popMap.print();

    return 0;
}

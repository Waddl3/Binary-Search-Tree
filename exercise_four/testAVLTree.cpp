#include <iostream>
#include "BetterPopMap.h"

int main(int argc, char const *argv[])
{
    BetterPopMap<int, std::string> BPM("C:/Users/jesus/GitHub/Binary-Search-Tree/popSmall.txt");
    
    std::cout << "Author: Jesus Rodriguez-Luna" << std::endl << std::endl;

    //List all records
    BPM.print();

    //Search for 6037 and 6000
    std::cout << std::endl;
    BPM.find(6037);
    BPM.find(6000);

    //insert
    BPM.insert(6066, "1, New County, CA");
    BPM.insert(6065, "2000, Riverside, CA");

    //delete
    BPM.erase(6999);
    BPM.erase(6075);
    BPM.erase(6055);

    //List all records
    std::cout << std::endl;
    BPM.print();

    return 0;
}

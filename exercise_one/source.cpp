#include <iostream>
#include <string>
#include "bst.h"
#include "Entry.h"

int main(int argc, char const *argv[])
{
    SearchTree<Entry<int, std::string>> st;

    //Question 1 operations
    st.insert(10, "Avalon");
    st.insert(20, "BMW");
    st.insert(4, "Camaro");
    st.insert(8, "Dodge");
    st.insert(15, "EV");
    st.erase(8);
    st.erase(10);

    SearchTree<Entry<int, std::string>>::Iterator p = st.begin();

    //Search for...
    p = st.find(15);
    std::cout << (*p).key() << " " << (*p).value() << std::endl;

    p = st.find(30);
    std::cout << (*p).key() << " " << (*p).value() << std::endl;
    
    p = st.find(8);
    std::cout << (*p).key() << " " << (*p).value() << std::endl;
    
    //Print BST
    p = st.begin();
    while(!(p == st.end())){
        std::cout << (*p).key() << " " << (*p).value() << std::endl;
        ++p;
    }
    

    return 0;
}

// Created for CSCI 220 Fall 21
#include <iostream>
#include <string>
#include "Entry.h"
#include "AVLEntry.h"
#include "AVLTree1.h"

using namespace std;

int main()
{
	AVLTree<AVLEntry<Entry<int, string>>> myTree;
	AVLTree<AVLEntry<Entry<int, string>>>::Iterator iter(NULL);

	std::cout << "Author: Jesus Rodriguez-Luna" << std::endl << std::endl;

	//Question 1 operations
    myTree.insert(10, "Avalon");
    myTree.insert(20, "BMW");
    myTree.insert(4, "Camaro");
    myTree.insert(8, "Dodge");
    myTree.insert(15, "EV");
    myTree.erase(8);
    myTree.erase(10);

	//find operation
	auto p = myTree.find(15);
	std::cout << (*p).key() << ", " << (*p).value() << std::endl;
	p = myTree.find(30);
	std::cout << (*p).key() << ", " << (*p).value() << std::endl;
	p = myTree.find(8);
	std::cout << (*p).key() << ", " << (*p).value() << std::endl;

	//print tree
	p = myTree.begin();
	while(!(p == myTree.end())) {
		std::cout << (*p).key() << ", " << (*p).value() << std::endl;
		++p;
	}

	return 0;
}
#ifndef BETTER_POP_MAP_H
#define BETTER_POP_MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "AVLTree1.h"
#include "Entry.h"
#include "RuntimeExceptions.h"

template <typename K, typename V>
class BetterPopMap {
private:
    AVLTree<AVLEntry<Entry<K, V>>> T;

public:
    //constructor
    BetterPopMap(const std::string& filename) {
        std::ifstream file(filename);
        if(file.is_open()) {
            std::string line;
            while(std::getline(file, line)) {
                std::stringstream ss(line);
                std::string countyCode, value;
                
                //Read the first field as an integer
                if(std::getline(ss, countyCode, ',')) { 
                    int key = std::stoi(countyCode);

                    // Read the rest of the line
                    if(std::getline(ss, value)) {

                        //store it into the BST
                        T.insert(key, value);
                    }
                }
            }
        }
        else {
            std::cout << "Not open" << std::endl;
        }
    }

    // print appropriate message and data if found/not found
    void find(int code){
        if(T.empty()) throw BoundaryViolation("Tree is empty.");

        if(T.find(code) == T.end()) 
            std::cout << "Could not find " << code << std::endl;
        else 
            std::cout << "Found " << code << std::endl;
    }

    // print appropriate message and insert node if not found 
    // replace data if found
    void insert(int code, string popCounty) {
        auto p = T.find(code);
        if(p == T.end()){
            std::cout << "New Entry: " << code << std::endl;
            T.insert(code, popCounty);
        }
        else {
            std::cout << "Found: " << code;
            std::cout <<  ", Replaced data: " << (*p).value() << " - w/: " << popCounty << std::endl;
            (*p).setValue(popCounty);
        }
    }

    // print appropriate message and erase node if found
    void erase(int code) {
        if(T.empty()) throw BoundaryViolation("Tree is empty.");

        auto p = T.find(code);
        if(!(p == T.end())){
            T.erase(p);
        }
        else {
            std::cout << "Could not find " << code << " for deletion." << std::endl;
        }
    }

    // print one record per line using an in-order traversal; 
    // include height of each node
    void print() {
        auto it = T.begin();
        while(!(it == T.end())) {
            std::cout << (*it).key() << " - " << (*it).value() << std::endl;
            ++it;
        }
    }

};

#endif
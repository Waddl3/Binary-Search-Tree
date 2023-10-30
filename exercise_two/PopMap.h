#ifndef POPMAP_H
#define POPMAP_H

#include "bst.h"
#include "Entry.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

template<typename K, typename V>
class PopMap {
private:
    SearchTree<Entry<K, V>> st;
   

public:
    // constructor accepts file name and construct search tree
    PopMap(const std::string& filename) {
        std::ifstream file(filename);
        if(file.is_open()){
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
                        st.insert(key, value);
                    }
                }
            }
        }
        else {
            std::cout << "NOT OPEN." << std::endl;
        }
    }

    // print appropriate message and data if found/not found
    void find(int code) {
        auto p = st.find(code);
        if(p == st.end()){
            std::cout << "Not Found " << code << std::endl;
        }
        else {
            std::cout << "Found " << (*p).key() << std::endl;
        }
    }

    // print appropriate message and insert node if not found
    // replace data if found
    void insert(int code, std::string popCounty) {
        auto p = st.find(code);
        if(p == st.end()) {
            std::cout << "New Entry: " << code << " - " << popCounty << std::endl;
            st.insert(code, popCounty);
        }
        else {
            st.insert(code, popCounty);
        }
    }

    // print appropriate message and erase node if found
    void erase(int code) {
        auto p = st.find(code);
        if(!(p == st.end())) {
            std::cout << "Found & Erased: " << code << std::endl;
            st.erase(code);
        }
        else {
            std::cout << "Not Found" << std::endl;
        }
    }

    // print one record per line using an in-order traversal
    void print(){
        for(auto it = st.begin(); !(it == st.end()); ++it){
            std::cout << (*it).key() << " - " << (*it).value() << std::endl;
        }
    }

};

#endif
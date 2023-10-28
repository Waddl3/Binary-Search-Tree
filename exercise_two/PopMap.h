#ifndef POPMAP_H
#define POPMAP_H

#include "bst.h"
#include "Entry.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

template<typename K, typename V>
class PopMap {
private:
    SearchTree<Entry<K, V>> st;

   

public:
    // constructor accepts file name and construct search tree
    PopMap(const std::string& filename) {
        std::ifstream file(filename);
        if(file.is_open()) {
            std::string line;
            while(std::getline(file, line)) {
                std::istringstream iss(line);
                int countyCode;
                std::string _population, _county;

                if(std::getline(iss, _population, ',')) {
                    if(std::getline(iss, _county, ',')) {
                        countyCode = std::stoi(_population);
                        st.insert(countyCode, _county + ", " + _pop);
                    }
                }
            }

            file.close();
        }
        else {
            std::cout << "Could not open" << std::endl;
        }
    }

    // print appropriate message and data if found/not found
    void find(int code) const {
        auto iter = st.find(code);
        if(!(iter == st.end())){
            std::cout << "Found: " << (*iter).key() << " " << (*iter).value() << std::endl;
        }
        else {
            std::cout << "Not Found" << std::endl;
        }
    }

    // print appropriate message and insert node if not found
    // replace data if found
    void insert(int code, std::string popCounty) {
        st.insert(code, popCounty);
    }

    // print appropriate message and erase node if found
    void erase(int code) {
        st.erase(code);
    }

    // print one record per line using an in-order traversal
    void print(){
        for(auto it = st.begin(); !(it == st.end()); ++it){
            std::cout << (*it).key() << " - " << (*it).value() << std::endl;
        }
    }

};

#endif
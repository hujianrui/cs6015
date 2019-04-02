//
//  main.cpp
//  assignment3
//
//  Created by Hu on 1/16/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "checkShape.hpp"
#include "validInput.hpp"

std::vector<std::string> split(const std::string& currLine , char split) {
    std::vector<std::string> result;
    std::string str;
    std::istringstream stream(currLine);
    while(getline(stream, str, split)) {
        result.push_back(str);
    }
    return result;
}


int main(int argc, const char * argv[]) {
    
    //std::ifstream ins("data.txt");
    std::string str;

    while(getline(std::cin,str)){
        std::vector<std::string> data = split(str,' ');
        if(validInput(data)){
            std::vector<int> val = strToInt(data);
            std::string result = checkShape(val[0],val[1],val[2],val[3],val[4],val[5]);
            std::cout<<result<<std::endl;
        }
    }
    
//    std::string result = checkShape(10,25,32,58,23,34);
//    std::cout<<result<<std::endl;
    return 0;
}

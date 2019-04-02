//
//  validInput.cpp
//  assignment3
//
//  Created by Hu on 1/31/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "validInput.hpp"
#include <iostream>

bool validNumber(std::vector<std::string> data){
    if(data.size() != 6){
        std::cout<<"error 1"<<std::endl;
//        std::cout<<"error 1 : wrong input size"<<std::endl;
        return false;
    }
    for(std::string str: data) {
        for(char c: str) {
            if(!isdigit(c)) {
                std::cout<<"error 1"<<std::endl;
//                std::cout<<"error 1 : wrong input type"<<std::endl;
                return false;
            }
        }
    }
    return true;
}

std::vector<int> strToInt(std::vector<std::string> data){
    std::vector<int> val;
    for(std::string str: data) {
        val.push_back(stoi(str));
    }
    return val;
}

bool rangeNumber(int x1, int y1, int x2, int y2, int x3, int y3){
    if(x1 > 100 || x1 < 0 || y1 > 100 || y1 < 0 ||
       x2 > 100 || x2 < 0 || y2 > 100 || y2 < 0 ||
       x3 > 100 || x3 < 0 || y3 > 100 || y3 < 0 ){
        std::cout<<"error 1"<<std::endl;
//        std::cout<<"error 1 : out of range"<<std::endl;
        return false;
    }
    return true;
}

bool coincide(int x1, int y1, int x2, int y2, int x3, int y3){
    if((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0) || (x3 == 0 && y3 ==0) ||
       (x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) ||
       (x2 == x3 && y2 == y3)
       ){
        std::cout<<"error 2"<<std::endl;
//        std::cout<<"error 2 : point coincide"<<std::endl;
        return true;
    }
    return false;
}

//https://stackoverflow.com/questions/14176776/find-out-if-2-lines-intersect
//((A2-A0)*(B1-B0) - (B2-B0)*(A1-A0)) * ((A3-A0)*(B1-B0) - (B3-B0)*(A1-A0)) < 0
//&&
//((A0-A2)*(B3-B2) - (B0-B2)*(A3-A2)) * ((A1-A2)*(B3-B2) - (B1-B2)*(A3-A2)) < 0
bool cross(int x1, int y1, int x2, int y2, int x3, int y3){
    //CD cross AB
    bool CDcrossAB = (x2*y1 - y2*x1) * (x3*y1 - y3*x1) < 0
    &&
    ((-x2)*(y3-y2) - (-y2)*(x3-x2)) * ((x1-x2)*(y3-y2) - (y1-y2)*(x3-x2)) < 0;
    // AD cross CB
    bool ADcrossCB = (x1*y3 - y1*x3) * (x2*y3 - y2*x3) < 0
    &&
    ((-x1)*(y2-y1) - (-y1)*(x2-x1)) * ((x3-x1)*(y2-y1) - (y3-y1)*(x2-x1)) < 0;
    if(CDcrossAB || ADcrossCB){
        std::cout<<"error 3"<<std::endl;
//        std::cout<<"error 3 : line cross"<<std::endl;
        return true;
    }
    return false;
}

//https://stackoverflow.com/questions/3813681/checking-to-see-if-3-points-are-on-the-same-line
//Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By)/2 == 0
bool colinear(int x1, int y1, int x2, int y2, int x3, int y3){
    //ABC on line
    int check1 = x1 * y2 + x2 * (-y1);
    //BCD on line
    int check2 = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    //CDA on line
    int check3 = x2 * y3 + x3 * (-y2);
    //DAB on line
    int check4 = x3 * (-y1) + x1 * y3;
    if(check1 == 0 || check2 == 0 || check3 == 0 || check4 == 0){
        std::cout<<"error 4"<<std::endl;
//        std::cout<<"error 4 : points colinear"<<std::endl;
        return true;
    }
    return false;
}

bool validInput(std::vector<std::string> data){
    std::vector<int> val;
    if(validNumber(data)){
        val = strToInt(data);
        if(rangeNumber(val[0], val[1], val[2], val[3], val[4], val[5]) &&
           !coincide(val[0], val[1], val[2], val[3], val[4], val[5]) &&
           !cross(val[0], val[1], val[2], val[3], val[4], val[5]) &&
           !colinear(val[0], val[1], val[2], val[3], val[4], val[5])
           ){
            return true;
        }
    }
    return false;
}

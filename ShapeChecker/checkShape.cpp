//
//  checkShape.cpp
//  assignment3
//
//  Created by Hu on 1/31/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "checkShape.hpp"
#include <cmath>
#include <iostream>

bool parallelogram(int x1, int y1, int x2, int y2, int x3, int y3){
    int len1 = pow((x2-x1),2) + pow((y2-y1),2);
    int len2 = pow((x3-0),2) + pow((y3-0),2);
    int len3 = pow((y2-y3),2) + pow((x2-x3),2);
    int len4 = pow((x1-0),2) + pow((y1-0),2);
    if(len1 == len2 && len3 == len4){
        return true;
    }
    return false;
}

bool rectangle(int x1, int y1, int x2, int y2, int x3, int y3){
    int ang1 = (x3-0)*(x1-0) + (y3-0)*(y1-0);
    int ang2 = (x2-x3)*(0-x3) + (y2-y3)*(0-y3);
    int ang3 = (x2-x1)*(0-x1) + (y2-y1)*(0-y1);
    if(ang1==0 && ang2==0 && ang3==0){
        return true;
    }
    return false;
}

bool rhombus(int x1, int y1, int x2, int y2, int x3, int y3){
    int len1 = pow((x2-x1),2) + pow((y2-y1),2);
    int len2 = pow((x3-0),2) + pow((y3-0),2);
    int len3 = pow((y2-y3),2) + pow((x2-x3),2);
    int len4 = pow((x1-0),2) + pow((y1-0),2);
    if(len1 == len2 && len2 == len3 && len3 == len4 ){
        return true;
    }
    return false;
}


bool square(int x1, int y1, int x2, int y2, int x3, int y3){
    
    if(rectangle(x1,y1,x2,y2,x3,y3) && rhombus(x1,y1,x2,y2,x3,y3)){
        return true;
    }
    return false;
}

bool kite(int x1, int y1, int x2, int y2, int x3, int y3){
    int len1 = pow((x2-x1),2) + pow((y2-y1),2);
    int len2 = pow((x3-0),2) + pow((y3-0),2);
    int len3 = pow((y2-y3),2) + pow((x2-x3),2);
    int len4 = pow((x1-0),2) + pow((y1-0),2);
    if(len1 == len3 && len2 == len4){
        return true;
    }
    return false;
}

bool trapezoid(int x1, int y1, int x2, int y2, int x3, int y3){
    double slope1 = 0;
    if(y2-y3 != 0){
        slope1 = (x2-x3-0.0)/(y2-y3-0.0);
//        std::cout<<slope1<<std::endl;
    }
    double slope2 = 0;
    if(y1-0 != 0){
        slope2 = (x1-0.0)/(y1-0.0);
//        std::cout<<slope2<<std::endl;
    }
    double slope3 = 0;
    if(y3-0 != 0){
        slope3 = (x3-0.0)/(y3-0.0);
//        std::cout<<slope3<<std::endl;
    }
    double slope4 = 0;
    if(y2-y1 != 0){
        slope4 =(x2-x1-0.0)/(y2-y1-0.0);
//        std::cout<<slope4<<std::endl;
    }
    
    if(slope1 == slope2 || slope3 == slope4){
        return true;
    }
    return false;
}

std::string checkShape(int x1, int y1, int x2, int y2, int x3, int y3){
    if(square(x1, y1, x2, y2, x3, y3)){
        return "square";
    } else if (rectangle(x1, y1, x2, y2, x3, y3)){
        return "rectangle";
    } else if (rhombus(x1, y1, x2, y2, x3, y3)){
        return "rhombus";
    } else if(parallelogram(x1, y1, x2, y2, x3, y3)){
        return "parallelogram";
    } else if(kite(x1, y1, x2, y2, x3, y3)){
        return "kite";
    } else if (trapezoid(x1, y1, x2, y2, x3, y3)){
        return "trapezoid";
    } else{
        return "quadrilateral";
    }
}

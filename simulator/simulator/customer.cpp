//
//  customer.cpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "customer.hpp"

customer::customer(int arrive, int service){
    arriveTime = arrive;
    serviceTime = service;
}

int customer::getServiceTime(){
    return serviceTime;
}

int customer::getArriveTime(){
    return arriveTime;
}

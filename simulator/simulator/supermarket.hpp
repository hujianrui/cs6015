//
//  supermaket.hpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#ifndef supermarket_hpp
#define supermarket_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "customer.hpp"

using namespace std;

class supermarket{
private:
    double customerArrivalRate;
    double maxCustomerServiceTime;
    int randomNumberSeed;
    vector<int> casherRemianServiceTime;
    vector<queue <customer> > cashersQ;
    vector<int> queueTotalWaitingTime;
    vector<int> customersTotalWaitingTime;
    int numCustomer;
    int nextCustomerArrive;
    int currentTime;
    int skipTime;
    //added variable, incase cashiers change in future
    int numCashiers;
public:
    supermarket(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed, int numCashiers);
    void run();
    int getNumCashiers();
private:
    void addNewCustomer();
    void cashierCheck();
    void nextEvent();
    void updateTime();
    void printResult();
};

#endif /* supermarket_hpp */

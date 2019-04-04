//
//  bank.hpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#ifndef bank_hpp
#define bank_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "customer.hpp"

using namespace std;

class bank{
private:
    double customerArrivalRate;
    double maxCustomerServiceTime;
    int randomNumberSeed;
    priority_queue< int, vector<int>, greater<int> > cashierQ;
    queue <customer> customerQ;
    vector<int> customes;
    int numCustomer;
    int nextCustomerArrive;
    int currentTime;
    int skipTime;
public:
    bank(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed);
    void run();
private:
    void addNewCustomer();
    void cashierCheck();
    void nextEvent();
    void updateTime();
    void printResult();
};









void bankaaa(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed);

#endif /* bank_hpp */

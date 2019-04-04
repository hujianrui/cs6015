//
//  supermaket.cpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "supermarket.hpp"

supermarket::supermarket(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed){
    for(int i = 0; i < 6 ; i++){
        this -> casherRemianServiceTime.push_back(0);
        this -> queueTotalWaitingTime.push_back(0);
        this -> customersTotalWaitingTime.push_back(0);
        this -> cashersQ.push_back(queue<customer>());
    }
    this->customerArrivalRate = customerArrivalRate;
    this->maxCustomerServiceTime = maxCustomerServiceTime;
    this->randomNumberSeed = randomNumberSeed;
    numCustomer = 0;
    nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
    currentTime = 0;
    numCustomer++;
}

void supermarket::addNewCustomer(){
    int customerServiceTime = (rand() % (int)(maxCustomerServiceTime * 60)) + 1;
    if(nextCustomerArrive == currentTime){
        customer newCustomer = customer(currentTime,customerServiceTime);
        int minTotalWaitingTime = queueTotalWaitingTime[0];
        int casherIndex = 0;
        for(int i = 0; i < 6; i++){
            int waitTime = queueTotalWaitingTime[i];
            if(waitTime < minTotalWaitingTime){
                minTotalWaitingTime = waitTime;
                casherIndex = i;
            }
        }
        cashersQ[casherIndex].push(newCustomer);
        queueTotalWaitingTime[casherIndex] += customerServiceTime;
        nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
        numCustomer++;
    }
}

void supermarket::cashierCheck(){
    for(int i = 0; i < 6; i++){
        if(casherRemianServiceTime[i] == 0 && !cashersQ[i].empty()){
            customer currentCustomer = cashersQ[i].front();
            int serviceTime = currentCustomer.getServiceTime();
            int waitingTime = currentTime - currentCustomer.getArriveTime();
            int totalWaitingTime =  serviceTime + waitingTime;
            customersTotalWaitingTime.push_back(totalWaitingTime);
            cashersQ[i].pop();
            casherRemianServiceTime[i] = serviceTime;
            queueTotalWaitingTime[i] -= serviceTime;
        }
    }
}

void supermarket::nextEvent(){
    int minSericeTime = casherRemianServiceTime[0];
    for(int i = 0; i < 6; i++){
        if( minSericeTime < casherRemianServiceTime[i]){
            minSericeTime = casherRemianServiceTime[i];
        }
    }
    int nextCustomerCount = nextCustomerArrive - currentTime;
    skipTime = min(minSericeTime,nextCustomerCount);
    if(minSericeTime == 0){
        skipTime = nextCustomerCount;
    }
}

void supermarket::updateTime(){
    for(int i = 0; i < 6 ; i++){
        int update = casherRemianServiceTime[i] - skipTime;
        casherRemianServiceTime[i] = max(update,0);
    }
    currentTime += skipTime;
}

void supermarket::printResult(){
    sort(customersTotalWaitingTime.begin(),customersTotalWaitingTime.end());
    int tenTile = customersTotalWaitingTime.size() * 0.1;
    int fiftyTile = customersTotalWaitingTime.size() * 0.5;
    int ninetyTile = customersTotalWaitingTime.size() * 0.9;
    cout<<"Supermarket 10% tail is :" << customersTotalWaitingTime[tenTile]/60.0 << "\n";
    cout<<"Supermarket 50% tail is :" << customersTotalWaitingTime[fiftyTile]/60.0 << "\n";
    cout<<"Supermarket 90% tail is :" << customersTotalWaitingTime[ninetyTile]/60.0 << "\n";
}

void supermarket::run(){
    int totalTime = 12 * 60 * 60;
    while(currentTime < totalTime){
        addNewCustomer();
        cashierCheck();
        nextEvent();
        updateTime();
    }
    printResult();
}

//
//  supermaket.cpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "supermarket.hpp"

/*
 Descr: Supermarket class contructor, Initializes variables, loads cashier queue, generates random number
 Params: double, double, int, int
 Returned value: none
 */
supermarket::supermarket(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed, int numCashiers){
    for(int i = 0; i < numCashiers ; i++){
        this -> casherRemianServiceTime.push_back(0);
        this -> queueTotalWaitingTime.push_back(0);
        this -> customersTotalWaitingTime.push_back(0);
        this -> cashersQ.push_back(queue<customer>());
    }
    this->customerArrivalRate = customerArrivalRate;
    this->maxCustomerServiceTime = maxCustomerServiceTime;
    this->randomNumberSeed = randomNumberSeed;
    this->numCashiers = numCashiers;
    numCustomer = 0;
    nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
    currentTime = 0;
    numCustomer++;
}

/*
 Descr: Adds new customer, generates random service time, generates next customer arrival
 Params: none
 Returned value: none
 */
void supermarket::addNewCustomer(){
    int customerServiceTime = (rand() % (int)(maxCustomerServiceTime * 60)) + 1;
    if(nextCustomerArrive == currentTime){
        customer newCustomer = customer(currentTime,customerServiceTime);
        int minTotalWaitingTime = queueTotalWaitingTime[0];
        int casherIndex = 0;
        for(int i = 0; i < getNumCashiers(); i++){
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

/*
 Descr: Checks customer queue, updates customer class and customer queue
 Params: none
 Returned value: none
 */
void supermarket::cashierCheck(){
    for(int i = 0; i < getNumCashiers(); i++){
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

/*
 Descr: Sets customer times and sets next customers time
 Params: none
 Returned value: none
 */
void supermarket::nextEvent(){
    int minSericeTime = casherRemianServiceTime[0];
    for(int i = 0; i < getNumCashiers(); i++){
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

/*
 Descr: Updates time for cashier queue
 Params: none
 Returned value: none
 */
void supermarket::updateTime(){
    for(int i = 0; i < getNumCashiers() ; i++){
        int update = casherRemianServiceTime[i] - skipTime;
        casherRemianServiceTime[i] = max(update,0);
    }
    currentTime += skipTime;
}

/*
 Descr: Prints the results for the different customer times
 Params: none
 Returned value: none
 */
void supermarket::printResult(){
    sort(customersTotalWaitingTime.begin(),customersTotalWaitingTime.end());
    int tenTile = customersTotalWaitingTime.size() * 0.1;
    int fiftyTile = customersTotalWaitingTime.size() * 0.5;
    int ninetyTile = customersTotalWaitingTime.size() * 0.9;
    cout<<"Supermarket 10% tail is :" << customersTotalWaitingTime[tenTile]/60.0 << "\n";
    cout<<"Supermarket 50% tail is :" << customersTotalWaitingTime[fiftyTile]/60.0 << "\n";
    cout<<"Supermarket 90% tail is :" << customersTotalWaitingTime[ninetyTile]/60.0 << "\n";
//    cout <<customersTotalWaitingTime[ninetyTile]/60.0 <<"\n";
}

/*
 Descr: Runs the program for the Supermarket simulator
 Params: none
 Returned value: none
 */
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

//added getter for number of cashiers, scalability
int supermarket::getNumCashiers() {
    return numCashiers;
}

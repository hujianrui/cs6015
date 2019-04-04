//
//  bank.cpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "bank.hpp"

using namespace std;

bank::bank(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed){
    for(int i = 0; i < 6 ; i++){
        this -> cashierQ.push(0);
    }
    this->customerArrivalRate = customerArrivalRate;
    this->maxCustomerServiceTime = maxCustomerServiceTime;
    this->randomNumberSeed = randomNumberSeed;
    numCustomer = 0;
    nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
    currentTime = 0;
    numCustomer++;
}

void bank::addNewCustomer(){
    int customerServiceTime = (rand() % (int)(maxCustomerServiceTime * 60)) + 1;
    if(nextCustomerArrive == currentTime){
        customer newCustomer = customer(currentTime,customerServiceTime);
        customerQ.push(newCustomer);
        nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
        numCustomer++;
    }
}

void bank::cashierCheck(){
    while(cashierQ.top() == 0 && !customerQ.empty()){
        customer currentCustomer = customerQ.front();
        int serviceTime = currentCustomer.getServiceTime();
        int waitingTime = currentTime - currentCustomer.getArriveTime();
        int totalWaitingTime =  serviceTime + waitingTime;
        customes.push_back(totalWaitingTime);
        customerQ.pop();
        cashierQ.pop();
        cashierQ.push(serviceTime);
    }
}

void bank::nextEvent(){
    int cashierRemain = cashierQ.top();
    int nextCustomerCount = nextCustomerArrive - currentTime;
    skipTime = min(cashierRemain,nextCustomerCount);
    if(cashierRemain == 0){
        skipTime = nextCustomerCount;
    }
}

void bank::updateTime(){
    priority_queue< int, vector<int>, greater<int> > cashierNewQ;
    for(int i = 0; i < 6 ; i++){
        int current = cashierQ.top();
        cashierQ.pop();
        int update = current - skipTime;
        cashierNewQ.push(max(update,0));
    }
    cashierQ = cashierNewQ;
    currentTime += skipTime;
}

void bank::printResult(){
    sort(customes.begin(),customes.end());
    int tenTile = customes.size() * 0.1;
    int fiftyTile = customes.size() * 0.5;
    int ninetyTile = customes.size() * 0.9;
    cout<<"Bank 10% tail is :" << customes[tenTile]/60.0 << "\n";
    cout<<"Bank 50% tail is :" << customes[fiftyTile]/60.0 << "\n";
    cout<<"Bank 90% tail is :" << customes[ninetyTile]/60.0 << "\n";
//    cout << customes[ninetyTile]/60.0 << "\n";
}

void bank::run(){
    int totalTime = 12 * 60 * 60;
    while(currentTime < totalTime){
        addNewCustomer();
        cashierCheck();
        nextEvent();
        updateTime();
    }
    printResult();
}

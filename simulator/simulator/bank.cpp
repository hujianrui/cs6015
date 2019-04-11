//
//  bank.cpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "bank.hpp"

using namespace std;

/*
    Descr: Bank class contructor, Initializes variables, loads cashier queue, generates random number
    Params: double, double, int, int
    Returned value: none
 */
bank::bank(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed, int numTeller){
    this->customerArrivalRate = customerArrivalRate;
    this->maxCustomerServiceTime = maxCustomerServiceTime;
    this->randomNumberSeed = randomNumberSeed;
    this->numTeller = numTeller;
    numCustomer = 0;
    for(int i = 0; i < getNumTeller() ; i++){
        this -> cashierQ.push(0);
    }
    nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
    currentTime = 0;
    numCustomer++;
}

/*
    Descr: Adds new customer, generates random service time, generates next customer arrival
    Params: none
    Returned value: none
 */
void bank::addNewCustomer(){
    int customerServiceTime = (rand() % (int)(maxCustomerServiceTime * 60)) + 1;
    if(nextCustomerArrive == currentTime){
        customer newCustomer = customer(currentTime,customerServiceTime);
        customerQ.push(newCustomer);
        nextCustomerArrive = (numCustomer * 60/customerArrivalRate) + (rand()%(int)(60/customerArrivalRate));
        numCustomer++;
    }
}

/*
 Descr: Checks customer queue, updates customer class and customer queue
 Params: none
 Returned value: none
 */
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

/*
 Descr: Adds new customer, generates random service time, generates next customer arrival
 Params: none
 Returned value: none
 */
void bank::nextEvent(){
    int cashierRemain = cashierQ.top();
    int nextCustomerCount = nextCustomerArrive - currentTime;
    skipTime = min(cashierRemain,nextCustomerCount);
    if(cashierRemain == 0){
        skipTime = nextCustomerCount;
    }
}

/*
 Descr: Updates time for cashier queue
 Params: none
 Returned value: none
 */
void bank::updateTime(){
    priority_queue< int, vector<int>, greater<int> > cashierNewQ;
    for(int i = 0; i < getNumTeller() ; i++){
        int current = cashierQ.top();
        cashierQ.pop();
        int update = current - skipTime;
        cashierNewQ.push(max(update,0));
    }
    cashierQ = cashierNewQ;
    currentTime += skipTime;
}

/*
 Descr: Prints the results for the different customer times
 Params: none
 Returned value: none
 */
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

/*
 Descr: Runs the program for the Bank simulator
 Params: none
 Returned value: none
 */
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

//added getter for number of tellers, scalability
int bank::getNumTeller() {
    return numTeller;
}

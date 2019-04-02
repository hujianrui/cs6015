//
//  main.cpp
//  simulator
//
//  Created by Hu on 3/31/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

void bank(double customerArrivalRate, double maxCustomerServiceTime, int randomNumberSeed){
    queue <int> customerQ;
    priority_queue< int, vector<int>, greater<int> > cashierQ;
    vector<int> customes;
    srand(randomNumberSeed);
    int waitingTime = 60/customerArrivalRate;
    int waitingTimeCount = 0;
    int customerCount = 1;
    int totalTime = 12 * 60 * 60;
    int currentTime = 0;
    //add 6 cashiers
    for(int i = 0; i < 6 ; i++){
        cashierQ.push(0);
    }
    while(currentTime < totalTime){
        //check for new come customer
        int customerServiceTime = ((double)rand() / RAND_MAX) * maxCustomerServiceTime * 60;
        if(waitingTimeCount == waitingTime){
            customerQ.push(customerServiceTime);
            waitingTimeCount = 0;
        }
        //check each cashiers
        while(cashierQ.top() == 0 && !customerQ.empty()){
            int serviceTime = customerQ.front();
            int totalWaitingTime = currentTime - (customerCount * waitingTime) + serviceTime;
            customes.push_back(totalWaitingTime);
            customerQ.pop();
            cashierQ.pop();
            cashierQ.push(serviceTime);
            customerCount++;
        }
        //check next event
        int cashierRemain = cashierQ.top();
        int customerRemian = waitingTime - waitingTimeCount;
        int skip = min(cashierRemain,customerRemian);
        if(cashierRemain == 0){
            skip = customerRemian;
        }
        //move skip step
        waitingTimeCount += skip;
        priority_queue< int, vector<int>, greater<int> > cashierNewQ;
        for(int i = 0; i < 6 ; i++){
            int current = cashierQ.top();
            cashierQ.pop();
            int update = current - skip;
            cashierNewQ.push(max(update,0));
        }
        cashierQ = cashierNewQ;
        currentTime += skip;
    }
    sort(customes.begin(),customes.end());
    int tenTile = customes.size() * 0.1;
    int fiftyTile = customes.size() * 0.5;
    int ninetyTile = customes.size() * 0.9;
    cout<<"Bank 10% tail is :" << customes[tenTile]/60.0 << "\n";
    cout<<"Bank 50% tail is :" << customes[fiftyTile]/60.0 << "\n";
    cout<<"Bank 90% tail is :" << customes[ninetyTile]/60.0 << "\n";
}

void supermarket(){
    queue <int> customerQ1;
    queue <int> customerQ2;
    queue <int> customerQ3;
    queue <int> customerQ4;
    queue <int> customerQ5;
    queue <int> customerQ6;
    
}

int main(int argc, const char * argv[]) {
    
    double customerArrivalRate = stod(argv[1]);
    double maxCustomerServiceTime = stod(argv[2]);
    int randomNumberSeed = atoi(argv[3]);
    bank(customerArrivalRate, maxCustomerServiceTime, randomNumberSeed);
    
    
    
    return 0;
}

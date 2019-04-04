//
//  main.cpp
//  simulator
//
//  Created by Hu on 3/31/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#include "bank.hpp"
#include "supermarket.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    double customerArrivalRate = stod(argv[1]);
    double maxCustomerServiceTime = stod(argv[2]);
    int randomNumberSeed = atoi(argv[3]);
    bank bk = bank(customerArrivalRate, maxCustomerServiceTime, randomNumberSeed);
    bk.run();
    supermarket sm = supermarket(customerArrivalRate, maxCustomerServiceTime, randomNumberSeed);
    sm.run();
    
    return 0;
}

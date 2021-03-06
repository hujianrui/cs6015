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
    
//    double customerArrivalRate = stod(argv[1]);
//    double maxCustomerServiceTime = stod(argv[2]);
//    int randomNumberSeed = atoi(argv[3]);
//    if(stod(argv[1]) == 0 || stod(argv[2]) == 0){
//        cout<<"Bank 10% tail is : 0 \n";
//        cout<<"Bank 50% tail is : 0 \n";
//        cout<<"Bank 90% tail is : 0 \n";
//        cout<<"Supermarket 10% tail is : 0 \n";
//        cout<<"Supermarket 50% tail is : 0 \n";
//        cout<<"Supermarket 90% tail is : 0 \n";
//        cout<<"0 \n";
//        cout<<"0 \n";
//        return 0;
//    }
    
    bank bk = bank(0.5, 3, 7890, 6);
    bk.run();
    supermarket sm = supermarket(0.5, 3, 7890, 6);
    sm.run();
    
    //New Tests
    bank bk2 = bank(0.32, 5.1, 34534, 6);
    bk.run();
    supermarket sm2 = supermarket(0.32, 5.1, 34534, 6);
    sm.run();
    
    bank bk3 = bank(1.0, 7, 34534, 6);
    bk.run();
    supermarket sm3 = supermarket(1.0, 7, 34534, 6);
    sm.run();
    
    return 0;
}

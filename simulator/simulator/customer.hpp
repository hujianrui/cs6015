//
//  customer.hpp
//  simulator
//
//  Created by Hu on 4/2/19.
//  Copyright © 2019 Hu. All rights reserved.
//

#ifndef customer_hpp
#define customer_hpp

#include <stdio.h>

class customer{
private:
    int arriveTime;
    int serviceTime;
public:
    customer(int arrive, int service);
    int getServiceTime();
    int getArriveTime();
};

#endif /* customer_hpp */

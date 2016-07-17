//
//  TCSilverDistance.cpp
//  playground
//
//  Created by 張正昊 on 17/7/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>

using namespace std;

class SilverDistance{
public:
    int minSteps(int sx,int sy,int gx,int gy){
        int res = 0;
        int dx = gx-sx,dy = gy-sy;
        if((dx+dy)%2){
            dy--;
            res++;
        }
        res += max(abs(dx),abs(dy));
        return res;
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

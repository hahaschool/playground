//
//  SGU123.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/17.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//


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

using namespace std;

long long fib[43];
long long sum[43];

int main(){
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= 41; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    sum[0] = 0;
    for (int i = 1; i <= 41; i++) {
        sum[i] = sum[i-1]+fib[i];
    }
    int toQuery = 0;
    scanf(" %d",&toQuery);
    printf("%lld\n",sum[toQuery]);
    
    return 0;
}
 


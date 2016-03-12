//
//  ACDream1408.cpp
//  playground
//
//  Created by 張正昊 on 12/3/2016.
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

int main(){
    long long a;
    while (cin >> a) {
        if (a%2) {
            printf("%lld %lld\n",2LL,a+2);
        }else{
            puts("0 0");
        }
    }
    return 0;
}

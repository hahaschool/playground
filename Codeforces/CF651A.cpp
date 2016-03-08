//
//  CF651A.cpp
//  playground
//
//  Created by 張正昊 on 7/3/2016.
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
    int a,b;
    while (scanf(" %d %d",&a,&b) != EOF) {
        int res = 0;
        while (a > 0 && b > 0) {
            if (a == 1 && b == 1) {
                break;
            }
            if (a > b) {
                swap(a, b);
            }
            a++,b-=2,res++;
        }
        printf("%d\n",res);
    }
    
    
    return 0;
}
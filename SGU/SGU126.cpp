//
//  SGU126.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/7.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(){
    long long a = 0,b = 0,sum = 0;
    cin >> a >> b;
    sum = a+b;
    if(a == 0 || b == 0){
        cout << 0 << endl;
    }
    if(sum%2){
        cout << -1 << endl;
        return 0;
    }
    int res = 0;
    long long now = min(a,b);
    while(now != sum/2){
        if(res > 10000){
            cout << -1 << endl;
            return 0;
        }
        res++;
        now *= 2;
        now = min(now,sum-now);
    }
    cout << res+1 << endl;
    return 0;
}

//
//  LA4119.cpp
//  playground
//
//  Created by 張正昊 on 17/4/2016.
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

string str;
long long cur = 0;
inline void get_bracket(){
    while (cur < str.size()) {
        if (str[cur] == '(' || str[cur] == ')') {
            cur++;
            break;
        }
        cur++;
    }
}
inline long long get_num(){
    string numstr;
    long long sgn = 0;
    while (cur < str.size()) {
        if (isdigit(str[cur])) {
            if (!sgn) sgn = 1;
            numstr += str[cur];
        }else if(!sgn && str[cur] == '-'){
            sgn = -1;
        }else if(!sgn && str[cur] == '+'){
            sgn = 1;
        }else{
            break;
        }
        cur++;
    }
    if (!sgn) sgn = 1;
    if (!numstr.size()) return sgn;
    long long ret = 0;
    long long fac = 1;
    for(long long i = (long long)numstr.size()-1;i >= 0; i--){
        ret += (numstr[i] - '0')*fac;
        fac *= 10;
    }
    return sgn * ret;
}

long long fac[105],below;

void proc(){
    memset(fac, 0, sizeof(fac));
    below = 0;
    cur = 0;
    get_bracket();
    long long e,p;
    while ((e = get_num())) {
        if (str[cur] != 'n') {
            fac[0] = e;
            break;
        }
        cur++;
        if (str[cur] == '^') {
            cur++;
            p = get_num();
        }else{
            p = 1;
        }
        fac[p] = e;
        if (str[cur] == ')') {
            break;
        }
    }
    get_bracket();
    cur++;
    below = get_num();
}

bool solve(long long a){
    long long loc = 0;
    for(long long i = 0; i <= 100; i++){
        if (fac[i]) {
            long long delta = 1;
            for(long long j = 1; j <= i; j++){
                delta *= a;
                delta %= below;
            }
            delta *= fac[i];
            delta %= below;
            loc += delta;
            loc %= below;
        }
    }
    return loc == 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt = 0;
    while(cin >> str){
        if (str == ".") {
            break;
        }else{
            printf("Case %d: ",++caseCnt);
        }
        proc();
        int i = 1;
        for(; i <= 200; i++){
            if(!solve(i)){
                puts("Not always an integer");
                break;
            }
        }
        if (i == 201) {
            puts("Always an integer");
        }
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

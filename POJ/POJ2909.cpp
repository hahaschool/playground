//
//  POJ2909.cpp
//  playground
//
//  Created by Adam Chang on 2015/05/27.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

/*
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

using namespace std;

#define MAXN 32800

bool prime[MAXN];
vector<int> primels;
int cnt[MAXN];

bool isPrime(int n){
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void genPrime(){
    memset(prime, true, sizeof(prime));
    for (int i = 2; i < MAXN; i++) {
        if (prime[i]) {
            if (isPrime(i)) {
                for (int k = 2; k * i < MAXN; k++) {
                    prime[k*i] = false;
                }
            }else{
                prime[i] = false;
                continue;
            }
        }else{
            continue;
        }
    }
}

int main(){
    genPrime();
    for (int i = 2; i <= MAXN; i++) {
        if (prime[i]) {
            primels.push_back(i);
        }
    }
    for (int i = 0; i < primels.size(); i++) {
        for (int j = i; j < primels.size(); j++) {
            if (primels[i] + primels[j] < MAXN) {
                cnt[primels[i] + primels[j]]++;
            }
        }
    }
    int q = 0;
    while (cin >> q && q) {
        cout << cnt[q] << endl;
    }
    
    return 0;
}
*/
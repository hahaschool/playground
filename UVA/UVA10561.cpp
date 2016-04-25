//
//  UVA10561.cpp
//  playground
//
//  Created by 張正昊 on 23/4/2016.
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

string brd;

int sg[205];

void prepare(){
    sg[0] = 0;
    sg[1] = sg[2] = sg[3] = 1;
    for(int i = 4; i <= 200; i++){
        set<int> st;
        for(int j = 1; j <= i; j++){
            if (j <= 3) {
                st.insert(sg[max(0,i - j - 2)]);
            }else if(j >= i-2){
                st.insert(sg[max(0,j - 3)]);
            }else{
                st.insert(sg[max(0,j-3)]^sg[max(0,i-j-2)]);
            }
        }
        for(int j = 0; j <= 222;j++){
            if (!st.count(j)) {
                sg[i] = j;
                break;
            }
        }
    }
}


bool mkr[205];
set<int> winpos;
int n;
bool checkmkr(){
    int ctr = 0,tsg = 0;
    mkr[n+1] = false;
    for (int i = 1;i <= n+1; i++) {
        if (mkr[i]) {
            ctr++;
        }else{
            tsg ^= sg[ctr];
            ctr = 0;
        }
    }
    return tsg;
}

void markdown(int a){
    for(int j = max(1,a-2),k = min(n,a+2);j <= k;j++){
        mkr[j] = false;
    }
}

void printans(){
    printf("%d",*winpos.begin());
    for (set<int>::iterator it = ++winpos.begin(); it != winpos.end(); it++) {
        printf(" %d",*it);
    }
    puts("");
}

void solve(){
    n = (int)brd.size();
    winpos.clear();
    for (int i = 0; i < n; i++) {
        if (i+1 < n && brd[i] == 'X' && brd[i+1] == 'X') {
            if(i-1 >= 0) winpos.insert(i);
            if(i+2 < n) winpos.insert(i+3);
        }
        if (i+2 < n && brd[i] == 'X' && brd[i+1] == '.' && brd[i+2] == 'X') {
            winpos.insert(i+2);
        }
    }
    if (winpos.size()) {
        puts("WINNING");
        printans();
        return;
    }
    memset(mkr, 1, sizeof(mkr));
    for(int i = 1; i <= n; i++){
        if (brd[i-1] == 'X') {
            markdown(i);
        }
    }
    
    if (checkmkr()) {
        puts("WINNING");
        for(int i = 1;i <= n; i++){
            memset(mkr, 1, sizeof(mkr));
            for(int j = 1; j <= n; j++){
                if (brd[j-1] == 'X') {
                    markdown(j);
                }
            }
            if (!mkr[i]) {
                continue;
            }
            markdown(i);
            if (!checkmkr()) {
                winpos.insert(i);
            }
        }
        printans();
    }else{
        puts("LOSING\n");
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        cin >> brd;
        solve();
    }
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

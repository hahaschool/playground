//
//  UVA11995.cpp
//  playground
//
//  Created by 張正昊 on 14/3/2016.
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

int n;
priority_queue<int> pque;
queue<int> que;
stack<int> stk;
int pqf,qf,sf;

void clr(){
    while (!pque.empty()) {
        pque.pop();
    }
    while (!que.empty()) {
        que.pop();
    }
    while (!stk.empty()) {
        stk.pop();
    }
    pqf = sf = qf = 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF) {
        clr();
        for(int i = 1; i <= n; i++){
            int typ,arg;
            scanf(" %d %d",&typ,&arg);
            if (typ == 1) {
                pque.push(arg);
                que.push(arg);
                stk.push(arg);
            }else{
                if (pque.empty()) {
                    pqf = false;
                }else{
                    if (pque.top() != arg) {
                        pqf = false;
                    }
                    pque.pop();
                }
                
                if (que.empty()) {
                    qf = false;
                }else{
                    if (que.front() != arg) {
                        qf = false;
                    }
                    que.pop();
                }
                
                if (stk.empty()) {
                    sf = false;
                }else{
                    if (stk.top() != arg) {
                        sf = false;
                    }
                    stk.pop();
                }
            }
        }
        
        int cnt = sf + pqf + qf;
        if (cnt > 1) {
            puts("not sure");
        }else if(!cnt){
            puts("impossible");
        }else{
            if (sf) {
                puts("stack");
            }
            if (pqf) {
                puts("priority queue");
            }
            if (qf) {
                puts("queue");
            }
        }
    }
    return 0;
}

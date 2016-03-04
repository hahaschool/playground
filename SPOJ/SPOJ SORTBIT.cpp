//
//  SPOJ SORTBIT.cpp
//  playground
//
//  Created by Adam Chang on 2015/08/04.
//  Copyright © 2015年 Adam Chang. All rights reserved.
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
#include <map>

using namespace std;

unsigned int cnt[33][33];//cnt[height][required num of 1]
void get_cnt(){
    cnt[0][0] = 1;
    cnt[1][0] = 1;
    cnt[1][1] = 1;
    for (int i = 2; i <= 32; i++) {
        cnt[i][0] = 1;
        for (int j = 1; j <= 32; j++) {
            cnt[i][j] = cnt[i-1][j] + cnt[i-1][j-1];
        }
    }
}

unsigned int count_to(unsigned int a, int k){
    unsigned int ret = 0;
    int hav = 0;
    for (int i = 31; i >= 0; i--) {
        if (a & (1U << (unsigned int)i)) {
            if (k >= hav) {
                ret += cnt[i][k - hav];
            }
            hav++;
        }
    }
    return ret;
}

unsigned int count_num(int lb, int rb, int k){
    unsigned int ret = 0;
    if (lb > rb) {
        swap(lb, rb);
    }
    unsigned int ulb = lb, urb = rb;
    if (lb * rb != 0) {
        if (lb > 0) {
            ret = count_to(urb+1,k) - count_to(ulb, k);
        }else {
            if (rb == -1) {
                ret = count_to(urb, k) - count_to(ulb, k);
                if (k == 32) {
                    ret++;
                }
            }else{
                ret = count_to(urb+1, k) - count_to(ulb, k);
            }
        }
    }else {
        if (lb == 0) {
            ret = count_to(urb+1, k);
        }else {
            ret = cnt[32][k] - count_to(ulb, k);
            if (k == 0) {
                ret++;
            }
        }
    }
    return ret;
}

int get_ans(int m, int n, long long k){
    if (m > n) {
        swap(m, n);
    }
    long long curcnt = 0;
    long long target = 0;
    int lasti = 0;
    for (int i = 0; i <= 32; i++) {
        lasti = i;
        curcnt += count_num(m, n, i);
        if (curcnt >= k) {
            target = count_num(m, n, i) - curcnt + k;
            break;
        }
    }
    int l = m, r = n, mid = l + (r - l)/2;
    while (l < r) {
        if (count_num(m, mid, lasti) < target) {
            l = mid + 1;
        }else {
            r = mid;
        }
        mid = l + (r - l)/2;
    }
    return mid;
}

int main(){
    priority_queue<int> que;
    que.top();
    get_cnt();
    int caseCnt = 0;
    cin >> caseCnt;
    while (caseCnt--) {
        int m = 0, n = 0, k = 0;
        cin >> m >> n >> k;
        cout << get_ans(m, n, k) << endl;
    }
    return 0;
}

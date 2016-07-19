//
//  TCCartInSupermarket.cpp
//  playground
//
//  Created by 張正昊 on 18/7/2016.
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

class CartInSupermarket{
public:
    vector<int> A;
    int B,N;
    
    
    bool check_split(int idx,int spl,int tml){//Sequence Index,Split Assign,Time Limit
        int use = 0, tim = 0, cnt = 1, x = A[idx];
        while (tim <= spl) {
            tim = ((tim+1)<<1)-1;
            cnt <<= 1;
            use++;
        }use--,cnt>>=1,tim = ((tim+1)>>1)-1;
        int rspl = spl - tim,rnum = cnt - rspl;
        x = max(0,x-rnum);
        return use + 1 + (x+cnt+rspl-1)/(cnt+rspl) <= tml;
    }
    /*
    bool check_split(int x, int numSplits, int timeLimit) {
        x = A[x];
        int time = 0;
        int numParts = 1;
        while (numParts <= numSplits) {
            numSplits -= numParts;
            numParts *= 2;
            ++time;
        }
        
        x = max(0, x - (numParts - numSplits));
        return (time + 1) + (x + numParts + numSplits - 1) / (numParts + numSplits) <= timeLimit;
    }
    */
    int minSplit(int idx,int tml){
        if(tml == 1){
            return (A[idx]==1)?0:B+1;//注意对时间限制为1的特判(这时候不能做划分操作)
        }
        int l = 0,r = A[idx],mid;
        while (l+1<r) {
            mid = l + ((r-l)>>1);
            if(check_split(idx, mid, tml)) r = mid;
            else l = mid+1;
        }
        if(check_split(idx, l, tml)) return l;
        return r;
    }
    
    bool check(int t){
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            cnt += minSplit(i, t);
            if(cnt > B) return false;
        }
        return cnt <= B;
    }
    
    int solve(){
        int l = 1,r = *max_element(A.begin(), A.end()),mid;
        while (l + 1 < r) {
            mid = l+((r-l)>>1);
            if(check(mid)) r = mid;
            else l = mid+1;
        }
        if(check(l)) return l;
        return r;
    }
    
    int calcmin(vector<int> _a,int _b){
        N = _a.size();
        A = _a;
        B = _b;
        return solve();
    }
    CartInSupermarket(){}
};

CartInSupermarket solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.calcmin({2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 114514810) << endl;
    cout << solver.calcmin({6,6,5},3) << endl;
    cout << solver.calcmin({12,5,6,2,6,8},4) << endl;
    cout << solver.calcmin({15,20,11,13,18,24,25,21,22,10,15,14,19},0) << endl;
    cout << solver.calcmin({671122748,846444748,84701624,608579554,672060899,967957440,31438849,734849843,376589643,904285209
        ,80693344,211737743,85405464,444633541,293184188,935462519,146753109,972886045,496631016,601669536
        ,257574086,958464570,6294570,546189534,668105964,601197313,784337929,921840143,70408284,722040626
        ,253400894,56411549,811940644,152086353,122638884,776352066,118932182,177589709,538122558,127914469
        ,523761221,290027568,734517444,819458123,699130727,784698122,810265337,283326309,593596316,368671876},6478) << endl;
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

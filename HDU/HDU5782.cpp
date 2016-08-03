//
//  HDU5782.cpp
//  playground
//
//  Created by 張正昊 on 2/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//PURE BITSET TRICK

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
#include <functional>
#include <numeric>
#include <bitset>

using namespace std;

const int MAXLEN = 10005;
char A[MAXLEN],B[MAXLEN];
int len;

bitset<MAXLEN> pfx_sfx,sfx_pfx,sum;//A_B
bitset<MAXLEN> aph_up[27],aph_down[27];//alphabet up:abcde down:edcba

void prep(){
    for(int i = 0;i < 26; i++){
        aph_up[i].reset();
        aph_down[i].reset();
    }
    for (int i = 0; i < len; i++) {
        aph_up[A[i]-'a'][i+1] = 1;
        aph_down[B[len-i-1]-'a'][i+1] = 1;
    }
}

int cur = 0;
void progress(){
    pfx_sfx <<= 1;
    pfx_sfx[1] = 1;
    pfx_sfx &= aph_up[B[cur]-'a'];
    
    
    sfx_pfx &= aph_down[A[cur]-'a'] >> (len-cur);
    sfx_pfx[++cur] = 1;
}

void solve(){
    cur = 0;
    prep();
    for (int i = 1; i <= len; i++) {
        progress();
        sum = pfx_sfx & sfx_pfx;
        if (sum.any()) {
            putchar('1');
        }else{
            putchar('0');
        }
    }
    puts("");
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %s %s",A,B) != EOF) {
        len = strlen(A);
        solve();
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

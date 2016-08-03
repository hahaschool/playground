//
//  HDU5785.cpp
//  playground
//
//  Created by 張正昊 on 3/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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

const int MAXLEN = 1000005;
const long long MODER = 1000000007;

char t[MAXLEN*2];
int p[MAXLEN*2];
int manacher(char *str){
    t[0] = '@',t[1] = '#';
    int len = strlen(str);
    for(int i = 0;i < len; i++){
        t[(i<<1)+2] = str[i];
        t[(i<<1)+3] = '#';
    }
    len = ((len+1)<<1);
    t[len] = '\0';
    
    int id = 0,mx = 0;
    for (int i = 1; i < len; i++) {
        if(mx > i) p[i] = min(mx-i,p[id*2-i]);
        else p[i] = 1;
        while(t[i-p[i]] == t[i+p[i]]) ++p[i];
        if(i + p[i] > mx) id = i,mx = i+p[i];
    }
    return len;
}

char str[MAXLEN];
int len,t_len;

typedef long long LL;

LL arr_dlt[MAXLEN],dst_dlt[MAXLEN];
LL arr_num[MAXLEN],dst_num[MAXLEN];
LL arr[MAXLEN],dst[MAXLEN];
void solve(){
    memset(arr_dlt, 0, sizeof(arr_dlt));
    memset(arr_num, 0, sizeof(arr_num));
    memset(dst_dlt, 0, sizeof(dst_dlt));
    memset(dst_num, 0, sizeof(dst_num));
    memset(arr, 0, sizeof(arr));
    memset(dst, 0, sizeof(dst));
    
    t_len = manacher(str);
    for (LL i = 1,j = 2; j < t_len; i++,j += 2) {
        LL ext = (p[j]>>1);
        if(ext){
            arr_dlt[i] += i;
            arr_dlt[i] %= MODER;
            arr_num[i]++;
            arr_dlt[i+ext] -= i-ext;
            arr_dlt[i+ext] %= MODER;
            arr_num[i+ext]--;
            
            dst_dlt[i-ext+1] += i+ext-1;
            dst_dlt[i-ext+1] %= MODER;
            dst_num[i-ext+1]++;
            dst_dlt[i+1] -= i-1;
            dst_dlt[i+1] %= MODER;
            dst_num[i+1]--;
        }
    }
    for (LL l = 1,r = 2,j = 3; r <= len; l++,r++,j+=2) {
        LL ext = (p[j]-1)>>1;
        if(ext){
            arr_dlt[r] += l;
            arr_dlt[r] %= MODER;
            arr_num[r]++;
            arr_dlt[r+ext] -= l-ext;
            arr_dlt[r+ext] %= MODER;
            arr_num[r+ext]--;
            
            dst_dlt[l-ext+1] += r+ext-1;
            dst_dlt[l-ext+1] %= MODER;
            dst_num[l-ext+1]++;
            dst_dlt[r] -= r-1;
            dst_dlt[r] %= MODER;
            dst_num[r]--;
        }
    }
    
    LL arr_leg = 0,arr_cur = 0;
    LL dst_leg = 0,dst_cur = 0;
    for(int i = 1;i <= len; i++){
        arr_leg -= arr_cur;
        arr_leg += arr_dlt[i];
        arr_cur += arr_num[i];
        arr[i] = arr_leg;
        arr_leg %= MODER;
        arr_cur %= MODER;
        
        dst_leg -= dst_cur;
        dst_leg += dst_dlt[i];
        dst_cur += dst_num[i];
        dst[i] = dst_leg;
        dst_leg %= MODER;
        dst_cur %= MODER;
    }
    
    long long res = 0;
    for(int i = 1;i < len; i++){
        res += arr[i] * dst[i+1];
        res %= MODER;
    }
    res %= MODER;
    if(res < 0) res += MODER;
    printf("%lld\n",res);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (scanf(" %s",str) != EOF) {
        len = strlen(str);
        solve();
    }
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

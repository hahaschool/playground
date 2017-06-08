#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005, MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],fail[MAXN];
    long long cnt[MAXN],num[MAXN];
    int str[MAXN],n;
    int q,last;

    int alloc(int plen){
        for (int i = 0; i < MAXC; i++) {
            ch[q][i] = 0;
        }
        len[q] = plen;
        num[q] = 0;
        fail[q] = 0;
        cnt[q] = 0;
        return q++;
    }

    void init(){
        q = 0;
        alloc(0);
        alloc(-1);
        last = 0;
        n = 0;
        str[n] = -1;
        fail[0] = 1;
    }

    int getfail(int x){
        while(str[n - len[x] - 1] != str[n]){
            x = fail[x];
        }
        return x;
    }

    void addchar(int c){
        c -= 'a';
        str[++n] = c;
        int cur = getfail(last);
        if(!ch[cur][c]){
            int now = alloc(len[cur] + 2);
            fail[now] = ch[getfail(fail[cur])][c];
            ch[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = ch[cur][c];
        cnt[last]++;
    }

    void count(){
        for(int i = q-1;i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
    }
} pal;

const long long MODER = 19930726;
long long get_mod(long long x){
    x %= MODER;
    if(x < 0) x += MODER;
    return x;
}
long long sum_mod(long long x,long long y){
    return get_mod(get_mod(x) + get_mod(y));
}
long long mul_mod(long long x,long long y){
    return get_mod(get_mod(x) * get_mod(y));
}
long long pow_mod(long long x,long long p){
    long long ret = 1;
    while(p){
        if(p&1) ret = mul_mod(ret,x);
        x = mul_mod(x,x);
        p >>= 1;
    }
    return ret;
}

int N;
long long K;
char buf[MAXN];

vector<pair<int, long long> > vec;

int main(int argc, char *argv[]) {

    while(scanf(" %d %lld",&N,&K) != EOF){
        scanf(" %s",buf);
        pal.init();
        for(int i = 0;i < N; i++){
            pal.addchar(buf[i]);
        }
        pal.count();
        vec.clear();
        for(int i = 2;i < pal.q; i++){
            if(pal.len[i]&1) vec.push_back(make_pair(pal.len[i],pal.cnt[i]));
        }
        sort(vec.begin(),vec.end());
        reverse(vec.begin(),vec.end());
        long long res = 1,acc = 0;
        for(int i = 0;i < vec.size(); i++){
            if(acc + vec[i].second <= K){
                res = mul_mod(res,pow_mod(vec[i].first,vec[i].second));
                acc += vec[i].second;
            }else{
                res = mul_mod(res,pow_mod(vec[i].first,K-acc));
                break;
            }
        }
        cout << res << '\n';
    }
    return 0;
}

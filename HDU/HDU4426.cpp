#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005, MAXC = 26, MAXK = 22;
const long long MODER = 777777777;

inline long long get_mod(long long x){
    if(x >= MODER || x < 0) x %= MODER;
    if(x < 0) x += MODER;
    return x;
}
inline long long sum_mod(long long x,long long y){
    return get_mod(get_mod(x) + get_mod(y));
}
inline long long mul_mod(long long x,long long y){
    return get_mod(get_mod(x) * get_mod(y));
}
inline long long pow_mod(long long x,long long p){
    long long ret = 1;
    while(p){
        if(p&1){
            ret = mul_mod(ret,x);
        }
        p >>= 1;
        x = mul_mod(x,x);
    }
    return ret;
}

struct PalTree{
    int k;
    int ch[MAXN][MAXC],len[MAXN],fail[MAXN];
    long long chrval[MAXK][MAXC];
    long long num[MAXN],cnt[MAXN],val[MAXN][MAXK];
    int str[MAXN],n;
    int last,q;

    int alloc(int plen){
        for(int i = 0;i < MAXC; i++){
            ch[q][i] = 0;
        }
        len[q] = plen;
        num[q] = cnt[q] = fail[q] = 0;
        for(int i = 1;i <= k; i++){
            val[q][i] = 0;
        }
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

            for(int i = 1;i <= k; i++){
                val[now][i] = sum_mod(val[cur][i], mul_mod(pow_mod(26,(len[now]&1)?len[now]/2:len[now]/2-1),chrval[i][c]));
            }
        }
        last = ch[cur][c];
        cnt[last]++;
    }

    void count(){
        for(int i = q-1; i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
    }
} pal;

int n,m;
char buf[MAXN];
long long val[MAXK][MAXC];
long long req[MAXK];

int cmp_k;
bool cmp(int a,int b){
    return pal.val[a][cmp_k] < pal.val[b][cmp_k];
}
int pts[MAXN];

void solve(){
    pal.init();
    pal.k = m;
    for(int i = 1;i <= m; i++){
        for(int j = 0;j < 26; j++){
            pal.chrval[i][j] = val[i][j];
        }
    }
    for(int i = 0;i < n; i++){
        pal.addchar(buf[i]);
    }
    pal.count();
    
    for(int i = 2, j = 0;i < pal.q; i++, j++){
        pts[j] = i;
    }

    for(int i = 1;i <= m;i++){
        cmp_k = i;
        sort(pts,pts+pal.q-2,cmp);
        for(int j = 0;j < pal.q-2; j++){
            if(pal.cnt[pts[j]] >= req[i]){
                cout << pal.val[pts[j]][i] << '\n';
                break;
            }else{
                req[i] -= pal.cnt[pts[j]];
            }
        }
    }
}

int main(int argc, char *argv[]) {

    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %d %d",&n,&m);
        scanf(" %s",buf);
        for(int i = 1;i <= m; i++){
            cin >> req[i]; //scanf(" %lld",&req[i]);
            for(int j = 0;j < 26; j++){
                cin >> val[i][j];// scanf(" %lld",&val[i][j]);
            }
        }
        solve();
        puts("");
    }

    return 0;
}

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 100005,MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],num[MAXN],fail[MAXN],cnt[MAXN];
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

int len;
char buf[MAXN];
long long num_fwd[MAXN],num_rev[MAXN];
long long nums_fwd[MAXN],nums_rev[MAXN];

int main(int argc, char *argv[]) {

    //int caseCnt = 0;
    //scanf(" %d",&caseCnt);
    //for(int d = 1;d <= caseCnt;d++){
    while( scanf(" %s",buf) != EOF){
        pal.init();
        len = strlen(buf);
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i]);
            num_fwd[i+1] = pal.num[pal.last];
            num_fwd[i+1] += num_fwd[i];
        }
        pal.init();
        for(int i = len-1; i >= 0; i--){
            pal.addchar(buf[i]);
            num_rev[i+1] = pal.num[pal.last];
        }
        long long res = 0;
        for(int i = 1;i < len; i++){
            res += num_fwd[i] * num_rev[i+1];
        }
        cout << res << '\n';
    }
    return 0;
}

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

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
} pal[2];

char buf[MAXN];
int len;
int mxlen_fwd[MAXN],mxlen_rev[MAXN];

int main(int argc, char *argv[]){

    while(scanf(" %s",buf) != EOF){
        pal[0].init();
        pal[1].init();
        len = strlen(buf);
        for(int i = 0;i < len; i++){
            pal[0].addchar(buf[i]);
            mxlen_fwd[i] = pal[0].len[pal[0].last];
        }
        for(int i = len-1; i >= 0; i--){
            pal[1].addchar(buf[i]);
            mxlen_rev[i] = pal[1].len[pal[1].last];
        }
        int res = 2;
        for(int i = 0,j = 1;j < len; i++,j++){
            res = max(res,mxlen_fwd[i] + mxlen_rev[j]);
        }
        printf("%d\n",res);
    }

    return 0;
}

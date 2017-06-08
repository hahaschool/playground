#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <set>
#include <ctime>
#include <vector>

using namespace std;

const int MAXN = 1005,MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],fail[MAXN],len[MAXN],num[MAXN],cnt[MAXN];
    int str[MAXN],n;
    int q,last;

    int alloc(int plen){
        for (int i = 0; i < MAXC; i++) {
            ch[q][i] = 0;
        }
        fail[q] = num[q] = cnt[q] = 0;
        len[q] = plen;
        return q++;
    }

    void init(){
        q = last = n = 0;
        alloc(0);
        alloc(-1);
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
    }
} pal[MAXN];

char buf[MAXN];
int len;
int res[MAXN][MAXN];
int Q;

int main(int argc, char *argv[]) {
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %s",buf);
        len = strlen(buf);
        for(int i = 1;i <= len; i++){
            pal[i].init();
            for(int j = i-1;j < len; j++){
                pal[i].addchar(buf[j]);
                res[i][j+1] = pal[i].q-2;
            }
        }
        scanf(" %d",&Q);
        for(int i = 1;i <= Q; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            printf("%d\n",res[a][b]);
        }
    }
    
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 400005,MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],fail[MAXN],len[MAXN];
    long long num[MAXN],cnt[MAXN][2];
    int last,q;
    int str[MAXN],n;
    
    int alloc(int plen){
        for (int i = 0; i < MAXC; i++) {
            ch[q][i] = 0;
        }
        len[q] = plen;
        num[q] = 0;
        fail[q] = 0;
        cnt[q][0] = cnt[q][1] = 0;
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

    void addchar(int c,int id){
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
        cnt[last][id]++;
    }

    void count(){
        for(int i = q-1; i >= 0; i--){
            cnt[fail[i]][0] += cnt[i][0];
            cnt[fail[i]][1] += cnt[i][1];
        }
    }
} pal;

char buf[MAXN];

int main(int argc, char *argv[]) {

    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        printf("Case #%d: ",d);
        scanf(" %s",buf);
        int len = strlen(buf);
        pal.init();
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i], 0);
        }
        scanf(" %s",buf);
        len = strlen(buf);
        pal.n = 0;
        pal.last = 0;
        for(int i = 0;i < len; i++){
            pal.addchar(buf[i], 1);
        }
        pal.count();
        long long res = 0;
        for(int i = 2;i < pal.q; i++){
            res += pal.cnt[i][0] * pal.cnt[i][1];
        }
        cout << res << '\n';
    }

    return 0;
}

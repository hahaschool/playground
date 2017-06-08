#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 100005,MAXC = 26;

struct PalTree{
    int ch[MAXN][MAXC],len[MAXN],num[MAXN],fail[MAXN];
    int str[MAXN],n;
    int q,last;

    int alloc(int plen){
        for (int i = 0; i < MAXC; i++) {
            ch[q][i] = 0;
        }
        len[q] = plen;
        num[q] = 0;
        fail[q] = 0;
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
    }
}pal;

string STR;

int main(int argc, char *argv[]) {

    while(cin >> STR){
        pal.init();
        for(int i = 0;i < STR.size(); i++){
            pal.addchar(STR[i]);
            printf("%d",pal.q-2);
            if(i == STR.size()-1) putchar('\n');
            else putchar(' ');
        }
    }

    return 0;
}

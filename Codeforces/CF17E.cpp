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

struct PalTree{
    //num : 节点表示回文串的后缀回文串有多少个
    //cnt : 节点表示了多少回文串
    static const int MAXN = 2000005,MAXC = 26;
    int fail[MAXN],num[MAXN],len[MAXN];
    vector<pair<int,int> > ch[MAXN];
    int str[MAXN],n;
    int q,last;
    int alloc(int newlen){
        ch[q].clear();
        num[q] = 0;
        len[q] = newlen;
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
        while (str[n - len[x] - 1] != str[n]) {
            x = fail[x];
        }
        return x;
    }

    int getch(int x,int c){
        for(int i = 0;i < ch[x].size(); i++){
            if(ch[x][i].first == c) return ch[x][i].second;
        }
        return 0;
    }

    void setch(int x,int c,int v){
        int t = 0;
        if((t = getch(x,c))) ch[x][t].second = v;
        else ch[x].push_back(make_pair(c,v));
    }

    void addchar(int c){
        c -= 'a';
        str[++n] = c;
        int cur = getfail(last);
        if(!getch(cur,c)){
            int now = alloc(len[cur] + 2);
            fail[now] = getch(getfail(fail[cur]),c);
            setch(cur,c,now);
            num[now] = num[fail[now]] + 1;
        }
        last = getch(cur,c);
    }
} pal;

const long long MODER =  51123987;

int N;
string STR;

long long nums_fwd[PalTree::MAXN];

int main() {
    while(cin >> N >> STR){
        pal.init();
        long long res = 0;
        for (int i = 0; i < STR.size(); i++) {
            pal.addchar(STR[i]);
            nums_fwd[i+1] = pal.num[pal.last];
        }
        for(int i = 1;i <= STR.size(); i++){
            nums_fwd[i] += nums_fwd[i-1];
            nums_fwd[i] %= MODER;
        }
        res = (nums_fwd[STR.size()] * (nums_fwd[STR.size()] - 1LL)) >> 1LL;
        res %= MODER;
        pal.init();
        for(int i = STR.size() - 1; i >= 0; i--){
            pal.addchar(STR[i]);
            long long num_rev = pal.num[pal.last];
            if(i) res -= num_rev * nums_fwd[i], res %= MODER; 
        }
        res %= MODER;
        if(res < 0) res += MODER;
        cout << res << endl;
    }

    return 0;
}

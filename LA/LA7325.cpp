#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int mxn = 500000 + 10;
string buf;
int st[mxn],lng[mxn];
int id[mxn];
int n;
void init(){
    n = buf.size();
    int last = 1;
    for(int i=0;i<n;i++){
        id[i] = last;
        if(buf[i] == ' '){
            last ++;
            id[i] = -1;
        }
    }
    last = -1;
    for(int i=0;i<n;i++){
        if(id[i] == -1)
            continue;
        if(id[i] != last){
            last = id[i];
            st[last] = i;
            lng[last] = 1;
            continue;
        }
        lng[last] ++;
    }
}
int solve(int a){
    int ret = 0;
    for(int i=0;i<n;i+=a){
        if(id[i] == -1)
            i ++;
        if(i >= st[id[i]]){
            ret += lng[id[i]]+1;
            i = st[id[i]];
        }
    }
    if(ret)ret --;
    return ret;
}
int main(){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif

    while(getline(cin,buf)){
        init();
        int a,b;
        cin >> a >> b;
        cin.ignore();
        for(int i=a;i<=b;i++){
            printf("%d\n",solve(i));
        }
    }

    return 0;
}
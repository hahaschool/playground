#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

struct Node{
    long long mi,mx;
    bool operator < (const Node &b) const{
        if(mi != b.mi) return mi > b.mi;
        return mx > b.mx;
    }
    bool operator > (const Node &b) const{
        if(mi != b.mi) return mi < b.mi;
        return mx < b.mx;
    }
};

long long N,K;
map<Node,long long> mp;

void make(){
    mp.clear();
    priority_queue<Node,vector<Node>,greater<Node> > que;
    if(N&1) que.push((Node){(N-1LL)/2LL,(N-1LL)/2LL});
    else que.push((Node){N/2LL-1LL,N/2LL});
    mp[que.top()] = 1;
    while(!que.empty()){
        Node cur = que.top();
        que.pop();
        //cerr << cur.mi << ' ' << cur.mx << " --> " << mp[cur] << endl;;
        if(cur.mi){
            if(cur.mi&1){
                Node nxt = (Node){(cur.mi-1LL)/2LL,(cur.mi-1LL)/2LL};
                if(!mp.count(nxt)){
                    que.push(nxt);
                }
                mp[nxt] += mp[cur];
            }else{
                Node nxt = (Node){cur.mi/2LL-1LL,cur.mi/2LL};
                if(!mp.count(nxt)){
                    que.push(nxt);
                }
                mp[nxt] += mp[cur];
            }
        }
        if(cur.mx){
            if(cur.mx&1){
                Node nxt = (Node){(cur.mx-1LL)/2LL,(cur.mx-1LL)/2LL};
                if(!mp.count(nxt)){
                    que.push(nxt);
                }
                mp[nxt] += mp[cur];
            }else{
                Node nxt = (Node){cur.mx/2LL-1LL,cur.mx/2LL};
                if(!mp.count(nxt)){
                    que.push(nxt);
                }
                mp[nxt] += mp[cur];
            }
        }
    }
}

void solve(){
    make();
    long long acc = 0;
    for(map<Node, long long>::iterator it = mp.begin(); it != mp.end();it++){
        acc += it->second;
        if(acc >= K) {
            cout << it->first.mx << ' ' << it->first.mi << '\n';
            return;
        }
    }
}

int main(int argc, char *argv[]){

    int caseCnt;
    cin >> caseCnt;
    for(int d = 1;d <= caseCnt ;d++){
        printf("Case #%d: ",d);
        cin >> N >> K;
        solve();
    }

    return 0;
}

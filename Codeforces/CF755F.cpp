#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
int N,K,seq[MAXN];
bool vis[MAXN];

vector<vector<int> > cyc;

void decomp(){
    for(int i = 1; i <= N; i++){
        if(!vis[i]){
            int cur = seq[i];
            cyc.push_back(vector<int>());
            cyc[cyc.size()-1].push_back(i);
            while(cur != i){
                vis[cur] = true;
                cyc[cyc.size()-1].push_back(cur);
                cur = seq[cur];
            }
        }
    }
}

const int T = 100;
int cnt[T+1];
vector<int> oth,all;

int solvemax(){
    sort(all.begin(),all.end());
    int cnt = 0,tk = K;
    for(int i = (int)all.size()-1; i >= 0; i--){
        int quota = all[i]/2;
        if(!tk) break;
        if(tk < quota){
            all[i] -= tk*2;
            cnt += tk*2;
            tk = 0;
            break;
        }else{
            all[i] -= quota*2;
            cnt += quota*2;
            tk -= quota;
        }
    }
    for(int i = 0;i < all.size(); i++){
        if(!tk) break;
        if(all[i]){
            tk--;
            cnt++;
        }
    }
    return cnt;
}

bitset<1000001> bs;

int solvemin(){
    bs.set(0);
    //oth part
    for(int i = 0;i < oth.size(); i++){
        bitset<1000001> tbs = bs << oth[i];
        tbs.set(oth[i]);
        bs |= tbs;
    }
    //cnt part
    for(int i = 1;i <= T; i++){
        int cur = 1;
        while(cur <= cnt[i]){
            bitset<1000001> tbs = bs << i*cur;
            tbs.set(i*cur);
            bs |= tbs;
            cnt[i] -= cur;
            cur <<= 1;
        }
        bitset<1000001> tbs = bs << i*cnt[i];
        tbs.set(i*cnt[i]);
        bs |= tbs;
    }

    if(bs.test(K)) return K;
    return K+1;
}



int main(int argc, char *argv[]){
    
    cin >> N >> K;
    for(int i = 1;i <= N; i++){
        cin >> seq[i];
    }
    decomp();
    for(int i = 0;i < cyc.size(); i++){
        all.push_back(cyc[i].size());
        if(cyc[i].size() > T){
            oth.push_back(cyc[i].size());
        }else{
            cnt[cyc[i].size()]++;
        }
    }
    cout <<solvemin() << ' ' <<  solvemax() << endl;
    /*
    for(int i = 0;i < cyc.size(); i++){
        for(int j = 0;j < cyc[i].size(); j++){
            cerr << cyc[i][j] << ' ';
        }cerr << endl;
    }
    */


    
    return 0;
}

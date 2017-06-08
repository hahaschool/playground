#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Event{
    int typ;//2:ship arrive 1:crane done
    int id;
    long long time;
    bool operator < (const Event &b) const{
        if(time != b.time) return time > b.time;
        if(typ != b.typ) return typ > b.typ;
        return id > b.id;
    }
};
priority_queue<Event> evtque;

struct Ship{
    int typ;
    long long load,arrival;
    int id;
    bool operator < (const Ship &b) const{
        if(arrival != b.arrival) return arrival > b.arrival;
        return id > b.id;
    }
};
int assign[100005];
Ship ships[100005];
priority_queue<Ship> shipque;

struct Crane{
    long long idle;
    int id;
    bool operator < (const Crane &b) const{
        if(idle != b.idle) return idle < b.idle;
        return id < b.id;
    }
};
set<Crane> freelist[11];
long long lastidle[100005];
long long cranespd[100005];
vector<int> cranetyp[100005];
bool assigncrane(int shipid){
    Ship &cur = ships[shipid];
    if(freelist[cur.typ].size() == 0) return false;
    int craneid = freelist[cur.typ].begin()->id;
    assign[shipid] = craneid;
    long long newidle = max(lastidle[craneid],ships[shipid].arrival) + (cur.load + cranespd[craneid] - 1)/cranespd[craneid];
    for(int i = 0;i < cranetyp[craneid].size(); i++){
        freelist[cranetyp[craneid][i]].erase(freelist[cranetyp[craneid][i]].find((Crane){lastidle[craneid],craneid}));
    }
    lastidle[craneid] = newidle;
    evtque.push((Event){1,craneid,newidle});
    return true;
}
void insertcrane(int craneid){
    for(int i = 0;i < cranetyp[craneid].size(); i++){
        freelist[cranetyp[craneid][i]].insert((Crane){lastidle[craneid],craneid});
    }
}

int N,M,C;
void solve(){
    long long today = 0;//FUCK THAT!
    while(shipque.size()){
        while(evtque.size() && evtque.top().time == today){
            Event cur = evtque.top();evtque.pop();
            if(cur.typ == 1){
                insertcrane(cur.id);
            }else if(cur.typ == 2){
                shipque.push(ships[cur.id]);
            }
        }
        if(assigncrane(shipque.top().id)){
                shipque.pop();
        }
        today = evtque.top().time;
    }
    for(int i = 1;i <= N; i++){
        printf("%d\n",assign[i]);
    }
}

inline bool scan_d(int &num)  
{
    char in;bool IsN=false;
    in=getchar();
    if(in==EOF) return false;
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();
    if(in=='-'){ IsN=true;num=0;}
    else num=in-'0';
    while(in=getchar(),in>='0'&&in<='9'){
        num*=10,num+=in-'0';
    }
    if(IsN) num=-num;
    return true;
}

int main(int argc, char *argv[]){

    //freopen("seaport.in","r",stdin);
    //freopen("seaport.out","w",stdout);
    scan_d(N);
    scan_d(M);
    scan_d(C);
    //scanf(" %d %d %d",&N,&M,&C);
    for(int i = 1;i <= N; i++){
        int d,c,s;
        scan_d(d);
        scan_d(c);
        scan_d(s);
        //scanf(" %d %d %d",&d,&c,&s);
        ships[i] = (Ship){c,s,d,i};
        shipque.push(ships[i]);
    }
    for(int i = 1;i <= M; i++){
        int v,cn;
        scan_d(v);
        scan_d(cn);
        //scanf(" %d %d",&v,&cn);
        cranespd[i] = v;
        for(int j = 1;j <= cn; j++){
            int ca;
            scan_d(ca);
            //scanf(" %d",&ca);
            cranetyp[i].push_back(ca);
        }
        evtque.push((Event){1,i,0});
    }
    solve();

    return 0;
}

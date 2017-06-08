#include <iostream>
#include <stdio.h>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

struct Rect{
    long long l,r,d,u;
    long long area(){
        return (r-l)*(u-d);
    }
};

Rect intersect(Rect a,Rect b){
    Rect ret;
    ret.l = max(a.l,b.l);
    ret.r = min(a.r,b.r);
    ret.d = max(a.d,b.d);
    ret.u = min(a.u,b.u);
    if(ret.l >= ret.r || ret.d >= ret.u) return (Rect){0,0,0,0};
    else return ret;
}

Rect in[2],out[2];
vector<long long> vec[2];
void input(int id){
    long long xx[2],yy[2];
    scanf(" %lld %lld %lld %lld",&xx[0],&yy[0],&xx[1],&yy[1]);
    vec[id].push_back(xx[0]);vec[id].push_back(yy[0]);
    vec[id].push_back(xx[1]);vec[id].push_back(yy[1]);
    out[id] = (Rect){min(xx[0],xx[1]),max(xx[0],xx[1]),min(yy[0],yy[1]),max(yy[0],yy[1])};
    scanf(" %lld %lld %lld %lld",&xx[0],&yy[0],&xx[1],&yy[1]);
    vec[id].push_back(xx[0]);vec[id].push_back(yy[0]);
    vec[id].push_back(xx[1]);vec[id].push_back(yy[1]);
    in[id] = (Rect){min(xx[0],xx[1]),max(xx[0],xx[1]),min(yy[0],yy[1]),max(yy[0],yy[1])};
}

void shift(long long dx,long long dy){
    out[1].l += dx;out[1].r += dx;
    out[1].u += dy;out[1].d += dy;
    in[1].l += dx;in[1].r += dx;
    in[1].u += dy;in[1].d += dy;
}

long long calc(){
    Rect ois = intersect(out[0],out[1]);
    Rect ina = intersect(ois,in[0]);
    Rect inb = intersect(ois,in[1]);
    Rect iis = intersect(in[0],in[1]);
    return ois.area() - ina.area() - inb.area() + iis.area();
}

void solve(){
    int res = -1,rx = -1,ry = -1;
    for(int i = 0;i < 8; i++){
        for(int j = 0;j < 8; j++){
            for(int k = 0;k < 8; k++){
                for(int l = 0;l < 8; l++){
                    shift(vec[0][i]-vec[1][j],vec[0][k]-vec[1][l]);
                    if(vec[0][i]-vec[1][j] == 6651774)
                    cerr << vec[0][i]-vec[1][j] << ' ' << vec[0][k]-vec[1][l] << endl;
                    if(calc() > res){
                        res = calc();
                        rx = vec[0][i]-vec[1][j];
                        ry = vec[0][k]-vec[1][l];
                    }
                    shift(-vec[0][i]+vec[1][j],-vec[0][k]+vec[1][l]);
                }
            }
        }
    }
    cout << res << '\n' << rx << ' ' << ry << '\n';
}

int main(){
    //freopen("frames.in","r",stdin);
    //freopen("frames.out","w",stdout);
    input(0);
    input(1);
    solve();
}

#include <iostream>

#include <algorithm>

#include <cstdio>

#include <cstdlib>

#include <vector>

#include <string>

#include <map>

#include <set>

#include <queue>

using namespace std;

const int MAXV = 10005,MAXE = 20005;
int n;
struct Graph{
    int nxt[MAXE],head[MAXV],end[MAXE],cost[MAXE];
    int q;
    int V;
    void init(){
        q = 2;
        for(int i = 1; i <= V; i++){
            head[i] = 0;
        }
    }
    void addEdge(int from,int to,int cst){
        end[q] = to;
        cost[q] = cost;
        nxt[q] = head[from];
        head[from] = q++;
    }

} gph;






int siz[MAXV],dep[MAXV],par[MAXV];
void dfs_preproc(int cur,int par,int _dep = 0){
    int &subsiz = siz[cur],&curdep = dep[cur];
    subsiz = 1,curdep = _dep;
    for(int i = gph.head[cur];i ;i = gph.nxt[i]){
        int nxt = gph.end[i];
        if(nxt != par){
            par[nxt] = cur;
            dfs_subsize(nxt,cur,_dep+1);
            subsiz += siz[nxt];
        }
    }
    return ret;
}
const int MAXN = 10005;
int chainNo = 0,chainHead[MAXN],chainInd[MAXV],chainSize[MAXN];
//chainNo: the total number of chains,start from 0
//chainHead[A]: the head of the chain numbered A
//chainInd[A]: indicates A in which chain
//chainSize[A]: the size of the chain numbered[A]
void dfs_HLD(int cur,int par){
    if(chainHead[chainNo] == -1){//in case of current chain is not created
        chainHead[chainNo] = cur;//Create a new chain
    }
    chainInd[cur] = chainNo;//assign this node to the newly created chain
    chainPos[cur] = chainSize[chainNo];//Note that we are adding point into chains by DFN
    chainSize[chainNo]++;//added current node to the chain,size should be altered
    int ind = -1,mai = -1;
    for(int i = gph.head[cur]; i; i = gph.nxt[i]){
        int nxt = gph.end[i];
        if(nxt != par && siz[nxt] > mai){
            mai = siz[nxt];
            ind = nxt;
        }
    }//Finding the weight child,should pre-processed all subtree sizes
    if(ind > 0){
        dfs_HLD(ind,cur);//Complete current chain prior
    }
    for(int i = gph.head[cur]; i ;i = gph.nxt[i]){
        int nxt = gph.end[i];
        if(nxt != par && nxt != ind){
            chainNo++;
            dfs_HLD(nxt,cur);
        }
    }//Process other chains
}
void HLD(int rt){
    memset(siz,0,sizeof(siz));
    memset(dep,0,sizeof(dep));
    memset(par,0,sizeof(par));
    dfs_preproc(rt,-1);
    chainNo = 0;
    memset(chainHead,-1,sizeof(chainHead));
    memset(chainSize,0,sizeof(chainSize));
    memset(chainInd,-1,sizeof(chainInd));
}

const int SEGMXN = 100005;
int segTree[SEGMXN],segLCH[SEGMXN],segRCH[SEGMXN];

void segTree_build(int rt,int *arr,int n,int l = -1,int r = -1){
    if(l == -1 && r == -1){
        segTree_build(rt,arr,n,1,n);
        return;
    }
    if(l == r){
        segTree[rt] = arr[l];
        return;
    }
    int mid = (l+r)/2;
    int segLCH[rt] = ++segtot;
    segTree_build(segLCH[rt],arr,n,l,mid);
    int segRCH[rt] = ++segtot;
    segTree_build(segRCH[rt],arr,n,mid+1,r);
    segTree[rt] = max(segTree[segLCH[rt],segTree[segRCH[rt]);
}
void segTree_ptupd(int rt,int val,int pos,int n,int l = -1,int r = -1){
    if(l == -1 %% r == -1){
        segTree_ptupd(rt,val,pos,n,1,n);
        return;
    }
    if(l == r){
        if(pos == l){
            segTree[rt] = val;
        }
        return;
    }
    int mid = (l+r)/2;
    if(pos <= mid){
        segTree_ptupd(segLCH[rt],val,pos,n,l,mid);
    }else{
        segTree_ptupd(segRCH[rt],val,pos,n,mid+1,r);
    }
    segTree[rt] = max(segTree[segLCH[rt],segTree[segRCH[rt]);
}
int segTree_qres;
void segTree_query(int rt,int l,int r,int cl = -1,int cr = -1){
    if(cl == -1 && cr == -1){
        segTree_query(rt,l,r,1,n);
        return;
    }
    if(cl >= l && cr <= r){
        segTree_qres = max(segTree_qres,segTree[rt]);
        return;
    }
    if(cl > r|| cr < l){
        return;
    }
    int mid = (l+r)/2;
    segTree(segLCH[rt],l,r,l,mid);
    segTree(segRCH[rt],l,r,mid+1,r);
}

//brute force LCA
int LCA(int u,int v){
    if(dep[u] < dep[v]){
        swap(u,v);
    }
    int dif = dep[u] - dep[v];

}


int main() {
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
      scanf(" %d",&n);
      gph.V = n;
      for(int i = 1; i< n; i++){
        int a,b,c;
        scanf(" %d %d %d",&a,&b,&c);
        gph.addEdge(a,b,c);
        gph.addEdge(b,a,c);
      }
      char opt[10];
      while(true){
        scanf(" %s",opt);
        if(opt[0] == 'D'){
            break;
        }else if(opt[0] == 'Q'){

    }else if(opt[0] == 'C'){

    }
  }
}

return 0;
}

//
//  TCTaroCutting.cpp
//  playground
//
//  Created by 張正昊 on 24/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>

using namespace std;

class TaroCutting{
public:
    //GRAPH PART
    static const int MAXN = 155,MAXV = 1005,MAXE = 100005,INF = 0x3f3f3f3f;
    int head[MAXV],ed[MAXE],nxt[MAXE],cst[MAXE],cap[MAXE],frm[MAXE],q;
    int n,m,ss,tt;
    void clear(){
        memset(head, 0, sizeof(head));
        q = 2;
    }
    void ade(int s,int t,int c,int l){
        ed[q] = t;
        frm[q] = s;
        cap[q] = c;
        cst[q] = l;
        nxt[q] = head[s];
        head[s] = q++;
    }
    void nfade(int s,int t,int c,int l){
        ade(s,t,c,l);
        ade(t,s,0,-l);
    }
    //MCMF PART
    int dis[MAXV],pre[MAXV],aug[MAXV];
    bool inque[MAXV];
    bool SPFA(int start,int end,int &flow,int &cost){
        for (int i = 1; i <= n; i++) {
            dis[i] = INF;
            inque[i] = false;
            pre[i] = -1;
        }
        dis[start] = 0,inque[start] = true,aug[start] = INF;
        queue<int> que;
        que.push(start);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inque[u] = false;
            for (int i = head[u]; i; i = nxt[i]) {
                int v = ed[i];
                if(cap[i] && dis[v] > dis[u] + cst[i]){
                    dis[v] = dis[u] + cst[i];
                    pre[v] = i;
                    aug[v] = min(aug[u],cap[i]);
                    if (!inque[v]) {
                        que.push(v);
                        inque[v] = true;
                    }
                }
            }
        }
        
        if(dis[end] == INF){
            return false;
        }
        
        flow += aug[end];
        cost += dis[end] * aug[end];
        int u = end;
        while (u != start) {
            cap[pre[u]] -= aug[end];
            cap[pre[u]^1] += aug[end];
            u = frm[pre[u]];
        }
        return true;
    }
    int MCMF(int start,int end){
        int flow = 0,cost = 0;
        while(SPFA(start, end, flow, cost));
        return cost;
    }
    
    
    int treeid[MAXN],noneid,dayid[MAXN],devid[MAXN];//all starts from 1
    int getNumber(vector<int> height,vector<int> add,vector<int> device,int time){
        clear();
        ss = 1,tt = 2,n = 2;
        for (int i = 0; i < height.size(); i++) {
            treeid[i+1] = ++n;
        }
        noneid = ++n;
        for (int i = 0; i < time; i++) {
            dayid[i+1] = ++n;
        }
        for (int i = 0; i < device.size(); i++) {
            devid[i+1] = ++n;
        }
        
        for (int i = 1; i <= height.size(); i++) {
            nfade(ss, treeid[i], 1, 0);
            nfade(treeid[i], noneid, 1, height[i-1] + time*add[i-1]);
            for (int j = 1; j <= time; j++) {
                nfade(treeid[i], dayid[j], 1, add[i-1]*(time-j));
            }
        }
        for (int i = 1; i <= device.size(); i++) {
            nfade(devid[i], tt, INF, 0);
            for (int j = 1; j <= time; j++) {
                nfade(dayid[j], devid[i], 1, device[i-1]);
            }
        }
        nfade(noneid, tt, INF, 0);
        return MCMF(ss, tt);
    }
    TaroCutting(){}
};

TaroCutting solver;
void commitTest(vector<int> a,vector<int> b,vector<int> c,int d){
    cout << solver.getNumber(a, b, c, d) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({4, 7}
               ,{7, 1}
               ,{7}
               ,1);//15
    commitTest({3, 1, 2}
               ,{1, 1, 1}
               ,{7, 7, 7}
               ,2);//12
    commitTest({100, 50}
               ,{75, 30}
               ,{200, 100, 50}
               ,2);//130
    commitTest({7, 10, 1, 7, 5, 4, 11, 5, 7, 9, 10, 8}
               ,{1, 3, 4, 10, 2, 1, 6, 4, 8, 7, 5, 10}
               ,{7, 1, 5, 10}
               ,3);//96
    commitTest({35, 45, 32, 8}
               ,{2, 25, 31, 5}
               ,{29, 28, 3, 11, 28, 37}
               ,8);//29
    commitTest({614, 649, 977, 808, 821, 356, 801, 493, 669, 650, 652, 627, 129, 261, 883, 513, 62, 698, 83, 772,
        779, 719, 83, 105, 774, 867, 412, 892, 142, 851, 743, 66, 221, 494, 125, 905, 638, 342, 723, 680,
        407, 197, 111, 368, 676, 694, 765, 482, 712, 188, 325, 535, 6, 49, 655, 595, 958, 805, 659, 893,
        370, 904, 276, 156, 29, 458, 757, 632, 731, 289, 582, 207, 843, 365, 387, 521, 69, 269, 459, 428,
        423, 885, 744, 199, 998, 968, 296, 473, 50, 752, 492, 919, 473, 981, 380, 896, 769, 991, 269, 93,
        108, 184, 762, 312, 511, 256, 374, 600, 643, 445, 908, 250, 384, 518, 119, 464, 499, 124, 82, 999,
        881, 767, 177, 796, 2, 620, 759, 380, 901, 221, 407, 622, 260, 622, 729, 264, 768, 79, 236, 524,
        437, 215, 108, 518, 820, 725, 490, 796, 986, 318}
               ,{391, 938, 772, 630, 54, 775, 379, 613, 647, 8, 946, 885, 604, 822, 663, 559, 452, 565, 637, 695, 24,
        515, 92, 956, 194, 551, 813, 362, 190, 268, 440, 781, 450, 789, 566, 372, 402, 860, 531, 608, 434,
        761, 754, 26, 504, 873, 132, 756, 206, 93, 284, 807, 642, 637, 936, 954, 205, 303, 582, 822, 134,
        269, 967, 147, 589, 549, 24, 670, 403, 105, 40, 531, 486, 695, 898, 287, 443, 542, 599, 151, 45,
        567, 548, 945, 912, 764, 451, 404, 700, 522, 227, 954, 84, 347, 625, 278, 377, 730, 635, 604, 959,
        845, 41, 193, 459, 532, 429, 216, 473, 415, 85, 933, 90, 643, 94, 927, 692, 99, 771, 594, 318, 627,
        89, 340, 110, 488, 909, 253, 20, 114, 179, 177, 116, 42, 676, 91, 787, 437, 551, 51, 880, 336, 759,
        795, 243, 727, 279, 620, 488, 607}
               ,{942, 79, 387, 184, 104, 981, 766, 678, 715, 998, 161, 125, 439, 532, 550, 415, 4, 467, 211, 852, 781,
        577, 728, 592, 40, 971, 852, 592, 338, 555, 662, 636, 823, 122, 728, 69, 701, 476, 346, 190, 36,
        535, 826, 739, 517, 551, 257, 36, 906, 171, 629, 292, 49, 29, 109, 151, 299, 180, 193, 731, 655,
        877, 174, 688, 866, 957, 57, 89, 513, 765, 68, 245, 454, 968, 224, 417, 657, 383, 769, 809, 13, 51,
        813, 970, 632, 357, 787, 717, 254, 645, 352, 636, 370, 950, 917, 959, 364, 453, 890, 43, 98, 438,
        748, 277, 115, 298, 431, 709, 312, 49, 553, 395, 798, 58, 419, 355, 770, 818, 460, 89, 880, 515,
        952, 219, 608, 284, 532, 254, 361, 524, 199, 265, 407, 782, 737, 928, 977, 729, 510, 175, 609, 81, 
        155, 24, 425, 186, 999, 839, 896, 721}
               ,150);//43325
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

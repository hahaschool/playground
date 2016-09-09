//
//  ACDream1361.cpp
//  playground
//
//  Created by 張正昊 on 24/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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
#include <functional>
#include <numeric>
#include <bitset>

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])

using namespace std;

typedef long long LL;

const int MAXN = 2005;
int tab[MAXN][MAXN];
int opt[MAXN][MAXN];

struct Tag{
    int type;//1:table 2:TR 3:TD
    bool end;
    int rowspan,colspan;
};

bool error_happened;
Tag lexical(){
    //will stop when meet "<>"
    Tag ret = {-1,false,1,1};
    bool open = false;
    char ch;
    string buf;
    int mode = 0;//0:no arg 1:rowspan 2:colspan
    bool arg_open = false;
    int argcnt = 0;
    while ((ch = cin.get()) != EOF) {
        if(open){
            if(ch == '\n' || ch == ' '){
                continue;
            }
            if(ch == '>'){
                if(buf.size()) error_happened = true;
                return ret;
            }
            if(ret.type == 0){
                if(ch == '/'){
                    if(ret.end){
                        //double '/' mark
                        error_happened = true;
                        return ret;
                    }
                    ret.end = true;
                    continue;
                }
                if(isalpha(ch)){
                    ch = tolower(ch);
                    buf += ch;
                    if(buf.size() == 2){
                        if(buf == "tr"){
                            buf.clear();
                            ret.type = 2;
                        }else if(buf == "td"){
                            buf.clear();
                            ret.type = 3;
                        }
                    }
                    if(buf.size() == 5){
                        if(buf == "table"){
                            buf.clear();
                            ret.type = 1;
                        }else{
                            error_happened = true;
                            return ret;
                        }
                    }
                }else{
                    error_happened = true;
                    return ret;
                }
            }else{
                if(ret.type == 3 && !ret.end){
                    //td
                    
                    if(mode == 1 || mode == 2){
                        if(arg_open){
                            if(ch == '"'){
                                if(buf.size() == 0){
                                    error_happened = true;
                                    return ret;
                                }else{
                                    istringstream iss(buf);
                                    if(mode == 1) iss >> ret.rowspan;
                                    else iss >> ret.colspan;
                                    buf.clear();
                                    arg_open = false;
                                    mode = 0;
                                }
                            }else if(isdigit(ch)){
                                buf += ch;
                            }else{
                                error_happened = true;
                                return ret;
                            }
                        }else{
                            
                            if(ch == '='){
                                buf += ch;
                            }else if(ch == '"'){
                                buf += ch;
                            }else{
                                error_happened = true;
                                return ret;
                            }
                            
                            if(buf.size() == 2){
                                if(buf == "=\""){
                                    buf.clear();
                                    arg_open = true;
                                }else{
                                    error_happened = true;
                                    return ret;
                                }
                            }
                        }
                    }else{
                        if(isalpha(ch)) {
                            ch = tolower(ch);
                            buf += ch;
                            if(buf.size() == 7){
                                if(buf == "rowspan"){
                                    mode = 1;
                                    buf.clear();
                                    argcnt++;
                                }else if(buf == "colspan"){
                                    mode = 2;
                                    buf.clear();
                                    argcnt++;
                                }else{
                                    error_happened = true;
                                    return ret;
                                }
                                if(argcnt > 2){
                                    error_happened = true;
                                    return ret;
                                }
                            }
                        }else{
                            error_happened = true;
                            return ret;
                        }
                    }
                    
                }else{
                    //ending or table or tr, no args
                    error_happened = true;
                    return ret;
                }
            }
        }else{
            if(ch == '<'){
                open = true;
                ret.type = 0;
            }
        }
    }
    return ret;
}


vector<Tag> vec;
stack<Tag> stk;

void minusify(int &a){
    if(a == '+'){
        return;
    }else{
        a = '-';
    }
}
void rectify(int &a){
    if(a == '+'){
        return;
    }else{
        a = '|';
    }
}

void syntax(){
    Tag tg;
    error_happened = false;
    while (true) {
        tg = lexical();
        if(error_happened || !tg.type){
            return;
        }else if(tg.type == -1){
            break;
        }else{
            vec.push_back(tg);
        }
    }
    
    
    
    memset(tab, 0, sizeof(tab));
    memset(opt, 0, sizeof(opt));
    int cr = 1,cc = 1;
    int blkcnt = 0;
    while(stk.size()) stk.pop();
    for(int i = 0;i < vec.size(); i++){
        if(!stk.size()){
            stk.push(vec[i]);
            continue;
        }
        if(stk.top().type == vec[i].type){
            if(vec[i].end){
                
                if(stk.top().type == 1){
                    //close the table
                    return;
                }else if(stk.top().type == 2){
                    //Move on to next row
                    cr++,cc = 1;
                }else if(stk.top().type == 3){
                    blkcnt++;
                    //finding start point
                    for(;cc < MAXN; cc++){
                        if(tab[cr][cc] == 0){
                            break;
                        }
                    }
                    //mark diag
                    opt[cr*2 - 1][cc*2 - 1] = '+';
                    opt[(cr+stk.top().rowspan-1)*2 + 1][cc*2 - 1] = '+';
                    opt[cr*2 - 1][(cc+stk.top().colspan-1)*2 + 1] = '+';
                    opt[(cr+stk.top().rowspan-1)*2 + 1][(cc+stk.top().colspan-1)*2 + 1] = '+';
                    
                    
                    for(int j = 0;j < stk.top().rowspan; j++){
                        rectify(opt[(cr+j)*2-1][cc*2-1]);
                        rectify(opt[(cr+j)*2][cc*2-1]);
                        rectify(opt[(cr+j)*2+1][cc*2-1]);
                        rectify(opt[(cr+j)*2-1][(cc+stk.top().colspan-1)*2 + 1]);
                        rectify(opt[(cr+j)*2][(cc+stk.top().colspan-1)*2 + 1]);
                        rectify(opt[(cr+j)*2+1][(cc+stk.top().colspan-1)*2 + 1]);
                        
                    }
                    for(int j = 0;j < stk.top().colspan; j++){
                        //LT
                        minusify(opt[cr*2-1][(cc+j)*2-1]);
                        //T
                        minusify(opt[cr*2-1][(cc+j)*2]);
                        //RT
                        minusify(opt[cr*2-1][(cc+j)*2+1]);
                        //LB
                        minusify(opt[(cr+stk.top().rowspan-1)*2+1][(cc+j)*2-1]);
                        //B
                        minusify(opt[(cr+stk.top().rowspan-1)*2+1][(cc+j)*2]);
                        //RB
                        minusify(opt[(cr+stk.top().rowspan-1)*2+1][(cc+j)*2+1]);
                    }
                    
                    
                    //start fill
                    for(int j = 0;j < stk.top().rowspan;j++){
                        for(int k = 0;k < stk.top().colspan; k++){
                            if(tab[cr+j][cc+k] == 0){
                                tab[cr+j][cc+k] = blkcnt;
                            }else{
                                error_happened = true;
                                return;
                            }
                        }
                    }
                    
                }
                
                
                
                
                
                
                
                
                
                stk.pop();
            }else{
                error_happened = true;
                return;
            }
        }else{
            stk.push(vec[i]);
        }
    }
    
    if(stk.size()){
        error_happened = true;
        return;
    }
}


void output(){
    if(error_happened){
        cout << "ERROR" << endl;
    }else{
        for(int i = 1;i < MAXN;i++){
                int bnd = 0;
                for(int j = 1;j < MAXN ; j++){
                    if(opt[i][j]){
                        bnd = j;
                    }
                }
            if(!bnd){
                break;
            }
                for(int j = 1;j <= bnd; j++){
                    if(!opt[i][j]){
                        putchar(' ');
                    }else{
                        putchar(opt[i][j]);
                    }
                }
                puts("");
        }
    }
}

void solve(){
    syntax();
    output();
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    solve();
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

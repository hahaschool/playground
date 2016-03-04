//
//  HDU2243.cpp
//  playground
//
//  Created by Adam Chang on 2015/05/07.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

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

using namespace std;

#pragma mark -
#pragma mark Matrix Fastpow
const int M = 105;
const long long mod = 100000;
int LEN;//0~LEN-1,len is LEN
class Matrix
{
    typedef long long typev;
public:
    typev val[M][M];
    void zero()
    {
        memset(val,0,sizeof(val));
    }
    void unit()
    {
        zero();
        for(int i=0; i<M; i++) val[i][i]=1;
    }
};

Matrix operator * (const Matrix &a,const Matrix &b)
{
    Matrix tmp;
    tmp.zero();
    for(int k=0; k<LEN; k++)
        for(int i=0; i<LEN; i++)
        {
            if(a.val[i][k])
                for(int j=0; j<LEN; j++)
                {
                    tmp.val[i][j]+=a.val[i][k]*b.val[k][j];
                    tmp.val[i][j]%=mod;
                }
        }
    return tmp;
}
Matrix operator ^ (Matrix &a,int p)
{
    Matrix tmp;
    tmp.unit();
    while(p)
    {
        if(p&1) tmp=tmp*a;
        a=a*a;
        p>>=1;
    }
    return tmp;
}
#pragma mark - 
#pragma mark trie & AC Automation
int steper = 0;
struct trieNode{
    trieNode *child[26];
    trieNode *fail;
    int freq;
    int id;
    void init(){
        memset(child,NULL,sizeof(child));
        fail = NULL;
        freq = 0;
        id = steper++;
    }
};

inline int iget(char c){
    return c - 'a';
}

void trie_insert(trieNode *root,string &str){
    trieNode *parent = root;
    for(int i = 0;i < str.size();i++){
        int idx = iget(str[i]);
        if(parent->child[idx] == NULL){
            parent->child[idx] = (trieNode*)malloc(sizeof(trieNode));
            parent->child[idx]->init();
        }
        parent = parent->child[idx];
    }
    parent->freq++;
}

void aca_buildfail(trieNode *root){
    queue<trieNode*> que;
    que.push(root);
    while(!que.empty()){
        trieNode *now = que.front();
        que.pop();
        for(int i = 0;i < 4;i++){
            if(now->child[i] == NULL){
                continue;
            }
            if(now == root){
                now->child[i]->fail = root;
            }else {
                trieNode *fail = now->fail;
                while(fail != NULL){
                    if(fail->child[i] != NULL){
                        now->child[i]->fail = fail->child[i];
                        //WARNING//
                        if (fail->child[i]->freq != 0) {
                            now->child[i]->freq++;
                        }
                        //ISSUE//
                        break;
                    }
                    fail = fail->fail;
                }
                if(fail == NULL){
                    now->child[i]->fail = root;
                }
            }
            que.push(now->child[i]);
        }
    }
}



#pragma mark -



int main(){
    
    return 0;
}

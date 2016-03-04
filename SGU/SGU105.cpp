//
//  SGU105.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/18.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

#include <stdio.h>

int main(){
    int toProc = 0;
    scanf(" %d",&toProc);
    printf("%d\n",toProc%3?(toProc/3*2+toProc%3-1):(toProc/3*2));
    return 0;
}


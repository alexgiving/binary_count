//
//  stack.c
//  equation
//
//  Created by Алексей Трутнев on 25.04.2020.
//  Copyright © 2020 Алексей Трутнев. All rights reserved.
//

#include "stack.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

Stack* push(Stack* phead, char v){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->value = v;
    p->pnext = phead;
    return p;
}

Stack* pop(Stack* phead){
    Stack *p = phead->pnext;
    free(phead);
    return p;
 }

int IsEmpty(Stack *phead){
    if(phead)
        return 0;
    return 1;
}


int fcount(int a[], Stack **phead){
    if((*phead)->value == '|'){
        (*phead) = pop(*phead);
        return (fcount(a, phead) + fcount(a, phead))/2;
    }else if((*phead)->value == '*'){
        (*phead) = pop(*phead);
        return (fcount(a, phead) * fcount(a, phead));
    }else{
        int k;
        if ((*phead)->value >= 'a' && (*phead)->value <= 'z')
            k = a[(*phead)->value - 'a'];
        else
            k = a[(*phead)->value - 'A' + 26];
        (*phead) = pop(*phead);
        if (k == 0) return 0;
        else return 1;
    }
    return -1;
}

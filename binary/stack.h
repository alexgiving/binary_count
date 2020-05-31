//
//  stack.h
//  equation
//
//  Created by Алексей Трутнев on 25.04.2020.
//  Copyright © 2020 Алексей Трутнев. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>

typedef struct Stack {
    char value;
    struct Stack* pnext;
}Stack;

int IsEmpty(Stack *phead);
Stack* pop(Stack* phead);
Stack* push(Stack* phead, char v);
int count(int a[], Stack **phead);
#endif /* stack_h */

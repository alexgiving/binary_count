//
//  Tree.h
//  equation
//
//  Created by Алексей Трутнев on 26.04.2020.
//  Copyright © 2020 Алексей Трутнев. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <stdio.h>
#include "stack.h"

typedef struct tree{
    int value;
    char symb;
    struct tree * left, * right, * parent;
}Tree;

void add(Tree **phead, int value, char symb);
Tree *create(Tree *phead, int value, char symb);
void inorderPrint(Tree *phead);
void MasinorderPrint(Tree *phead, int string[]);


Tree *createLeaf(Tree *phead);
void BinaryTree(Stack** stack, Tree** head);
int countTree(int* a, Tree *phead);

#endif /* Tree_h */

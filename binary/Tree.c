//
//  Tree.c
//  equation
//
//  Created by Алексей Трутнев on 26.04.2020.
//  Copyright © 2020 Алексей Трутнев. All rights reserved.
//

#include "Tree.h"
#include "stack.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void inorderPrint(Tree *phead){
    if (phead == NULL)
        return;
    inorderPrint(phead->left);
    if (phead->value) printf("%c %d \n", phead->symb, phead->value);
    inorderPrint(phead->right);
}

void MasinorderPrint(Tree *phead, int *string){
    if (phead == NULL)
        return;
    MasinorderPrint(phead->left, string);
    if (phead->value){
        printf("Номер строки = %d", (int)phead->symb);
        printf(" число повторений = %d\n", phead->value);
//        printf("%d", string[phead->symb]);
//        printf(" %d\n", phead->value);
    }
    MasinorderPrint(phead->right, string);
}

Tree *create(Tree *phead, int value, char symb){
    Tree *p = (Tree*) malloc(sizeof(Tree));
    p->value = value;
    p->symb = symb;
    p->left = p->right = NULL;
    p->parent = phead;
    return p;
}

void add(Tree **head, int value, char symb){
    Tree *tmp = NULL;
    if (*head == NULL) {
        *head = create(NULL, value, symb);
        return;
    }
    tmp = *head;
    while (tmp) {
        if (value >= tmp->value) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = create(tmp, value, symb);
                return;
            }
        } else {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = create(tmp, value, symb);
                return;
            }
        }
    }
}



Tree *createLeaf(Tree *phead){
    Tree *p = (Tree*) malloc(sizeof(Tree));
    p->left = p->right = NULL;
    return p;
}

void BinaryTree(Stack** stack, Tree** head){
    if (!IsEmpty(*stack)) return;
    char c = (*stack)->value;    
    if (!(*head)){
        (*head) = createLeaf(*head);
        (*head)->symb = c;
        (*stack) = pop(*stack);
        BinaryTree(stack, head);
        return;
    }
    if ((*head)->symb == '|' || (*head)->symb == '*'){
        if(!(*head)->right){
            (*head)->right = createLeaf((*head)->right);
            (*head)->right->symb = c;
            (*stack) = pop(*stack);
            BinaryTree(stack, &(*head)->right);
            BinaryTree(stack, &(*head)->left);
        } else if(!(*head)->left){
            (*head)->left = createLeaf((*head)->left);
            (*head)->left->symb = c;
            (*stack) = pop(*stack);
            BinaryTree(stack, head);
        }
    }else return;
}

int countTree(int a[], Tree *phead){
    if(phead->symb == '|'){
        return (countTree(a, phead->right) + countTree(a, phead->left))/2;
    }else if(phead->symb == '*'){
        return (countTree(a, phead->right) * countTree(a, phead->left));
    }else{
        int k;
        if (phead->symb >= 'a' && phead->symb <= 'z')
            k = a[phead->symb - 'a'];
        else
            k = a[phead->symb - 'A' + 26];
        if (k == 0) return 0;
        else return 1;
    }
    return -1;
    
}

//
//  main.c
//  equation
//
//  Created by Алексей Трутнев on 25.04.2020.
//  Copyright © 2020 Алексей Трутнев. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <string.h>
#include "stack.h"
#include "Tree.h"
#include <stdlib.h>
#define Flag 1


int main(int argc, const char * argv[]) {
    
    // Первое задание (done)
    //=============================
    if (argc != 1){                         // Проверка количества файлов для открытия
        puts("Format: input.txt");
        return -1;
    }
    FILE *fr = fopen("input.txt", "r");     // Отрываем файл

    if (fr == NULL){                        // Проверяем открыли ли его
        printf("Could not open file!");
        return 1;
    }
    int count[255] = {0};                   // Вхождение этого символа в файл
    char sarr[255];                             // ASKII код символа

    while(! feof(fr)){
        char symb = fgetc(fr);              // Получили символ
        int value = (int)symb;              // Получили ASKII код символа
        if (value > 0){
            count[value]++;
            sarr[value] = symb;
        }else  break;
    }
    fclose(fr);
    Tree *p = NULL;
    for (int i = 0; i<= 255; i++)
        if(count[i] != 0) add(&p, count[i], sarr[i]);
    inorderPrint(p);

    printf("\n\n\n");

    
   // Второе задание(done)
    //================================
    #define NUM  50
    if (argc != 1){                         // Проверка количества файлов для открытия
        puts("Format: input2.txt");
        return -1;
    }

    FILE *fp = fopen("input2.txt", "r");     // Отрываем файл
    if (fp == NULL){                        // Проверяем открыли ли его
        printf("Could not open file!");
        return 1;
    }

    char buf[100];                 // Одно слово
    char strings[NUM][100];        // Массив слов
    int counter[NUM] = {0};        // Массив количества слов

    int h = 0;
    while(fscanf(fp,"%s", buf) > 0){
         int flag = 0;
        if (h == 0){
            strcpy(strings[h], buf);
            counter[h]++;
            h++;
        }else{
            for(int i = 0; i < h; i++){
                if(strcmp(buf, strings[i]) == 0){
                    counter[i]++;
                    flag++;
                    continue;
                }
            }
            if(flag) continue; // Как это реализовать нормально? Даже go to лучше выглядит
            strcpy(strings[h], buf);
            counter[h]++;
            h++;
        }
    }
    fclose(fp);

    for (int i = 0; i < h; i++)
        printf("%s, номер = %d\n", strings[i], i);
        puts("\n");
    Tree *ph = NULL;
    for (int i = 0; i < h; i++)
        add(&ph, counter[i], i);
    MasinorderPrint(ph, strings);
    printf("\n\n\n");
    
    
   //Третье задание

    #define Flag 1
        
        char alphVar[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int varVal[52] = {0};
        char alphAct1[] = "*";
        char alphAct2[] = "|";
        
        char* str = (char*)malloc(50 * sizeof(char));
        
        Stack* headOutput = 0;
        Stack* headOperate = 0;
        
        puts("Введите уравнение");
        scanf("%s",str);
        
        for (int i = 0; i < strlen(str); i++){                              // делаем постфиксную форму
            if (strchr(alphVar, str[i]) != NULL){                           // Явлеяется ли переменной
                headOutput = push(headOutput, str[i]);                      // Ввод в стек
                if(str[i] - 'a' >= 0 && str[i] - 'a' < 26)                  // Мальние буквы
                    varVal[str[i] - 'a'] = Flag;                            // Флаг наличия переменной
                else if(str[i] - 'A' >= 0 && str[i] - 'A' < 26)             // Большие буквы
                    varVal[str[i] - 'A' + 26] = Flag;                       // Флаг наличия переменной
            }
            else if (str[i] == '(')                                         // Проверяем на открытую скобку
                headOperate = push(headOperate, str[i]);                    // Ввод в стек
            else if (str[i] == ')'){                                        // Закрытая скобка
                while(!IsEmpty(headOperate) && headOperate->value != '('){  // Пока не дойдем до открытой строки
                    headOutput = push(headOutput, headOperate->value);      // Все операции сохраняем
                    headOperate = pop(headOperate);                         // Очищяем стек
                }
                headOperate = pop(headOperate);                             // Отчищяем стек
            }else if (strchr(alphAct2, str[i]) != NULL){                    // Проверка на операцию 2 приоритета
                while(!IsEmpty(headOperate) && headOperate->value != '('){  // Пока не дойдем до открытой строки
                    headOutput = push(headOutput, headOperate->value);      // Все операции сохраняем
                    headOperate = pop(headOperate);                         // Очищяем стек
                }
                headOperate = push(headOperate, str[i]);
            }else if (strchr(alphAct1, str[i]) != NULL){                    // Проверка на операцию 1 приоритета
                while (!IsEmpty(headOperate) && headOperate->value != '|' && headOperate->value != '('){  // Пока не пустой стек операторов
                    headOutput = push(headOutput, headOperate->value);      // Все операции сохраняем
                    headOperate = pop(headOperate);                         // Очищяем стек
                }
                headOperate = push(headOperate, str[i]);
            }else if (str[i] == ' ') continue;
        }

        while(!IsEmpty(headOperate)){                                       // Заношу операции в стек вывода
            headOutput = push(headOutput, headOperate->value);              // Все операции сохраняем
            headOperate = pop(headOperate);                                 // Очищяем стек
        }
        
        while(!IsEmpty(headOutput)){                                        // Переворачиваем стек для красивого вывода
            headOperate = push(headOperate, headOutput->value);             // Все операции сохраняем
            headOutput = pop(headOutput);                                   // Отчищяем стек
        }
        
        while(!IsEmpty(headOperate)){
            printf("%c", headOperate->value);                               // Вывод стека
            headOutput = push(headOutput, headOperate->value);              // Все операции сохраняем
            headOperate = pop(headOperate);                                 // Очищяем стек
        }
        
        // Занесем значения переменных
        
        for(int i = 0; i < 52; i++){                                        // Если стоит флаг, то переменная используется
            if(varVal[i] == Flag && i < 26){
                printf("\nВведите значение переменной %c: ", i + 'a' );     // Вводим маленькие буквы
                scanf("%d",&varVal[i]);
            }else if(varVal[i] == Flag && i > 25){
                printf("\nВведите значение переменной %c: ", i + 'A' - 26); // Вводим большие буквы
                scanf("%d",&varVal[i]);
            }
        }
        
    //printf("\nОтвет: %d\n", fcount(varVal, &headOutput));                //  Выведем ответ
    
    Tree *phead = NULL;
    BinaryTree(&headOutput, &phead);
    //printf("\nОтвет: %d\n", countTree(varVal, headOutput));
    printf("\nОтвет: %d\n", fcount(varVal, &headOutput));                //  Выведем ответ
    
    return 0;
}

//
// Created by mi on 19.09.2020.
//

#include <iostream>
#include <vector>

namespace prog1 {
    struct MatrixElement {
        int x;//номер в строке
        int y;//номер в столбце
        int value;//значение элемента матрицы
        struct MatrixElement *next;//следующий элемент списка
    };

    struct Matrix {
        int N;//количество строк в матрице
        int M;//количество столбцов
        struct MatrixElement **rows;//массив, содержащий указатели на первые элементы строк матрицы
    };

    int sumOfRow(MatrixElement *elem);

    void addElement(Matrix *matrix, int x, int y, int value);

    Matrix *input();

    void output(const char *msg, Matrix *matrix);

    int findMinSumRow(Matrix *matrix);

    int findMaxSumRow(Matrix *matrix);

    int getInt(int *a);

    int getNaturalInt(int *a);

    MatrixElement *upSort(MatrixElement *head);

    MatrixElement *downSort(MatrixElement *head);

    int Choice(int, int);

    Matrix* erase(Matrix *matrix);

    void sort(Matrix *matrix);

    inline int isLess(int a, int b) {
        if (a < b) return 1;
        return 0;
    }

    inline int isGreater(int a, int b) {
        if (a > b) return 1;
        return 0;
    }
    inline int isGreaterEqual(int a,int b){
        if (isGreater(a,b)||a==b) return 1;
        return 0;
    }
    inline int isEqual(int a,int b){
        if (a==b) return 1;
        return 0;
    }
    inline void Swap(int *a, int *b, int *c, int *d) {
        *b = *a;
        *c = *d;
    }
    inline void Change(MatrixElement **a,MatrixElement **b){
        (*a)->next=*b;
        *b=*a;
    }
    inline void isGreaterSwap(MatrixElement *array,int *sum,int *index,int *i){
        if(array){
            if(isGreater(sumOfRow(array),*sum)){
                int t=sumOfRow(array);
                Swap(&t,sum,index,i);
            }
        }
    }
    inline void Swap(MatrixElement **a, MatrixElement **b) {
        (*a)->next = (*b)->next;
        (*b)->next = (*a);
    }
    inline void isLessSwap(MatrixElement *array,int *sum,int *index,int *i){
        if(array){
            if(isLess(sumOfRow(array),*sum)){
                int t=sumOfRow(array);
                Swap(&t,sum,index,i);
            }
        }
    }

}

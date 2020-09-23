//
// Created by mi on 19.09.2020.
//
#include <iostream>

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

    int getNaturalInt(int *a, const int *max);

    MatrixElement *Sort(MatrixElement *head, int (*f)(int, int), int (*h)(int, int));


    int Choice(int, int);

    Matrix *erase(Matrix *matrix);

    void sort(Matrix *matrix);

    inline int isLess(int a, int b) {
        if (a < b) return 1;
        return 0;
    }

    inline int isGreater(int a, int b) {
        if (a > b) return 1;
        return 0;
    }

    inline int isGreaterEqual(int a, int b) {
        if (isGreater(a, b) || a == b) return 1;
        return 0;
    }

    inline int isLessEqual(int a, int b) {
        if (isLess(a, b) || a == b) return 1;
        return 0;
    }

    inline void Swap(int *a, int *b, int *c, int *d) {
        *b = *a;
        *c = *d;
    }

    inline void isGreaterSwap(MatrixElement *array, int *sum, int *index, int *i) {
        if (array) {
            if (isGreater(sumOfRow(array), *sum)) {
                int t = sumOfRow(array);
                Swap(&t, sum, index, i);
            }
        }
    }

    inline void isLessSwap(MatrixElement *array, int *sum, int *index, int *i) {
        if (array) {
            if (isLess(sumOfRow(array), *sum)) {
                int t = sumOfRow(array);
                Swap(&t, sum, index, i);
            }
        }
    }

}


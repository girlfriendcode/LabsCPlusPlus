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
        int NZ;//количество ненулевых элементов
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

    void sort(Matrix *matrix);

    int Choice(int, int);
}

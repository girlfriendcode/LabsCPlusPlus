//
// Created by mi on 19.09.2020.
//
#include <iostream>
#include "prog1.h"

namespace prog1 {
    int getInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }

    int getNaturalInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0);
        return 1;
    }

    int getNaturalInt(int *a, const int *max) {//ввод с верхней границей
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (*a > *max) {
                printf("%s\n", "Error!You exceeded the limit!Repeat input: ");
                scanf("%*[^\n]");
            }
            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0 || *a > *max);
        return 1;
    }

    Matrix *input() {
        int lines, columns;
        std::cout << "Enter number of rows -->";
        getNaturalInt(&lines);
        std::cout << "Enter number of columns -->";
        getNaturalInt(&columns);
        auto *matrix = new Matrix;
        matrix->N = lines;
        matrix->M = columns;
        matrix->rows = new MatrixElement *[lines];
        for (int i = 0; i < matrix->N; i++) {
            matrix->rows[i] = nullptr;
        }
        int choice;
        bool check = true;
        while (check) {
            std::cout << "Do you want to input next element ( press 1 for Yes, 0-No)?" << std::endl;
            std::cin >> choice;
            if (choice) {
                int x, y, value;
                std::cout << "Input number of line in range [" << 1 << ";" << lines << "]" << std::endl;
                getNaturalInt(&x, &lines);
                std::cout << "Input number of column in range [" << 1 << ";" << columns << "]" << std::endl;
                getNaturalInt(&y, &columns);
                std::cout << "Input value of element -->";
                getInt(&value);
                x--;
                y--;
                addElement(matrix, x, y, value);//увеличиваем количество ненулевых тут
            }
            if (!choice) {
                check = false;
            }
        }
        return matrix;
    }

    int sumOfRow(MatrixElement *elem) {
        int sum = 0;
        MatrixElement *ptr = elem;
        while (ptr) {
            sum += ptr->value;
            ptr = ptr->next;
        }
        return sum;
    }

    int findMaxSumRow(Matrix *matrix) {
        int max = 0;
        int maxSum = sumOfRow(matrix->rows[0]);
        for (int i = 0; i < matrix->N; i++) {
            isGreaterSwap(matrix->rows[i], &maxSum, &max, &i);
        }
        return max;
    }

    int findMinSumRow(Matrix *matrix) {
        int min = 0;
        int minSum = sumOfRow(matrix->rows[0]);
        for (int i = 0; i < matrix->N; i++) {
            isLessSwap(matrix->rows[i], &minSum, &min, &i);
        }
        return min;
    }

    MatrixElement *upSort(MatrixElement *head) {
        MatrixElement *new_head = nullptr;
        while (head != nullptr) {
            MatrixElement *node = head;
            node = head;
            head = head->next;
            if (new_head == nullptr || !isGreater(node->value, new_head->value)) {//меняем меcтами
                Change(&node, &new_head);
            } else {
                MatrixElement *current = new_head;
                while (current->next != nullptr && isGreaterEqual(node->value,
                                                                  current->next->value)) {//пропускаем ряд элементов, идущих по возрастанию
                    current = current->next;
                }
                Swap(&node, &current);
            }
        }

        return new_head;
    }

    MatrixElement *downSort(MatrixElement *head) {
        MatrixElement *new_head = nullptr;

        while (head != nullptr) {
            MatrixElement *node = head;
            head = head->next;

            if (new_head == nullptr || isGreater(node->value, new_head->value)) {
                Change(&node, &new_head);
            } else {
                MatrixElement *current = new_head;
                while (current->next != nullptr && !isGreaterEqual(node->value, current->next->value)) {
                    current = current->next;
                }
                Swap(&node, &current);
            }
        }

        return new_head;
    }

    void sort(Matrix *matrix) {
        int max, min;
        max = findMaxSumRow(matrix);
        min = findMinSumRow(matrix);
        matrix->rows[max] = upSort(matrix->rows[max]);
        matrix->rows[min] = downSort(matrix->rows[min]);
    }

    void addElement(Matrix *matrix, int x, int y, int value) {
        /* случаи: создаем новую строку-значит,надо создать новый список
         * добавляем новый элемент:находим нужный элемент массива, а там вставка в список.
         */
        MatrixElement *elem = new MatrixElement;//выделяем память под новый элемент списка
        elem->x = x;
        elem->y = y;
        elem->value = value;
        elem->next = nullptr;
        //первый элемент в строке матрицы или же y вставляемого элемента меньше y первого элемента
        if (matrix->rows[x] == nullptr || elem->y < matrix->rows[x]->y) {
            elem->next = matrix->rows[x];
            matrix->rows[x] = elem;
            return;
        }
        //ищем нужную позицию, при этом может оказаться , что нужная позиция не занимает промежуточное место в списке,двигать ничего не нужно, просто ставим после
        // ячейка уже занята-делаем запрос, менять ли
        // нужна позиция занимает промежуточное положение в списке-"отодвигаем" хвост списка
        if (matrix->rows[x] != nullptr && matrix->rows[x]->y == elem->y) {//делаем замену
            if (Choice(x, y)) {
                matrix->rows[x]->value = value;
                return;
            } else
                return;
        }

        MatrixElement *prev, *curr;
        prev = matrix->rows[x];
        curr = matrix->rows[x]->next;

        while (curr && elem->y > curr->y) {
            prev = prev->next;
            curr = curr->next;
        }
        if (curr != nullptr && curr->y == elem->y) {
            if (Choice(x, y)) {
                curr->value = elem->value;
                return;
            } else
                return;
        }
        prev->next = elem;
        elem->next = curr;
    }

    int Choice(int x, int y) {
        int choice;
        std::cout << "Do you want to change element in position[" << x + 1 << ";" << y + 1
                  << "]?Type 1 for Yes , 0 for No " << std::endl;
        std::cin >> choice;
        return choice;
    }

    void output(const char *msg, Matrix *matrix) {
        std::cout << "\n" << "Matrix's elements are printed in format :[x,y,value]" << std::endl;
        std::cout << msg << std::endl;
        for (int i = 0; i < matrix->N; i++) {
            std::cout << "\n";
            if (matrix->rows[i] != nullptr) {
                MatrixElement *ptr;
                ptr = matrix->rows[i];
                while (ptr) {
                    std::cout << " [" << ptr->x + 1 << ";" << ptr->y + 1 << ";" << ptr->value << "] ";
                    ptr = ptr->next;
                }
                std::cout << "   Sum of row:" << sumOfRow(matrix->rows[i]);
            }
        }
    }

    Matrix *erase(Matrix *matrix) {
        MatrixElement *ptr = new MatrixElement;
        for (int i = 0; i < matrix->N; i++) {
            ptr = matrix->rows[i];
            while (ptr != nullptr) {
                MatrixElement *trash;
                trash = ptr;
                ptr = ptr->next;
                delete trash;
            }
        }
        delete matrix->rows;
        return nullptr;
    }
}

//стоит подумать над массивом списков, так как сортировка в них проще ,так и сумму привязать можно

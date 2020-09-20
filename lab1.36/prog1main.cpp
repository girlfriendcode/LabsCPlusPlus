//
// Created by mi on 19.09.2020.
//

#include <iostream>
#include "prog1.h"
#include <vector>

using namespace prog1;

int main() {
    auto *matrix = new Matrix;
    matrix = input();
    output("Sourced matrix", matrix);
    sort(matrix);
    output("New matrix", matrix);
    return 0;
}

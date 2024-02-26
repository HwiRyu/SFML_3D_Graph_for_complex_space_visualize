//
// Created by Persist on 2/3/24.
//

#ifndef PICARD_ITERATION_SCALE_H
#define PICARD_ITERATION_SCALE_H
#include <cmath> // cmath 헤더 인클루드

double x_scale(double x, double size) {
    return x * size;
}
double y_scale (double y, double size) {
    return -y * size;
}

#endif //PICARD_ITERATION_SCALE_H

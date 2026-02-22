#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef vec3 color;

void colorWriteToFile(
    FILE* fp,
    const color* c1
);

#endif
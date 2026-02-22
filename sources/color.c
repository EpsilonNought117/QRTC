#include "../headers/color.h"


void colorWriteToFile(
    FILE* fp,
    const color* c1
)
{
    float r = c1->x;
    float g = c1->y;
    float b = c1->z;

    int rByte = (int)(255.0f * r + 0.5f);
    int gByte = (int)(255.0f * g + 0.5f);
    int bByte = (int)(255.0f * b + 0.5f);

    fprintf(fp, "%d %d %d\n", rByte, gByte, bByte);
    return;
}
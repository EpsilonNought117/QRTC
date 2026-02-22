#include "../headers/vec3.h"
#include "../headers/color.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file name>.ppm\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    /* Check .ppm extension */
    const char* ext = strrchr(filename, '.');
    
    if (ext == NULL || strcmp(ext, ".ppm") != 0)
    {
        fprintf(stderr, "Error: output file must end with .ppm\n");
        return EXIT_FAILURE;
    }

    FILE* fp = fopen(filename, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Error: fopen(\"%s\") failed: %s\n", filename, strerror(errno));
        return EXIT_FAILURE;
    }

    /* Square Image */
    int image_width = 1024;
    int image_height = image_width;

    /* PPM header */
    fprintf(fp, "P3\n%d %d\n255\n", image_width, image_height);

    /* Render */
    for (int j = 0; j < image_height; j++)
    {
        printf("Scanlines remaining: %d\n", (image_height - j));

        for (int i = 0; i < image_width; i++)
        {
            color pixel_color = {
                (double)i / (double)(image_width - 1),
                (double)j / (double)(image_height - 1),
                0.0f
            };

            colorWriteToFile(fp, &pixel_color);
        }
    }

    printf("Done.\n");
    fclose(fp);

    return EXIT_SUCCESS;
}
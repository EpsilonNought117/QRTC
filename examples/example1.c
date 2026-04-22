#include "../include/qrtc.h"

int main(void)
{
    printf("P3\n");

    uint32_t maxval = 65535;
    size_t image_width = 1920;
    size_t image_height = 1200;

    printf("P3\n%zu %zu\n" PRIu32 "\n", image_width, image_height, maxval);

    for (size_t j = 0; j < image_height; j++)
    {
        fprintf(stderr, )

        for (size_t i = 0; i < image_width; i++)
        {
        }    
    }


    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/inOut.h"
#include "../include/transfer.h"

int main(int argc, char** argv) {
    image_s image;
    bool clockwise = true;
    char* path;
    FILE* in = NULL;


    if(argc == 1 || argc > 3) {
        printf("Wrong count of arguments\n");
        return 1;
    }
    if(strcmp(argv[2], "-r") && strcmp(argv[2], "-l")){
        printf("Second argument should be '-r' or '-l' depends on rotation direction\n");
        return 1;
    }


    path = argv[1];

    if(strcmp(argv[2], "-l"))
        clockwise = false;

    in = fopen(path, "r+b");

    switch(read_data(in, &image))
    {
        case MISSING_FILE:
            printf("Cannot open file\n");
            return 1;
        case READ_INVALID_FORMAT:
            printf("Incorrect header format.\nSupport only 24bit BMP images\n");
            return 2;

        case READ_INVALID_HEADER:
            printf("Incorrect bitCount in BMP.\nSupport only 24bit BMP images\n");
            return 3;
        case READ_OK:
            printf("Input size: \t%lux%lu\n", image.width, image.height);
            break;
    }

    image_s  new;

    if(clockwise)
        rotate_left(&image, &new);
    else
        rotate_right(&image, &new);
    FILE* out;
    out = fopen("rotated.bmp", "w");
    write_code res;
    res = to_bmp(out, &new);
    if(res == WRITE_OK)
        printf("\nSuccess!\n");
    else
        printf("\nError!\n");
    return 0;
}



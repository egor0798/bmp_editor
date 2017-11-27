#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/inOut.h"
#include "../include/transfer.h"
//int argc, char** argv
int main() {
    image_s image;
    bool clockwise = true;
    char* path = "smiley.bmp";
    FILE* in = NULL;
    read_code result;
    bmpHeader_s header;

//    if(argc == 1 || argc > 3) {
//        printf("Wrong count of arguments");
//        return 1;
//    }
//    if(strcmp(argv[2], "-r") && strcmp(argv[2], "-l")){
//        printf("Second argument should be '-r' or '-l' depends on rotation direction");
//        return 1;
//    }
//    path = argv[1];
//    if(strcmp(argv[2], "-l"))
//        clockwise = false;
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
            printf("Input size: %lux%lux24\n", image.width, image.height);
            break;
    }
    image_s * new = rotate_right(&image);
    FILE* out;
    out = fopen("rotated.bmp", "w");
    write_code res;
    res = to_bmp(out, new);
    return 0;
}




write_code to_bmp(FILE* output, image_s* image)
{
    int i, j;
    bmpHeader_s  header;
    int offset;
    offset = image->width * sizeof(pixel_s) % 4;
    if(offset != 0)
    {
        offset = 4 - offset;
    }
    header.bfType = 0x4d42;
    header.bfileSize = 54 + (image->width*3 + offset) * image->height;
    header.bfReserved = 0;
    header.bOffBits = 54;
    header.biSize = 40;
    header.biWidth = image->width;
    header.biHeight = image->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0xb13;
    header.biYPelsPerMeter = 0xb13;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    fwrite(&header, sizeof(char)*2, 1, output);
    fseek(output, 54, SEEK_SET);
    for(i = 0; i < image->height; i++)
    {
        for(j = 0; j < image->width; j++)
        {
            fwrite(&image->data[i*(image->width) + j], sizeof(pixel_s), 1, output);
        }
        fseek(output, offset, SEEK_CUR);
    }
    return WRITE_OK;
}
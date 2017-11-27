//
// Created by egor on 27.11.17.
//
#pragma once
#include <stdio.h>
#include "bmp.h"

typedef enum {
    READ_OK = 0,
    MISSING_FILE,
    READ_INVALID_HEADER,
    READ_INVALID_FORMAT
} read_code;

read_code read_header(FILE* , bmpHeader_s*);
read_code read_data(FILE*, image_s*);

typedef enum {
    WRITE_OK =0,
    ERROR
} write_code;

write_code to_bmp(FILE*, image_s*);
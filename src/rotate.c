//
// Created by egor on 27.11.17.
//
#pragma once
#include <stdlib.h>
#include "../include/transfer.h"

image_s* rotate_right(image_s* src, image_s* new){
    new->width = src->height;
    new->height = src->width;
    new->data = (pixel_s*)malloc(sizeof(pixel_s)*new->width*new->height);
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j)
            new->data[src->height*(src->width-j) + i] = src->data[i*src->width + j];
    }
    return new;
}

image_s* rotate_left(image_s* src, image_s* new){
    new->width = src->height;
    new->height = src->width;
    new->data = (pixel_s*)malloc(sizeof(pixel_s)*new->width*new->height);
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j)
            new->data[src->height*(j) + i] = src->data[(src->height-i)*src->width + j];
    }
    return new;
}

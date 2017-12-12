//
// Created by egor on 27.11.17.
//
#include <math.h>
#include <stdlib.h>
#include "../include/edit.h"
#include "../include/bmp.h"

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

void extend_borders(image_s* src, image_s* new_img){
    uint32_t new_height = src->height + 2;
    uint32_t new_width = src->width+2;
    pixel_s* new = (pixel_s*)malloc(sizeof(pixel_s)*new_height*new_width);
    for (int j = 0; j < src->width ; ++j) // BOTTOM LINE
        new[j+1] = src->data[j];
    for (int j = 0; j < src->width ; ++j)  // TOP LINE
        new[j+1+(new_height-1)*new_width] = src->data[j+(src->height-1)*src->width];
    for (int i = 0, j = 2; i < src->height*src->width; i+=src->width, j+=2) // LEFT LINE
        new[i+src->width+j] = src->data[i];
    for (int i = 0, j = 2; i <= src->height*src->width; i+=src->width, j+=2) // RIGHT LINE
        new[i+src->width+j-1] = src->data[i-1];

    int offset = 0;
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j)
            new[new_width+j+1+i*src->width+offset] = src->data[j+i*src->width];
        offset+=2;
    }

    new[0]=src->data[0]; // LEFT BOTTOM
    new[new_width-1]=src->data[src->width-1]; // RIGHT BOTTOM
    new[(new_height-1)*new_width] = src->data[(src->height-1)*src->width];  // LEFT TOP
    new[(new_height)*new_width-1] = src->data[(src->height)*src->width-1];  // RIGHT TOP
    new_img->data = new;
    new_img->width = new_width;
    new_img->height = new_height;
}

image_s* blur(image_s* src, image_s* extended){
    double red, green, blue;
    int a, b, offset = 0;
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j) {
            a = extended->width+j+1+i*src->width+offset;
            b = j+i*src->width;

            red = extended->data[a].red/4 + extended->data[a + 1].red/8 + extended->data[a - 1].red/8;
            red += extended->data[a - extended->width].red/8 + extended->data[a - extended->width + 1].red/16 + extended->data[a - extended->width - 1].red/16;
            red += extended->data[a + extended->width].red/8 + extended->data[a + extended->width + 1].red/16 + extended->data[a + extended->width - 1].red/16;

            green = extended->data[a].green/4 + extended->data[a + 1].green/8 + extended->data[a - 1].green/8;
            green += extended->data[a - extended->width].green/8 + extended->data[a - extended->width + 1].green/16 + extended->data[a - extended->width - 1].green/16;
            green += extended->data[a + extended->width].green/8 + extended->data[a + extended->width + 1].green/16 + extended->data[a + extended->width - 1].green/16;

            blue = extended->data[a].blue/4 + extended->data[a + 1].blue/8 + extended->data[a - 1].blue/8;
            blue += extended->data[a - extended->width].blue/8 + extended->data[a - extended->width + 1].blue/16 + extended->data[a - extended->width - 1].blue/16;
            blue += extended->data[a + extended->width].blue/8 + extended->data[a + extended->width + 1].blue/16 + extended->data[a + extended->width - 1].blue/16;


            src->data[b].red = round(red);
            src->data[b].green = round(green);
            src->data[b].blue = round(blue);
        }
        offset+=2;
    }
    return src;
}



image_s* smth(image_s* src, image_s* blurred){
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j) {
            src->data[i*(src->width) + j].red =src->data[i*(src->width) + j].red - abs(src->data[i*(src->width) + j].red - blurred->data[i*(src->width) + j].red);
            src->data[i*(src->width) + j].green = src->data[i*(src->width) + j].green - abs(src->data[i*(src->width) + j].green - blurred->data[i*(src->width) + j].green);
            src->data[i*(src->width) + j].blue = src->data[i*(src->width) + j].blue - abs(src->data[i*(src->width) + j].blue - blurred->data[i*(src->width) + j].blue);
        }
    }
    return src;
}
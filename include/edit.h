#pragma once
#include "bmp.h"


//
// Created by egor on 27.11.17.
//
image_s* rotate_right(image_s*, image_s*);
image_s* rotate_left(image_s*, image_s*);
void extend_borders(image_s*, image_s*);
image_s* blur(image_s*, image_s*);
image_s* smth(image_s*, image_s*);

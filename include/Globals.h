#pragma once

#include <iostream>
#include <raylib.h>

/*
* Loads in an image using the LoadObjectImage method and generates the required inputs for specified image.
* Input must be capitalised as to reference the appropriate macro. 
*
* For example, an input of FOOD will generate FOOD_IMAGE_FORMAT (and the other relevant macros)
*
*/
#define LOAD_OBJECT_IMAGE(NAME_UPPERCASE)  \
LoadObjectImage(					\
NAME_UPPERCASE##_IMAGE_FORMAT,		\
NAME_UPPERCASE##_IMAGE_HEIGHT,		\
NAME_UPPERCASE##_IMAGE_WIDTH,		\
NAME_UPPERCASE##_IMAGE_DATA			\
)									\

const static int screenWidth = 750;
const static int screenHeight = 750;
const static int cellNum = 25;
const static int cellSize = std::min(screenWidth, screenHeight) / cellNum;



static Image LoadObjectImage(const int format, const int height, const int width, unsigned char data[]) {
        Image image = { 0 };                                 
        image.height = height;
        image.width = width;
        image.format = format;
        image.data = data;
        image.mipmaps = 1;

        return image;
}
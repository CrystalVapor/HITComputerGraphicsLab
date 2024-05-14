//
// Created by m1504 on 24-5-10.
//

#include "Texture.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FTexture::FTexture(const char *texturePath) {
    glGenTextures(1, &ID);
    int Channels = 0;
    unsigned char* Data = stbi_load(texturePath, &Width, &Height,
        &Channels, 0);
    if(!Data)
    {
        std::cout<< "Failed to load texture: " << texturePath << std::endl;
        return;
    }
    int Format;
    switch (Channels) {
        case 1:
            Format = GL_RED;
            break;
        case 3:
            Format = GL_RGB;
            break;
        case 4:
            Format = GL_RGBA;
            break;
        default:
            Format = GL_RGB;
    }
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format,
        GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);
    if(Format != GL_RGBA) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }else {

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(Data);
}

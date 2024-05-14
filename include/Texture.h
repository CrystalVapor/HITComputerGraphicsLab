//
// Created by m1504 on 24-5-10.
//

#ifndef TEXTURE_H
#define TEXTURE_H

class FTexture {
public:
    // ReSharper disable once CppNonExplicitConvertingConstructor
    FTexture(const char *texturePath); // NOLINT(*-explicit-constructor)
    FTexture(const FTexture& other) = default;
    FTexture& operator=(const FTexture& other) = default;
    ~FTexture() = default;

    unsigned int ID = 0;
    int Width = 0;
    int Height = 0;
};

#endif //TEXTURE_H

//
// Created by m1504 on 24-5-10.
//

#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <memory>

class FTexture;
class FTextureFactory {
public:
    static std::shared_ptr<FTexture> CreateTexture(const char* texturePath);
};

#endif //TEXTUREFACTORY_H

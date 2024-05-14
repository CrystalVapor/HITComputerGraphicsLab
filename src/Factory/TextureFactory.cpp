//
// Created by m1504 on 24-5-10.
//

#include <memory>

#include "Factory/TextureFactory.h"
#include "Texture.h"

std::shared_ptr<FTexture> FTextureFactory::CreateTexture(const char *texturePath) {
    return std::make_shared<FTexture>(texturePath);
}

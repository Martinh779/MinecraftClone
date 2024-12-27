//
// Created by herte on 03.12.2024.
//

#ifndef TEXTUREPATHS_H
#define TEXTUREPATHS_H
#include <string>
#include <vector>

#include "../Utils/PathUtils.h"

#endif //TEXTUREPATHS_H

const std::vector<std::string> TEXTURE_PATHS = {
        resolvePath("Resources/dirt.png"),
        resolvePath("Resources/stone.png"),
        resolvePath("Resources/grass_block_side.png"),
        resolvePath("Resources/grass_block_top.png")
};
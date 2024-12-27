//
// Created by herte on 27.12.2024.
//

#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <filesystem>

inline std::string resolvePath(const std::string& path) {
    return (std::filesystem::path(PROJECT_ROOT) / path).string();
}

#endif //PATHUTILS_H

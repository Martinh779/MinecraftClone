/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <filesystem>

inline std::string resolvePath(const std::string& path) {
    return (std::filesystem::path(PROJECT_ROOT) / path).string();
}

#endif //PATHUTILS_H

//
// Created by Martin Hertel on 04.08.2024.
//

#ifndef MINECRAFTCLONE_PERLINNOISE_H
#define MINECRAFTCLONE_PERLINNOISE_H

#include <vector>

namespace Math {

    class PerlinNoise {
    public:
        std::vector<int> p;

        PerlinNoise();
        PerlinNoise(unsigned int seed);

        double noise(double x, double y, double z);

    private:
        double fade(double t);
        double lerp(double t, double a, double b);
        double grad(int hash, double x, double y, double z);
    };

} // Minecraft

#endif //MINECRAFTCLONE_PERLINNOISE_H

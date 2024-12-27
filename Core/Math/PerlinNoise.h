//
// Created by Martin Hertel on 04.08.2024.
//

#ifndef MINECRAFTCLONE_PERLINNOISE_H
#define MINECRAFTCLONE_PERLINNOISE_H

#include <vector>

namespace Math {

    class PerlinNoise {
    public:
        static PerlinNoise* getInstance();

        std::vector<int> permutation;

        PerlinNoise(unsigned int seed);

        int calculatePerlin(double x, double y);

    protected:
        double m_frequency = 0.003;
        int m_minRange = 50;
        int m_maxRange = 200;

    private:
        static PerlinNoise* instance;

        double fade(double t);

        double lerp(double t, double a, double b);

        double grad(int ix, int iy, double x, double y);

        int wrapIndex(int value, int max);
    };

} // Minecraft

#endif //MINECRAFTCLONE_PERLINNOISE_H

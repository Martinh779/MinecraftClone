//
// Created by Martin Hertel on 04.08.2024.
//

#include <numeric>
#include <random>
#include "PerlinNoise.h"

#include <algorithm>

namespace Math {

    PerlinNoise* PerlinNoise::instance = nullptr;

    /**
     * Get the m_instance of the PerlinNoise class
     * @return
     */
    PerlinNoise* PerlinNoise::getInstance() {
        if (instance == nullptr) {
            instance = new PerlinNoise(21231);
        }
        return instance;
    }


    /**
     * Constructor with seed
     * @param seed
     */
    PerlinNoise::PerlinNoise(unsigned int seed) {
        int indx = 0;
        permutation.resize(256);

        // Fill permutation vector with values from 0 to 255
        std::ranges::generate(permutation, [&indx]() { return indx++; });
    }


    /**
     * Calculate the noise value for a given point
     * @param x
     * @param y
     * @param z
     * @return
     */
    double PerlinNoise::fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }


    /**
     * Calculate the linear interpolation
     * @param t
     * @param a
     * @param b
     * @return
     */
    double PerlinNoise::lerp(double t, double a, double b) {
        return a + t * (b - a);
    }


    /**
     * Calculate the gradient
     * @param ix
     * @param iy
     * @param x
     * @param y
     * @return
     */
    double PerlinNoise::grad(int ix, int iy, double x, double y) {
        int hash = permutation[(permutation[ix % 256] + iy) % 256] % 8;
        double gradients[8][2] = {
                {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };
        double* gradient = gradients[hash];

        double dx = x - (double)ix;
        double dy = y - (double)iy;

        return dx * gradient[0] + dy * gradient[1];
    }


    /**
     * Calculate the Perlin noise value for a given point
     * @param x
     * @param y
     * @return
     */
    int PerlinNoise::calculatePerlin(double x, double y) {
        x *= frequency;
        y *= frequency;

        int x0 = (int)floor(x);
        int x1 = x0 + 1;

        int y0 = (int)floor(y);
        int y1 = y0 + 1;

        // Determine the gradient values
        float n0, n1, ix0, ix1;
        n0 = grad(x0, y0, x, y);
        n1 = grad(x1, y0, x, y);
        ix0 = lerp(fade(x - x0), n0, n1);

        n0 = grad(x0, y1, x, y);
        n1 = grad(x1, y1, x, y);
        ix1 = lerp(fade(x - x0), n0, n1);

        // Interpolate between the two points
        double noise = lerp(fade(y - y0), ix0, ix1);
        int clamped = static_cast<int>(std::round((noise * (maxRange - minRange)) + minRange));
        noise = std::clamp(clamped, minRange, maxRange);

        return noise;

    }
} // Minecraft
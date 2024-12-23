//
// Created by Martin Hertel on 15.11.2024.
//

#ifndef MINECRAFTCLONE_FRUSTUM_H
#define MINECRAFTCLONE_FRUSTUM_H

#include "Plane.h"

namespace Math {

    class Frustum {
    public:
        Frustum() = default;

        Frustum(const Plane& top, const Plane& bottom, const Plane& left, const Plane& right, const Plane& near, const Plane& far)
            : topFace(top), bottomFace(bottom), leftFace(left), rightFace(right), nearFace(near), farFace(far) {}

        void createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar);

        bool isBoxInFrustum(const glm::vec3& min, const glm::vec3& max);

    private:
        Plane topFace;
        Plane bottomFace;

        Plane leftFace;
        Plane rightFace;

        Plane nearFace;
        Plane farFace;
    };

} // Rendering

#endif //MINECRAFTCLONE_FRUSTUM_H

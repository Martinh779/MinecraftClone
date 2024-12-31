/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_TRANSFORM_H
#define MINECRAFTCLONE_TRANSFORM_H


#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"

namespace Math {

    class Transform {
    public:
        void computeModelMatrix();

    protected:
        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 m_modelMatrix = glm::mat4(1.0f);

        bool m_isDirty = true;

        glm::mat4 getLocalModelMatrix();
    };
}



#endif //MINECRAFTCLONE_TRANSFORM_H

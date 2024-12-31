/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

namespace Utils {

class ConfigLoader {

public:
    static ConfigLoader* getInstance();

    ConfigLoader();

    /// Getters
    // General
    float getCameraSpeed() const { return m_cameraSpeed; }
    float getCameraSensitivity() const { return m_cameraSensitivity; }

    // Graphics
    int getChunkRenderDistance() const { return m_chunkRenderDistance; }
    bool getIsFullscreen() const { return m_isFullscreen; }
    int getScreenWidth() const { return m_screenWidth; }
    int getScreenHeight() const { return m_screenHeight; }

    // Controls
    int getForwardKey() const { return m_forwardKey; }
    int getBackwardKey() const { return m_backwardKey; }
    int getLeftKey() const { return m_leftKey; }
    int getRightKey() const { return m_rightKey; }
    int getJumpKey() const { return m_jumpKey; }
    int getCrouchKey() const { return m_crouchKey; }

    // World
    int getSeed() const { return m_seed; }
    double getPerlinNoiseFrequency() const { return m_perlinNoiseFrequency; }
    int getPerlinNoiseMin() const { return m_perlinNoiseMin; }
    int getPerlinNoiseMax() const { return m_perlinNoiseMax; }

private:
    static ConfigLoader* m_instance;

    void loadConfig();

    // General
    float m_cameraSpeed = 0.5f;
    float m_cameraSensitivity = 0.1f;

    // Graphics
    int m_chunkRenderDistance = 5;
    bool m_isFullscreen = false;
    int m_screenWidth = 800;
    int m_screenHeight = 600;

    // Controls
    int m_forwardKey = 87;
    int m_backwardKey = 83;
    int m_leftKey = 65;
    int m_rightKey = 68;
    int m_jumpKey = 32;
    int m_crouchKey = 340;

    // World
    int m_seed = 0;
    double m_perlinNoiseFrequency = 0.1;
    int m_perlinNoiseMin = 0;
    int m_perlinNoiseMax = 250;
};

} // Utils

#endif //CONFIGLOADER_H

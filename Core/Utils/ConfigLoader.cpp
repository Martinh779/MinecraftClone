//
// Created by herte on 27.12.2024.
//

#include "ConfigLoader.h"
#include "PathUtils.h"
#include "IniReader.h"
#include <iostream>

#include "Logger.h"

namespace Utils {

    ConfigLoader* ConfigLoader::m_instance = nullptr;

    ConfigLoader* ConfigLoader::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new ConfigLoader();
        }
        return m_instance;
    }


    ConfigLoader::ConfigLoader() {
        loadConfig();
    }


    void ConfigLoader::loadConfig() {
        INIReader reader(resolvePath("Config.ini"));

        if (reader.ParseError() < 0) {
            LOG(LOG_ERROR, "Failed to load config file!");
            return;
        }

        // General
        m_cameraSpeed = reader.GetReal("General", "CameraSpeed", m_cameraSpeed);
        m_cameraSensitivity = reader.GetReal("General", "CameraSensitivity", m_cameraSensitivity);

        // Graphics
        m_chunkRenderDistance = reader.GetInteger("Graphics", "ChunkRenderDistance", m_chunkRenderDistance);
        m_isFullscreen = reader.GetBoolean("Graphics", "Fullscreen", m_isFullscreen);
        m_screenWidth = reader.GetInteger("Graphics", "ScreenWidth", m_screenWidth);
        m_screenHeight = reader.GetInteger("Graphics", "ScreenHeight", m_screenHeight);

        // Controls
        m_forwardKey = reader.GetInteger("Controls", "MoveForward", m_forwardKey);
        m_backwardKey = reader.GetInteger("Controls", "MoveBackward", m_backwardKey);
        m_leftKey = reader.GetInteger("Controls", "MoveLeft", m_leftKey);
        m_rightKey = reader.GetInteger("Controls", "MoveRight", m_rightKey);
        m_jumpKey = reader.GetInteger("Controls", "Jump", m_jumpKey);
        m_crouchKey = reader.GetInteger("Controls", "Crouch", m_crouchKey);

        // World
        m_seed = reader.GetInteger("World", "Seed", m_seed);
        m_perlinNoiseFrequency = reader.GetReal("World", "PerlinNoiseFrequency", m_perlinNoiseFrequency);
        m_perlinNoiseMin = reader.GetInteger("World", "PerlinNoiseMin", m_perlinNoiseMin);
        m_perlinNoiseMax = reader.GetInteger("World", "PerlinNoiseMax", m_perlinNoiseMax);
    }


} // Utils
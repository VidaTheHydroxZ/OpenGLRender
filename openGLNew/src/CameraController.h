#pragma once
#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class CameraController
{
public:

    CameraController();

    ~CameraController();

    void ProcessInput(GLFWwindow* window, float deltaTime);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback_static(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback_static(GLFWwindow* window, double xoffset, double yoffset);
    glm::mat4 LookAround();

    inline float GetFov() { return FOV; }

    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_cameraUp;
    glm::vec3 m_cameraRight;
    glm::mat4 m_viewMatrix;

private:
    float lastX = 2560.0f / 2.0f;
    float lastY = 1560.0f / 2.0f;
	float m_CameraSpeed = 0.005f;
    float YAW = -90.0f;
    float PITCH = 0.0f;
    float SPEED = 2.5f;
    float SENSITIVITY = 0.01f;
    float FOV = 45.0f;
    bool firstMouse = true;
};
#endif

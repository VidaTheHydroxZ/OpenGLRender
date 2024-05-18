#include "CameraController.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

Renderer* renderer;

CameraController::CameraController() 
{
}

CameraController::~CameraController()
{

}

void CameraController::ProcessInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    m_CameraSpeed = SPEED * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cameraPos += m_CameraSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= m_CameraSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_CameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_CameraSpeed;

    m_cameraPos.y = 0.0f;
}

void CameraController::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    float xposIn = static_cast<float>(xpos);
    float yposIn = static_cast<float>(ypos);

    if (firstMouse)
    {
        lastX = xposIn;
        lastY = yposIn;
        firstMouse = false;
    }

    float xoffset = xposIn - lastX;
    float yoffset = lastY - yposIn;
    lastX = xposIn;
    lastY = yposIn;

    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    YAW += xoffset;
    PITCH += yoffset;

    if (PITCH > 89.0f)
        PITCH = 89.0f;
    if (PITCH < -89.0f)
        PITCH = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
    front.y = sin(glm::radians(PITCH));
    front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
    m_cameraFront = glm::normalize(front);
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}

void CameraController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    FOV -= (float)yoffset;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 45.0f)
        FOV = 45.0f;
}

void CameraController::mouse_callback_static(GLFWwindow* window, double xpos, double ypos)
{
    CameraController* controller = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->mouse_callback(window, xpos, ypos);
    }
}

void CameraController::scroll_callback_static(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraController* controller = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->scroll_callback(window, xoffset, yoffset);
    }
}

glm::mat4 CameraController::LookAround()
{
    m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    return m_viewMatrix;
}

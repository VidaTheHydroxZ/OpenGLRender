#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer(float deltaTime);
    ~Renderer();
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void CalculateDeltaTime(float currentFrame);
    inline float GetDeltaTime() const { return m_deltaTime; }
private:
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;
    float m_currentFrame = (float)glfwGetTime();
};

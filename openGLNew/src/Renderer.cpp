#include "Renderer.h"
#include "UtilFunctions.h"

#include <iostream>

Renderer::Renderer(float deltaTime)
    :m_deltaTime(deltaTime)
{
}


Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::CalculateDeltaTime(float currentFrame)
{
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}

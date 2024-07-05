#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLFW/glfw3.h>

#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "CameraController.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int SCREEN_WIDTH = 2560;
int SCREEN_HEIGHT = 1440;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (window)
    {
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Error!" << std::endl;
        }
    }
    
    CameraController Camera;
    glfwSetWindowUserPointer(window, &Camera);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Camera.mouse_callback_static);
    

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float vertices[] = {
            //positions       normals           textures
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,    0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,     0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
                                      
    -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,     0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,     1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,     1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,     1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,     0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,     0.0f, 1.0f,
                                      
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,     0.0f, 1.0f
    };


    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float crosshairPosition[] = {
    -0.01f, 0.0f,
     0.01f, 0.0f,
     0.0f, -0.01f,
     0.0f,  0.01f
    };

    unsigned int indices[]{
            0, 1, 2, 3, 4, 5
    };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        
        VertexBuffer vb(vertices, 36 * 8 * sizeof(float));
        VertexBufferLayout layout;
        
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        
        va.AddBuffer(vb, layout);
        
        IndexBuffer ib(indices, 6);

        VertexArray crosshairVAO;
        VertexBuffer vbcrossHair(crosshairPosition, 8 * sizeof(float));
        VertexBufferLayout crosshairLayout;
        crosshairLayout.Push(GL_FLOAT, 2);
        crosshairVAO.AddBuffer(vbcrossHair, crosshairLayout);


        VertexArray lightVAO;
        lightVAO.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        Shader crosshairShader("res/shaders/crosshair.shader");
        Shader lightShader("res/shaders/lightShader.shader");


        glm::vec3 objectColorPosition(1.0f, 0.5f, 0.31f);
        glm::vec3 lightColorPosition(1.0f, 1.0f, 1.0f);
        glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);
        glm::vec3 viewerPosition(0.0f, 0.0f, 0.0f);
        
        shader.Bind();
        shader.SetUniformVec3("objectColor", objectColorPosition);
        shader.SetUniformVec3("lightColor", lightColorPosition);
        shader.SetUniformVec3("lightPos", lightPosition);
        shader.SetUniformVec3("viewerPosition", viewerPosition);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 mvp;

        Renderer renderer(deltaTime);
        
        glEnable(GL_DEPTH_TEST);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            renderer.CalculateDeltaTime(currentFrame);
            Camera.ProcessInput(window, renderer.GetDeltaTime());
            glfwSetScrollCallback(window, Camera.scroll_callback_static);

            GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
            renderer.Clear();
            va.Bind();

            //ImGui_ImplGlfwGL3_NewFrame();

            viewMatrix = Camera.LookAround();
            projectionMatrix = glm::perspective(glm::radians(Camera.GetFov()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
            {
                shader.Bind();
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(5.0f, 0.0f, -2.0f));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(8.0f, 3.0f, 0.2f));
                shader.SetUniformMat4f("modelMatrix", modelMatrix);
                mvp = projectionMatrix * viewMatrix * modelMatrix;
                shader.SetUniformMat4f("u_MVP", mvp);
                texture1.Bind();
                renderer.Draw(va, ib, shader);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            }
            {
                lightShader.Bind();
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, lightPosition);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
                mvp = projectionMatrix * viewMatrix * modelMatrix;
                lightShader.SetUniformMat4f("mvp", mvp);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            }
            {
                crosshairShader.Bind();
                crosshairVAO.Bind();
                GLCall(glDrawArrays(GL_LINES, 0, 4));
            }

            //ImGui::Render();
            //ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
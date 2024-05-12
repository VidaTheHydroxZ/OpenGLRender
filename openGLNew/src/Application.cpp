#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLFW/glfw3.h>
#include <conio.h>

#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

#define KEY_UP 72
#define KEY_DOWN 80

struct Wall
{
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 color;
    Texture wallTextureID;
};

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
    window = glfwCreateWindow(2560, 1440, "Hello World", NULL, NULL);
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

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
          1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
          1.0f,-1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         -1.0f,-1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         -1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
        };

        float texCoordinates[] = {
          0.0f, 0.0f,
          1.0f, 0.0f,
          1.0f, 1.0f,
          0.0f, 1.0f
        };

        unsigned int indices[]{
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 8 * 4 * sizeof(float));

        VertexBufferLayout layout;
       
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        //glm::mat4 proj = glm::ortho(0.0f, 2560.0f, 0.0f, 1440.0f, -1.0f, 1.0f); // this means that projection matrix is between -2.0x and 2.0x and -2.0y and 2.0y (-1 and +1) 
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        //glm::mat4 projection = glm::perspective();

        

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("textures/wooden_container.jpg");
        Texture awesomeFace("textures/awesomeface.png");



        shader.SetUniform1i("MyTexture", 0);
        shader.SetUniform1i("MyTexture2", 1);

        
        float visibility = 1;
        

        

       
        
        
        //shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();


        glm::vec3 translationA(400, 800, 0);
        glm::vec3 translationB(300, 250, 0);
        glm::vec3 translationC(300, 500, 0);

        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            {
                float timeValue = glfwGetTime();
                float greenValue = sin(timeValue) / 2.0f + 0.5f;
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                //glm::mat4 mvp = proj * view * model;
                shader.Bind();
                //shader.SetUniformMat4f("u_MVP", mvp);
                shader.SetUniform1f("Visibility", visibility);
                texture.Bind();
                renderer.Draw(va, ib, shader);
            }
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                //glm::mat4 mvp = proj * view * model;
                shader.Bind();
                //shader.SetUniformMat4f("u_MVP", mvp);
                shader.SetUniform1f("Visibility", visibility);
                awesomeFace.Bind(1);
                renderer.Draw(va, ib, shader);
            }

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                if (visibility <= 1) visibility += 0.001;
            }

            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                if (visibility >= 0) visibility -= 0.001;
            }
          
            ImGui::Text("Hello, world!");                          
            ImGui::SliderFloat3("##button1", &translationA.x, 0.0f, 2560.0f);

            ImGui::SliderFloat3("##button2", &translationB.x, 0.0f, 2560.0f);
              
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spinning Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("vertex_shader.vs", "fragment_shader.fs");

    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right         
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // top-left
        // front face
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // bottom-left
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // top-right
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // top-right
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // bottom-left
        // left face
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // bottom-right
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
        // right face
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom-left
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom-left
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // top-right
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // bottom-right 
         // bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-right 
        // top face
       -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-left
        0.5f,  0.5f , 0.5f, 0.0f, 1.0f, 1.0f, // bottom-right
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // top-right     
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // bottom-right
       -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-left
       -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // bottom-left
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        // input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}










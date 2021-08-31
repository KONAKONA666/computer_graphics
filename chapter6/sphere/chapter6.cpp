// chapter6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

#include "Sphere.h"

using namespace std;

#define numVAOs 1
#define numVBOs 3

Sphere mySphere(100);

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint renderingProgram;

float cameraX, cameraY, cameraZ;

GLuint mvLoc, projLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

void setupVertices() {
    std::vector<int> ind = mySphere.getIndicies();
    std::vector<glm::vec3> vert = mySphere.getVerticies();
    std::vector<glm::vec2> tex = mySphere.getTexCoords();
    std::vector<glm::vec3> norm = mySphere.getNormals();
    
    std::vector<float> pvalues; // vertex positions
    std::vector<float> tvalues; // texture coordinates
    std::vector<float> nvalues; // normal vectors

    int numIndices = mySphere.getNumIndicies();
    for (int i = 0; i < numIndices; i++) {
        pvalues.push_back(vert[ind[i]].x);
        pvalues.push_back(vert[ind[i]].y);
        pvalues.push_back(vert[ind[i]].z);

        tvalues.push_back(tex[ind[i]].s);
        tvalues.push_back(tex[ind[i]].t);

        nvalues.push_back(norm[ind[i]].x);
        nvalues.push_back(norm[ind[i]].y);
        nvalues.push_back(norm[ind[i]].z);
    }

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
}


void display(GLFWwindow* window, double currentTime) {

    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    mvLoc = glGetUniformLocation(renderingProgram, "mv_Matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_Matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mMat *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0f, 1.0f, 0.0f));

    mvMat = vMat * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndicies());
}

void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram(
        "vertShader.glsl",
        "fragmentShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
    setupVertices();  
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // I don't know what this does
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // and neither this
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter3 - exercise1", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

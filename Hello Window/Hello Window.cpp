// Hello Window.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>

// includes for Open GL - libraries to open a window on Windows
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"


// Constants for creating window
const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Window 1";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullscreen = false; //true;

// keyboard callback
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
// fps
void showFPS(GLFWwindow* window);


int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW Initialization failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow* pWindow = NULL;

    if (gFullscreen)
    {
        GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);

        if (pVmode != NULL)
        {
            pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
        }
    }
    else {
        pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
    }

    if (pWindow == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        // opposite of Init - destroy object
        glfwTerminate();
        return -1;
    }

    // make window focus
    glfwMakeContextCurrent(pWindow);

    glfwSetKeyCallback(pWindow, glfw_onKey);


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW Initialization failed" << std::endl;

        return -1;
    }

    // main loop
    while (!glfwWindowShouldClose(pWindow))
    {
        // get fps
        showFPS(pWindow);

        glfwPollEvents();

        // clear color
        glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // buffer on screen - buffer we are currently drawing on
        glfwSwapBuffers(pWindow);
    }

    // clean up glfw Init
    glfwTerminate();
    return 0;
}


// implement callback Key function
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

//show fps
void showFPS(GLFWwindow* window)
{
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime(); // returns number of seconds GLFW started

    elapsedSeconds = currentSeconds - previousSeconds;

    // limit text 4 time per second
    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
            << APP_TITLE << "    "
            << "FPS: " << fps << "     "
            << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());
        frameCount = 0;

    }

    frameCount++;
}
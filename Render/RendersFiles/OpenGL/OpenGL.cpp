#include "..\..\Headers\OpenGL\OpenGL.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void _main()
{
    // Инициализация GLFW
    if (!glfwInit())
        return;

    // Устанавливаем версию OpenGL и создаем окно
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    // Устанавливаем контекст текущим и устанавливаем callback функцию изменения размера окна
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Основной цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        // Отрисовываем что-то с использованием OpenGL
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glEnd();

        // Поддерживаем двойную буферизацию
        glfwSwapBuffers(window);

        // Проверяем события
        glfwPollEvents();
    }

    // Закрываем GLFW и завершаем программу
    glfwTerminate();
    return;
}
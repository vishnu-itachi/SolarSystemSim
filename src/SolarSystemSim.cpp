// SolarSystemSim.cpp : Defines the entry point for the application.
//

#include "SolarSystemSim.h"
#include <vector>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    {

        std::vector<CelestialBody> bodies;
        bodies.push_back(CelestialBody("Sun", 0.1f, 10e10, Point(0.0f, 0.0f)));
        bodies.push_back(CelestialBody("Earth", 0.1f, 1e10, Point(0.5f, 0.0f)));

        GLuint VAO; // vb + layout
        CheckedGLCall(glGenVertexArrays(1, &VAO));
        CheckedGLCall(glBindVertexArray(VAO));

        VertexBuffer vb(Vertices, sizeof(Vertices));
        IndexBuffer ib(Elements, 3);

        Shader shaderProgram(vertexShaderPath, fragmentShaderPath);

        // CheckedGLCall(glBindFragDataLocation(shaderProgram.getShaderProgram(), 0, "outColor"));

        ib.bind();
        vb.bind();
        // GLint PositionAttribute = CheckedGLResult(glGetAttribLocation(shaderProgram.getShaderProgram(), "position"));
        shaderProgram.bind();

        CheckedGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        CheckedGLCall(glEnableVertexAttribArray(0));
        CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        while (!glfwWindowShouldClose(window))
        {
            CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            CheckedGLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        ib.unbind();
        vb.unbind();
        CheckedGLCall(glDeleteVertexArrays(1, &VAO));
        shaderProgram.unbind();
    }
    glfwTerminate();
    return 0;
}

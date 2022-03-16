// SolarSystemSim.cpp : Defines the entry body for the application.
//

#include "SolarSystemSim.h"
#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void add_point_vertices(std::vector<CelestialBody> &bodies, std::vector<float> &q1)
{
    float *quad = new float[bodies.size() * 24];
    vector resolution = vector(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0; i < bodies.size(); i++)
    {
        auto body = bodies[i];
        auto center = body.position();

        float x_radius = (float)body.GetRadius() / SCREEN_WIDTH;
        float y_radius = (float)body.GetRadius() / SCREEN_HEIGHT;
        // add the 6 vertices for the triangles.
        int offset = 0;
        quad[24 * i + offset++] = body.position()._a + x_radius;
        quad[24 * i + offset++] = body.position()._b - y_radius;
        quad[24 * i + offset++] = 1;
        quad[24 * i + offset++] = -1;

        quad[24 * i + offset++] = body.position()._a + x_radius;
        quad[24 * i + offset++] = body.position()._b + y_radius;
        quad[24 * i + offset++] = 1;
        quad[24 * i + offset++] = 1;

        quad[24 * i + offset++] = body.position()._a - x_radius;
        quad[24 * i + offset++] = body.position()._b + y_radius;
        quad[24 * i + offset++] = -1;
        quad[24 * i + offset++] = 1;

        quad[24 * i + offset++] = body.position()._a - x_radius;
        quad[24 * i + offset++] = body.position()._b + y_radius;
        quad[24 * i + offset++] = -1;
        quad[24 * i + offset++] = 1;

        quad[24 * i + offset++] = body.position()._a - x_radius;
        quad[24 * i + offset++] = body.position()._b - y_radius;
        quad[24 * i + offset++] = -1;
        quad[24 * i + offset++] = -1;

        quad[24 * i + offset++] = body.position()._a + x_radius;
        quad[24 * i + offset++] = body.position()._b - y_radius;
        quad[24 * i + offset++] = 1;
        quad[24 * i + offset++] = -1;
    }
    q1.insert(q1.end(), quad, quad + bodies.size() * 24);
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    {

        std::vector<CelestialBody> bodies;
        size_t earth_or = 1.5e8l;
        auto astro_scale = vector(1, 480.0 / 604) * 2 * earth_or;
        bodies.push_back(CelestialBody("Sun", 30, 2e30, vector(.0f, .0f), astro_scale, vector(.0f, .0f)));
        bodies.push_back(CelestialBody("Earth", 10, 5.97e24, vector(.5f, .0f), astro_scale, vector(.0f, 29.780f)));
        Simulator sim(bodies, 10ms, 15);

        // std::string vertexShaderPath = "../res/shaders/Vertex.vert";
        // std::string fragmentShaderPath = "../res/shaders/Fragment.frag";
        std::string vertexShaderPath = "res/shaders/Vertex.vert";
        std::string fragmentShaderPath = "res/shaders/Fragment.frag";
        Shader shaderProgram(vertexShaderPath, fragmentShaderPath);
        shaderProgram.bind();

        VertexBuffer vb;

        int ATTRIB_VERTEX = glGetAttribLocation(shaderProgram.getShaderProgram(), "vertex");
        int ATTRIB_VALUE = glGetAttribLocation(shaderProgram.getShaderProgram(), "value");
        glEnableVertexAttribArray(ATTRIB_VERTEX);
        glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, 16, 0);
        glEnableVertexAttribArray(ATTRIB_VALUE);
        glVertexAttribPointer(ATTRIB_VALUE, 2, GL_FLOAT, GL_FALSE, 16, BUFFER_OFFSET(8));

        std::vector<float> simulated_positions;
        auto num_steps = 1000;
        for (unsigned int i = 0; i < num_steps; i++)
        {
            std::vector<float> vertices;
            add_point_vertices(sim.bodies(), vertices);
            simulated_positions.insert(simulated_positions.end(), vertices.begin(),vertices.end());
            sim.forward();
        }
        vb.send_data(simulated_positions.data(), simulated_positions.size() * 4);
        std::cout << simulated_positions.size() << "\n";

        int i = 0;
        while (!glfwWindowShouldClose(window) && i < simulated_positions.size())
        {
            CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT));

            auto num_vertices = simulated_positions.size() / num_steps / 4;
            CheckedGLCall(glDrawArrays(GL_TRIANGLES, num_vertices * i++, num_vertices));

            sim.wait();
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        std::cout << "\n";

        vb.unbind();
        shaderProgram.unbind();
    }
    glfwTerminate();
    return 0;
}

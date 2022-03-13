// SolarSystemSim.cpp : Defines the entry body for the application.
//

#include "SolarSystemSim.h"
#include <vector>

#define BUFFER_OFFSET(i) ((char *) NULL + (i))

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
	// Use a Vertex Array Object
	// GLuint vao;
	// glGenVertexArrays(1, &vao);
	// glBindVertexArray(vao);

	float *quad = new float[bodies.size() * 24];
	Point resolution = Point(SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < bodies.size(); i++) {
		// transform the body
        auto body = bodies[i];
        auto center = body.GetPosition();

        float x_radius = (float) body.GetRadius() / SCREEN_WIDTH;
        float y_radius = (float) body.GetRadius() / SCREEN_HEIGHT;
        std::cout << "x_radius: " << x_radius << std::endl;
        std::cout << "y_radius: " << y_radius << std::endl;
		// add the 6 vertices for the triangles.
		int offset = 0;
		quad[24 * i + offset++] = body.GetPosition().x + x_radius;
		quad[24 * i + offset++] = body.GetPosition().y - y_radius;
		quad[24 * i + offset++] = 1;
		quad[24 * i + offset++] = -1;

		quad[24 * i + offset++] = body.GetPosition().x + x_radius;
		quad[24 * i + offset++] = body.GetPosition().y + y_radius;
		quad[24 * i + offset++] = 1;
		quad[24 * i + offset++] = 1;

		quad[24 * i + offset++] = body.GetPosition().x - x_radius;
		quad[24 * i + offset++] = body.GetPosition().y + y_radius;
		quad[24 * i + offset++] = -1;
		quad[24 * i + offset++] = 1;

		quad[24 * i + offset++] = body.GetPosition().x - x_radius;
		quad[24 * i + offset++] = body.GetPosition().y + y_radius;
		quad[24 * i + offset++] = -1;
		quad[24 * i + offset++] = 1;

		quad[24 * i + offset++] = body.GetPosition().x - x_radius;
		quad[24 * i + offset++] = body.GetPosition().y - y_radius;
		quad[24 * i + offset++] = -1;
		quad[24 * i + offset++] = -1;

		quad[24 * i + offset++] = body.GetPosition().x + x_radius;
		quad[24 * i + offset++] = body.GetPosition().y - y_radius;
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
        bodies.push_back(CelestialBody("Sun", 30, 10e10, Point(.0f, .0f)));
        bodies.push_back(CelestialBody("Earth", 20, 1e10, Point(.5f, .0f)));

        // GLuint VAO; // vb + layout
        // CheckedGLCall(glGenVertexArrays(1, &VAO));
        // CheckedGLCall(glBindVertexArray(VAO));

        // float vertices[] = {};
        std::vector<float> vertices;
        add_point_vertices(bodies, vertices);
        VertexBuffer vb(vertices.data(), vertices.size() * 4);
        // iBuffer ib(Elements, 3);

        std::string vertexShaderPath = "res/shaders/Vertex.vert";
        std::string fragmentShaderPath = "res/shaders/Fragment.frag";
        Shader shaderProgram(vertexShaderPath, fragmentShaderPath);

        // CheckedGLCall(glBindFragDataLocation(shaderProgram.getShaderProgram(), 0, "outColor"));

        // ib.bind();
        // vb.bind();
        shaderProgram.bind();

        while (!glfwWindowShouldClose(window))
        {
            // CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT));
            
            int ATTRIB_VERTEX = glGetAttribLocation(shaderProgram.getShaderProgram(), "vertex");
            int ATTRIB_VALUE = glGetAttribLocation(shaderProgram.getShaderProgram(), "value");
            // std::cout << ATTRIB_VERTEX << " " << ATTRIB_VALUE << " " << vertices[0] << " " << vertices[1] << std::endl;

            glEnableVertexAttribArray(ATTRIB_VERTEX);
            glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, 16, 0);
            glEnableVertexAttribArray(ATTRIB_VALUE);
            glVertexAttribPointer(ATTRIB_VALUE, 2, GL_FLOAT, GL_FALSE, 16, BUFFER_OFFSET(8));


            CheckedGLCall(glDrawArrays(GL_TRIANGLES, 0, vertices.size()));
            // shaderProgram.unbind();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // ib.unbind();
        vb.unbind();
        // CheckedGLCall(glDeleteVertexArrays(1, &VAO));
        shaderProgram.unbind();
    }
    glfwTerminate();
    return 0;
}

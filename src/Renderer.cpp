#include "SolarSystemSim.h"
#include <format>
void PrintOpenGLErrors(char const *const Function, char const *const File, int const Line)
{
    bool Succeeded = true;

    GLenum Error = glGetError();
    if (Error != GL_NO_ERROR)
    {
        char const *ErrorString = (char const *)gluErrorString(Error);
        if (ErrorString)
            printf("OpenGL Error in %s at line %d calling function %s: '%s'\n", File, Line, Function, ErrorString);
        else
            printf("OpenGL Error in %s at line %d calling function %s: '%d 0x%X' \n", File, Line, Function, Error,
                   Error);
    }
}

void PrintShaderInfoLog(GLint const Shader)
{
    int InfoLogLength = 0;
    int CharsWritten = 0;

    glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0)
    {
        GLchar *InfoLog = new GLchar[InfoLogLength];
        glGetShaderInfoLog(Shader, InfoLogLength, &CharsWritten, InfoLog);
        std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
        delete[] InfoLog;
    }
}

#include "Shader.h"
#include "gl/glew.h"
#include <cassert>
#include <filesystem>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    : vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath), m_RendererID(0)
{
    std::string vertexsource = GetShadderFromSource(vertexShaderPath);
    std::string fragmentsource = GetShadderFromSource(fragmentShaderPath);
    m_RendererID = CreateShader(vertexsource, fragmentsource);
}

Shader::~Shader()
{
    CheckedGLCall(glDeleteProgram(m_RendererID));
}

std::string Shader::GetShadderFromSource(const std::string &filepath)
{
    if (!std::filesystem::exists(filepath))
        throw std::exception("File not found");
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss;
    while (getline(stream, line))
    {
        ss << line << "\n";
    }
    return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = CheckedGLResult(glCreateShader(type));
    const char *src = source.c_str();
    CheckedGLCall(glShaderSource(id, 1, &src, nullptr));
    CheckedGLCall(glCompileShader(id));

    /*Error handling*/
    int result;
    CheckedGLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result)
    {
        int length;
        CheckedGLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        auto message = (char *)alloca(length * sizeof(char));
        CheckedGLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertexshader" : "fragmentshader") << std::endl;
        std::cout << message << std::endl;
        CheckedGLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexshader, const std::string &fragmentshader)
{
    unsigned int program = CheckedGLResult(glCreateProgram());
    unsigned int vs = CheckedGLResult(CompileShader(GL_VERTEX_SHADER, vertexshader));
    unsigned int fs = CheckedGLResult(CompileShader(GL_FRAGMENT_SHADER, fragmentshader));
    PrintShaderInfoLog(vs);
    PrintShaderInfoLog(fs);
    CheckedGLCall(glAttachShader(program, vs));
    CheckedGLCall(glAttachShader(program, fs));
    CheckedGLCall(glLinkProgram(program));
    CheckedGLCall(glValidateProgram(program));

    CheckedGLCall(glDeleteShader(vs));
    CheckedGLCall(glDeleteShader(fs));

    return program;
}

void Shader::bind() const
{
    CheckedGLCall(glUseProgram(m_RendererID));
    // glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
    CheckedGLCall(glUseProgram(0));
}

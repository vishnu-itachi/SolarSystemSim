#include "Renderer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
private:
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    unsigned int m_RendererID;

public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    ~Shader();
    void bind() const;
    void unbind() const;
    unsigned int getShaderProgram()
    {
        return m_RendererID;
    }

private:
    std::string GetShadderFromSource(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexshader, const std::string &fragmentshader);
};

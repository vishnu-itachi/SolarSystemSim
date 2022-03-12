#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count)
{
    static_assert(sizeof(unsigned int) == sizeof(GLuint), "Size error");
    CheckedGLCall(glGenBuffers(1, &m_RendererID));
    CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    CheckedGLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const
{
    CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const
{
    CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

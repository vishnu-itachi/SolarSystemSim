#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer()
{
    CheckedGLCall(glGenBuffers(1, &m_RendererID));
    CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    CheckedGLCall(glGenBuffers(1, &m_RendererID));
    CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    CheckedGLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const
{
    CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind() const
{
    CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::send_data(const void *data, unsigned int size)
{
    CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

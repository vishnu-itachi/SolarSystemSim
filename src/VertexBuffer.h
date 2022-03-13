#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererID;

public:
    VertexBuffer();
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void send_data(const void *data, unsigned int size);
};

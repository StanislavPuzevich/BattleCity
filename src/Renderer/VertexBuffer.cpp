#include "VertexBuffer.h"

namespace Renderer
{
    VertexBuffer::VertexBuffer() : m_id(0)
    {
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    {
        m_id = vertexBuffer.m_id;
        vertexBuffer.m_id = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
    { 
        m_id = vertexBuffer.m_id;
        vertexBuffer.m_id = 0;
        return *this;
    }

    void VertexBuffer::init(const void* data, const unsigned size)
    {
        glGenBuffers(1, &m_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::update(const void* data, const unsigned size) const
    {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
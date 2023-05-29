#include "IndexBuffer.h"

#include <iostream>

namespace Renderer
{
    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
    {
        m_id = indexBuffer.m_id;
        indexBuffer.m_id = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
    { 
        m_id = indexBuffer.m_id;
        indexBuffer.m_id = 0;
        return *this;
    }

    void IndexBuffer::init(const void* data, const unsigned size)
    {
        glGenBuffers(1, &m_id);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
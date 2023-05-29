#pragma once

#include <glad/glad.h>

namespace Renderer
{
    class IndexBuffer
    {
    public:
        IndexBuffer() : m_id(0) {}
        ~IndexBuffer() { glDeleteBuffers(1, &m_id); }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;

        void init(const void* data, const unsigned size);
        void bind() const;
        void unbind() const;

    private:
        GLuint m_id;
    };
}
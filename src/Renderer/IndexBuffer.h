#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
    class IndexBuffer
    {
    public:
        IndexBuffer() : m_id(0), m_count(0) {}
        ~IndexBuffer() { glDeleteBuffers(1, &m_id); }

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;

        unsigned getCount() const { return m_count; }
        void init(const void* data, const unsigned count);
        void bind() const;
        void unbind() const;

    private:
        GLuint m_id;
        unsigned m_count;
    };
}
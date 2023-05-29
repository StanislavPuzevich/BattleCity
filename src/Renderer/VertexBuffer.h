#pragma once

#include <glad/glad.h>

namespace Renderer
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
        VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;

        void init(const void* data, const unsigned size);
        void update(const void* data, const unsigned size) const;
        void bind() const;
        void unbind() const;

    private:
        GLuint m_id;
    };
}
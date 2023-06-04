#pragma once

#include <vector>

#include <glad/glad.h>

namespace Renderer
{
    struct VertexBufferLayoutElement
    {
        GLint m_count;
        GLenum m_type;
        GLboolean m_normalized;
        unsigned m_size;

        VertexBufferLayoutElement(GLint count, GLenum type, GLboolean normalized, unsigned sz) : m_count(count), m_type(type), m_normalized(normalized), m_size(sz) {}
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() : m_stried(0) {}

        void reserveElements(const unsigned count) { m_layoutElements.reserve(count); }
        unsigned getStried() const { return m_stried; }
        const std::vector<VertexBufferLayoutElement>& getLayoutElement() const { return m_layoutElements; }

        void addElementLayoutFloat(const int count, const bool normalized);

    private:
        std::vector<VertexBufferLayoutElement> m_layoutElements;
        unsigned m_stried;
    };
}
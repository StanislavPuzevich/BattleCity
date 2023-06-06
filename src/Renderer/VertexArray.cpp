#include "VertexArray.h"

namespace RenderEngine
{
    VertexArray::VertexArray() : m_id(0), m_elementsCount(0)
    {
        glGenVertexArrays(1, &m_id);
    }

    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
    {
        m_id = vertexArray.m_id;
        m_elementsCount = vertexArray.m_elementsCount;
        vertexArray.m_id = 0;
        vertexArray.m_elementsCount = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
    { 
        m_id = vertexArray.m_id;
        m_elementsCount = vertexArray.m_elementsCount;
        vertexArray.m_id = 0;
        vertexArray.m_elementsCount = 0;
        return *this;
    }

    void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        GLbyte* offset = nullptr;
        const auto& LayoutElements = layout.getLayoutElement();

        unsigned counter = 0;
        for (auto& currentLyoutElement : LayoutElements)
        {
            GLuint currentAttribIndex = m_elementsCount + counter;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, currentLyoutElement.m_count, currentLyoutElement.m_type, currentLyoutElement.m_normalized, layout.getStried(), offset);
            offset += currentLyoutElement.m_size;
            counter++;
        }
        m_elementsCount += static_cast<unsigned>(LayoutElements.size());
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
}
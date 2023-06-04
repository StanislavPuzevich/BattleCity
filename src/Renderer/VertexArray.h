//#pragma once
//
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//
//#include <glad/glad.h>
//
//namespace Renderer
//{
//    class VertexArray
//    {
//    public:
//        VertexArray();
//        ~VertexArray() { glDeleteVertexArrays(1, &m_id); }
//
//        VertexArray(const VertexArray&) = delete;
//        VertexArray& operator=(const VertexArray&) = delete;
//
//        VertexArray(VertexArray&& vertexArray) noexcept;
//        VertexArray& operator=(VertexArray&& vertexArray) noexcept;
//
//        void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
//        void bind() const;
//        void unbind() const;
//
//    private:
//        GLuint m_id;
//        unsigned m_elementsCount;
//    };
//}

#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace Renderer {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray& operator=(VertexArray&& vertexArray) noexcept;
        VertexArray(VertexArray&& vertexArray) noexcept;

        void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
        void bind() const;
        void unbind() const;

    private:
        GLuint m_id = 0;
        unsigned int m_elementsCount = 0;
    };

}
#pragma once

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "IndexBuffer.h"

namespace RenderEngine
{
    class Renderer
    {
    public:
        static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);

        static void clear() { glClear(GL_COLOR_BUFFER_BIT); }
        static void setClearColor(const float red, const float green, const float blue, const float alpha) { glClearColor(red, green, blue, alpha); }
        static void setViewport(const unsigned width, const unsigned height, const unsigned leftOffset, const unsigned bottomtOffset) { glViewport(leftOffset, bottomtOffset, width, height); }
        static const unsigned char* getString(const unsigned name) { return glGetString(name); }
    };
}
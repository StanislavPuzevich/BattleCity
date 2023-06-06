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
        static void setClearColor(float red, float green, float blue, float alpha) { glClearColor(red, green, blue, alpha); }
        static void setViewport(int width, int height) { glViewport(0, 0, width, height); }
        static const unsigned char* getString(unsigned name) { return glGetString(name); }
    };
}
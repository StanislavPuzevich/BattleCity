#include "VertexBufferLayout.h"

void Renderer::VertexBufferLayout::addElementLayoutFloat(const int count, const bool normalized)
{
    m_layoutElements.push_back({ count, GL_FLOAT, normalized, count * sizeof(GLfloat) });
    m_stried += m_layoutElements.back().m_size;
}

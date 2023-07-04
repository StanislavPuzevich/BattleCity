#include "BrickWall.h"
#include "../../src/Renderer/Sprite.h"

void BrickWall::render() const
{
    m_pCurrentSpite->render(m_position, m_size, m_rotation);
}

void BrickWall::update(const uint64_t delta)
{

}
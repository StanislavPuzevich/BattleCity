#include "Tank.h"
#include "../../Renderer/Sprite.h"

void Tank::render() const
{ 
    switch (m_eOrientation)
    {
    case Tank::EOrientation::Top:
        m_pSpite_top->render(m_position, m_size, m_rotation, m_spriteAnimator_top.getCurrentFrame());
        break;
    case Tank::EOrientation::Bottom:
        m_pSpite_bottom->render(m_position, m_size, m_rotation, m_spriteAnimator_bottom.getCurrentFrame());
        break;
    case Tank::EOrientation::Left:
        m_pSpite_left->render(m_position, m_size, m_rotation, m_spriteAnimator_left.getCurrentFrame());
        break;
    case Tank::EOrientation::Right:
        m_pSpite_right->render(m_position, m_size, m_rotation, m_spriteAnimator_right.getCurrentFrame());
        break;
    }
}

void Tank::setOrientation(const EOrientation eOrientation)
{
    if (m_eOrientation == eOrientation) return;

    m_eOrientation = eOrientation;
    switch (m_eOrientation)
    {
    case Tank::EOrientation::Top:;
        m_moveOfset.x = 0.f;
        m_moveOfset.y = 1.f;
        break;
    case Tank::EOrientation::Bottom:
        m_moveOfset.x =  0.f;
        m_moveOfset.y = -1.f;
        break;
    case Tank::EOrientation::Left: 
        m_moveOfset.x = -1.f;
        m_moveOfset.y =  0.f;
        break;
    case Tank::EOrientation::Right:
        m_moveOfset.x = 1.f;
        m_moveOfset.y = 0.f;
        break;
    default:
        break;
    }
}

void Tank::update(const uint64_t delta)
{
    if (m_move == false) return;

    m_position += delta * m_velocity * m_moveOfset;

    switch (m_eOrientation)
    {
    case Tank::EOrientation::Top:
        m_spriteAnimator_top.update(delta);
        break;
    case Tank::EOrientation::Bottom:
        m_spriteAnimator_bottom.update(delta);
        break;
    case Tank::EOrientation::Left:
        m_spriteAnimator_left.update(delta);
        break;
    case Tank::EOrientation::Right:
        m_spriteAnimator_right.update(delta);
        break;
    }
}
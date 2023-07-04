#include "Tank.h"
#include "../../Renderer/AnimatedSprite.h"

void Tank::render() const
{ 
    m_pSpite->render(m_position, m_size, m_rotation);
}

void Tank::setOrientation(const EOrientation eOrientation)
{
    if (m_eOrientation == eOrientation) return;

    m_eOrientation = eOrientation;
    switch (m_eOrientation)
    {
    case Tank::EOrientation::Top:;
        m_pSpite->setState("tankTopState");
        m_moveOfset.x = 0.f;
        m_moveOfset.y = 1.f;
        break;
    case Tank::EOrientation::Bottom:
        m_pSpite->setState("tankBottomState");
        m_moveOfset.x =  0.f;
        m_moveOfset.y = -1.f;
        break;
    case Tank::EOrientation::Left: 
        m_pSpite->setState("tankLeftState");
        m_moveOfset.x = -1.f;
        m_moveOfset.y =  0.f;
        break;
    case Tank::EOrientation::Right:
        m_pSpite->setState("tankRightState");
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

    if (m_position.x < 555 && m_position.x > -10 && m_position.y < 388 && m_position.y > -10)
        m_position += delta * m_velocity * m_moveOfset;
    else if (m_position.x >= 555) m_position.x = 554;
    else if (m_position.x <= -10) m_position.x = -9;
    else if (m_position.y >= 388) m_position.y = 387;
    else if (m_position.y <= -10) m_position.y = -9;

    m_pSpite->update(delta);
}
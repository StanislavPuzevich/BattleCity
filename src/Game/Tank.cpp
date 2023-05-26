#include "Tank.h"
#include "../Renderer/AnimatedSprite.h"

Tank::Tank(std::shared_ptr<Renderer::AnimatedSprite> pSpite, const float velocity, const glm::vec2& position)
    : m_eOrientation(EOrientation::Top),
      m_pSpite(pSpite), 
      m_move(false), 
      m_velocity(velocity), 
      m_position(position),
      m_moveOfset(glm::vec2(0.f, 1.f))
{

}

void Tank::render() const 
{ 
    m_pSpite->render();
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

    m_position += delta * m_velocity * m_moveOfset;
    m_pSpite->setPosition(m_position);
    m_pSpite->update(delta);
}
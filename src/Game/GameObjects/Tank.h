#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"

namespace RenderEngine
{
    class AnimatedSprite;
}

class Tank : public IGameObject
{
public:
    enum class EOrientation
    {
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSpite, const float velocity, const glm::vec2& position, const glm::vec2& size)
        : IGameObject(position, size, 0.f),
          m_eOrientation(EOrientation::Top),
          m_pSpite(pSpite),
          m_move(false),
          m_velocity(velocity),
          m_moveOfset(glm::vec2(0.f, 1.f)) {}

    void render() const override;
    void move(const bool move) { m_move = move; }
    void setOrientation(const EOrientation eOrientation);
    void update(const uint64_t delta) override;

private:
    EOrientation m_eOrientation;
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSpite;
    bool m_move;
    float m_velocity;
    glm::vec2 m_moveOfset;
};
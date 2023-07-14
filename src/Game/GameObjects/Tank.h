#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine
{
    class Sprite;
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

    Tank(std::shared_ptr<RenderEngine::Sprite> pSpite_top,
         std::shared_ptr<RenderEngine::Sprite> pSpite_bottom,
         std::shared_ptr<RenderEngine::Sprite> pSpite_left,
         std::shared_ptr<RenderEngine::Sprite> pSpite_right,
         const float velocity, 
         const glm::vec2& position, 
         const glm::vec2& size)
        : IGameObject(position, size, 0.f),
          m_eOrientation(EOrientation::Top),
          m_pSpite_top(std::move(pSpite_top)),
          m_pSpite_bottom(std::move(pSpite_bottom)),
          m_pSpite_left(std::move(pSpite_left)),
          m_pSpite_right(std::move(pSpite_right)),
          m_spriteAnimator_top(m_pSpite_top),
          m_spriteAnimator_bottom(m_pSpite_bottom),
          m_spriteAnimator_left(m_pSpite_left),
          m_spriteAnimator_right(m_pSpite_right),
          m_move(false),
          m_velocity(velocity),
          m_moveOfset(glm::vec2(0.f, 1.f)) {}

    void render() const override;
    void move(const bool move) { m_move = move; }
    void setOrientation(const EOrientation eOrientation);
    void update(const uint64_t delta) override;

private:
    EOrientation m_eOrientation;
    std::shared_ptr<RenderEngine::Sprite> m_pSpite_top;
    std::shared_ptr<RenderEngine::Sprite> m_pSpite_bottom;
    std::shared_ptr<RenderEngine::Sprite> m_pSpite_left;
    std::shared_ptr<RenderEngine::Sprite> m_pSpite_right;
    RenderEngine::SpriteAnimator m_spriteAnimator_top;
    RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
    RenderEngine::SpriteAnimator m_spriteAnimator_left;
    RenderEngine::SpriteAnimator m_spriteAnimator_right;
    bool m_move;
    float m_velocity;
    glm::vec2 m_moveOfset;
};
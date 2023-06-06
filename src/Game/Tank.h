#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace RenderEngine
{
    class AnimatedSprite;
}

class Tank
{
public:
    enum class EOrientation
    {
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSpite, const float velocity, const glm::vec2& position);

    void render() const;
    void move(const bool move) { m_move = move; }
    void setOrientation(const EOrientation eOrientation);
    void update(const uint64_t delta);

private:
    EOrientation m_eOrientation;
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSpite;
    bool m_move;
    float m_velocity;
    glm::vec2 m_position;
    glm::vec2 m_moveOfset;
};
#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine
{
    class Sprite;
}

class BrickWall : public IGameObject
{
public: 
    BrickWall(std::shared_ptr<RenderEngine::Sprite> pSpite, const glm::vec2& position, const glm::vec2& size, const float rotation)
        : IGameObject(position, size, rotation),
          m_pCurrentSpite(pSpite) {}

    void render() const override;
    void update(const uint64_t delta) override;
    ~BrickWall() {}

private:
    std::shared_ptr<RenderEngine::Sprite> m_pCurrentSpite;
};
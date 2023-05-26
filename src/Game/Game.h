#pragma once

#include <glm/vec2.hpp>

#include <array>
#include <memory>

constexpr unsigned MAX_KEY_NUMBER = 349;

class Tank;

class Game
{
public:
    Game(const glm::ivec2& WindowSize);
    ~Game();

    void render();
    void update(const uint64_t delta);
    void setKey(const int key, const int action);
    bool init();

private:
    std::array<bool, MAX_KEY_NUMBER> m_keys;

    enum class EGameState
    {
        Active,
        Pause
    };

    glm::ivec2 m_WindowSize;
    EGameState m_eCurrentGaneState;
    std::unique_ptr<Tank> m_pTank;
};
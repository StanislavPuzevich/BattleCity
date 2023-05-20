#include "Game.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Resources/ResourceManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Renderer/ShaderProgram.h"

#include <iostream>

Game::Game(const glm::ivec2& WindowSize) : m_eCurrentGaneState(EGameState::Active), m_WindowSize(WindowSize)
{
    m_keys.fill(false);
}

Game::~Game()
{

}

void Game::render()
{
    ResourceManager::getAnimatedSprite("NewAnimatedSprite")->render();
}

void Game::update(const uint64_t delta)
{
    ResourceManager::getAnimatedSprite("NewAnimatedSprite")->update(delta);
}

void Game::setKey(const int key, const int action)
{
    m_keys[key] = action;
}

bool Game::init()
{
    auto pDefaultShaderProgram = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Can't load shader program: DefaultShader" << std::endl;
        return false;
    }

    auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't load shader program: SpriteShader" << std::endl;
        return false;
    }

    auto pTex = ResourceManager::loadTexture("DefaultTexture", "res/textures/map_16x16.png");

    std::vector<std::string> subTexturesNames =
    {
        "block",
        "topBlock",
        "bottomBlock",
        "leftBlock",
        "rightBlock",
        "topLeftBlock",
        "topRightBlock",
        "bottomLeftBlock",

        "bottomRigntBlock",
        "beton",
        "topBeton",
        "bottomBeton",
        "leftBeton",
        "rightBeton",
        "topLeftBeton",
        "topRightBeton",

        "bottomLeftBeton",
        "bottomRightBeton",
        "water1",
        "water2",
        "water3",
        "trees",
        "ice",
        "wall",

        "eagle",
        "deadeagle",
        "nothing",
        "respawn1",
        "respawn2",
        "respawn3",
        "respawn4"
    };
    auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);

    auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "rightBlock");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));

    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    std::vector<std::pair<std::string, uint64_t>> eagleState;
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadeagle", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->insertState("eagleState", std::move(eagleState));

    pAnimatedSprite->setState("waterState");

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));
    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_WindowSize.x), 0.f, static_cast<float>(m_WindowSize.y), -100.f, 100.f);

    pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    return true;
}
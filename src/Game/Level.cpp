#include "Level.h"
#include "GameObjects/BrickWall.h"

#include <iostream>

const unsigned BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> createGameObjectFromDescripton(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
    switch (description)
    {
    case '0':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation);
    case '1':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation);
    case '2':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation);
    case '3':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation);
    case '4':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation);
    case 'G':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation);
    case 'H':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation);
    case 'I':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation);
    case 'J':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRihgt, position, size, rotation);
    case 'D':
        return nullptr;
    default:
        std::cerr << "Unknown GameObject description: " << description << "!" << std::endl;
    }

    return nullptr;
}

Level::Level(const std::vector<std::string>& levelDescription)
{
    if (levelDescription.empty())
        std::cerr << "Empty level descriprion!" << std::endl;

    m_width = levelDescription[0].size();
    m_height = levelDescription.size();
    m_mapObjects.reserve(m_width * m_height);

    unsigned currentBottomOffset = static_cast<unsigned>(BLOCK_SIZE * (m_height - 1));
    for (const std::string& currentRow : levelDescription)
    {
        unsigned currentLeftOffset = 0;
        for (const char currentElement : currentRow)
        {
            m_mapObjects.emplace_back(createGameObjectFromDescripton(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }
}

void Level::render() const
{
    for (const auto& currentObject : m_mapObjects)
    {
        if (currentObject)
        {
            currentObject->render();
        }
    }
}

void Level::update(const uint64_t delta)
{
    for (const auto& currentObject : m_mapObjects)
    {
        if (currentObject)
        {
            currentObject->update(delta);
        }
    }
}
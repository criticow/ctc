#pragma once

#include <core/engine.hpp>
#include <ecs/entities/entities.hpp>
#include <ecs/components/components.hpp>
#include <resources/shapes.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "player.hpp"
#include "enemy.hpp"

class Game : public Engine
{
  public:
  Game(int width, int height, const char* title) : Engine(width, height, title){};
  void setup() override;
  void update() override;
  Player player;
  // Enemy enemy;
  std::vector<Enemy> enemies;
  bool isGameOver = false;
};
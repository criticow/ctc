#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include <core/window.hpp>
#include <core/logger.hpp>

struct ActionState
{
  bool pressed = false;
  bool held = false;
  bool released = false;
};

struct Action
{
  ActionState state;
  std::vector<int> keys;
};

class Input
{
  public:
  Input();
  void update(Window window);
  bool actionPressed(std::string action);
  bool actionHeld(std::string action);
  bool actionReleased(std::string action);

  private:
  std::unordered_set<std::string> pressedActions;
  std::unordered_set<std::string> heldActions;
  std::unordered_map<std::string, Action> actions;
};
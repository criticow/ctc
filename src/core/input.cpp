#include "input.hpp"

Input::Input()
{
  this->actions = {
    { "left",   { ActionState{}, { GLFW_KEY_A, GLFW_KEY_LEFT } } },
    { "right",  { ActionState{}, { GLFW_KEY_D, GLFW_KEY_RIGHT } } },
    { "up",     { ActionState{}, { GLFW_KEY_W, GLFW_KEY_UP } } },
    { "down",   { ActionState{}, { GLFW_KEY_S, GLFW_KEY_DOWN } } },
    { "jump",   { ActionState{}, { GLFW_KEY_SPACE } } },
    { "accept", { ActionState{}, { GLFW_KEY_ENTER } } },
    { "cancel", { ActionState{}, { GLFW_KEY_ESCAPE } } },
    { "f1",     { ActionState{}, { GLFW_KEY_F1 } } },
    { "f2",     { ActionState{}, { GLFW_KEY_F2 } } },
    { "f3",     { ActionState{}, { GLFW_KEY_F3 } } },
    { "f4",     { ActionState{}, { GLFW_KEY_F4 } } },
    { "f5",     { ActionState{}, { GLFW_KEY_F5 } } },
    { "f6",     { ActionState{}, { GLFW_KEY_F6 } } },
    { "f7",     { ActionState{}, { GLFW_KEY_F7 } } },
    { "f8",     { ActionState{}, { GLFW_KEY_F8 } } },
    { "f9",     { ActionState{}, { GLFW_KEY_F9 } } },
    { "f10",    { ActionState{}, { GLFW_KEY_F10 } } },
    { "f11",    { ActionState{}, { GLFW_KEY_F11 } } },
    { "f12",    { ActionState{}, { GLFW_KEY_F12 } } },
  };
}

void Input::update(Window window)
{
  for(auto& [_, action] : this->actions)
  {
    bool pressed, held, released;

    action.state.released = false;

    for(size_t i = 0; i < action.keys.size(); i++)
    {
      int key = action.keys[i];
      int keyState = glfwGetKey(window.handle, key);

      if(keyState == GLFW_PRESS)
      {
        if(!action.state.pressed && !action.state.held)
        {
          action.state.pressed = true;
          action.state.held = true;
          action.state.released = false;
        }
        else
        {
          action.state.pressed = false;
          action.state.held = true;
          action.state.released = false;
        }

        break;
      }
      else if(keyState == GLFW_RELEASE)
      {
        // Check if it is the last key entry
        if(i == action.keys.size() -1)
        {
          action.state.held = false;
          action.state.pressed = false;
        }

        // Release only if the current state is held or pressed
        if(action.state.pressed || action.state.held)
        {
          action.state.released = true;
        }
      }
    }
  }
}

bool Input::actionPressed(std::string action)
{
  bool isPressed = false;

  // The action exists
  if(this->actions.find(action) != this->actions.end())
  {
    isPressed = this->actions[action].state.pressed;
  }

  return isPressed;
}

bool Input::actionHeld(std::string action)
{
  bool isHeld = false;

  // The action exists
  if(this->actions.find(action) != this->actions.end())
  {
    isHeld = this->actions[action].state.held;
  }

  return isHeld;
}

bool Input::actionReleased(std::string action)
{
  bool isReleased = false;

  // The action exists
  if(this->actions.find(action) != this->actions.end())
  {
    isReleased = this->actions[action].state.released;
  }

  return isReleased;
}
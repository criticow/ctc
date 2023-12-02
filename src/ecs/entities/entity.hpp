#pragma once

#include <core/engine.hpp>
#include <core/logger.hpp>
#include <entt/entt.hpp>

class Entity
{
  public:
  entt::entity handle;

  explicit Entity()
  {
    LOGGER_DEBUG("Entity created");
    this->handle = Engine::registry.create();
  };

  template<typename T, typename... Args>
  T *addComponent(Args&&... args)
  {
    return &Engine::registry.emplace_or_replace<T>(this->handle, std::forward<Args>(args)...);
  }

  template<typename T>
  bool hasComponent()
  {
    return Engine::registry.any_of<T>(this->handle);
  }

  template<typename T>
  T &getComponent()
  {
    return Engine::registry.get<T>(this->handle);
  }
};
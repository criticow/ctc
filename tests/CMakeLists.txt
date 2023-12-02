link_libraries(ctc)

set(SOURCES
  main.cpp
  game.cpp game.hpp
  player.cpp player.hpp
  enemy.cpp enemy.hpp
)
add_executable(main ${SOURCES})

set(DATA_DESTINATION ${CMAKE_BINARY_DIR}/tests/${CMAKE_BUILD_TYPE}/data)

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/data ${DATA_DESTINATION}
)

add_custom_target(
  copy_data_folder ALL
  DEPENDS ${DATA_DESTINATION}
)
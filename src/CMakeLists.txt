find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)
find_package(ftxui CONFIG)

add_library(game game_ui.cpp game_ui.hpp)
target_link_libraries(
  game
  PRIVATE project_options
          project_warnings
          fmt::fmt
          spdlog::spdlog
          ftxui::screen
          ftxui::dom
          ftxui::component)

target_include_directories(
  game
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} 
  PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

add_executable(galaxy main.cpp)
target_link_libraries(
  galaxy
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          game)

target_include_directories(galaxy PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

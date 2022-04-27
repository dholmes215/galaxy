find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)
find_package(ftxui CONFIG)

# Generic test that uses conan libs
add_executable(galaxy main.cpp)
target_link_libraries(
  galaxy
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog
          ftxui::screen
          ftxui::dom
          ftxui::component)

target_include_directories(galaxy PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

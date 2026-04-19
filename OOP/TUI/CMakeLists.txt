cmake_minimum_required(VERSION 3.11)
project(ftxui_menu)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)

add_executable(main main.cpp)
add_executable(baseScreen baseScreen.cpp)
add_executable(dashboard dashboard.cpp)
add_executable(signup signup.cpp)


target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

target_link_libraries(baseScreen
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

target_link_libraries(dashboard
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

target_link_libraries(signup
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

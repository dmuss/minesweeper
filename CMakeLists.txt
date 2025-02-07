cmake_minimum_required(VERSION 3.16)

project(minesweeper)

if (EMSCRIPTEN)
  set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)


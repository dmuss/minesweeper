cmake_minimum_required(VERSION 3.16)

project(minesweeper
        VERSION 1.0
        LANGUAGES CXX)

option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands." ON)

# Prevent in-source builds.
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
message(
    FATAL_ERROR
    "You may not build in the same location as source files. Please create a
    build subfolder and direct CMake to build in it.

    NOTE: CMake has created the file `CMakeCache.txt` and the directory
    `CMakeFiles/` in ${PROJECT_SOURCE_DIR}. You must delete these two items
    before CMake will build the project."
  )
endif()

# Update submodules, if needed.
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE "Check submodule during build." ON)
  if (GIT_SUBMODULE)
    message(STATUS "Updating submodules...")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if (NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(
        FATAL_ERROR
        "git submodule update --init --recusrive failed with ${GIT_SUBMOD_RESULT}, please check out submodules."
      )
    endif()
  endif()
endif()

# Ensure submodules exist.
if(NOT EXISTS
  "${PROJECT_SOURCE_DIR}/extern/SDL/CMakeLists.txt" OR
  "${PROJECT_SOURCE_DIR}/extern/SDL_image/CMakeLists.txt" OR
  "${PROJECT_SOURCE_DIR}/extern/SDL_ttf/CMakeLists.txt"
)
  message(
    FATAL_ERROR
    "Required submodules have not been downloaded. `GIT_SUBMODULE` is not enabled or has failed. Please update submodules and try again."
  )
endif()

if (EMSCRIPTEN)
  set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)

set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_GIF OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_LBM OFF)
set(SDLIMAGE_PCX OFF)
set(SDLIMAGE_PNG ON)
set(SDLIMAGE_PNM OFF)
set(SDLIMAGE_QOI OFF)
set(SDLIMAGE_SVG OFF)
set(SDLIMAGE_TGA OFF)
set(SDLIMAGE_TIFF OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_XCF OFF)
set(SDLIMAGE_XPM OFF)
set(SDLIMAGE_XV OFF)
add_subdirectory(extern/SDL_image EXCLUDE_FROM_ALL)


set(SDLTTF_VENDORED ON)
add_subdirectory(extern/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
  main.cpp
  game.cpp
  input/mouse_manager.cpp
  minefield/cell.cpp
  minefield/minefield.cpp
  scenes/game_scene.cpp
  scenes/menu_scene.cpp
  scenes/scene_manager.cpp
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wshadow -Wcast-align -Wunused
  -Wconversion -Wsign-conversion -pedantic -Wnon-virtual-dtor -Wold-style-cast
  -Woverloaded-virtual
)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image SDL3::SDL3)
# Web builds require preloading asset files by passing as linker options.
if(EMSCRIPTEN)
  target_link_libraries(${PROJECT_NAME} PRIVATE 
    "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/assets/spritesheet.png@/\""
    "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/assets/SILKSCREENFONT.TTF@/\""
  )
endif()


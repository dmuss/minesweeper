#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_pixels.h>
#pragma GCC diagnostic pop

namespace Colors {
constexpr SDL_Color Black{.r = 0, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};
constexpr SDL_Color White{.r = 255, .g = 255, .b = 255, .a = SDL_ALPHA_OPAQUE};
constexpr SDL_Color Gray{.r = 175, .g = 175, .b = 175, .a = SDL_ALPHA_OPAQUE};
constexpr SDL_Color Yellow{.r = 230, .g = 194, .b = 47, .a = SDL_ALPHA_OPAQUE};
constexpr SDL_Color Orange{.r = 226, .g = 107, .b = 53, .a = SDL_ALPHA_OPAQUE};
constexpr SDL_Color Green{.r = 154, .g = 255, .b = 82, .a = SDL_ALPHA_OPAQUE};
};  // namespace Colors

#endif

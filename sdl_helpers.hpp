#ifndef SDL_HELPERS_HPP_
#define SDL_HELPERS_HPP_

#include <memory>
#include <utility>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class SDL3 {
  /// Create and return a unique pointer to an SDL resource that will destroy
  /// itself when appropriate.
  ///
  /// If resource creation fails, application will exit while logging an error
  /// message.
  ///
  /// \param create The creation function for the requested resource.
  /// \param destroy The destruction function for the requested resource.
  /// \param args Arguments to be forwarded to the creation function.
  ///
  /// \return A unique pointer to the requested resource that appropriately
  /// calls the destruction function.
  template <typename CreateFunc, typename DestroyFunc, typename... Args>
  auto static getSDLResource_(CreateFunc create, DestroyFunc destroy,
                              Args&&... args) {
    auto res = create(std::forward<Args>(args)...);

    if (!res) {
      SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL error! %s", SDL_GetError());
      std::exit(EXIT_FAILURE);
    }

    return std::unique_ptr<std::decay_t<decltype(*res)>, decltype(destroy)>(
        res, destroy);
  }

 public:
  using WindowUPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  using RendererUPtr =
      std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
  using SurfaceUPtr =
      std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;
  using TextureUPtr =
      std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
  using FontUPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

  inline static WindowUPtr CreateWindow(const char* title, int w, int h,
                                        SDL_WindowFlags flags) {
    return getSDLResource_(SDL_CreateWindow, SDL_DestroyWindow, title, w, h,
                           flags);
  }

  inline static RendererUPtr CreateRenderer(SDL_Window* window,
                                            const char* name) {
    return getSDLResource_(SDL_CreateRenderer, SDL_DestroyRenderer, window,
                           name);
  }

  inline static SurfaceUPtr CreateBlendedTextSurface(TTF_Font* font,
                                                     const char* str,
                                                     size_t length,
                                                     SDL_Color color) {
    return getSDLResource_(TTF_RenderText_Blended, SDL_DestroySurface, font,
                           str, length, color);
  }

  inline static TextureUPtr CreateTextureFromImage(SDL_Renderer* renderer,
                                                   const char* filename) {
    return getSDLResource_(IMG_LoadTexture, SDL_DestroyTexture, renderer,
                           filename);
  }

  inline static TextureUPtr CreateTextureFromSurface(SDL_Renderer* renderer,
                                                     SDL_Surface* surface) {
    return getSDLResource_(SDL_CreateTextureFromSurface, SDL_DestroyTexture,
                           renderer, surface);
  }

  inline static FontUPtr CreateFont(const std::string& filePath, float ptSize) {
    return getSDLResource_(TTF_OpenFont, TTF_CloseFont, filePath.c_str(),
                           ptSize);
  }
};

struct SDLPointHash {
  size_t operator()(const SDL_Point point) const {
    return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
  }
};

constexpr bool operator==(const SDL_Point& first, const SDL_Point& second) {
  return (first.x == second.x) && (first.y == second.y);
}

#endif

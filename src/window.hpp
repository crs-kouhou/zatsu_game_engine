#pragma once

#include <string>
#include <optional>
#include <SDL3/SDL.h>

namespace zatsu_ge::window {
	struct Window final {
		SDL_Window * window_p;

		static auto make(const std::string title, const std::pair<int, int> size, const SDL_WindowFlags flag) -> std::optional<Window> {
			if(const auto window_p = SDL_CreateWindow(title.c_str(), size.second, size.first, flag)) {
				return std::make_optional<Window>(window_p);
			}
			else {
				return std::nullopt;
			}
		}
	};
}
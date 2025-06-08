#pragma once

#include <optional>
#include <SDL3/SDL.h>

#include "window.hpp"

namespace zatsu_ge::renderer {
	struct Renderer final {
		SDL_Renderer * renderer_p;

		static auto make(window::Window windw) -> std::optional<Renderer> {
			if(const auto renderer_p = SDL_CreateRenderer(windw.window_p, nullptr)) {
				return std::make_optional<Renderer>(renderer_p);
			}
			else {
				return std::nullopt;
			}
		}
	};
}
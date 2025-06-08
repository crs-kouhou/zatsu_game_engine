#pragma once

#include <optional>
#include <SDL3/SDL.h>

#include "window.hpp"

namespace zatsu_ge::renderer {
	struct Renderer final {
		SDL_Renderer * renderer_p;

		static auto make(const window::Window& windw) -> std::optional<Renderer> {
			if(const auto renderer_p = SDL_CreateRenderer(windw.window_p, nullptr)) {
				return std::make_optional<Renderer>(renderer_p);
			}
			else {
				return std::nullopt;
			}
		}

		Renderer(SDL_Renderer *const renderer_p)
		: renderer_p{renderer_p}
		{}

		Renderer(const Renderer&) = delete;
		auto operator=(const Renderer&) -> Renderer& = delete;

		Renderer(Renderer&& rhs)
		: renderer_p{rhs.renderer_p}
		{
			rhs.renderer_p = nullptr;
		}

		auto operator=(Renderer&& rhs) -> Renderer& {
			if(this->renderer_p) {
				SDL_DestroyRenderer(this->renderer_p);
			}
			this->renderer_p = rhs.renderer_p;
			rhs.renderer_p = nullptr;
			return *this;
		}

		~Renderer() {
			if(this->renderer_p) {
				SDL_DestroyRenderer(this->renderer_p);
			}
		}
	};
}
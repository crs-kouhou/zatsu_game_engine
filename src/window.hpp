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

		Window(SDL_Window * window_p)
		: window_p{window_p}
		{}


		Window(const Window& rhs) = delete;
		auto operator=(const Window& rhs) -> Window& = delete;

		Window(Window&& rhs)
		: window_p{rhs.window_p}
		{
			rhs.window_p = nullptr;
		}

		auto operator=(Window&& rhs) -> Window& {
			if(this->window_p != nullptr) {
				SDL_DestroyWindow(this->window_p);
			}
			this->window_p = rhs.window_p;
			rhs.window_p = nullptr;
			return *this;
		}

		~Window() {
			if(this->window_p != nullptr) {
				SDL_DestroyWindow(this->window_p);
			}
		}
	};

	struct SomethingHasWindow final {
		Window widw;

		SomethingHasWindow(const SomethingHasWindow&) = delete;
		auto operator=(const SomethingHasWindow&) -> SomethingHasWindow& = delete;
		SomethingHasWindow(SomethingHasWindow&&) = default;
		auto operator=(SomethingHasWindow&&) -> SomethingHasWindow& = default;
	};
}
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_CreateWindowAndRenderer("Hello SDL3(TODO)", 800, 640, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_Texture * todo_image = IMG_LoadTexture(renderer, "data/todo.png");
	SDL_Event e{};
	while(true) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) goto end;
		}


		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, todo_image, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	end:

	SDL_DestroyTexture(todo_image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
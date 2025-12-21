//Using SDL, standard IO, and strings
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	bool running = true;
	SDL_Event event;

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.x = 0;
	rect.y = 0;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: {
				running = false;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT: {
					cout << "left button pressed" << endl;
					break;
				}
				case SDL_BUTTON_RIGHT: {
					cout << "right button pressed" << endl;
					break;
				}
				default:
					break;
				}
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT: {
					cout << "left button released" << endl;
					break;
				}
				case SDL_BUTTON_RIGHT: {
					cout << "right button released" << endl;
					break;
				}
				default:
					break;
				}
				break;
			}
			case SDL_MOUSEMOTION: {
				cout << "Mouse position: " << event.motion.x << ", " << event.motion.y << endl;
				break;
			}
			case SDL_KEYDOWN: {
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W: {
					cout << "W pressed" << endl;
					rect.y -= 1;
					break;

				}
				case SDL_SCANCODE_A: {
					cout << "A pressed" << endl;
					rect.x -= 1;
					break;
				}
				case SDL_SCANCODE_S: {
					cout << "S pressed" << endl;
					rect.y += 1;
					break;
				}
				case SDL_SCANCODE_D: {
					cout << "D pressed" << endl;
					rect.x += 1;
					break;
				}
				default:
					break;
				}
				break;
			}
			case SDL_KEYUP: {
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W: {
					cout << "W released" << endl;
					break;
				}
				case SDL_SCANCODE_A: {
					cout << "A released" << endl;
					break;
				}
				case SDL_SCANCODE_S: {
					cout << "S released" << endl;
					break;
				}
				case SDL_SCANCODE_D: {
					cout << "D released" << endl;
					break;
				}
				default:
					break;
				}
			}
			default:
				break;
			}
			break;
		}
		
		//Отрисовываем фон
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);



		//Делаем делэй для 60fps 
		//TODO+ в идеале разобраться как делать так, чтобы если кадр считается скажем миллисекунду, то делэй уже 15. или вообще по другому как то делать
		SDL_Delay(16);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 1;
}

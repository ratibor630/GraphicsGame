#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int RESOLUTION_WIDTH = 800;
	const int RESOLUTION_HEIGHT = 800;
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	bool running = true;
	const int PLAYER_WALKING_SPRITE_COUNT = 29;
	const int ANIMATION_SPEED = 32;
	int playerSpriteCountCurrent = 0;
	SDL_Event event;

	SDL_Texture* playerWalkingTexture = IMG_LoadTexture(renderer, "resources/images/player/walking_middle.png");
	SDL_Rect playerWalkingSrc = { 0, 0, 400, 400 };
	SDL_Rect playerWalkingDest = { 0, 0, 400, 400 };

	Uint32 lastUpdate = SDL_GetTicks();

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
					break;

				}
				case SDL_SCANCODE_A: {
					cout << "A pressed" << endl;
					break;
				}
				case SDL_SCANCODE_S: {
					cout << "S pressed" << endl;
					break;
				}
				case SDL_SCANCODE_D: {
					cout << "D pressed" << endl;
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
		SDL_SetRenderDrawColor(renderer, 225, 255, 255, 255);
		SDL_RenderClear(renderer);

		Uint32 currentTicks = SDL_GetTicks();
		if (currentTicks - lastUpdate >= ANIMATION_SPEED) {
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
			lastUpdate = currentTicks;
		}

		SDL_RenderCopy(renderer, playerWalkingTexture, &playerWalkingSrc, &playerWalkingDest);

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

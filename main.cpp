#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	//Инициилизируем модули видео и картинок
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	//Создаем окно и рендерер
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//создаем переменные
	const int RESOLUTION_WIDTH = 800;
	const int RESOLUTION_HEIGHT = 800;
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	const int FPS = 60;
	int debug = 0;

	bool running = true;

	SDL_Event event;
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	//Инициализация необходимых переменных для главного персонажа
	const int PLAYER_WALKING_SPRITE_COUNT = 29;
	int playerSpriteCountCurrent = 0;
	int playerLastDirection = 0;
	SDL_Texture* playerWalkingTexture = IMG_LoadTexture(renderer, "resources/images/player/walking_middle.png");
	SDL_Rect playerWalkingSrc = { 0, 0, 400, 400 };
	SDL_Rect playerWalkingDest = { 0, 0, 400, 400 };

	//Запускаем счетчик тиков
	Uint32 lastUpdate = SDL_GetTicks();
	// вот эту парашу уебать, сделать нормально


	//////////////////////////////////////////
	// Основной цикл программы
	//////////////////////////////////////////
	while (running)
	{
		Uint32 framePreparing = SDL_GetTicks();
		Uint32 currentTicks = SDL_GetTicks();




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
					if (debug > 0) {
						cout << "left button pressed" << endl;
					}
					break;
				}
				case SDL_BUTTON_RIGHT: {
					if (debug > 0) {
						cout << "right button pressed" << endl;
					}
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
					if (debug > 0) {
						cout << "left button released" << endl;
					}
					break;
				}
				case SDL_BUTTON_RIGHT: {
					if (debug > 0) {
						cout << "right button released" << endl;
					}
					break;
				}
				default:
					break;
				}
				break;
			}
			case SDL_MOUSEMOTION: {
				if (debug > 0) {
					cout << "Mouse position: " << event.motion.x << ", " << event.motion.y << endl;
				}
				break;
			}
			case SDL_KEYDOWN: {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_F2: {
					debug = (debug + 1) % 2;
					break;
				}
				default:
					break;
				}
			default:
				break;
			}
			break;
			}
		}


		//Движение игрока на WASD
		if (keyboardState[SDL_SCANCODE_W]) {
			if (debug > 0) {
				cout << "W pressed" << endl;
			}
			playerWalkingSrc.y = 400;
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
		}
		if (keyboardState[SDL_SCANCODE_S]) {
			if (debug > 0) {
				cout << "S pressed" << endl;
			}
			playerWalkingSrc.y = 0;
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
		}
		if (keyboardState[SDL_SCANCODE_A]) {
			if (debug > 0) {
				cout << "A pressed" << endl;
			}
			playerWalkingSrc.y = 800;
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
		}
		if (keyboardState[SDL_SCANCODE_D]) {
			if (debug > 0) {
				cout << "D pressed" << endl;
			}
			playerWalkingSrc.y = 1200;
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
		}


		//Отрисовываем фон
		SDL_SetRenderDrawColor(renderer, 225, 255, 255, 255);
		SDL_RenderClear(renderer);



		//Отрисовываем персонажа
		SDL_RenderCopy(renderer, playerWalkingTexture, &playerWalkingSrc, &playerWalkingDest);

		SDL_RenderPresent(renderer);


		Uint32 frameShown = SDL_GetTicks();

		// ожидание ровно необходимого времени до следующего кадра
		SDL_Delay((1000 / FPS) - (framePreparing - frameShown));
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 1;
}



// TODO в идеале убрать окно дебага до вызова дебага
// TODO завершать анимацию ходьбы и ждать следующей команды
// TODO сделать защиту от отрицательного SDL_Delay
// TODO разделить логику и отрисовку кадров на 2 независимых потока чтобы игра не зависела от количества fps
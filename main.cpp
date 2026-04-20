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

	bool running = true;
	const int ANIMATION_SPEED = 32;
	// че за animation speed нахуй?

	SDL_Event event;

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
		///////////////////////
		//Движок анимации
		///////////////////////






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
					playerWalkingSrc.y = 400;
					playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
					playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
					break;

				}
				case SDL_SCANCODE_A: {
					cout << "A pressed" << endl;
					playerWalkingSrc.y = 800;
					playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
					playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
					break;
				}
				case SDL_SCANCODE_S: {
					cout << "S pressed" << endl;
					playerWalkingSrc.y = 0;
					playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
					playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
					break;
				}
				case SDL_SCANCODE_D: {
					cout << "D pressed" << endl;
					playerWalkingSrc.y = 1200;
					playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
					playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
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

// TODO сделать подготовку следующего кадра заранее, хуй знает как 
// TODO завершать анимацию ходьбы и ждать следующей команды
// TODO решить надо ли запоминать очередь команд
// TODO при зажатии кнопки надо реализовать плавную анимацию
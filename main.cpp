#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {

	//Инициилизируем модули видео, картинок и шрифтов
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

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

	//Инициализация переменных для хранения состояний клавиатуры
	bool keyboardKeyPressedW;
	bool keyboardKeyPressedS;
	bool keyboardKeyPressedA;
	bool keyboardKeyPressedD;

	//Инициализация необходимых переменных для главного персонажа
	const int PLAYER_WALKING_SPRITE_COUNT = 29;
	int playerSpriteCountCurrent = 0;
	int playerLastDirection = 0;
	SDL_Texture* playerWalkingTexture = IMG_LoadTexture(renderer, "resources/images/player/walking_middle.png");
	SDL_Rect playerWalkingSrc = { 0, 0, 400, 400 };
	SDL_Rect playerWalkingDest = { 0, 0, 400, 400 };

	//Отрисовываем курсор
	SDL_Surface* surfaceCursor = IMG_Load("resources/images/cursor.png");
	SDL_Cursor* cursor = SDL_CreateColorCursor(surfaceCursor, 0, 0);
	SDL_SetCursor(cursor);
	SDL_FreeSurface(surfaceCursor);

	// Создаем текстовое поле
	TTF_Font* fontMontserrat_Black = TTF_OpenFont("resources/fonts/Montserrat/Montserrat-Black.ttf", 24);
	SDL_Color fontColor = { 0,0,0,255 };
	SDL_Surface* fontSurface = TTF_RenderText_Solid(fontMontserrat_Black, "Press F2 to debug", fontColor);

	SDL_Texture* fontTex = SDL_CreateTextureFromSurface(renderer, fontSurface);
	int fontW, fontH;
	SDL_QueryTexture(fontTex, NULL, NULL, &fontW, &fontH);
	SDL_Rect fontRect = { 550, 0, fontW, fontH };
	


	//////////////////////////////////////////
	// Основной цикл программы
	//////////////////////////////////////////
	while (running)
	{
		// запускаем счетчик тиков
		Uint32 framePreparing = SDL_GetTicks();
		Uint32 currentTicks = SDL_GetTicks();

		// дебаггер
		if (debug) {
			if (AllocConsole()) {

				FILE* dummy;
				_wfreopen_s(&dummy, L"CONOUT$", L"w", stdout);
				_wfreopen_s(&dummy, L"CONOUT$", L"w", stderr);
			}
		}

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
			//Обновляем статусы клавиатуры
			case SDL_KEYDOWN: {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_F2: {
					debug = (debug + 1) % 2;
					break;
				}
				case SDL_SCANCODE_W: {
					if (debug > 0) {
						cout << "W pressed" << endl;
					}
					keyboardKeyPressedW = true;
					playerLastDirection = 400;
					break;
				}
				case SDL_SCANCODE_S: {
					if (debug > 0) {
						cout << "S pressed" << endl;
					}
					keyboardKeyPressedS = true;
					playerLastDirection = 0;
					break;
				}
				case SDL_SCANCODE_A: {
					if (debug > 0) {
						cout << "A pressed" << endl;
					}
					keyboardKeyPressedA = true;
					playerLastDirection = 800;
					break;
				}
				case SDL_SCANCODE_D: {
					if (debug > 0) {
						cout << "D pressed" << endl;
					}
					keyboardKeyPressedD = true;
					playerLastDirection = 1200;
					break;
				}
				default:
					break;
				}
			}
			case SDL_KEYUP: {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W: {
					if (debug > 0) {
						cout << "W released" << endl;
					}
					keyboardKeyPressedW = false;
					break;
				}
				case SDL_SCANCODE_S: {
					if (debug > 0) {
						cout << "S released" << endl;
					}
					keyboardKeyPressedS = false;
					break;
				}
				case SDL_SCANCODE_A: {
					if (debug > 0) {
						cout << "A released" << endl;
					}
					keyboardKeyPressedA = false;
					break;
				}
				case SDL_SCANCODE_D: {
					if (debug > 0) {
						cout << "D released" << endl;
					}
					keyboardKeyPressedD = false;
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


		playerWalkingSrc.y = playerLastDirection;


		//Движение игрока на WASD
		if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_D]) {
			
			playerSpriteCountCurrent = (playerSpriteCountCurrent + 1) % PLAYER_WALKING_SPRITE_COUNT;
			playerWalkingSrc.x = playerWalkingSrc.w * playerSpriteCountCurrent;
		}
		


		//Отрисовываем фон
		SDL_SetRenderDrawColor(renderer, 225, 255, 255, 255);
		SDL_RenderClear(renderer);



		//Отрисовываем персонажа
		SDL_RenderCopy(renderer, playerWalkingTexture, &playerWalkingSrc, &playerWalkingDest);

		//Отрисовываем текст
		SDL_RenderCopy(renderer, fontTex, NULL, &fontRect);


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
// TODO сделать чтобы последняя нажатая клавиша была направлением ходьбы
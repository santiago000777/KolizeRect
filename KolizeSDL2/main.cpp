#include "common.h"
#include "SDL.h"

/*
	1. "Solution Platforms" -> x64
*/

//#define PressedKey(s)	GetAsyncKeyState(toupper(s) )

//#define PressedKey(s) ((GetAsyncKeyState(s) & 0x80000000) ? 1 : 0)
//bool PressedKey(int Key) {
//
///*	short i;
//	i = GetAsyncKeyState(Key);
//	if ((i & (short)0x8000) != 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//	i++;*/
//	return 0;
//}
#define FPS		165

#define BREAK	__debugbreak

#define ISDEBUG		1

enum class eBodKolize : int {
	NONE = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

bool PressedKey(short key) {
	short i = GetAsyncKeyState(toupper(key));
	if ((i & 0x8000) == 0) {
		return false;
	}
	return true;
}


struct TPosition {
public:
	int x, y;

	TPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	TPosition operator+(const TPosition& p) const {
		return { this->x + p.x, this->y + p.y };
	}

	TPosition operator-(const TPosition& p) const {
		return { this->x - p.x, this->y - p.y };
	}
};

/*Funkcni pro mensi
if (rect1->y + rect1->h >= rect2->y && rect1->y <= rect2->y + rect2->h) {
		if (rect1->x + rect1->w >= rect2->x && rect1->x < rect2->x) {
			std::cout << "Right\n";
		}
		if (rect1->x <= rect2->x + rect2->w && rect1->x + rect1->w > rect2->x + rect2->w) {
			std::cout << "Left\n";
		}
	}
	if (rect1->x + rect1->w >= rect2->x && rect1->x <= rect2->x + rect2->w) {
		if (rect1->y + rect1->h >= rect2->y && rect1->y < rect2->y) {
			std::cout << "Down\n";
		}
		if (rect1->y <= rect2->y + rect2->h && rect1->y + rect1->h > rect2->y + rect2->h) {
			std::cout << "Up\n";
		}
	}*/

eBodKolize MistoKolize(SDL_Rect rect1, SDL_Rect rect2) {

	if (rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w
		&& rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h) {

		if (abs(rect1.y - (rect2.y + rect2.h)) < abs((rect1.y + rect1.h) - rect2.y)) {

			if (abs(rect1.y - (rect2.y + rect2.h)) < abs(rect1.x - (rect2.x + rect2.w))
				&& abs(rect1.y - (rect2.y + rect2.h)) < abs((rect1.x + rect1.w) - rect2.x)) {
				std::cout << "Up\n";
				return eBodKolize::UP;
			} else {
				if (abs(rect1.x - (rect2.x + rect2.w)) < abs((rect1.x + rect1.w) - rect2.x)) {
					std::cout << "Left\n";
					return eBodKolize::LEFT;
				} else {
					std::cout << "Right\n";
					return eBodKolize::RIGHT;
				}
			}
		} else {
			if (abs((rect1.y + rect1.h) - rect2.y) < abs(rect1.x - (rect2.x + rect2.w))
				&& abs((rect1.y + rect1.h) - rect2.y) < abs((rect1.x + rect1.w) - rect2.x)) {

				std::cout << "Down\n";
				return eBodKolize::DOWN;
			} else {
				if (abs(rect1.x - (rect2.x + rect2.w)) < abs((rect1.x + rect1.w) - rect2.x)) {
					std::cout << "Left\n";
					return eBodKolize::LEFT;
				} else {
					std::cout << "Right\n";
					return eBodKolize::RIGHT;
				}
			}
		}

		//std::cout << "Kolize!\n";
	} else {
		return eBodKolize::NONE;
	}

	/*if (rect1->y > rect2->y && rect1->y + rect1->h < rect2->y + rect2->h || rect1->y < rect2->y && rect1->y + rect1->h > rect2->y + rect2->h) {
		if (rect1->x + rect1->w >= rect2->x && rect1->x < rect2->x) {
			std::cout << "Right\n";
		}
		if (rect1->x <= rect2->x + rect2->w && rect1->x + rect1->w > rect2->x + rect2->w) {
			std::cout << "Left\n";
		}
	}
	if (rect1->x > rect2->x && rect1->x + rect1->w < rect2->x + rect2->w || rect1->x < rect2->x && rect1->x + rect1->w > rect2->x + rect2->w) {
		if (rect1->y + rect1->h >= rect2->y && rect1->y < rect2->y) {
			std::cout << "Down\n";
		}
		if (rect1->y <= rect2->y + rect2->h && rect1->y + rect1->h > rect2->y + rect2->h) {
			std::cout << "Up\n";
		}
	}*/
}
//if ((rect1->x + posun1->x + rect1->w > rect2->x && rect1->x + posun1->x < rect2->x + rect2->w)
	//	&& (rect1->y + posun1->y + rect1->h > rect2->y && rect1->y + posun1->y < rect2->y + rect2->h)) {

	//	if (/*posun1->x > 0 && */rect1->x + rect1->w + posun1->x >= rect2->x
	//		&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {
	//		std::cout << "RIGHT\n";
	//		/*posun1->x = rect2->x - (rect1->x + rect1->w) + posun2->x;
	//		rect1->x += posun1->x;

	//		return eBodKolize::RIGHT;*/
	//	}
	//	if (/*posun1->x < 0 && */rect1->x + posun1->x <= rect2->x + rect2->w
	//		&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {

	//		/*posun1->x = rect1->x - (rect2->x + rect2->w) - posun2->x;
	//		posun1->x *= -1;
	//		rect1->x += posun1->x;

	//		return eBodKolize::LEFT;*/
	//		std::cout << "LEFT\n";
	//	}
	//	if (/*posun1->y > 0 && */rect1->y + rect1->h + posun1->y >= rect2->y
	//		&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

	//		/*posun1->y = rect2->y - (rect1->y + rect1->h) + posun2->y;
	//		rect1->y += posun1->y;

	//		return eBodKolize::DOWN;*/
	//		std::cout << "DOWN\n";
	//	}
	//	if (/*posun1->y < 0 && */rect1->y + posun1->y <= rect2->y + rect2->h
	//		&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

	//		/*posun1->y = rect1->y - (rect2->y + rect2->h) - posun2->y;
	//		posun1->y *= -1;
	//		rect1->y += posun1->y;

	//		return eBodKolize::UP;*/
	//		std::cout << "UP\n";
	//	}
	//}
	//else
	//	return eBodKolize::NONE;

/*if ((rect1->x + posun1->x + rect1->w > rect2->x && rect1->x + posun1->x < rect2->x + rect2->w)
		&& (rect1->y + posun1->y + rect1->h > rect2->y && rect1->y + posun1->y < rect2->y + rect2->h)) {

		if (posun1->x > 0 && rect1->x + rect1->w + posun1->x >= rect2->x
			&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {

			posun1->x = rect2->x - (rect1->x + rect1->w) + posun2->x;
			rect1->x += posun1->x;

			return eBodKolize::RIGHT;
		}
		if (posun1->x < 0 && rect1->x + posun1->x <= rect2->x + rect2->w
			&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {

			posun1->x = rect1->x - (rect2->x + rect2->w) - posun2->x;
			posun1->x *= -1;
			rect1->x += posun1->x;

			return eBodKolize::LEFT;
		}
		if (posun1->y > 0 && rect1->y + rect1->h + posun1->y >= rect2->y
			&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

			posun1->y = rect2->y - (rect1->y + rect1->h) + posun2->y;
			rect1->y += posun1->y;

			return eBodKolize::DOWN;
		}
		if (posun1->y < 0 && rect1->y + posun1->y <= rect2->y + rect2->h
			&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

			posun1->y = rect1->y - (rect2->y + rect2->h) - posun2->y;
			posun1->y *= -1;
			rect1->y += posun1->y;

			return eBodKolize::UP;
		}
	}*/

void Posun(SDL_Rect* rect1, TPosition* posun1, SDL_Rect rect2, TPosition* posun2) {
	eBodKolize posledniKolize = MistoKolize({ rect1->x + posun1->x, rect1->y + posun1->y, rect1->w, rect1->h }, { rect2.x + posun2->x, rect2.y + posun2->y, rect2.w, rect2.h });
	//MistoKolize(rect1, posun1, rect2, posun2);	

	if (posledniKolize == eBodKolize::DOWN) {
		if (posun1->y < 0)
			rect1->y += posun1->y;
		rect1->x += posun1->x;
	}
	if (posledniKolize == eBodKolize::UP) {
		if (posun1->y > 0)
			rect1->y += posun1->y;
		rect1->x += posun1->x;
	}
	if (posledniKolize == eBodKolize::RIGHT) {
		if (posun1->x < 0)
			rect1->x += posun1->x;
		rect1->y += posun1->y;
	}
	if (posledniKolize == eBodKolize::LEFT) {
		if (posun1->x > 0)
			rect1->x += posun1->x;
		rect1->y += posun1->y;
	}
	if (posledniKolize == eBodKolize::NONE) {
		rect1->x += posun1->x;
		rect1->y += posun1->y;
	}
	/*rect1->x += posun1->x;
	rect1->y += posun1->y;*/
}
void Posun2(SDL_Rect* rect1, TPosition* posun1, SDL_Rect rect2) {

	rect1->x += posun1->x;
	rect1->y += posun1->y;
}


int main(int argc, char* args[]) {

	const float deltaTime = 1000.0f / FPS;
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	std::chrono::milliseconds duration;


	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	TPosition gravity(0, 1);

	SDL_Rect* rect1 = new SDL_Rect();
	rect1->x = 600;
	rect1->y = 500;
	rect1->w = 30;
	rect1->h = 40;
	TPosition vec1(0, 0);


	SDL_Rect* rect2 = new SDL_Rect();
	rect2->x = 230;
	rect2->y = 230;
	rect2->w = 80;
	rect2->h = 140;
	/*rect2->x = 10;
	rect2->y = 550;
	rect2->w = 700;
	rect2->h = 10;*/
	TPosition vec2(0, 0);

	SDL_Event* e = new SDL_Event();
	bool end = false;


	float velocity1 = 3.0f;
	//first = std::chrono::high_resolution_clock::now();
	while (!end) {
		if (PressedKey(VK_SPACE))
			__debugbreak();
		if (PressedKey(VK_ESCAPE))
			end = true;

		Sleep(deltaTime / 4);

		// Je stisknuta klavesa	
		vec1.x = 0;
		vec1.y = 0;

		vec2.x = 0;
		vec2.y = 0;

		/*if (PressedKey(VK_UP)) {
			vec1.y = -1;
		}
		if (PressedKey(VK_DOWN)) {
			vec1.y = 1;
		}
		if (PressedKey(VK_LEFT)) {
			vec1.x = -1;
		}
		if (PressedKey(VK_RIGHT)) {
			vec1.x = 1;
		}*/

		if (PressedKey(VK_UP)) {
			vec1.y = -3;
		}
		if (PressedKey(VK_DOWN)) {
			vec1.y = 3;
		}
		if (PressedKey(VK_LEFT)) {
			vec1.x = -3;
		}
		if (PressedKey(VK_RIGHT)) {
			vec1.x = 3;
		}
		//vec1 = vec1 + gravity;


		if (PressedKey('w')) {
			vec2.y = -1;
		}
		if (PressedKey('s')) {
			vec2.y = 1;
		}
		if (PressedKey('a')) {
			vec2.x = -1;
		}
		if (PressedKey('d')) {
			vec2.x = 1;
		}

		Posun(rect1, &vec1, *rect2, &vec2);
		Posun2(rect2, &vec2, *rect1);

		duration = std::chrono::duration_cast<std::chrono::milliseconds>(second - first);

		if (duration.count() >= deltaTime) {
			first = std::chrono::high_resolution_clock::now();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);



			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, rect1);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, rect2);
			SDL_RenderPresent(renderer);

		}
		second = std::chrono::high_resolution_clock::now();

	}

	return 0;
}

/*
git init -b <branch>
git remote add origin master
git remote -v

*/

//if ((rect1->x + posun1->x + rect1->w > rect2->x && rect1->x + posun1->x < rect2->x + rect2->w)
	//	&& (rect1->y + posun1->y + rect1->h > rect2->y && rect1->y + posun1->y < rect2->y + rect2->h)) {

	//	if (/*posun1->x > 0 && */rect1->x + rect1->w + posun1->x >= rect2->x
	//		&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {
	//		std::cout << "RIGHT\n";
	//		/*posun1->x = rect2->x - (rect1->x + rect1->w) + posun2->x;
	//		rect1->x += posun1->x;

	//		return eBodKolize::RIGHT;*/
	//	}
	//	if (/*posun1->x < 0 && */rect1->x + posun1->x <= rect2->x + rect2->w
	//		&& rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y) {

	//		/*posun1->x = rect1->x - (rect2->x + rect2->w) - posun2->x;
	//		posun1->x *= -1;
	//		rect1->x += posun1->x;

	//		return eBodKolize::LEFT;*/
	//		std::cout << "LEFT\n";
	//	}
	//	if (/*posun1->y > 0 && */rect1->y + rect1->h + posun1->y >= rect2->y
	//		&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

	//		/*posun1->y = rect2->y - (rect1->y + rect1->h) + posun2->y;
	//		rect1->y += posun1->y;

	//		return eBodKolize::DOWN;*/
	//		std::cout << "DOWN\n";
	//	}
	//	if (/*posun1->y < 0 && */rect1->y + posun1->y <= rect2->y + rect2->h
	//		&& rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x) {

	//		/*posun1->y = rect1->y - (rect2->y + rect2->h) - posun2->y;
	//		posun1->y *= -1;
	//		rect1->y += posun1->y;

	//		return eBodKolize::UP;*/
	//		std::cout << "UP\n";
	//	}
	//}
	//else
	//	return eBodKolize::NONE;
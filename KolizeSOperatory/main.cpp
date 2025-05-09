#include "common.h"
#include "SDL.h"


#define FPS		165
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

float Round(float number, float precision) {
	return round(number / precision) * precision;
}

struct Vec2f {
public:
	float x { 0.0f }, y { 0.0f };

	Vec2f() {}

	Vec2f(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vec2f operator+(const Vec2f& p) const {
		return { this->x + p.x, this->y + p.y };
	}

	void operator+=(const Vec2f& p) {
		this->x += p.x;
		this->y += p.y;
	}

	Vec2f operator-(const Vec2f& p) const {
		return { this->x - p.x, this->y - p.y };
	}

	bool operator==(const Vec2f& rhs) const {
		if (round(x) == round(rhs.x) && round(y) == round(rhs.y)) {
			return true;
		} else {
			return false;
		}
	}
};

struct Rect {
public:
	Vec2f pos { 0.0f, 0.0f };
	int w { 0 }, h { 0 };

	const SDL_Rect& Round() {
		return { (int)round(pos.x), (int)round(pos.y), w, h };
	}
};

struct HitPoint {

	HitPoint() {}
	bool value = 0;
	Vec2f position { 0.0f, 0.0f };

	bool operator==(const HitPoint& rhs) {
		if (value == rhs.value && roundf(position.x) == roundf(rhs.position.x) && roundf(position.y) == roundf(rhs.position.y)) {
			return true;
		} else {
			return false;
		}
	}
};

void Posun(Rect& rect, const Vec2f& dir, Vec2f& posun1, HitPoint* pArr1, int pocet1, double vecAngle1, int const angle1, eBodKolize& coll1, eBodKolize& previousColl,
		   Rect& rect2, Vec2f& posun2, HitPoint* pArr2, int pocet2, int const angle2,
		   SDL_Renderer* renderer) {
	
	if (coll1 == eBodKolize::NONE) {
		posun1 = dir;
	}
	double prepona;
	if (coll1 != eBodKolize::NONE && previousColl == eBodKolize::NONE && (dir.x != 0 || dir.y != 0)) {
		if (angle2 == 0.0) {
			posun1 = { 0.0f, 0.0f };
			return;
		}

		std::vector<Vec2f> hitPoints;

		for (int i = 0; i < pocet1; i++) {
			if (pArr1[i].value == 1) {
				hitPoints.emplace_back(pArr1[i].position);    // dotyku je vice za sebou nemuze zde byt   break;
				//break;
			}
		}

		Vec2f row1[4];
		row1[0] = pArr1[0].position;
		row1[1] = pArr1[rect.w].position;
		row1[2] = pArr1[(2 * rect.w) + (2 * rect.h) - 1].position;
		row1[3] = pArr1[(rect.w + rect.h * 2) - 1].position;

		Vec2f row2[4];
		row2[0] = pArr2[0].position;
		row2[1] = pArr2[rect2.w].position;
		row2[2] = pArr2[(2 * rect2.w) + (2 * rect2.h) - 1].position;
		row2[3] = pArr2[(rect2.w + rect2.h * 2) - 1].position;
		

		auto VypocetPrepony = [](Vec2f start, Vec2f end) {
			return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
		};


		int closestIndex = 0;
		Vec2f closestRow = row2[0];
		Vec2f hitPoint = hitPoints[0];

		for (int k = 0; k < hitPoints.size(); k++) {
			for (int i = 1; i < 4; i++) {
				if (abs(closestRow.x - hitPoint.x) + abs(closestRow.y - hitPoint.y) >
					abs(row2[i].x - hitPoints[k].x) + abs(row2[i].y - hitPoints[k].y)) {

					hitPoint = hitPoints[k];

					closestRow = row2[i];
					closestIndex = i;
				}
			}
		}

		/*bool condition = false;
		Vec2f currHitPointIndex;
		for (int i = 0; i < hitPoints.size(); i++) {
			if (closestRow == hitPoint) condition = true; currHitP = hitPoints[i];


		}*/

		Vec2f directionRow;
		if (closestRow == hitPoint) { // kolize v Collision je ale zde neni!!

			/// -?

			closestIndex = 0;
			closestRow = row1[0];
			for (int i = 1; i < 4; i++) {
				if (abs(closestRow.x - hitPoint.x) + abs(closestRow.y - hitPoint.y) >
					abs(row1[i].x - hitPoint.x) + abs(row1[i].y - hitPoint.y)) {
					closestRow = row1[i];
					closestIndex = i;
				}
			}

			/// - 

			for (int i = 0; i < 4; i++) {
				if (i == closestIndex || i == (closestIndex + 2) % 4) {
					continue;
				}

				if (round(VypocetPrepony(closestRow, hitPoint)) + round(VypocetPrepony(row1[i], hitPoint)) == round(VypocetPrepony(closestRow, row1[i]))) {
					directionRow = row1[i];
					break;
				}
			}
		}
		else {

			for (int i = 0; i < 4; i++) {
				if (i == closestIndex || i == (closestIndex + 2) % 4) {
					continue;
				}

				if (round(VypocetPrepony(closestRow, hitPoint)) + round(VypocetPrepony(row2[i], hitPoint)) == round(VypocetPrepony(closestRow, row2[i]))) {
					directionRow = row2[i];
					break;
				}
			}
		}

		
		/*if (closestRow == hitPoint) {

			for (int i = 0; i < 4; i++) {
				if (i == closestIndex || i == (closestIndex + 2) % 4) {
					continue;
				}

				if (round(VypocetPrepony(closestRow, hitPoint)) + round(VypocetPrepony(row1[i], hitPoint)) == round(VypocetPrepony(closestRow, row1[i]))) {
					directionRow = row1[i];
					break;
				}
			}

		} else {
			for (int i = 0; i < 4; i++) {
				if (i == closestIndex || i == (closestIndex + 2) % 4) {
					continue;
				}

				if (round(VypocetPrepony(closestRow, hitPoint)) + round(VypocetPrepony(row2[i], hitPoint)) == round(VypocetPrepony(closestRow, row2[i]))) {
					directionRow = row2[i];
					break;
				}
			}
		}*/
		
		Vec2f unitVec;
		prepona = VypocetPrepony(directionRow, hitPoint);
		unitVec = { (directionRow.x - hitPoint.x) / (float)prepona, (directionRow.y - hitPoint.y) / (float)prepona };
		std::cout << "vypocet\n";

		
		SDL_Rect pom1 = { hitPoint.x, hitPoint.y, 15, 15 };  // blue
		SDL_Rect pom2 = { directionRow.x, directionRow.y, 15, 15 }; // yellow
		SDL_Rect pom3 = { closestRow.x, closestRow.y, 15, 15 };  // pink

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &pom1);

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &pom2);

		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderFillRect(renderer, &pom3);

		


		SDL_RenderPresent(renderer);
		SDL_Delay(100);

		switch (coll1) {
			case eBodKolize::LEFT: {
				if (unitVec.x > 0) {
					unitVec.x *= -1;
				}
				/*if (closestRow.x > hitPoint.x) {
					unitVec.y *= -1;
				}*/
				if (closestRow.x < hitPoint.x) {
					unitVec.y *= -1;
				}
				break;
			}
			case eBodKolize::RIGHT: {
				if (unitVec.x < 0) {
					unitVec.x *= -1;
				}
				/*if (closestRow.x < hitPoint.x) {
					unitVec.y *= -1;
				}*/
				if (closestRow.x > hitPoint.x) {
					unitVec.y *= -1;
				}
				break;
			}
			case eBodKolize::UP: {
				if (unitVec.y > 0) {
					unitVec.y *= -1;
				}
				/*if (closestRow.y > hitPoint.y) {
					unitVec.x *= -1;
				}*/
				if (closestRow.y < hitPoint.y) {
					unitVec.x *= -1;
				}
				break;
			}
			case eBodKolize::DOWN: {
				if (unitVec.y < 0) {
					unitVec.y *= -1;
				}
				/*if (closestRow.y < hitPoint.y) {
					unitVec.x *= -1;
				}*/
				if (closestRow.y > hitPoint.y) {
					unitVec.x *= -1;
				}
				break;
			}
		}

		posun1 = unitVec;
		std::cout << "x: " << posun1.x << ", y: " << posun1.y << std::endl;
		
	}

	Vec2f center { rect.w / 2.0f, rect.h / 2.0f };
	center += rect.pos;

	
	rect.pos.x += posun1.x;
	rect.pos.y += posun1.y;
	
	
	double addedRadians = (vecAngle1 * PI) / 180;
	double radians;
	float deltaX, deltaY;

	for (int i = 0; i < pocet1; i++) {
		
		deltaX = pArr1[i].position.x - center.x;
		deltaY = pArr1[i].position.y - center.y;
		prepona = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));

		radians = std::atanf((float)deltaY / deltaX);
		
		if (deltaX < 0 && deltaY >= 0) {
			radians += PI;
		}
		else if (deltaX < 0 && deltaY < 0) {
			radians += PI;
		}
		if (deltaX > 0 && deltaY < 0) {
			radians += 2 * PI;
		}
		
		deltaX = prepona * std::cos(radians + addedRadians);
		deltaY = prepona * std::sin(radians + addedRadians);

		radians = 0.0;

		pArr1[i].position.x = (deltaX + center.x) + posun1.x;
		pArr1[i].position.y = (deltaY + center.y) + posun1.y;
		
		
	}
}

void Collision(HitPoint* pArr1, int pocet1, const Vec2f& dir1, eBodKolize& coll1, eBodKolize& previousColl1, const Vec2f& vec1,
			   HitPoint* pArr2, int pocet2, const Vec2f& dir2) {

	previousColl1 = coll1;
	coll1 = eBodKolize::NONE;

	for (int k = 0; k < pocet1; k++) {
		for (int i = 0; i < pocet2; i++) {
			if (round(pArr2[i].position.x) == round(pArr1[k].position.x)
			&& round(pArr2[i].position.y) == round(pArr1[k].position.y)) {

				if (dir1.x > 0 || dir2.x < 0) {
					coll1 = eBodKolize::RIGHT;
				}
				if (dir1.x < 0 || dir2.x > 0) {
					coll1 = eBodKolize::LEFT;
				}
				if (dir1.y > 0 || dir2.y < 0) {
					coll1 = eBodKolize::DOWN;
				}
				if (dir1.y < 0 || dir2.y > 0) {
					coll1 = eBodKolize::UP;
				}

				pArr1[k].value = 1;
				break;

			} else {
				pArr1[k].value = 0;
			}
		}
	}
	
	/*switch (coll1) {
		case eBodKolize::LEFT: {
			std::cout << "Kolize LEFT\n";
			break;
		}
		case eBodKolize::RIGHT: {
			std::cout << "Kolize RIGHT\n";
			break;
		}
		case eBodKolize::UP: {
			std::cout << "Kolize UP\n";
			break;
		}
		case eBodKolize::DOWN: {
			std::cout << "Kolize DOWN\n";
			break;
		}
		default: {
			std::cout << "Porad NONE!\n";
			break;
		}
	}*/
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

	Vec2f gravity(0, 1);

	Rect rect1 = { {500.0f, 270.0f/*300.0f*/}, 30, 40 };
	Vec2f vec1(0, 0), dir1 {0, 0};
	HitPoint collisionBox1[140];

	int p = 0;
	for (int k = 0; k <= 40; k++) {
		for (int i = 0; i <= 30; i++) {
			if (k == 0 || i == 0 || k == 40 || i == 30) {
				collisionBox1[p].value = 0;
				collisionBox1[p].position = { rect1.pos.x + i, rect1.pos.y + k };
				p++;
			}
		}
	}

	eBodKolize coll1 = eBodKolize::NONE;
	eBodKolize previousColl1 = eBodKolize::NONE;

	eBodKolize coll2 = eBodKolize::NONE;
	eBodKolize previousColl2 = eBodKolize::NONE;

	
	Rect rect2 = { { 230.0f, 230.0f}, 80, 140 };
	
	Vec2f vec2(0, 0), dir2 { 0, 0 };
	HitPoint collisionBox2[440];

	SDL_Point point1;
	point1.x = rect1.w / 2;
	point1.y = rect1.h / 2;

	p = 0;
	for (int k = 0; k <= 140; k++) {
		for (int i = 0; i <= 80; i++) {
			
			if (k == 0 || i == 0 || k == 140 || i == 80) {
				collisionBox2[p].value = 0;
				collisionBox2[p].position = { rect2.pos.x + i, rect2.pos.y + k };
				
				p++;
			}
		}
	}

	SDL_Event* e = new SDL_Event();
	bool end = false;


	SDL_Surface* surface = SDL_LoadBMP("paddle.bmp");

	SDL_Texture* picture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect srcBox = { 0, 0, surface->w, surface->h };
	SDL_FreeSurface(surface);

	SDL_Point point2;
	point2.x = rect2.w / 2;
	point2.y = rect2.h / 2;

	SDL_RendererFlip flip = SDL_FLIP_NONE;


	float velocity1 = 3.0f;

	int angle1 = 345;
	double vecAngle1 = 345.0;

	double vecAngle2 = 45.0;
	int angle2 = 45;
	

	while (!end) {
		if (PressedKey(VK_SPACE))
			__debugbreak();
		if (PressedKey(VK_ESCAPE))
			end = true;
		if (PressedKey(VK_BACK)) {
			system("cls");
		}
		Sleep(deltaTime / 4);

		// Je stisknuta klavesa
		/*vec1.x = 0;
		vec1.y = 0;

		vec2.x = 0;
		vec2.y = 0;*/
		dir1.x = 0;
		dir1.y = 0;

		dir2.x = 0;
		dir2.y = 0;


		if (PressedKey(VK_UP)) {
			dir1.y = -1;
		}
		if (PressedKey(VK_DOWN)) {
			dir1.y = 1;
		}
		if (PressedKey(VK_LEFT)) {
			dir1.x = -1;
		}
		if (PressedKey(VK_RIGHT)) {
			dir1.x = 1;
		}

		//dir1.x = -1;

		if (PressedKey('q')) {
			vecAngle1 = 5;
			angle1 += vecAngle1;
			angle1 %= 360;
		}

		int i;

		if (PressedKey('w')) {
			dir2.y = -1;
		}
		if (PressedKey('s')) {
			dir2.y = 1;
		}
		if (PressedKey('a')) {
			dir2.x = -1;
		}
		if (PressedKey('d')) {
			dir2.x = 1;
		}
		if (PressedKey('r')) {
			vecAngle2 = 5;
			angle2 += vecAngle2;
			angle2 %= 360;
		}
		
		
		Collision(collisionBox1, 140, dir1, coll1, previousColl1, vec1, collisionBox2, 440, dir2);
		Posun(rect1, dir1, vec1, collisionBox1, 140, vecAngle1, angle1, coll1, previousColl1, rect2, vec2, collisionBox2, 440, angle2, renderer);
		
		
		Collision(collisionBox2, 440, dir2, coll2, previousColl2, vec2, collisionBox1, 140, dir1);
		Posun(rect2, dir2, vec2, collisionBox2, 440, vecAngle2, angle2, coll2, previousColl2, rect1, vec1, collisionBox1, 140, angle1, renderer);

		vecAngle1 = 0.0;
		vecAngle2 = 0.0;

		duration = std::chrono::duration_cast<std::chrono::milliseconds>(second - first);

		if (duration.count() >= deltaTime) {
			first = std::chrono::high_resolution_clock::now();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);

			SDL_RenderCopyEx(renderer, picture, &srcBox, &rect1.Round(), angle1, &point1, flip);
			SDL_RenderCopyEx(renderer, picture, &srcBox, &rect2.Round(), angle2, &point2, flip);

			SDL_RenderPresent(renderer);
		}
		second = std::chrono::high_resolution_clock::now();

	}

	return 0;
}

/*
git init
git status
git add
git commit -m <msg>
git branch -M <branch>
git remote add origin <pathFromGitHub>
git remote -v
git push origin <branch>
*/
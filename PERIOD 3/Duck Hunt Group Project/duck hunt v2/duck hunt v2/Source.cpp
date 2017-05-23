#include <fstream>
#include <vector>
#include <string>
#include<iostream>
#include <array>
#include<winbgi.cpp>
#include<graphics.h>
#include<ctime>
#include<Windows.h>
#include"Resource.h"
#include"Virtual Keys.h"
using namespace std;
POINT t;
fstream High_Scores_Easy, High_Scores_Medium, High_Scores_Hard, High_Scores_Insane;
fstream Scores_Easy, Scores_Medium, Scores_Hard, Scores_Insane;
string name;
int score ;
int whileloop;
int difficulty;
int maxX, maxY;
int GrDriver, GrMode, ErrorCode;
int top3[2];
void duckRight(int x, int y);
void duckLeft(int x, int y);
int xbig, ybig, rbig, xlil, ylil, rlil, xloop, yloop, rloop;
int ducknum;
int maxduck;
bool checkHit = false;
bool mouse1press = false;
bool mousePress(int);
enum DIRECTION{LEFTCLICK};

void crossHair(int x, int y) {
	int Lh = crosshairnancy_Height;
	int Lw = crosshairnancy_Width;
	for (int i = 0; i < Lw; i++) {
		for (int j = 0; j < Lh; j++) {
			if (crosshairnancy_ARRY[j][i] != 1)
				putpixel(x + i - 12, y + j - 32, crosshairnancy_ARRY[j][i]);
		}
	}
}

void duckhuntstage(int x, int y) {
	int Lh = duck_hunt_stage_Height;
	int Lw = duck_hunt_stage_Width;
	for (int i = 0; i < Lw; i++) {
		for (int j = 0; j < Lh; j++) {
			if (duck_hunt_stage_ARRY[j][i] != 1)
				putpixel(x + i - 12, y + j - 32, duck_hunt_stage_ARRY[j][i]);
		}
	}
}

void gr_Start(int &GrDriver, int &GrMode, int &ErrorCode) {
	//set the graphics driver
	GrDriver = VGA; //800x600 by monitor
	GrMode = VGAMAX;//set graphics mode
	initgraph(&GrDriver, &GrMode, "");//start graphics
									  //check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
	}
	else {
		maxX = getmaxx();
		maxY = getmaxy();
	}
}
bool evens() {
	return rand() % 2 == 0;
}
struct Shape {
	int count;
	float poiX, poiY;
	bool intersect;
	bool overlap;
	struct Point {
		int X;
		int Y;
		void init(int x, int y) {
			X = x;
			Y = y;
		}
	};
	struct Rect {
		int x, y, h, w;
		Point TopLeft, BottomRight;
		int bColor, outline;
		void construct(int xc, int yc, int r) {
			xloop = xc;
			yloop = yc;
			rloop = r;
			TopLeft.init(xc - r, yc - r);
			BottomRight.init(xc + r, yc + r);
		}
		void init() {
			x = (rand() % (maxX - 50)) + (rand() % 20) + 5;
			y = (rand() % (maxY - 50)) + (rand() % 20) + 5;
			w = (rand() % (maxX - 25 - x)) + (rand() % 20) + 5;
			h = (rand() % (maxY - 25 - y)) + (rand() % 20) + 5;
			bColor = rand() % 15 + 1;
			TopLeft.init(x, y);
			BottomRight.init(x + w, y + h);
			oL();
		}
		void tick() {
			oL();
		}
		void render() {
			setcolor(bColor);
			bar(x, y, x + w, y + h);
			setcolor(outline);
			rectangle(x, y, x + w, y + h);
		}
		void oL() {
			do {
				outline = rand() % 15 + 1;
			} while (outline != bColor);
		}
	}rect, rect2, rect3;
	
	struct Circle {
		Rect hitBox;
		Rect CrossHitBox;
		int x, y, rh, rw;
		int dx, dy;
		int C;
		bool reset;
	



		struct pass {
			int VirtualKey;
			bool isPressed;
			bool isHeld;
			DIRECTION move;
			void reset() {
				isPressed = false;
				isHeld = false;
			}
		}mouseInput;
		
		void mousepress() {
				//mouseInput.isHeld = x, y;


				if (mousePress(VK_LBUTTON)) {
					mouseInput.isPressed = true;
				}
				if(mouseInput.isPressed == true){
					mouseInput.isPressed = false;
					hit();
				}
		}
		
		void hit() {
			if((((xlil - rlil) <= (xbig + rbig)) && ((xlil + rlil) >= (xbig - rbig))) && (((ylil - rlil) <= (ybig + rbig)) && ((ylil + rlil) >= (ybig - rbig)))) {
				checkHit = true;
				score++ ;
			}

		}
		void getCursor() {
	
			GetCursorPos(&t);
			crossHair(t.x, t.y);
			CrossHitBox.construct(t.x, t.y - 20, 1);
			xlil = xloop;
			ylil = yloop;
			rlil = rloop;
		}

		void init() {
			checkHit = false;
			ducknum++;
			x = (rand() % 1920);
			y = 810;
			set();
			hitBox.construct(x, y, 64);

		}
		void Reeset() {
			if (evens())
				dx *= -1;
			if (evens())
				dy *= 1;

		}
		void selectdifficulty() {

		}
		void set() {
			reset = false;
			int randneg = rand() % 2;
			rh = 64;
			rw = 60;
			dx = difficulty;
			dy = rand() % difficulty;
			if (randneg == 0) {
				dx = dx * -1;
			}

			if (dy == 0) {
				set();
			}

		
		}
		void wall() {
			if (x - rw < 5) {
				x = rw + 5;
				Reeset();
			}
			if (x > (maxX - rw - 3)) {
				x = maxX - rw - 3;
				Reeset();
			}
			if (y - rh < 3)
			{
				y = rh + 3;
				init();

			}
			if (y > (maxY - rh - 3)) {
				y = maxY - rh + 3;
				system("pause");
				init();
			}
		}
		void tick() {
			if (reset)
				set();
			x += dx;
			y -= dy;
			wall();
			getCursor();
			mousepress();
			if (checkHit) {
				init();
			}
			
		

		}
		void render() {

			getCursor();
			
			if (dx > 0) {
				duckRight(x - rw, y - rh);
				hitBox.construct(x, y, 64);
				xbig = xloop;
				ybig = yloop;
				rbig = rloop;
			}
			else {
				duckLeft(x - rw, y - rh);
				hitBox.construct(x, y, 64);
				xbig = xloop;
				ybig = yloop;
				rbig = rloop;
			}
		
			
		}
	} circ;


	void init() {

		circ.init();

	}


	void tick() {
		circ.tick();

	}
	void render() {
		setbkcolor(1);
		cleardevice();
		setbkcolor(0);
		circ.render();
	}
}assignment;
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	cout << "Type a Difficulty" << endl;
	cout << "0 = Easy" << endl;
	cout << "1 = Medium" << endl;
	cout << "2 = Hard" << endl;
	cout << "3 = Insane" << endl;

	cin >> difficulty;
	if (difficulty == 0) {
		difficulty = 10;
		maxduck = 10;
	}
	if (difficulty == 1) {
		difficulty = 20;
		maxduck = 15;
	}
	if (difficulty == 2) {
		difficulty = 40;
		maxduck = 20;
	}
	if (difficulty == 3) {
		difficulty = 80;
		maxduck = 40;
	}
	cout << "3" << endl;
	Sleep(750);
	cout << "2" << endl;
	Sleep(750);
	cout << "1" << endl;
	Sleep(750);
	cout << "GO" << endl;
	assignment.init();
	ShowCursor(false);

	while (whileloop == 0) {
		assignment.tick();
		assignment.render();
		Sleep(20);
		if (ducknum > maxduck) {
			duckhuntstage(0, 0);
			whileloop++;
			
		}
	}
	ShowCursor(true);
	string gameover = "Game Over";
	string displayscore = "Score:";
	string displayplayerscore = to_string(score);
	settextstyle(0, 0, 40);
	outtextxy(625, 0, displayscore.c_str());
	outtextxy(1100, 0, displayplayerscore.c_str());
	putpixel(0, 0, LIGHTBLUE);
	cout << "Score" << ": " << score << "/" << maxduck << endl;
	system("pause");
	


}

void duckRight(int x, int y) {
	int Rh = duckRight_height;
	int Rw = duckRight_width;
	for (int i = 0; i < Rw; i++) {
		for (int j = 0; j < Rh; j++) {
			if (duckRight_ARRY[j][i] != 1)
				putpixel(x + i, y + j, duckRight_ARRY[j][i]);
		}
	}
}

void duckLeft(int x, int y) {
	int Lh = duckLeft_height;
	int Lw = duckLeft_width;
	for (int i = 0; i < Lw; i++) {
		for (int j = 0; j < Lh; j++) {
			if (duckLeft_ARRY[j][i] != 1)
				putpixel(x + i, y + j, duckLeft_ARRY[j][i]);
		}
	}
}

bool mousePress(int k){

	return GetAsyncKeyState(k) & 0x8000 != 0;
}




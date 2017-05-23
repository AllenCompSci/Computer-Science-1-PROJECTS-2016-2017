/*#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h> // Sleep()
#include <ctime>
#include <conio.h>
#define UpArrow 72
#define DownArrow 80
#define LeftArrow 75
#define RightArrow 77
using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
int setMyColor(int color, int rectColor);
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor

struct Line {
	int x, y, x1, y1;
	int length;
	int color;
	void init() {
		color = 3;
		PlayerLine();
		draw();
	}
	void PlayerLine() {
		Sleep(10);
		
		setlinestyle(2, 1, 3 & 3);

		x = (rand() % (maxX - 50)) + (rand() % 20) + 5;
		y = (rand() % (maxY - 50)) + (rand() % 20) + 5;
		x1 = (rand() % (maxX - 50)) + (rand() % 20) + 5;
		y1 = (rand() % (maxY - 50)) + (rand() % 20) + 5;
		if (x1 < x) {
			swap(x, x1);
			swap(y, y1);
		}
		length = (rand() % (maxY - 25 - y)) + (rand() % 20) + 5;
		slope();
		color = setMyColor(0, 0);
		cout << "new line \n";
	}
	void draw() {
		setcolor(color);
		cout << "Line : " << getcolor() << endl;

	}
	void outline() {
		setcolor(penColor);
		line(x, y, x1, y1);
	}
	void setColor(int c) {
		color = c;
	}
	int getColor() {
		return color;
	}
	float m;
	float b;

	void slope() {
		m = (y - y1) / (float)(x - x1);
		b = y - (m*x);
	}
}Player1, Player2;
bool contained(float val, int bound1, int bound2);
bool collide(Line myline, Line myline2);
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	maxX = getmaxx(); // From Graphics
	maxY = getmaxy(); // From Graphics

	setbkcolor(8);

	while (true) {
		Player1.init();
		Player2.init();
		penColor = setMyColor(15, Player1.getColor());
		while (!collide(Player1, Player2)) {
			if (penColor == 0) {
				cleardevice();
				Player1.PlayerLine();
				Player1.draw();
				Player2.PlayerLine();
				Player2.draw();

				penColor = setMyColor(penColor, Player1.getColor());
			}
			Player1.outline();
			Player2.outline();
			penColor = setMyColor(penColor, Player1.getColor());
			Sleep(3);
		}
		char t = getch();
	}
}
/// Outside struct
bool collide(Line Player1, Line Player2) {

	if (Player2.m == Player1.m) return false; // Parallel 
	float poiX = (Player1.b - Player2.b) / (Player2.m - Player1.m);
	float poiY = Player1.m * poiX + Player1.b;
	// Check to make sure is in the window /// return false if not

	if (!contained(poiX, Player1.x, Player1.x1)) {
		return false;
	}
	if (!contained(poiX, Player2.x, Player2.x1)) {
		return false;
	}
	// if you reach here
	penColor = setMyColor(14, 0);
	Player1.outline();
	Player2.outline();
	setcolor(14);
	fillellipse((int)poiX, (int)poiY, 8, 8);
	return true;

}

bool contained(float val, int bound1, int bound2) {
	if (val == bound1 || val == bound2) {
		return true;
	}
	if (val < bound1) {
		return val > bound2;
	}
	return val < bound2;
}
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode) {
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
}
int setMyColor(int color, int rectColor) {
	int val;
	do { val = rand() % 16; } while (val == color || val == rectColor);
	return val;
}*/
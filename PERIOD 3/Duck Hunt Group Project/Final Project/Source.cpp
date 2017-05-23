/*
David Freiberger && Drew Gray && Sarah Anderson
Duck Hunt
Period 3
4 April 2017
*/
#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h> // Sleep()
#include <ctime>
#include "VirtualKeys.h"
enum DIRECTION { UP, RIGHT, DOWN, LEFT, PAUSE, SELECT, LEFTCLICK, RIGHTCLICK };
POINT click;
using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
int setMyColor(int color, int rectColor);
const int MAXSPEEd = 15;
const int dRADIUS = 75;
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor
bool isRunning = true;
void getCursor(POINT &p, int VirtualKey);
bool mousePress(int);
bool clickint = false;
char score;
int universalcircleTRX;
bool XHIT;
bool YHIT;
int universalClickX;
int universalClickY;
bool CheckHit = false;
string MLGHitmark = "Hitmarker - MLG Sound Effect (HD).mp3";



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
struct CIRCLE {
	int x, y;
	double b;
	double m;
	int radius;
	int color;
	int dx, dy;
	bool collide;
	void init() {
		radius = 50;
		dx = 0;
		dy = 4;
		collide = false;
		color = 4;
		x = maxX / 2;
		y = maxY / 2;
		generateYMXB();
		draw();
	}
	void generateYMXB() {
		m = (double)(dy) / (double)(dx);
		b = y - m *x;
	}
	void generateRandomCircle() {
		cout << "New Circle :" << endl;
		collide = false;
		color = setMyColor(0, getColor());
		changeSPEED();
		radius = rand() % (dRADIUS - 3) + 10;
		generateYMXB();
		cout << "Color : " << color << "\n";
		if (collision()) {
			adjustXY();
		}
		draw();
	}
	void changeSPEED() {
		do {
			dx = rand() % MAXSPEEd;
			dy = rand() % MAXSPEEd;
			dx *= (rand() % 2 == 0) ? -1 : 1;
			dy *= (rand() % 2 == 0) ? -1 : 1;
		} while (dx == 0 && dy == 0);
	}
	void move() {
		deleteCircle();
		x += dx;
		y += dy;
		collide = collision();
		if (collide)
			adjustXY();
		draw();
		Sleep(6);
		if (collide) {
			Sleep(5);
			deleteCircle();
			generateRandomCircle();
		}
	}
	void MOUSE() {
		while (isRunning) {
			if (mousePress(VK_LBUTTON)) {
				mouseInput.isPressed = true;
			
			}
			if (mousePress(VK_RBUTTON)) {

			}
			if (mousePress(VK_MBUTTON))
			{

			}
			Sleep(15);
		}
	}
	bool collision() {
		if ((x + radius) >= maxX || (x - radius) <= 0) {
			return true;
		}
		if ((y + radius) >= maxY || (y - radius) <= 0) {
			return true;
		}
		return false;
	}
	void adjustXYinf() {
		int count = 0;
		while (collision()) {
			cout << "COLLISion : " << ++count << endl;
			if (count > 5) {
				if (x < radius && y < radius) {
					x = radius + 1;
					y = radius + 1;
				}
				else if ((x + radius) > maxX && y < radius) {
					x = maxX - radius - 1;
					y = radius + 1;
				}
				else if (x + radius > maxX && y + radius > maxY) {
					x = maxX - radius - 1;
					y = maxY - radius - 1;
				}
				else if (x < radius && (y + radius) > maxY) {
					x = radius + 1;
					y = maxY - radius - 1;
				}
				else if (y < radius) {
					y = radius + 1;
				}
				else if (x < radius) {
					x = radius + 1;
				}
				else if (y + radius >= maxY) {
					y = maxY - radius - 1;
				}
				else if (x + radius >= maxX) {
					x = maxX - radius - 1;
				}
				changeSPEED();
				return;
			}
			else if ((x - radius) < 0) {
				x = radius + 1;
			}
			else if ((y + radius) > maxY) {
				y = maxY - radius - 1;
			}
			else if ((y - radius) < 0) {
				y = radius + 1;
			}
			else if ((x + radius) > maxX) {
				x = maxX - radius - 1;
			}

		}
	}
	void adjustXY() {
		if (dx == 0 || dy == 0)
			return adjustXYinf();
		int count = 0;
		while (collision()) {
			cout << "XY   : " << count++ << " :x: " << x << " :y: " << y << " :R: " << radius << endl;
			if (count > 5) {
				if (x < radius && y < radius) {
					x = radius + 1;
					y = radius + 1;
				}
				else if ((x + radius) > maxX && y < radius) {
					x = maxX - radius - 1;
					y = radius + 1;
				}
				else if (x + radius > maxX && y + radius > maxY) {
					x = maxX - radius - 1;
					y = maxY - radius - 1;
				}
				else if (x < radius && (y + radius) > maxY) {
					x = radius + 1;
					y = maxY - radius - 1;
				}
				else if (y < radius) {
					y = radius + 1;
				}
				else if (x < radius) {
					x = radius + 1;
				}
				else if (y + radius >= maxY) {
					y = maxY - radius - 1;
				}
				else if (x + radius >= maxX) {
					x = maxX - radius - 1;
				}
				changeSPEED();
				return;
			}
			else if ((x + radius) > maxX) {
				x = maxX - radius - 1;
				y = (int)(m * x + b);
			}
			else if ((x - radius) < 0) {
				x = radius + 1;
				y = (int)(m * x + b);
			}
			else if ((y + radius) > maxY) {
				y = maxY - radius - 1;
				x = (int)((y - b) / m);
			}
			else if ((y - radius) < 0) {
				y = radius + 1;
				x = (int)((y - b) / m);
			}


		}
	}
	void deleteCircle() {
		setcolor(BLACK);
		fillellipse(x, y, radius + 5, radius + 5);
	}
	void draw() {
		setcolor(color);
		fillellipse(x, y, 10, 10);

		cout << "DRAW @ " << x << ", " << y << "\n";

		Sleep(3);
	}
	void setColor(int c) {
		color = c;
	}
	int getColor() {
		return color;
	}
	
}myCircle;
struct target {
	int x;
	int y;
	bool MouseClick = false;
	void getCursor(int x, int y) {
		mouseInput.isHeld = true;
		mouseInput.isHeld = x, y;

		if (mousePress(VK_LBUTTON)) {
			fillellipse(x, y - 20, 10, 10);
			Sleep(170);
			score = score + 1;
			x = universalClickX;
			y = universalClickY;
		}
		
		else{
			cleardevice();
		}
		fillellipse(x, y - 20, 4, 4);
	}
	}mytarget;
void checkhit() {
	

}
	void main(){
			srand((unsigned int)time(NULL));
			gr_Start(GrDriver, GrMode, ErrorCode);
			maxX = getmaxx(); // From Graphics
			maxY = getmaxy(); // From Graphics
			myCircle.init();
			ShowCursor(false);
			while (true) {
				myCircle.move();
				POINT t;
				GetCursorPos(&t);
				mytarget.getCursor(t.x,t.y);
				Sleep(0);
				string Score = to_string(score);
				string Title = "score ";
				settextstyle(1, 0, 8);
				outtextxy(50,900,Title.c_str());
				outtextxy(400,900, Score.c_str());


			}
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
		}


		bool mousePress(int k) {
			return GetAsyncKeyState(k) & 0x8000 != 0;
		}
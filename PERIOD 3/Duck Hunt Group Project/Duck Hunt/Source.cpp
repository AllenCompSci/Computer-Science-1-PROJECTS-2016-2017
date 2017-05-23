/*
David Freiberger && Drew Gray && Sarah Anderson
Duck Hunt
Period 3
4 April 2017
*/
#include<iostream>
#include<string>
#include<winbgi.cpp>
#include<graphics.h>
#include<ctime>
#include<Windows.h>
using namespace std;
#pragma once

int maxX, maxY;
int GrDriver, GrMode, ErrorCode;
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
	struct Line {
		int x1, x2, y1, y2;
		float b;
		float m;
		int pencolor;
		void init() {
			x1 = rand() % (maxX - 35) + 15 + (rand() % 20);
			x2 = rand() % (maxX - 35) + 15 + (rand() % 20);
			y1 = rand() % (maxY - 35) + 15 + (rand() % 20);
			y2 = rand() % (maxY - 35) + 15 + (rand() % 20);
			m = (y2 - y1) / (float)(x2 - x1);
			// y = mx+b -> y - mx = b
			b = y1 - (m * x1);
			pencolor = rand() % 15 + 1;
		}
		void tick() {
			pencolor = rand() % 15 + 1;
		}
		void render() {
			setcolor(pencolor);
			line(x1, y1, x2, y2);
		}
	}line1, line2;
	struct Rect {
		int x, y, h, w;
		Point TopLeft, BottomRight;
		int bColor, outline;
		void construct(int xc, int yc, int r) {
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
		Rect boundBox;
		int x, y, r;
		int dx, dy;
		int C;
		bool reset;
		void init() {
			x =  960;
			y = 810;
			set();
			boundBox.construct(x, y, r);
		}
		void set() {
			reset = false;
			r = rand() % 20 + 15;
			C = rand() % 15 + 1;
			dx = rand() % 150;
			if (evens())
				dx *= -1;
			dy = rand() % 20;
			if (evens())
				dy *= 1;
			if (dx == 0 && dx == dy) {
				set();
			}
		}
		void wall() {
			if (x - r < 5) {
				x = r + 5;
				system("pause");
			}
			if (x >(maxX - r - 3)) {
				x = maxX - r - 3;
				system("pause");
			}
			if (y - r < 3)
			{
				y = r + 3;
				system("pause");
			}
			if (y >(maxY - r - 3)) {
				y = maxY - r + 3;
				system("pause");
			}
		}
		void tick() {
			if (reset)
				set();
			x += dx;
			y -= dy;
			wall();
		}
		void render() {
			drawbigBird.construct();
			boundBox.construct(x, y, r);
		}
	} circ;
	
	void poi() {
		setcolor(14);
		fillellipse((int)poiX, (int)poiY, 7, 7);
	}
	bool contained(int p, int bound1, int bound2) {
		if (p == bound1 || p == bound2) {
			return true;
		}
		if (bound1 < bound2) {
			return bound1 < p && p < bound2;
		}
		return bound2 < p && p < bound1;
	}
	void init() {

		circ.init();

	}


	void tick() {
		circ.tick();

	}
	void render() {
		cleardevice();
		circ.render();
		Sleep(40);
	}
}assignment;
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	assignment.init();
	while (true) {
		assignment.tick();
		assignment.render();
		Sleep(35);
	}
}
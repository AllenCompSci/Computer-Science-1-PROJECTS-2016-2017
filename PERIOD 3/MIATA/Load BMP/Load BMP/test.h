#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include "draw.h"
#include <Windows.h>

using namespace std;
void KEY_LISTENER();
void getCursor(POINT &p, int VirtualKey);
bool mousePress(int VirtualKey);
bool KEYBOARD(int VirtualKey);
enum MIATA {
	BottomTone, TopTone, Interior, Outline, Wheels, Windows, TireWall, TailLights, STOCK, SLAMMED
};
struct pass {
	int VirtualKey;
	bool isPressed;
	bool isHeld;
	void reset() {
		isPressed = false;
		isHeld = false;
	}
}keyInput, mouseInput;
struct Button {
	int Top, Left, Right, Bottom, Color;
	bool isLEFT;
	void init(int left, int top, int right, int bottom, int color) {
		Top = top;
		Left = left;
		Right = right;
		Bottom = bottom;
		Color = color;
		draw();
	}

	void draw() {
		setcolor(Color);
		bar(Left, Top, Right, Bottom);
		if (Color != WHITE) {
			setcolor(WHITE);
		}
		else {
			setcolor(BLACK);
		}
		rectangle(Left + 1, Top + 1, Right - 1, Bottom - 1);
	}
	bool isPressed(POINT p) {
		
		return ((Left <= p.x) && (p.x <= Right)) && ((Top <= p.y) && (p.y <= Bottom));
	}
	void ARROW() {
		setcolor(WHITE);
		bar(Left, Top, Right, Bottom);
		setcolor(BLACK);
		rectangle(Left, Top, Right, Bottom);
		if (isLEFT) {
			// LEFT BUTTON
			line(((maxX / 8) * 2) - 30, (maxY / 3) * 2, ((maxX / 8) * 2) + 30, ((maxY / 3) * 2) + 30);
			line(((maxX / 8) * 2) - 30, (maxY / 3) * 2, ((maxX / 8) * 2) + 30, ((maxY / 3) * 2) - 30);
			line(((maxX / 8) * 2) + 30, (maxY / 3) * 2 + 30, ((maxX / 8) * 2) + 30, ((maxY / 3) * 2) - 30);
			
		}
		else {
			// RIGHT BUTTON
			line(((maxX / 8) * 6) - 30, ((maxY / 3) * 2) - 30, ((maxX / 8) * 6) + 30, (maxY / 3) * 2);
			line(((maxX / 8) * 6) - 30, ((maxY / 3) * 2) + 30, ((maxX / 8) * 6) + 30, (maxY / 3) * 2);
			line(((maxX / 8) * 6) - 30, (maxY / 3) * 2 + 30, ((maxX / 8) * 6) - 30, ((maxY / 3) * 2) - 30);
		}
		floodfill(Left + (Right - Left) / 2, Top + (Bottom - Top) / 2, BLACK);
	}

}COLOR[16], LEFT, RIGHT;

int GrDriver, GrMode, ErrorCode;
POINT click;
bool isRunning = true;
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

void button() {
	int countUp = 0;
	int screenInto8 = (getmaxx() / 8);
	while (countUp <= 7) {

		COLOR[countUp].init((((countUp + 1)*screenInto8) - screenInto8), (getmaxy()- 100), ((countUp + 1)*screenInto8),(getmaxy()-50), countUp);
		COLOR[countUp+8].init((((countUp + 1)*screenInto8) - screenInto8), (getmaxy() - 50), ((countUp + 1)*screenInto8), getmaxy(), countUp+8);

		countUp++;
	}
	LEFT.init(((maxX / 8) * 2) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 2) + 40, ((maxY / 3) * 2) + 40, WHITE);
	LEFT.isLEFT = true;
	RIGHT.init(((maxX / 8) * 6) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 6) + 40, ((maxY / 3) * 2) + 40, WHITE);
	
	LEFT.ARROW();
	RIGHT.ARROW();
	/*
	setcolor(WHITE);
	bar(((maxX / 8) * 2) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 2) + 40, ((maxY / 3) * 2) + 40);
	bar(((maxX / 8) * 6) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 6) + 40, ((maxY / 3) * 2) + 40);
	setcolor(BLACK);
	rectangle(((maxX / 8) * 2) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 2) + 40, ((maxY / 3) * 2) + 40);
	rectangle(((maxX / 8) * 6) - 40, ((maxY / 3) * 2) - 40, ((maxX / 8) * 6) + 40, ((maxY / 3) * 2) + 40);
	*/
	


	

}

void test() {
	gr_Start(GrDriver, GrMode, ErrorCode);
	char t;
	string Miata = "1990 Mazda MX-5 Miata";
	MIATA
	setbkcolor(14);
	cleardevice();
	setbkcolor(0);
	background = 14;
	tireWall = 8;
	outline = 0;
	bodyRails = 0;
	lightsAndHandle = 7;
	interior = 6;
	windows = 8;
	wheels = 7;
	bottomTone = 4;
	tailLights = 12;
	topTone = 4;	
	settextstyle(0, 0, 4);
		int textWidth = (textwidth(Miata.c_str())) / 2;
		int center = (getmaxx() / 2) - (textWidth);
		outtextxy(center, 5, Miata.c_str());

		button();
	while (isRunning) {

		
	

		drawbottomTone((maxX - miata_Width) / 2, ((maxY / 3) + (maxY / 3)) - bottomTone_Height);
		if (STOCK) {
			drawMiata((maxX - miata_Width) / 2, (maxY - miata_Height) / 3);
		}
		else if(SLAMMED) {

		}
		if (mouseInput.isPressed && LEFT.isPressed(click)) {

		}
		t = getch();
		cleardevice();
		setbkcolor(14);
		cleardevice();
		setbkcolor(0);
		outtextxy(center, 5, Miata.c_str());
		drawtopTone((maxX - miata_Width) / 2, ((maxY / 3) + (maxY / 3)) - topTone_Height);
		drawMiata((maxX - miata_Width) / 2, (maxY - miata_Height) / 3);

		t = getch();
	}
}
void KEY_LISTENER() {
	while (isRunning) {
		if (mousePress(VK_LBUTTON)) {

		}

	}
}
void getCursor(POINT &p, int VirtualKey) {
	while (true) {
		if (GetCursorPos(&p)) {
			if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0) {
				do {} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
				return;
			}
		}
	}
}
bool mousePress(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0) {
		GetCursorPos(&click);
		mouseInput.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 1400) {
				mouseInput.isHeld = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}
bool KEYBOARD(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		keyInput.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				keyInput.isHeld = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		keyInput.isPressed = true;
		return true;
	}
	return false;

}
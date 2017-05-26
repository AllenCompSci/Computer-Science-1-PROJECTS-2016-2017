#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include "draw.h"
#include <Windows.h>

#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include "VirtualKeys.h"
#include <thread>
#include <stdio.h>
#include <mmsystem.h>
#include <mciapi.h>
using namespace std;
bool KEYBOARD(int); // if keyboard hit


int GrDriver, GrMode, ErrorCode;
void gr_Start(int &GrDriver, int &GrMode, int &ErrorCode) {
	//set the graphics driver
	GrDriver = DETECT; //800x600 by monitor
	GrMode = VGAMAX;//set graphics mode
	initgraph(&GrDriver, &GrMode, "");//start graphics
									  //check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
	}
	else {
		int maxX = getmaxx();
		int maxY = getmaxy();
	}
}
int x = 5;
void test() {
	gr_Start(GrDriver, GrMode, ErrorCode);
	Sleep(100);
	drawSTARTscreen(160, 90);
	while (true) {

		if (KEYBOARD(VK_SPACE)) {

			cleardevice();
			drawgirl(248, 132);
			drawlevelONE(150, 120);
			drawdkFront(177, 147);
			drawmarioRun(155, 318);
		}
			

			if (KEYBOARD(VK_D)) {
				cleardevice();
				drawDKleft(177, 147);
				drawmarioRun(160, 318);
				drawgirl(248, 132);
				drawlevelONE(150, 120);
				system("pause");
				x = x + 5;
			}
			if (KEYBOARD(VK_S)) {
				cleardevice();
				drawDKhold(100, 100);
				drawDKright(150, 100);
				drawheart(200, 100);
				drawmarioJumpRight(250, 100);
				drawmarioLeft(300, 100);
			}

		}


		//drawmarioLadder(200, 140);
		//PageOutline();
		char t = getch();
	}

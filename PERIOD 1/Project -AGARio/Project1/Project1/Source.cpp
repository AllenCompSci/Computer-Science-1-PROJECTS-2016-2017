#include<iostream>
#include<cmath>
#include<string>
#include<thread> // THREADS
#include<graphics.h>
#include<winbgi.cpp>
#include<stdio.h>
#include"VirtualKeys.h"

#include <cstdio>
#include <cstdio>

#pragma region Globals
using namespace std;
int GrDriver, GrMode, ErrorCode;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
int maxX, maxY;
int direction;
enum DIRECTION { UP, RIGHT, DOWN, LEFT , NONE};
bool NPCisLarge;
int x, y, rad;

int GrowOverTime();
//void GrowOverTimeCirc();
void detLarge();
void gencircle();
void draw();
void Collision();
int KeyPress();
void AGARio();
void AGARioNPC();
bool KEYBOARD1(int);
//int Addrad(int, int);
#pragma endregion

struct pass {
	int VirtualKey;
	bool isPressed;
	bool isHeld;
	DIRECTION move;
	void reset() {
		isPressed = false;
		isHeld = false;
	}
}playerInput1;

pass *listener;

struct circles {
	int x, y, rad;				//PLAYER X, Y, RAD VALS
	int NPC_x, NPC_y, radNPC;	//NPC X, Y, RAD VALS
	//bool hasgrown = false;

	void init() {
		gencircle();
		draw(playercircle);
	}

	void initNPC() {
		gencircleNPC();
		drawNPC();
	}

	void gencircle() {			//PLAYER START PLACE IS ALWAYS CENTER OR NEAR
		x = 1000;
		y = 500;
		rad = 50;
	}

	void gencircleNPC() {
		//srand(time(NULL));
		NPC_x = (rand() % (maxX - 50)) + (rand() % 20) + 5;
		NPC_y = (rand() % (maxY - 50)) + (rand() % 20) + 5;
		//	radNPC = (rand() % 100 + 1);

		int radguess = (rand() % (10) + 1);
		switch (radguess) {
		case 1:
			radNPC = 15;
			break;
		case 2:
			radNPC = 20;
			break;
		case 3:
			radNPC = 25;
			break;
		case 4:
			radNPC = 40;
			break;
		case 5:
			radNPC = 60;
			break;
		case 6:
			radNPC = 60;
			break;
		case 7:
			radNPC = 70;
			break;
		case 8:
			radNPC = 80;
			break;
		case 9:
			radNPC = 95;
			break;
		case 10:
			radNPC = 150;
			break;
		}

		//NPC START PLACE IS ALWAYS RANDOM AS WELL AS SIZE
	}

	#pragma region GET VALUES
	int getrad() {
		return rad;
	}
	int getradNPC() {
		return radNPC;
	}
	int getx() {
		return x;
	}
	int getNPC_x() {
		return NPC_x;
	}
	int gety() {
		return y;
	}
	int getNPC_y() {
		return NPC_y;
	}
	#pragma endregion

	void draw(circles player) {
		int oldrad = rad;
		cout << eat(playercircle) << endl;
		rad = eat(playercircle);
		cout << eat(playercircle) << endl;
		if (rad != oldrad)
		{
			cout << "STOP" << endl;
		}
		if (rad == 0) { return; }
		//if (hasgrown == true) { rad = NPCdie(playercircle); }
		//cout << "rad = " << rad << endl;
		setfillstyle(1, 2);
		//rad = rad + radNPC;
		fillellipse(x, y, rad, rad);
		//cout << "Player generated at (" << x << ',' << y << ") with radius " << rad << endl;	
	}

	void remove()
	{
		setfillstyle(1, 7);
		//rad = rad + radNPC;
		fillellipse(x, y, eat(playercircle), eat(playercircle));
	}

	void drawNPC() {
		//setcolor(8);
		setfillstyle(1, 4);
		fillellipse(NPC_x, NPC_y, radNPC, radNPC);
	//	cout << "NPC generated at (" << NPC_x << ',' << NPC_y << ") with radius " << radNPC << endl;
	}

	void removeNPC() {
		setfillstyle(1, 7);
		fillellipse(NPC_x, NPC_y, radNPC, radNPC);
	}

	void movecircle() {
		if (!(NPC_x < 0 || NPC_x > 1920 || NPC_y < 0 || NPC_y > 1080) && rad != 0) {
			if (direction == RIGHT) { x += (80 / rad) + 1; }

			else if (direction == UP) { y -= (80 / rad) + 1; }

			else if (direction == LEFT) { x -= (80 / rad) + 1; }

			else if (direction == DOWN) { y += (80 / rad) + 1; }

			else { cout << "There is an error. " << endl; }

		}
		//Sleep(1);
		if ((NPC_x < 0 || NPC_x > 1920 || NPC_y < 0 || NPC_y > 1080) && rad != 0) {
			if (direction == RIGHT) { x -= (80 / rad) + 1; }

			else if (direction == UP) { y += (80 / rad) + 1; }

			else if (direction == LEFT) { x += (80 / rad) + 1; }

			else if (direction == DOWN) { y -= (80 / rad) + 1; }

			else { cout << "There is an error. " << endl; }

		//Sleep(1);
		}
	}

	void movecircleNPC() {		///CURRENTLY BACKWARDS FROM PLAYER MOVEMENTS
		double speed;
		if (radNPC != 0) { speed = (50 / radNPC); }
		else { speed = 0; }

		#pragma region GET X AND Y VALS
			x = playercircle.getx();
			NPC_x = getNPC_x();

			y = playercircle.gety();
			NPC_y = getNPC_y();

			rad = playercircle.getrad();
			radNPC = getradNPC();
		#pragma endregion

			//srand(time(NULL));
			int chancemove = rand() % 5 + 1;

			if (chancemove >= 4) {

				if (radNPC > rad || NPC_x < 0 || NPC_x > 1920 || NPC_y < 0 || NPC_y > 1080) {
					//cout << chancemove;
																							///	if (direction == RIGHT) { NPC_x -= (75 / radNPC) + 1; }
					if (x > NPC_x) { NPC_x += (speed)+1; }
																							///	else if (direction == UP) { NPC_y += (75 / radNPC) + 1; }
					else if (y > NPC_y) { NPC_y += (speed)+1; }
																							///	else if (direction == LEFT) { NPC_x += (75 / radNPC) + 1; }
					else if (x < NPC_x) { NPC_x -= (speed)+1; }
																							///	else if (direction == DOWN) { NPC_y -= (75 / radNPC) + 1; }
					else if (y < NPC_y) { NPC_y -= (speed)+1; }
																							///	else { cout << "There is an error. " << endl; }	
																							//Sleep(5);
																							//cout << "Seeking player at " << x << "," << y << endl;
				}
				else if (radNPC < rad) {
																							///	if (direction == RIGHT) { NPC_x -= (75 / radNPC) + 1; }
					if (x > NPC_x) { NPC_x -= (speed)+1; }
																							///	else if (direction == UP) { NPC_y += (75 / radNPC) + 1; }
					else if (y > NPC_y) { NPC_y -= (speed)+1; }
																							///	else if (direction == LEFT) { NPC_x += (75 / radNPC) + 1; }
					else if (x < NPC_x) { NPC_x += (speed)+1; }
																							///	else if (direction == DOWN) { NPC_y -= (75 / radNPC) + 1; }
					else if (y < NPC_y) { NPC_y += (speed)+1; }
																							///	else { cout << "There is an error. " << endl; }	
																							//Sleep(5);
																							//cout << "Seeking player at " << x << "," << y << endl;
				}
			}

			else if (chancemove < 4) { 
				//cout << chancemove; 
					if (radNPC < rad) {
																							///	if (direction == RIGHT) { NPC_x -= (75 / radNPC) + 1; }
						if (x > NPC_x) { NPC_x -= (speed); }//(speed)+1; }
																							///	else if (direction == UP) { NPC_y += (75 / radNPC) + 1; }
						else if (y > NPC_y) { NPC_y -= (speed); }//(speed)+1; }
																							///	else if (direction == LEFT) { NPC_x += (75 / radNPC) + 1; }
						else if (x < NPC_x) { NPC_x += (speed); }//(speed)+1; }
																							///	else if (direction == DOWN) { NPC_y -= (75 / radNPC) + 1; }
						else if (y < NPC_y) { NPC_y += (speed); }//(speed)+1; }
																							///	else { cout << "There is an error. " << endl; }	
																							//Sleep(5);
																							//cout << "Seeking player at " << x << "," << y << endl;
				} 
			}

		}
	
	void detIfLarge() {
		int radNPC1, radNPC2, radNPC3, radNPC4, radNPC5, radNPC6, radNPC7, radNPC8, radNPC9, radNPC10;
		bool NPCisLarge1, NPCisLarge2, NPCisLarge3, NPCisLarge4, NPCisLarge5, NPCisLarge6, NPCisLarge7, NPCisLarge8, NPCisLarge9, NPCisLarge10;
	//	cout << "Program running." << endl;
		rad = playercircle.getrad();
		//NPC1*********************************************************************
		radNPC1 = NPC1.getradNPC();

		if (radNPC1 > rad) { NPCisLarge1 = true;} // cout << "NPC1 IS LARGE" << endl; 
	
		else if (radNPC1 < rad) { NPCisLarge1 = false; }
		//NPC2*********************************************************************
		radNPC2 = NPC2.getradNPC();

		if (radNPC2 > rad) { NPCisLarge2 = true;} // cout << "NPC2 IS LARGE" << endl; 

		else if (radNPC2 < rad) { NPCisLarge2 = false; }
		//NPC3*********************************************************************
		radNPC3 = NPC3.getradNPC();

		if (radNPC3 > rad) { NPCisLarge3 = true;  }//cout << "NPC3 IS LARGE" << endl;

		else if (radNPC3 < rad) { NPCisLarge3 = false; }
		//NPC4*********************************************************************
		radNPC4 = NPC4.getradNPC();

		if (radNPC4 > rad) { NPCisLarge4 = true; } //cout << "NPC4 IS LARGE" << endl; 

		else if (radNPC4 < rad) { NPCisLarge4 = false; }
		//NPC5*********************************************************************
		radNPC5 = NPC5.getradNPC();

		if (radNPC5 > rad) { NPCisLarge5 = true; } //cout << "NPC5 IS LARGE" << endl;

		else if (radNPC5 < rad) { NPCisLarge5 = false; }
		//NPC6*********************************************************************
		radNPC6 = NPC6.getradNPC();

		if (radNPC6 > rad) { NPCisLarge6 = true;  } //cout << "NPC6 IS LARGE" << endl;

		else if (radNPC6 < rad) { NPCisLarge6 = false; }
		//NPC7*********************************************************************
		radNPC7 = NPC7.getradNPC();

		if (radNPC7 > rad) { NPCisLarge7 = true;  } //cout << "NPC7 IS LARGE" << endl;

		else if (radNPC7 < rad) { NPCisLarge7 = false; }
		//NPC8*********************************************************************
		radNPC8 = NPC8.getradNPC();

		if (radNPC8 > rad) { NPCisLarge8 = true;} //cout << "NPC8 IS LARGE" << endl; 

		else if (radNPC8 < rad) { NPCisLarge8 = false; }
		//NPC9*********************************************************************
		radNPC9 = NPC9.getradNPC();

		if (radNPC9 > rad) { NPCisLarge9 = true; } //cout << "NPC9 IS LARGE" << endl;

		else if (radNPC9 < rad) { NPCisLarge9 = false; }
		//NPC10********************************************************************
		radNPC10 = NPC10.getradNPC();

		if (radNPC10 > rad) { NPCisLarge10 = true; } //cout << "NPC10 IS LARGE" << endl;

		else if (radNPC10 < rad) { NPCisLarge10 = false; }
		//*************************************************************************
	}

	bool collision() {
		while (4 == 4) {
			x = getx();
			y = gety();
			NPC_x = getNPC_x();
			NPC_y = getNPC_y();

			int d = sqrt(pow((NPC_x - x), 2) + pow((NPC_y - y), 2));

			radNPC = getradNPC();

			if (((rad/2) + radNPC) <= d ) { return false; }
			else if (((rad/2) + radNPC) >= d + (rad / 2)) { return true; }// cout << "Collision";

		//	if (x == (NPC_x + radNPC) && y == NPC_y) { cout << "Collision" << endl; return true; } //CASE FOR PLAYER COLLIDING ON THE RIGHT SIDE OF NPC
		//	if (x == (NPC_x - radNPC) && y == NPC_y) { cout << "Collision" << endl; return true; } //CASE FOR PLAYER COLLIDING ON THE LEFT SIDE OF NPC
		//	if (x == NPC_x && y == (NPC_y + radNPC)) { cout << "Collision" << endl; return true; } //CASE FOR PLAYER COLLIDING ON THE TOP SIDE OF NPC
		//	if (x == NPC_x && y == (NPC_y - radNPC)) { cout << "Collision" << endl; return true; } //CASE FOR PLAYER COLLIDING ON THE BOTTOM SIDE OF NPC	
		//	else { cout << "false"; return false; }
		}
	}

	int eat(circles& player) {
		while (4 == 4) {
			rad = playercircle.getrad();
			radNPC = getradNPC();
			if (collision() == true && (radNPC > rad)) {
		
				cout << "NPC WINS";
				setbkcolor(4);
				cleardevice();
				settextstyle(2, 4, 40);
				outtextxy(960, 540, "YOU DIED");
				//Sleep(10);
				playercircle.die();
				cleardevice();
				return 0; // PLAYER DIES

			}
			else if (collision() == true && (radNPC < rad)) {

				cout << "PLAYER WINS" << endl;
				setbkcolor(2);
				cleardevice();
				Sleep(50);
				setbkcolor(7);
				cleardevice();
				cout << "Player : " << player.rad << endl;
				cout << getradNPC() << endl; ///////////
				rad = rad + getradNPC();
				player.rad = rad;
				cout << player.rad << endl;
				cout << rad << endl;		 ///////////
				Sleep(10);
				NPCdie();
				return rad;

			}
			else if(!collision()) {
				return rad;
			}
		}
	//	return rad;
	}

	void die() {
		rad = 0;
	}

	void NPCdie() {
		if (radNPC != 0) {
			radNPC = getradNPC();
			radNPC = 0;
		}
	}

}playercircle, NPC1, NPC2, NPC3, NPC4, NPC5, NPC6, NPC7, NPC8, NPC9, NPC10;

void DetLarge() {
	while (4 == 4) {
		NPC1.detIfLarge();
		NPC2.detIfLarge();
		NPC3.detIfLarge();
		NPC4.detIfLarge();
		NPC5.detIfLarge();
		NPC6.detIfLarge();
		NPC7.detIfLarge();
		NPC8.detIfLarge();
		NPC9.detIfLarge();
		NPC10.detIfLarge();
	}
}

void Collision() {
	while (4 == 4) {
		NPC1.collision();
		NPC2.collision();
		NPC3.collision();
		NPC4.collision();
		NPC5.collision();
		NPC6.collision();
		NPC7.collision();
		NPC8.collision();
		NPC9.collision();
		NPC10.collision();
	}
}

//int GrowOverTime() {
		//rad = playercircle.getrad();
		//rad++;
		//Sleep(10);
		//cout << "Rad increased to " << rad << endl;
		//return rad;
//}

void EAT() {
	while (4 == 4) {
		
		if (NPC1.collision() == true) {
			NPC1.eat(playercircle);
			NPC1.collision();
		}

		if (NPC2.collision() == true) {
			NPC2.eat(playercircle);
			NPC2.collision();
		}

		if (NPC3.collision() == true) {
			NPC3.eat(playercircle);
			NPC3.collision();
		}

		if (NPC4.collision() == true) {
			NPC4.eat(playercircle);
			NPC4.collision();
		}

		if (NPC5.collision() == true) {
			NPC5.eat(playercircle);
			NPC5.collision();
		}

		if (NPC6.collision() == true) {
			NPC6.eat(playercircle);
			NPC6.collision();
		}

		if (NPC7.collision() == true) {
			NPC7.eat(playercircle);
			NPC7.collision();
		}

		if (NPC8.collision() == true) {
			NPC8.eat(playercircle);
			NPC8.collision();
		}

		if (NPC9.collision() == true) {
			NPC9.eat(playercircle);
			NPC9.collision();
		}

		if (NPC10.collision() == true) {
			NPC10.eat(playercircle);
			NPC10.collision();
		}
	}
}

#pragma region MAIN

void main() {
	srand(time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	maxX = getmaxx(); // From Graphics
	maxY = getmaxy(); // From Graphics

	cleardevice();
	setbkcolor(7);

//PLAYER FIRST CIRCLE GENERATION
	playercircle.init();
#pragma region INIT
//NPC FIRST CIRCLE GENERATION
	NPC1.initNPC();
	NPC2.initNPC();
	NPC3.initNPC();
	NPC4.initNPC();
	NPC5.initNPC();
	NPC6.initNPC();
	NPC7.initNPC();
	NPC8.initNPC();
	NPC9.initNPC();
	NPC10.initNPC();
#pragma endregion

#pragma region THREADS
//THREADS FOR PLAYER AND NPC MOVEMENT
	thread DetLarge(DetLarge);		// DETERMINE WHO IS LARGER 
	thread player(KeyPress);		// KEY LISTENER
	thread agar(AGARio);			// PLAYER
 	thread agarNPC(AGARioNPC);		// NPC
	//thread detcollide(Collision);	// COLLISION
	thread EAT(EAT);				// EAT 

	DetLarge.join();				
	player.join();
	agar.join();
	agarNPC.join();
	//detcollide.join();
	EAT.join();
#pragma endregion

	system("pause");
}

	#pragma endregion

void AGARio() {
	cleardevice();
	while (4 == 4) {
		if (direction != NONE) {
			playercircle.remove();
			if (rand() % 4 != 0) {
				x = playercircle.getx();
				y = playercircle.gety();
				playercircle.movecircle();
			}
			else {
				playercircle.movecircle();
				x = playercircle.getx();
				y = playercircle.gety();

			}
			playercircle.draw(playercircle);
			///
			NPC1.removeNPC();
			NPC1.getradNPC();
			NPC1.movecircleNPC();
			///	
			NPC2.removeNPC();
			NPC2.getradNPC();
			NPC2.movecircleNPC();
			///
			NPC3.removeNPC();
			NPC3.getradNPC();
			NPC3.movecircleNPC();
			///
			NPC4.removeNPC();
			NPC4.getradNPC();
			NPC4.movecircleNPC();
			///
			NPC5.removeNPC();
			NPC5.getradNPC();
			NPC5.movecircleNPC();
			///
			NPC6.removeNPC();
			NPC6.getradNPC();
			NPC6.movecircleNPC();
			///
			NPC7.removeNPC();
			NPC7.getradNPC();
			NPC7.movecircleNPC();
			///
			NPC8.removeNPC();
			NPC8.getradNPC();
			NPC8.movecircleNPC();
			///
			NPC9.removeNPC();
			NPC9.getradNPC();
			NPC9.movecircleNPC();
			///
			NPC10.removeNPC();
			NPC10.getradNPC();
			NPC10.movecircleNPC();

		}
		
		//direction = UP;
		//system("pause");
		
		//cleardevice();
		Sleep(15);
		NPC1.drawNPC();
		NPC2.drawNPC();
		NPC3.drawNPC();
		NPC4.drawNPC();
		NPC5.drawNPC();
		NPC6.drawNPC();
		NPC7.drawNPC();
		NPC8.drawNPC();
		NPC9.drawNPC();
		NPC10.drawNPC();
		playercircle.draw(playercircle);

	}
}

void AGARioNPC() {
	srand((unsigned int)time(NULL));
	while (4 == 4) {
		if (direction != NONE) {
			
			///
		//	direction = NONE;
		}
		Sleep(15);
		//cleardevice();
		
		
	}
}

int KeyPress() {
	while (true) {
		if (KEYBOARD1(VK_A)) {
			direction = LEFT;
			//if (playerInput1.move != RIGHT)
				//playerInput1.move = LEFT;

		}
		if (KEYBOARD1(VK_D)) {
			direction = RIGHT;
			//if (playerInput1.move != LEFT)
				//playerInput1.move = RIGHT;

		}
		if (KEYBOARD1(VK_W)) {
			direction = UP;
			//if (playerInput1.move != DOWN)
				//playerInput1.move = UP;

		}
		if (KEYBOARD1(VK_S)) {
			direction = DOWN;
			//if (playerInput1.move != UP)
				//playerInput1.move = DOWN;

		}
		Sleep(15);
	}
}

bool KEYBOARD1(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		//irInBuf1.EventType = KEY_EVENT;  Not needed
		playerInput1.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				playerInput1.isHeld = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		playerInput1.isPressed = true;
		return true;
	}
	return false;

}

#pragma region GRAPHICS SET UP

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

#pragma endregion
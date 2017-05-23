#include "LoadBMP.h"
#include "Pixel.h"
#include "VirtualKeys.h"
#include <thread>
#include <ctime>
#include <mmsystem.h> /// WAV
#include <mciapi.h> /// MP3
#pragma comment(lib, "winmm.lib") /// WAV also maybe MP3
enum GAMESTATE { START_MENU, PLAYER_1, PLAYER_2, CONTROLS, OPTIONS, MAPOPTIONS, GAME, END };
enum DIRECTION { UP, RIGHT, DOWN, LEFT, PAUSE, SELECT, LEFTCLICK, RIGHTCLICK };
enum WIN { CONT, LOSE, TIE };
vector <int> PlayerColorChoices;
bool isRunning = true;
bool changeStates = true;
bool debug = false;
bool selectColor, finalizeColor;
char ** grid;
POINT click;
GAMESTATE Tron = START_MENU;
struct pass {
	int VirtualKey;                             
	bool isPressed;
	bool isHeld;
	DIRECTION move;
	void reset() {
		isPressed = false;
		isHeld = false;
	}
}playerInput1, playerInput2, mouseInput;
struct BUTTON {
	int Left, Top, Right, Bottom;
	void init(int x1, int y1, int x2, int y2) {
		if (x1 < x2) {
			Left = x1;
			Right = x2;
		}
		else {
			Left = x2;
			Right = x1;
		}
		if (y1 < y2) {
			Top = y1;
			Bottom = y2;
		}
		else {
			Top = y2;
			Bottom = y1;
		}
	}
	void init(BUTTON t) {
		Left = t.Left;
		Right = t.Right;
		Top = t.Top;
		Bottom = t.Bottom;
	}
	bool isPressed(POINT p) {
		if (debug) {
			cout << "Point.X : " << p.x << " Point.Y : " << p.y << endl;
			cout << "LEFT  : (" << Left << ")" << (Left <= p.x) << endl;
			cout << "RIGHT : (" << Right << ")" << (p.x <= Right) << endl;
			cout << "TOP   : (" << Top << ")" << (Top <= p.y) << endl;
			cout << "BOTTOM: (" << Bottom << ")" << (p.y <= Bottom) << endl;
		}
		return ((Left <= p.x) && (p.x <= Right)) && ((Top <= p.y) && (p.y <= Bottom));
	}
	void render(int color) {
		setcolor(color);
		bar(Left, Top, Right, Bottom);
	}
	bool isEqual(BUTTON t) {
		return t.Left == Left && t.Right == Right && t.Bottom == Bottom && t.Top == Top;
	}
}Playerselect[6];
struct PLAYERPOS {
	int maxR;
	int maxC;
	int color;
	int row;
	int col;
	pass *listener;
	int unit;
	char C;
	void init(int startR, int startC, int unitSize, pass *input, int COLOR, int row1, int col1) {
		color = COLOR;
		row = startR;
		col = startC;
		unit = unitSize;
		listener = input;
		maxR = row1;
		maxC = col1;
		switch (color)
		{
		case BLUE:
			C = 'B';
			break;
		case RED:
			C = 'R';
			break;
		case GREEN:
			C = 'G';
			break;
		case YELLOW:
			C = 'Y';
			break;
		case MAGENTA:
			C = 'M';
			break;
		}
		render();
	}
	void tick() {
		switch (listener->move) {
		case UP:
			row--;
			return;
		case DOWN:
			row++;
			return;
		case LEFT:
			col--;
			return;
		case RIGHT:
			col++;
			return;
		}
	}
	void render() {
		setcolor(color);
		bar(col*(unit + 1), row*(unit + 1), (col + 1)*(unit + 1), (row + 1)*(unit + 1));
	}
	WIN collide(PLAYERPOS opponent) {
		if (maxR < row || row < 0 || maxC < col || col < 0) {
			return LOSE;
		}
		if (opponent.row == row && opponent.col == col) {
			return TIE;
		}
		if (pix(opponent)) {
			return LOSE;
		}
		return CONT;
	}
	bool pix(PLAYERPOS opponent) {
		int X = (col) * (unit + 1) + (unit + 1) / 2;
		int Y = (row) * (unit + 1) + (unit + 1) / 2;
		return getpixel(X, Y) == color || getpixel(X, Y) == opponent.color;
	}
	void state() {
		cout << "row : " << row << " col : " << col << endl;
	}
}readyPlayer1, readyPlayer2;
struct ButtonHighlight {
	int Left, Top, Right, Bottom;
	int padding;
	BUTTON inner;
	void init(int x) {
		padding = x / 2;
	}
	void pick(BUTTON t) {
		inner.init(t);
		Left = t.Left - padding;
		Right = t.Right + padding;
		Top = t.Top - padding;
		Bottom = t.Bottom + padding;
	}
	void draw() {
		render(WHITE);
	}
	void remove() {
		render(BLACK);
	}
	void render(int color) {
		setcolor(color);
		rectangle(Left, Top, Right, Bottom);
		rectangle(inner.Left, inner.Top, inner.Right, inner.Bottom);
		floodfill(Left + 1, Top + 1, color);

	}
}selected;
int GrDriver, GrMode, ErrorCode;
INPUT_RECORD irInBuf1, irInBuf2;
void gr_Start(int &GrDriver, int &GrMode, int &ErrorCode);
void PLAYER1();
void PLAYER2();
//void OPTIONS();
int z = 1000;
int s;
int p;
int q;
void MOUSE();
void TRON();
void BACKGROUND();
void getCursor(POINT &p, int VirtualKey);
bool mousePress(int);
bool KEYBOARD1(int);
bool KEYBOARD2(int);
void playSound(string, int);
void playSoundSFX(string, int);
void resetListeners();
void setColorPallet();
void drawPLAYER(int);
bool checkPLAYER(int);
void main() {
	bool GmNotArt = (true);
	if (GmNotArt) {
		thread tron(TRON);
		thread p1(PLAYER1);
		thread p2(PLAYER2);
		thread mouse(MOUSE);
		thread audio(BACKGROUND);

		audio.join();
		tron.join();
		mouse.join();
		p1.join();
		p2.join();
	}
	else {
		CREATE("player2.bmp");
	}
}
void gr_Start(int&GrDriver, int&GrMode, int&ErrorCode) {
	GrDriver = VGA;
	GrMode = VGAMAX;
	initgraph(&GrDriver, &GrMode, "");
	ErrorCode = graphresult();
	if (ErrorCode != grOk) {
		cout << "Error : " << ErrorCode << "/n";
	}
}
void PLAYER1() {
	while (isRunning) {
		if (KEYBOARD1(VK_A)) {
			if (playerInput1.move != RIGHT)
				playerInput1.move = LEFT;
		}
		if (KEYBOARD1(VK_D)) {
			if (playerInput1.move != LEFT)
				playerInput1.move = RIGHT;
		}
		if (KEYBOARD1(VK_W)) {
			if (playerInput1.move != DOWN)
				playerInput1.move = UP;
		}
		if (KEYBOARD1(VK_S)) {
			if (playerInput1.move != UP)
				playerInput1.move = DOWN;
		}

		Sleep(10);
	}
}
void PLAYER2() {
	while (isRunning) {
		if (KEYBOARD2(VK_LEFT)) {
			if (playerInput2.move != RIGHT)
				playerInput2.move = LEFT;
		}
		if (KEYBOARD2(VK_RIGHT)) {
			if (playerInput2.move != LEFT)
				playerInput2.move = RIGHT;
		}
		if (KEYBOARD2(VK_UP)) {
			if (playerInput2.move != DOWN)
				playerInput2.move = UP;
		}
		if (KEYBOARD2(VK_DOWN)) {
			if (playerInput2.move != UP)
				playerInput2.move = DOWN;
		}

		Sleep(10);
	}
}
void MOUSE() {
	while (isRunning) {
		if (mousePress(VK_LBUTTON)) {
			mouseInput.isPressed = true;
		}
		if (mousePress(VK_RBUTTON)) {

		}
		if (GetAsyncKeyState(VK_Z) & 0x8000 != 0 || GetAsyncKeyState(VK_NUMPAD0) & 0x8000 != 0)
		{
			z = 0;
		}
		if (Tron == GAME) {
			do {
				Sleep(10);
			} while ((GetAsyncKeyState(VK_R) & 0x8000 != 0) || (GetAsyncKeyState(VK_M) & 0x8000 != 0) || (GetAsyncKeyState(VK_N) & 0x8000 != 0));

		}
		if (Tron == END) {
			if (GetAsyncKeyState(VK_R) & 0x8000 != 0) {
				changeStates = true;
				Tron = GAME;
			}
			else if (GetAsyncKeyState(VK_M) & 0x8000 != 0) {
				changeStates = true;
				Tron = START_MENU;
			}
			else if (GetAsyncKeyState(VK_N) & 0x8000 != 0) {
				isRunning = false;
			}
		}
		Sleep(15);
	}
}
void TRON() {
	gr_Start(GrDriver, GrMode, ErrorCode);
	int maxX = getmaxx();
	int maxY = getmaxy();
	int unitSize = 9;

	int row = maxY / (unitSize + 1);
	int col = maxX / (unitSize + 1);
	grid = new char *[row];
	for (int i = 0; i < row; i++) {
		grid[i] = new char[col];
		for (int j = 0; j < col; j++) {
			grid[i][j] = '0';
		}
	}
	// grid [row][col]

	int P1Score = 0;
	int P2Score = 0;
	BUTTON start, end;
	WIN P1, P2;
	cout << boolalpha; /// prints out true and false as bool vars
	resetListeners();
	///{START_MENU, PLAYER1, PLAYER2, GAME, END};
	BUTTON endTitleScreen;
	BUTTON options;
	BUTTON slowSpeed;
	BUTTON normalSpeed;
	BUTTON soupaSonicSpeed;
	BUTTON restart;
	BUTTON mainMenu;
	BUTTON controls;
	BUTTON back;
	BUTTON player2controls;
	BUTTON player1controls;
	BUTTON scoreboard;
	BUTTON player1Scoreboard;
	BUTTON player2Scoreboard;
	BUTTON normalMap;
	BUTTON helloKitty;
	BUTTON tundra;
	BUTTON desert;

	while (isRunning) {

		switch (Tron) {

		case START_MENU:
			if (changeStates) {
				setColorPallet();
				cleardevice();
				///BUTTON 1 START GAME BUTTON
			
				int top, left, bottom, right;
				top = (maxY / 1) / 3.45;
				bottom = maxY / 5;
				left = ((maxX / 2) / 2.32) / 2;
				bottom = bottom - top;
				top = ((maxY - title_Height) / 3) + title_Height;
				bottom = top + bottom;
				right = maxX - left +200;
				start.init(left, top, right, bottom);
				start.render(2);
				//setbkcolor(15);
				setcolor(WHITE);
			
				
				
				//setcolor(2);
				settextstyle(3, 0, 7);
				outtextxy((right + left -58 - textwidth("START                                                                         ")) / 2 + left, ( bottom - top- textheight("START                                                                         ")) / 2 + top, "START                                                                          ");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);

				///BUTTON 2 OPTIONS BUTTON
				int top1, left1, bottom1, right1;
				top1 = (maxY / 25) / 2; // Length to the Right
				bottom1 = maxY / .666 ; // Length to the Left
				left1 = ((maxX / 2.4) / 1.40) / 1; // Height going Up
				bottom1 = (bottom1 - top1); // Thickness Left to Right
				top1 = ((maxY - title_Height) / 11) + title_Height; // Left or Right
				bottom1 = (top1 + bottom1 + 200); // Thickness Left to Right
				right1 = (maxX - left1)/2.8; // Height going Down
				options.init(top1, left1, bottom1, right1);
				options.render(9);
				//setbkcolor(9);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((bottom1 + top1 -50 - textwidth("OPTIONS                                                                     ")) / 2 + top1, (right1 - left1 - textheight("OPTIONS                                                                    ")) / 2 + left1, "OPTIONS                                                                     ");
				//putpixel(0, 0, 0); 
				//setbkcolor(BLACK);
				
				///BUTTON 3 CONTROLS BUTTON
				int top2, left2, bottom2, right2;
				top2 = (maxY / 25) / 2; // Length to the Right
				bottom2 = maxY / .666; // Length to the Left
				left2 =((maxX / 1.92) / 1.40); // Height going Up
				bottom2 = (bottom2 - top2); // Thickness Left to Right
				top2 = ((maxY - title_Height) / 11) + title_Height; // Left or Right
				bottom2 = (top2 + bottom2 +200); // Thickness Left to Right
				right2 = (maxX - left2) / 1.92; // Height going Down
				controls.init(top2, left2, bottom2, right2);
				controls.render(5);
				//setbkcolor(8);
				setcolor(WHITE);

				settextstyle(3, 0, 7);
				outtextxy((bottom2 + top2 +39 - textwidth("CONTROLS                                                                     ")) /2 + top2, (right2 - left2 - textheight("CONTROLS                                                                     ") )/ 2 + left2, "CONTROLS                                                                     ");
				drawTitle((maxX - title_Width) / 10, (maxY - title_Height) / 8);
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);
			
				
				///BUTTON 10 END GAME BUTTON
				int top9, left9, bottom9, right9;
				top9 = (maxY / 1) / 3.45;
				bottom9 = maxY / 5;
				left9 = ((maxX / 2) / 2.32) / 2;
				bottom9 = bottom9 - top9;
				top9 = ((maxY - title_Height) / 1.209) + title_Height;
				bottom9 = top9 + bottom9;
				right9 = maxX - left9 + 200;
				endTitleScreen.init(left9, top9, right9, bottom9);
				endTitleScreen.render(4);
				//setbkcolor(4);
				setcolor(4);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right9 + left9 + 20 - textwidth("END GAME                                                                     ")) / 2 + left9, (bottom9 - top9 - textheight("END GAME                                                                     ")) / 2 + top9, "END GAME                                                                     ");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);

				changeStates = false;
			}
			if (mouseInput.isPressed && start.isPressed(click)) {
				s = 20; // speed
				p = 0; // primary color
				q = 8; // secondary color
				changeStates = true;
				Tron = PLAYER_1;//GAME;///
								//cout << "SWITCH STATE \n";
			}
			else if (mouseInput.isPressed && endTitleScreen.isPressed(click)) {
				isRunning = false;
			}
			else if (mouseInput.isPressed && options.isPressed(click)) {
				changeStates = true;
				Tron = OPTIONS;
			}
			else if (mouseInput.isPressed && controls.isPressed(click)) {
				changeStates = true;
				Tron = CONTROLS;
			}
			resetListeners();
			break;

		case PLAYER_1:
			if (changeStates) {
				selectColor = false;
				finalizeColor = false;
				cleardevice();
				drawPLAYER(1);
			}

			changeStates = checkPLAYER(1);
			resetListeners();
			break;

		case PLAYER_2:
			if (changeStates) {
				selectColor = false;
				finalizeColor = false;
				cleardevice();
				drawPLAYER(2);
			}
			changeStates = checkPLAYER(2);
			resetListeners();
			break;

		case CONTROLS:
			if (changeStates) {
				setColorPallet();
				cleardevice();
			///BUTTON PLAYER 1 CONTROLS TEXTBOX
			int top10, left10, bottom10, right10;
			top10 = (maxY / 1) / 3.45;
			bottom10 = maxY / 5;
			left10 = ((maxX / 2) / 2.32) / 2;
			bottom10 = bottom10 - top10;
			top10 = ((maxY - title_Height) / 11) + title_Height;
			bottom10 = top10 + bottom10;
			right10 = maxX - left10;
			int RESIZE3 = 500;
			player1controls.init(left10 + RESIZE3, top10, right10 - RESIZE3, bottom10);
			player1controls.render(15);
			//setbkcolor(15);
			setcolor(WHITE);
			settextstyle(3, 0, 6);
			outtextxy((right10 - left10 - textwidth("PLAYER 1")) / 2 + left10, (bottom10 - top10 - textheight("PLAYER 1")) / 2 + top10, "PLAYER 1");
			outtextxy((right10 - left10 - textwidth("MOVEMENT: W,A,S,D")) / 2 + left10, (bottom10 - top10 - textheight("MOVEMENT: W,A,S,D")) / 2 + top10 + 100, "MOVEMENT: W,A,S,D");
			outtextxy((right10 - left10 - textwidth("START GAME: Z")) / 2 + left10, (bottom10 - top10 - textheight("START GAME: Z")) / 2 + top10 + 170, "START GAME: Z");


			///BUTTON 12 PLAYER 2 CONTROLS TEXTBOX
			int top11, left11, bottom11, right11;
			top11 = (maxY / 1) / 3.45;
			bottom11 = maxY / 5;
			left11 = ((maxX / 2) / 2.32) / 2;
			bottom11 = bottom11 - top11;
			top11 = ((maxY - title_Height) / 2.6) + title_Height;
			bottom11 = top11 + bottom11;
			right11 = maxX - left11;
			int RESIZE1 = 500;
			player2controls.init(left11 + RESIZE1, top11, right11 - RESIZE1, bottom11);
			player2controls.render(15);
			//setbkcolor(15);
			setcolor(WHITE);
			settextstyle(3, 0, 6);
			outtextxy((right11 - left11 - textwidth("PLAYER 2")) / 2 + left11, (bottom11 - top11 - textheight("PLAYER 2")) / 2 + top11, "PLAYER 2");
			outtextxy((right11 - left11 - textwidth("MOVEMENT: ARROW KEYS")) / 2 + left11, (bottom11 - top11 - textheight("MOVEMENT: ARROW KEYS")) / 2 + top11 + 100, "MOVEMENT: ARROW KEYS");
			outtextxy((right11 - left11 - textwidth("START GAME: NUMPAD 0")) / 2 + left11, (bottom11 - top11 - textheight("START GAME: NUMPAD 0")) / 2 + top11 + 170, "START GAME: NUMPAD 0");
			//setlinestyle(3, 1, 1);
			line(0, 640, 2000, 640);// SEPERATE IN GAME
			outtextxy((right11 - left11 - textwidth("RESTART GAME: R")) / 2 + left11, (bottom11 - top11 - textheight("RESTART GAME: R")) / 2 + top11 + 270, "RESTART GAME: R");
			outtextxy((right11 - left11 - textwidth("END GAME: N")) / 2 + left11, (bottom11 - top11 - textheight("END GAME: N")) / 2 + top11 + 350, "END GAME: N");
			outtextxy((right11 - left11 - textwidth("BACK OUT TO MAIN MENU: M")) / 2 + left11, (bottom11 - top11 - textheight("BACK OUT TO MAIN MENU: M")) / 2 + top11 + 420, "BACK OUT TO MAIN MENU: M");


			///BUTTON 13 BACK BUTTON
			int top12, left12, bottom12, right12;
			top12 = (maxY / 1) / 3.45;
			bottom12 = maxY / 5;
			left12 = ((maxX / 2) / 2.32) / 2;
			bottom12 = bottom12 - top12;
			top12 = ((maxY - title_Height) / 1.02) + title_Height;
			bottom12 = top12 + bottom12;
			right12 = maxX - left12;
			int RESIZE2 = 600;
			back.init(left12 + RESIZE2, top12, right12 - RESIZE2, bottom12);
			back.render(14);
			//setbkcolor(15);
			setcolor(WHITE);
			settextstyle(3, 0, 7);
			outtextxy((right12 - left12 - textwidth("BACK")) / 2 + left12, (bottom12 - top12 - textheight("BACK")) / 2 + top12, "BACK");

			changeStates = false;
			resetListeners();
			}
		if (mouseInput.isPressed && back.isPressed(click)) {
			changeStates = true;
			Tron = START_MENU;
		}
		else if (mouseInput.isPressed && player1controls.isPressed(click)) {
			changeStates = false;
		}
		else if (mouseInput.isPressed && player2controls.isPressed(click)) {
			changeStates = false;
		}
		break;

		case OPTIONS:
			if (changeStates) {
				setColorPallet();
				cleardevice();
				///BUTTON 4 SLOW SPEED
				int top3, left3, bottom3, right3;
				top3 = (maxY / 1) / 3.45;
				bottom3 = maxY / 5;
				left3 = ((maxX / 2) / 2.32) / 2;
				bottom3 = bottom3 - top3;
				top3 = ((maxY - title_Height) / 3) + title_Height;
				bottom3 = top3 + bottom3;
				right3 = maxX - left3;
				slowSpeed.init(left3, top3, right3, bottom3);
				slowSpeed.render(15);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right3 - left3 - textwidth("SLOW")) / 2 + left3, (bottom3 - top3 - textheight("SLOW")) / 2 + top3, "SLOW");
				//s = 70;
				///BUTTON 5 NORMAL SPEED
				int top4, left4, bottom4, right4;
				top4 = (maxY / 25) / 2; // Length to the Right
				bottom4 = maxY / .666; // Length to the Left
				left4 = ((maxX / 2.4) / 1.40) / 1; // Height going Up
				bottom4 = (bottom4 - top4); // Thickness Left to Right
				top4 = ((maxY - title_Height) / 11) + title_Height; // Left or Right
				bottom4 = (top4 + bottom4); // Thickness Left to Right
				right4 = (maxX - left4) / 2.8; // Height going Down
				normalSpeed.init(top4, left4, bottom4, right4);
				normalSpeed.render(9);
				//setbkcolor(9);
				setcolor(9);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((bottom4 - top4 - textwidth("NORMAL")) / 2 + top4, (right4 - left4 - textheight("NORMAL")) / 2 + left4, "NORMAL");
				//s = 20;
				///BUTTON 6 SUPERFAST SPEED
				int top5, left5, bottom5, right5;
				top5 = (maxY / 25) / 2; // Length to the Right
				bottom5 = maxY / .666; // Length to the Left
				left5 = ((maxX / 1.92) / 1.40) / 1; // Height going Up
				bottom5 = (bottom5 - top5); // Thickness Left to Right
				top5 = ((maxY - title_Height) / 11) + title_Height; // Left or Right
				bottom5 = (top5 + bottom5); // Thickness Left to Right
				right5  = (maxX - left5) / 1.92; // Height going Down
				soupaSonicSpeed.init(top5, left5, bottom5, right5);
				soupaSonicSpeed.render(8);
				//setbkcolor(8);
				setcolor(8);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((bottom5 - top5 - textwidth("SOUPASONIC")) / 2 + top5, (right5 - left5 - textheight("SOUPASONIC")) / 2 + left5, "SOUPASONIC");
				//s = 9;
				///BUTTON 14 BACK BUTTON
				int top13, left13, bottom13, right13;
				top13 = (maxY / 1) / 3.45;
				bottom13 = maxY / 5;
				left13 = ((maxX / 2) / 2.32) / 2;
				bottom13 = bottom13 - top13;
				top13 = ((maxY - title_Height) / 1.02) + title_Height;
				bottom13 = top13 + bottom13;
				right13 = maxX - left13;
				int RESIZE = 600;
				back.init(left13 + RESIZE, top13, right13 - RESIZE, bottom13);
				back.render(14);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right13 - left13 - textwidth("BACK")) / 2 + left13, (bottom13 - top13 - textheight("BACK")) / 2 + top13, "BACK");

				changeStates = false;
				resetListeners();
			}
			if (mouseInput.isPressed && slowSpeed.isPressed(click)) {
				s = 50;
				changeStates = true;
				Tron = MAPOPTIONS;
			}
			else if (mouseInput.isPressed && normalSpeed.isPressed(click)) {
				s = 20;
				changeStates = true;
				Tron = MAPOPTIONS;
			}
			else if (mouseInput.isPressed && soupaSonicSpeed.isPressed(click)) {
				s = 9;
				changeStates = true;
				Tron = MAPOPTIONS;
			}
			else if (mouseInput.isPressed && back.isPressed(click)) {
				changeStates = true;
				Tron = START_MENU;
			}
			break;


		case MAPOPTIONS:
			if (changeStates) {
				setColorPallet();
				cleardevice();
				///BUTTON 18 NORMAL MAP
				int top17, left17, bottom17, right17;
				top17 = (maxY / 1) / 3.45;
				bottom17 = maxY / 5;
				left17 = ((maxX / 2) / 2.32) / 2;
				bottom17 = bottom17 - top17;
				top17 = ((maxY - title_Height) / 4.1) + title_Height;
				bottom17 = top17 + bottom17;
				right17 = maxX - left17;
				normalMap.init(left17, top17, right17, bottom17);
				normalMap.render(15);
				//setfillstyle(1, 8);
				//setbkcolor(15);
				settextstyle(3, 0, 7);
				outtextxy((right17 - left17 - textwidth("NORMAL MAP")) / 2 + left17, (bottom17 - top17 - textheight("NORMAL MAP")) / 2 + top17, "NORMAL MAP");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);
				
				///BUTTON 19 HELLO KITTY
				int top18, left18, bottom18, right18;
				top18 = (maxY / 1) / 3.45;
				bottom18 = maxY / 5;
				left18 = ((maxX / 2) / 2.32) / 2;
				bottom18 = bottom18 - top18;
				top18 = ((maxY - title_Height) / 2.5) + title_Height;
				bottom18 = top18 + bottom18;
				right18 = maxX - left18;
				helloKitty.init(left18, top18, right18, bottom18);
				helloKitty.render(13);
				//setbkcolor(15);
				setcolor(LIGHTMAGENTA);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy(( right18 - left18 - textwidth("HELLO KITTY MAP")) / 2 + left18, (bottom18 - top18 - textheight("HELLO KITTY MAP")) / 2 + top18, "HELLO KITTY MAP");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);

				///BUTTON 20 TUNDRA
				int top19, left19, bottom19, right19;
				top19 = (maxY / 1) / 3.45;
				bottom19 = maxY / 5;
				left19 = ((maxX / 2) / 2.32) / 2;
				bottom19 = bottom19 - top19;
				top19 = ((maxY - title_Height) / 1.8) + title_Height;
				bottom19 = top19 + bottom19;
				right19 = maxX - left19;
				
				tundra.init(left19, top19, right19, bottom19);
				//setfillstyle(1,3);
				tundra.render(3);
				//setbkcolor(15);
				setcolor(3);
				setcolor(WHITE);
			
				settextstyle(3, 0, 7);
				outtextxy((right19 - left19 - textwidth("TUNDRA MAP")) / 2 + left19, (bottom19 - top19 - textheight("TUNDRA MAP")) / 2 + top19, "TUNDRA MAP");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);

				///BUTTON 24 DESERT
				int top23, left23, bottom23, right23;
				top23 = (maxY / 1) / 3.45;
				bottom23 = maxY / 5;
				left23 = ((maxX / 2) / 2.32) / 2;
				bottom23 = bottom23 - top23;
				top23 = ((maxY - title_Height) / 1.41) + title_Height;
				bottom23 = top23 + bottom23;
				right23 = maxX - left23;

				desert.init(left23, top23, right23, bottom23);
				//setfillstyle(1,3);
				desert.render(6);
				//setbkcolor(15);
				setcolor(WHITE);

				settextstyle(3, 0, 7);
				outtextxy((right23 - left23 - textwidth("DESERT MAP")) / 2 + left23, (bottom23 - top23 - textheight("DESERT MAP")) / 2 + top23, "DESERT MAP");
				//putpixel(0, 0, 0);
				//setbkcolor(BLACK);

				///BUTTON 21 BACK BUTTON
				int top13, left13, bottom13, right13;
				top13 = (maxY / 1) / 3.45;
				bottom13 = maxY / 5;
				left13 = ((maxX / 2) / 2.32) / 2;
				bottom13 = bottom13 - top13;
				top13 = ((maxY - title_Height) / 1.02) + title_Height;
				bottom13 = top13 + bottom13;
				right13 = maxX - left13;
				int RESIZE = 600;
				back.init(left13 + RESIZE, top13, right13 - RESIZE, bottom13);
				setcolor(YELLOW);
				back.render(14);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right13 - left13 - textwidth("BACK")) / 2 + left13, (bottom13 - top13 - textheight("BACK")) / 2 + top13, "BACK");

				changeStates = false;
				resetListeners();
			}
			if (mouseInput.isPressed && normalMap.isPressed(click)) {
				p = 0;
				q = 8;
				changeStates = true;
				Tron = PLAYER_1;//GAME;///
								//cout << "SWITCH STATE \n";
			}
			else if (mouseInput.isPressed && helloKitty.isPressed(click)) {
				setlinestyle(3, 1, 1);
				p = 13;
				q = 15;
				changeStates = true;
				Tron = PLAYER_1;
			}
			else if (mouseInput.isPressed && tundra.isPressed(click)) {
				setlinestyle(3, 1, 1);
				p = 3;
				q = 15;
				changeStates = true;
				Tron = PLAYER_1;
			}
			else if (mouseInput.isPressed && desert.isPressed(click)) {
				setlinestyle(3, 1, 1);
				p = 6;
				q = 14;
				changeStates = true;
				Tron = PLAYER_1;
			}
			else if (mouseInput.isPressed && back.isPressed(click)) {
				changeStates = true;
				Tron = OPTIONS;
			}
			break;

		case GAME:
			if (changeStates) {
				drawGrid(unitSize, maxX, maxY, p , q);
				playerInput1.move = RIGHT;
				playerInput2.move = LEFT;
				readyPlayer1.init((row / 2), 10, unitSize, &playerInput1, readyPlayer1.color, row, col);
				readyPlayer2.init((row / 2), (col - 10), unitSize, &playerInput2, readyPlayer2.color, row, col);
				changeStates = false;
				int count = 0;
				z = 1000;
				while (count !=  z) {
					Sleep(10);
				}
			}

			readyPlayer1.tick();
			readyPlayer2.tick();
			P1 = readyPlayer1.collide(readyPlayer2);
			P2 = readyPlayer2.collide(readyPlayer1);
			if (P1 != CONT || P2 != CONT) {

				if (P1 == P2) {
					P1 = P2 = TIE;
				}
				changeStates = true;
				Tron = END;
				
			}
			else {
				readyPlayer1.render();
				readyPlayer2.render();

			}
			resetListeners();
			break;

		case END:
			if (changeStates) {
				///BUTTON 7 MAIN MENU BUTTON
				int top6, left6, bottom6, right6;
				top6 = (maxY / 1) / 3.45;
				bottom6 = maxY / 5;
				left6 = ((maxX / 2) / 2.32) / 2;
				bottom6 = bottom6 - top6;
				top6 = ((maxY - title_Height) / 2) + title_Height;
				bottom6 = top6 + bottom6;
				right6 = maxX - left6;
				mainMenu.init(left6, top6, right6, bottom6);
				mainMenu.render(2);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right6 - left6 - textwidth("MAIN MENU (M)")) / 2 + left6, (bottom6 - top6 - textheight("MAIN MENU (M)")) / 2 + top6, "MAIN MENU (M)");
				/// BUTTON 8 END GAME BUTTON
				int top7, left7, bottom7, right7;
				top7 = (maxY / 1) / 3.45;
				bottom7 = maxY / 5;
				left7 = ((maxX / 2) / 2.32) / 2;
				bottom7 = bottom7 - top7;
				top7 = ((maxY - title_Height) / 1.537) + title_Height;
				bottom7 = top7 + bottom7;
				right7 = maxX - left7;
				end.init(left7, top7, right7, bottom7);
				end.render(4);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right7 - left7 - textwidth("END GAME (N)")) / 2 + left7, (bottom7 - top7 - textheight("END GAME (N)")) / 2 + top7, "END GAME (N)");
				setbkcolor(BLACK);

				///BUTTON 9 RESTART GAME BUTTON
				int top8, left8, bottom8, right8;
				top8 = (maxY / 1) / 3.45;
				bottom8 = maxY / 5;
				left8 = ((maxX / 2) / 2.32) / 2;
				bottom8 = bottom8 - top8;
				top8 = ((maxY - title_Height) / 1.25) + title_Height;
				bottom8 = top8 + bottom8;
				right8 = maxX - left8;
				restart.init(left8, top8, right8, bottom8);
				restart.render(15);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right8 - left8 - textwidth("RESTART (R)")) / 2 + left8, (bottom8 - top8 - textheight("RESTART (R)")) / 2 + top8, "RESTART (R)");

				///BUTTON 15 SCOREBOARD 
				int top14, left14, bottom14, right14;
				top14 = (maxY / 1) / 2;
				bottom14 = maxY / 5;
				left14 = ((maxX / 2) / 2.32) / 2;
				bottom14 = bottom14 - top14;
				top14 = ((maxY - title_Height) / 4.3) + title_Height;
				bottom14 = top14 + bottom14;
				right14 = maxX - left14;
				scoreboard.init(left14, top14, right14, bottom14);
				scoreboard.render(15);
				//setbkcolor(15);
				setcolor(WHITE);
				settextstyle(3, 0, 7);
				outtextxy((right14 - left14 - textwidth("SCORE")) / 2 + left14, (bottom14 - top14 - textheight("SCORE")) / 2 + top14, "SCORE");

				///BUTTON 16 SCOREBOARD PLAYER 2
				int top15, left15, bottom15, right15;
				top15 = (maxY / 1) / 3;
				bottom15 = maxY / 5;
				left15 = ((maxX / 2) / 1) / 2;
				bottom15 = bottom15 - top15;
				top15 = ((maxY - title_Height) / 4.3) + title_Height;
				bottom15 = top15 + bottom15;
				right15 = maxX - left15;
				player2Scoreboard.init(left15 + 700, top15 - 275, right15 + 212 , bottom15 + 100);
				player2Scoreboard.render(readyPlayer2.color);
				//setbkcolor(15);
				

				///BUTTON 17 SCOREBOARD PLAYER 1
				int top16, left16, bottom16, right16;
				top16 = (maxY / 1) / 3;
				bottom16 = maxY / 5;
				left16 = ((maxX / 2) / 1) / 2;
				bottom16 = bottom16 - top16;
				top16 = ((maxY - title_Height) / 4.3) + title_Height;
				bottom16 = top16 + bottom16;
				right16 = maxX - left16;
				player1Scoreboard.init(left16 - 212 , top16 -275, right16 - 700, bottom16 +100 );
				player1Scoreboard.render(readyPlayer1.color);
				//setbkcolor(15);
				
				mouseInput.reset();
				int Xs = (maxX - title_Width) / 2;
				int Ys = (maxY - title_Height) / 2;
				string GAMEOVER = "";
				if (P1 == LOSE) {
					GAMEOVER = "PLAYER 2 HAS SLAIN PLAYER 1!";
					P2Score++;
					
					//Player2((maxX - player_Width) / 2, Ys - player_Height, readyPlayer2.color);
				}
				else if (P2 == LOSE) {
					GAMEOVER = "PLAYER 1 HAS SLAIN PLAYER 2!";
					P1Score++;
					//Player1((maxX - player_Width) / 2, Ys - player_Height, readyPlayer1.color);
				}
				else {
					GAMEOVER = "HOW EMBARRASSING!";
					setcolor(WHITE);
			}
				setcolor(WHITE);
				settextstyle(3, 0, 8);
				outtextxy((right15 - 1450 + left16 - textwidth("00")) / 2 + left16 - 212, (bottom16 - top16 - textheight("00")) / 2 + top16 - 97, to_string(P1Score).c_str());//Player 1 score on scoreboard

				setcolor(WHITE);
				settextstyle(3, 0, 8);
				outtextxy((right15 + left15 - textwidth("00")) / 2 + left15 - 25, (bottom15 - top15 - textheight("00")) / 2 + top15 - 97, to_string(P2Score).c_str());//Player 2 score o scoreboard


				Ys -= textheight(GAMEOVER.c_str());
					Xs = (maxX - textwidth(GAMEOVER.c_str())) / 2;
					outtextxy(Xs, Ys, GAMEOVER.c_str());
					putpixel(0, 0, CYAN);
				setcolor(BLACK);
				setbkcolor(BLACK);
				cout << GAMEOVER << "\n";
				changeStates = false;
			}

			
			if (mouseInput.isPressed && mainMenu.isPressed(click) ) {// END => START MENU
				changeStates = true;
				Tron = START_MENU;
			}
			else if (mouseInput.isPressed && restart.isPressed(click) ) {// END => GAME
				changeStates = true;
				Tron = GAME;
			}
			else if (mouseInput.isPressed && end.isPressed(click)  ) {//COMPLETELY EXIT GAME
				isRunning = false;
			}
			resetListeners();

			break;
		}
		Sleep(s);
	}
	exit(0);
}
void BACKGROUND() {
	string bkgMusic = "MortalKombat.mp3";
	string sfxCrash = "Explosion+3.mp3";
	bool game = false;
	while (isRunning) {
		while (Tron != END) {
			playSoundSFX(bkgMusic, 216000);
			game = true;
			Sleep(2);
		}
		if (Tron == END && game) {
			playSoundSFX(sfxCrash, 2000);
			game = false;
		}
		Sleep(15);
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
bool KEYBOARD1(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf1.EventType = KEY_EVENT;
		playerInput1.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				playerInput1.isHeld = true;
			}
		} 
		while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		playerInput1.isPressed = true;
		return true;
	}
	return false;

}
bool KEYBOARD2(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf2.EventType = KEY_EVENT;
		playerInput2.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				playerInput2.isHeld = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		playerInput2.isPressed = true;
		return true;
	}
	return false;
}
void playSound(string fileName, int duration) {
	if (fileName.substr(fileName.length() - 2) == "v") {
		PlaySound(TEXT(fileName.c_str()), NULL, SND_ASYNC);
		Sleep(duration);
		PlaySound(TEXT(fileName.c_str()), 0, 0);
		return;
	}
	string concat = "open " + fileName + " type mpegvideo alias MP3_Device";
	LPCSTR a = concat.c_str();
	mciSendString(a, NULL, 0, 0);

	mciSendString("play MP3_Device", NULL, 0, 0);
	Sleep(duration);
	mciSendString("stop MP3_Device", NULL, 0, 0);
	mciSendString("close MP3_Device", NULL, 0, 0);
}
void playSoundSFX(string fileName, int duration) {
	int current = 0;
	GAMESTATE stop = (Tron != END) ? END : START_MENU;

	if (fileName.substr(fileName.length() - 2) == "v") {
		PlaySound(TEXT(fileName.c_str()), NULL, SND_ASYNC);

		while (current < duration && Tron != stop) {
			current += 15;
			Sleep(15);
		}
		PlaySound(TEXT(fileName.c_str()), 0, 0);
		return;
	}
	string concat = "open " + fileName + " type mpegvideo alias MP3_Device";
	LPCSTR a = concat.c_str();
	mciSendString(a, NULL, 0, 0);

	mciSendString("play MP3_Device", NULL, 0, 0);
	while (current < duration && Tron != stop) {
		current += 15;
		Sleep(15);
	}
	mciSendString("stop MP3_Device", NULL, 0, 0);
	mciSendString("close MP3_Device", NULL, 0, 0);
}
void resetListeners() {
	playerInput1.reset();
	playerInput2.reset();
	mouseInput.reset();
}
void setColorPallet() {
	PlayerColorChoices.clear();
	PlayerColorChoices.push_back(RED); // 0
	PlayerColorChoices.push_back(BLUE); // 1
	PlayerColorChoices.push_back(DARKGRAY); // 2
	PlayerColorChoices.push_back(MAGENTA); // 3
	PlayerColorChoices.push_back(GREEN); // 4
	PlayerColorChoices.push_back(LIGHTRED); // 5
	PlayerColorChoices.push_back(YELLOW); // 6
}
void drawOptions() {
	setColorPallet();
	cleardevice();

}
void drawPLAYER(int playerNum) {
	int Xf, Xs, Xt, Yf, Ys, Yt; // Xfirst, Xsecond, Xthird (three rows)
	int padding = 25;
	selected.init(padding);
	int h = player_Height;
	Yf = (getmaxy() - ((h * 3) + (padding * 2))) / 2;
	Ys = Yf + h + padding;
	Yt = Ys + h + padding;
	Xf = (getmaxx() - 520) / 2;
	padding = (padding * 2);
	Xt = Xs = (getmaxx() - (h * 3 + (padding * 2))) / 2;

	if (playerNum == 1) {
		Player1O(Xf, Yf, CYAN);
	}
	else {
		Player2O(Xf, Yf, CYAN);
	}

	int pointX = Xs;

	for (int i = 0; i < 3; i++) {
		Playerselect[i].init(pointX, Ys, pointX + h, Ys + h);
		Playerselect[i + 3].init(pointX, Yt, pointX + h, Yt + h);
		Playerselect[i].render(PlayerColorChoices.at(i));
		Playerselect[i + 3].render(PlayerColorChoices.at(i + 3));
		pointX += h + padding;
	}

}
bool checkPLAYER(int playerNum) {

	if (mouseInput.isPressed) {
		for (int i = 0; i < 6; i++) {
			if (Playerselect[i].isPressed(click)) {
				if (selectColor) {
					if (selected.inner.isEqual(Playerselect[i])) {
						if (playerNum == 1) {
							readyPlayer1.color = PlayerColorChoices.at(i);
							PlayerColorChoices.erase(PlayerColorChoices.begin() + i);
							Tron = PLAYER_2;
							return true;
						}
						else {
							readyPlayer2.color = PlayerColorChoices.at(i);
							Tron = GAME;
							return true;
						}
					}
					else {
						selected.remove();
						selected.pick(Playerselect[i]);
						selected.draw();
					}
				}
				else {
					selectColor = true;
					selected.pick(Playerselect[i]);
					selected.draw();
				}
			}
		}
	}
	return false;
}
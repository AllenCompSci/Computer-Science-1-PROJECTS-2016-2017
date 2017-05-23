#pragma region useless stuff
#include<iostream>
#include<cmath>
#include<string>
#include<ctime>
#include<thread> // THREADS
#include<graphics.h>
#include<winbgi.cpp>
#include<Windows.h>  // CURSOR
#include <stdio.h> 
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
#include "VirtualKeys.h" // CUSTOM Virtual key list
#pragma comment(lib, "winmm.lib") // SOUND
using namespace std;
#pragma region GLOBALVARss
int GrDriver, GrMode, ErrorCode;
bool cursorVisible;
int centerX, centerY;
BOOL curVis;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HCURSOR visible, hCur1, hCur3;
POINT v;
#pragma endregion
#pragma region myvars
enum PAGE { startingscreen, playingscreen, choosemode, choosedifficulty, instructionspage, screenoftwoplayers };
enum MOH { easy, medium, hard };
enum TYPE { numbers, letters, colors };
enum PLAYERS { P1, P2 };
PLAYERS players;
MOH difficulty;
TYPE mode;
PAGE screen = startingscreen;
#pragma endregion

#pragma region Function_Prototypes
void gr_Start(int&, int&, int&); // Starts the graphics window
void getCursor(POINT &p); // uses struct POINT
bool MOUSE(int); // if mouse pressed
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
void playSound(string, int);  // sound effect
void gameThread();
void drawboard();
void startscreen();
void twoplayerscreen();
void SecondPlayer();
void timer();
#pragma endregion


INPUT_RECORD irInBuf;
struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
}global;
void timeprinter(string one, string two, string three) {

	outtextxy(120, 500, one.c_str());
	outtextxy(80, 500, two.c_str());
	outtextxy(40, 500, three.c_str());
	outtextxy(40, 490, ":");
	getpixel(0, 0);
}

void timer() {
	string yo;
	string was;
	string sup;
	int ones = 0;
	int tens = 0;
	int minutes = 0;
	setbkcolor(15);
	setcolor(8);
	settextstyle(8, 0, 8);
	outtextxy(120, 500, "0");
	outtextxy(80, 500, "0");
	outtextxy(0, 500, "0");
	outtextxy(40, 490, ":");

	while (true) {

		delay(1000);

		ones = ones + 1;
		if (ones == 10) {
			ones = ones - 10;
			tens = tens + 1;
		}
		if (tens == 6) {
			tens = tens - 6;
			minutes = minutes + 1;
		}

		std::string yo = std::to_string(ones);
		std::string was = std::to_string(tens);
		std::string sup = std::to_string(minutes);

		timeprinter(yo, was, sup);

		outtextxy(40, 490, ":");
		getpixel(0, 0);
	}

}

void instructions() {
	setbkcolor(15);
	cleardevice();

	setcolor(3);
	settextstyle(8, 0, 70);
	outtextxy(530, 62, "Instructions");
	settextstyle(8, 0, 5);
	setcolor(6);
	outtextxy(55, 220, "Sudoku is a authentic weaboo-land game meant to satisfy your OCD. Normally");
	outtextxy(20, 260, "you start with a 9x9 grid partially filled with numbers in no particular ");
	outtextxy(20, 300, "order. To make our game more interesting, we have included the same game but ");
	outtextxy(20, 340, "with letters and colors instead. Nevertheless, the game is still played");
	outtextxy(20, 380, "exactly the same. The grid is made of 9 columns, rows, and 3x3 squares.");
	outtextxy(20, 420, "Depending on the difficulty you choose, more or less squares will be pre-");
	outtextxy(20, 460, "completed upon starting the game. Your objective is to fill in all the ");
	outtextxy(20, 500, "squares so that one and only one of each number (or letter or color) is");
	outtextxy(20, 540, "present in each row, column, and 3x3 box. Good luck you nerd!");

	setcolor(9);
	settextstyle(8, 0, 9);
	outtextxy(450, 700, "RETURN TO MAIN MENU");
	getpixel(0, 0);
}
void drawboard() {

	setbkcolor(15);
	cleardevice();
	setbkcolor(0);

	setcolor(0);

	setlinestyle(2, 1, 3);

	setcolor(7);

	line(810, 55, 810, 955);
	line(1110, 55, 1110, 955);

	line(510, 355, 1410, 355);
	line(510, 655, 1410, 655);

	setlinestyle(0, 1, 1);

	line(610, 55, 610, 955);
	line(710, 55, 710, 955);
	line(910, 55, 910, 955);
	line(1010, 55, 1010, 955);
	line(1210, 55, 1210, 955);
	line(1310, 55, 1310, 955);

	line(510, 155, 1410, 155);
	line(510, 255, 1410, 255);
	line(510, 455, 1410, 455);
	line(510, 555, 1410, 555);
	line(510, 755, 1410, 755);
	line(510, 855, 1410, 855);

	setlinestyle(2, 1, 3);
	setcolor(0);
	rectangle(510, 55, 1410, 955);
	settextstyle(1, 0, 8);

	getpixel(0, 0);
	return;
}
void twoplayerscreen() {
	setbkcolor(15);
	cleardevice();

	setlinestyle(0, 1, 3);
	setcolor(7);
	line(348, 75, 348, 945);
	line(639, 75, 639, 945);
	line(57, 366, 930, 366);
	line(57, 657, 930, 657);
	line(1281, 75, 1281, 945);
	line(1572, 75, 1572, 945);
	line(990, 366, 1863, 366);
	line(990, 657, 1863, 657);


	setlinestyle(0, 1, 1);
	line(154, 75, 154, 945);
	line(251, 75, 251, 945);
	line(445, 75, 445, 945);
	line(542, 75, 542, 945);
	line(736, 75, 736, 945);
	line(833, 75, 833, 945);

	line(57, 172, 930, 172);
	line(57, 269, 930, 269);
	line(57, 463, 930, 463);
	line(57, 560, 930, 560);
	line(57, 754, 930, 754);
	line(57, 851, 930, 851);

	line(1087, 75, 1087, 945);
	line(1184, 75, 1184, 945);
	line(1378, 75, 1378, 945);
	line(1475, 75, 1475, 945);
	line(1669, 75, 1669, 945);
	line(1766, 75, 1766, 945);

	line(990, 172, 1863, 172);
	line(990, 269, 1863, 269);
	line(990, 463, 1863, 463);
	line(990, 560, 1863, 560);
	line(990, 754, 1863, 754);
	line(990, 851, 1863, 851);

	setcolor(0);
	setbkcolor(0);
	setlinestyle(0, 1, 3);

	rectangle(57, 75, 930, 948);
	rectangle(990, 75, 1863, 948);
}
void choosethedifficulty() {
	setbkcolor(15);
	cleardevice();

	setcolor(8);
	settextstyle(8, 0, 90);
	outtextxy(920, 92, "DIFFICULTY");
	outtextxy(1230, 227, "SETTINGS");


	setcolor(2);
	outtextxy(50, 250, "n00b");
	//settextstyle(3, 0, 8);
	setcolor(14);

	outtextxy(525, 500, "Goldilocks");

	setcolor(4);
	//consider 2 and 8
	settextstyle(8, 0, 7);
	outtextxy(1200, 700, "getting the group");
	outtextxy(1200, 775, "to our left");
	outtextxy(1200, 850, "to work on");
	outtextxy(1200, 925, "their project");
	setcolor(8);
	outtextxy(75, 900, "CANCEL");
	getpixel(0, 0);
}
void choosethemode() {
	setbkcolor(15);
	cleardevice();

	setcolor(8);
	settextstyle(8, 0, 70);
	outtextxy(270, 242, "choose your poison");
	setlinestyle(4, 0, 7);

	settextstyle(8, 0, 9);
	setcolor(3);
	rectangle(200, 510, 675, 560);
	outtextxy(210, 455, "#Numbers");

	setcolor(4);
	rectangle(1260, 510, 1560, 560);
	outtextxy(1270, 455, "b@B3l");

	settextstyle(8, 0, 7);
	setcolor(2);
	rectangle(730, 670, 1180, 770);
	outtextxy(780, 675, "50 Shades");
	outtextxy(770, 745, "of Sudoku");

	setcolor(8);
	outtextxy(75, 900, "CANCEL");
	getpixel(0, 0);
}
void gr_Start(int&GrDriver, int&GrMode, int&ErrorCode)
{
	//set the graphics driver
	GrDriver = VGA; //800x600
					//set graphics mode
	GrMode = VGAMAX;
	//start graphics
	initgraph(&GrDriver, &GrMode, "");
	//check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
		//getch();
		//exit(1);
	}
}

void getCursor(POINT & p) {
	while (true)
		if (GetCursorPos(&p)) {
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
			{
				do {} while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
				return;
			}

			Sleep(45);
		}
}

bool MOUSE(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = MOUSE_EVENT;
		GetCursorPos(&global.p);
		global.press = true;
		int count = 0;
		do {
			if (count++ > 1400) {
				global.hold = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}

bool KEYBOARD(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		global.press = true;
		global.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				global.hold = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}




void startscreen() {
	string tm = "®";
	setbkcolor(15);
	cleardevice();
	setbkcolor(0);
	setcolor(0);
	setbkcolor(15);
	setcolor(8);
	settextstyle(8, 0, 70);
	//outtextxy(515, 62, "S U D O K U");
	outtextxy(685, 292, "S ");
	outtextxy(780, 292, "U ");
	outtextxy(875, 292, "D ");
	outtextxy(970, 292, "O ");
	outtextxy(1065, 292, "K ");
	outtextxy(1160, 292, "U ");
	settextstyle(8, 0, 5);

	outtextxy(1240, 290, tm.c_str());

	setcolor(4);
	settextstyle(8, 0, 4);

	setcolor(4);
	rectangle(750, 440, 1175, 495);
	outtextxy(790, 475, "forever alone mode");

	setcolor(1);
	rectangle(750, 520, 1175, 570);
	outtextxy(910, 550, "suDUO");

	setcolor(2);
	rectangle(750, 590, 1175, 640);
	outtextxy(842, 620, "Instructions");
}

void playSound(string fileName, int duration) {
	//duration = 500;
	//fileName = 33CarelessWhisper;
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

void gameThread() {
	screen = startingscreen;
	startscreen();
	//while (!global.press);

	global.press = global.hold = false;
	//cleardevice();
	//setcolor(4);

	/*while (true) {

	if (global.press) {
	cleardevice();
	if (irInBuf.EventType == MOUSE_EVENT) {
	fillellipse(centerX, centerY, 100, 100);
	}
	if (irInBuf.EventType == KEY_EVENT) {
	bar(centerX - 200, centerY - 200, centerX + 200, centerY + 200);
	}
	global.press = false;
	}
	if (global.hold) {
	setcolor(rand() % 15 + 1);
	if (irInBuf.EventType == MOUSE_EVENT) {
	fillellipse(centerX, centerY, 100, 100);
	}
	if (irInBuf.EventType == KEY_EVENT) {
	bar(centerX - 200, centerY - 200, centerX + 200, centerY + 200);
	}
	if (global.VirtualKey == VK_ESCAPE) {
	return;
	}
	global.hold = false;
	}

	}

	closegraph();*/


}




#pragma endregion




void main() {
	gr_Start(GrDriver, GrMode, ErrorCode);
	srand(time(NULL));
	startscreen();

	//thread g(gameThread);
	thread t(KEY_LISTENER);
	//	thread s(playSound);
	global.press = global.hold = false;
	t.join();
	//g.join(); 
	return;
}
struct puzzle {
	// [col][row]
	int basicPuzzle[9][9]{
		7, 9, 5, 6, 2, 1, 8, 4, 3,
		1, 2, 3, 4, 8, 9, 5, 6, 7,
		6, 4, 8, 3, 7, 5, 9, 1, 2,
		8, 7, 2, 5, 1, 4, 3, 9, 6,
		9, 5, 4, 8, 3, 6, 2, 7, 1,
		3, 1, 6, 2, 9, 7, 4, 5, 8,
		4, 8, 1, 7, 5, 3, 6, 2, 9,
		2, 6, 7, 9, 4, 8, 1, 3, 5,
		5, 3, 9, 1, 6, 2, 7, 8, 4
	};
	string stringPuzzle[9][9];
	bool showNum[9][9];
	bool isFixedValue[9][9];
	string currentPuzzle[9][9];


	void swapNum() { // swapping two random sets of numbers in the puzzle (ex. all the 2s become 7s, all 7s become 2s)
		int firstNum;
		int endNum;
		int repeatNum;

		repeatNum = rand() % 30 + 10; //the number of times that the swapping occurs
		for (int a = 0; a < repeatNum; a++) {
			do {
				firstNum = rand() % 9 + 1;
				endNum = rand() % 9 + 1;
			} while (firstNum == endNum); // want to generate 2 different random numbers

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (basicPuzzle[i][j] == firstNum) {
						basicPuzzle[i][j] = endNum;
					}
					else if (basicPuzzle[i][j] == endNum) {
						basicPuzzle[i][j] = firstNum; // numbers swapped
					}

				}
			}


		}
		return;
	}


	void swapCol() {// swapping two cols
		int firstCol;
		int endCol;
		int repeatCol;
		repeatCol = rand() % 10 + 30;
		for (int a = 0; a < repeatCol; a++) {
			do {
				firstCol = rand() % 9;
				endCol = rand() % 9;

			} while (firstCol / 3 != endCol / 3); // check to make sure they are in same block

			for (int i = 0; i < 9; i++) { // i=column num
				int temp = basicPuzzle[i][firstCol];
				basicPuzzle[i][firstCol] = basicPuzzle[i][endCol];
				basicPuzzle[i][endCol] = temp;
			}


		}
		return;
	}

	void swapRow() {
		int firstRow;
		int endRow;
		int repeatRow;
		repeatRow = rand() % 30 + 10;
		for (int a = 0; a < repeatRow; a++) {
			do {
				firstRow = rand() % 9;
				endRow = rand() % 9;
			} while (firstRow / 3 != endRow / 3);
			for (int i = 0; i < 9; i++) { // 
				int temp1 = basicPuzzle[firstRow][i];
				basicPuzzle[firstRow][i] = basicPuzzle[endRow][i];
				basicPuzzle[endRow][i] = temp1;

			}
		}
		return;

	}

	void convertToLetter() {// for medium level
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				basicPuzzle[i][j] += 96; // to cast to char (a =1=97, b=2=98)

			}
		}

	}
	void setValE() { // sets each position to either true or false (easy)
		int randxE[43];
		int randyE[43];
		for (int i = 0; i < 43; i++) { // 43 rand points not shown
			randxE[i] = rand() % 9;
			randyE[i] = rand() % 9;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
			{
				showNum[i][j] = true;
				isFixedValue[i][j] = true;// sets all to true by defalut
			}
		}
		for (int j = 0; j < 43; j++) {
			if (showNum[randxE[j]][randyE[j]] == false) { // if already false
				randxE[j] = rand() % 9; // makes new rand nums
				randyE[j] = rand() % 9;
				j--; // step back
			}
			else {
				showNum[randxE[j]][randyE[j]] = false;
				isFixedValue[randxE[j]][randyE[j]] = false;// sets others to false
			}
		}


	} // easy level
	void setValM() { // medium
		int randxM[58];
		int randyM[58];
		for (int i = 0; i < 58; i++) { // 58 rand points not shown
			randxM[i] = rand() % 9;
			randyM[i] = rand() % 9;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
			{
				showNum[i][j] = true;
				isFixedValue[i][j] = true;// sets all to true by defalut
			}
		}
		for (int j = 0; j < 58; j++) {
			if (showNum[randxM[j]][randyM[j]] == false) { // if already false
				randxM[j] = rand() % 9; // makes new rand nums
				randyM[j] = rand() % 9;
				j--; // step back
			}
			else {
				showNum[randxM[j]][randyM[j]] = false;
				isFixedValue[randxM[j]][randyM[j]] = false;// sets others to false
			}
		}


	}
	void setValH() { // hard

		int randxH[57];
		int randyH[57];
		for (int i = 0; i < 57; i++) { // 57 rand points not shown
			randxH[i] = rand() % 9;
			randyH[i] = rand() % 9;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
			{
				showNum[i][j] = true;
				isFixedValue[i][j] = true;// sets all to true by defalut
			}
		}
		for (int j = 0; j < 57; j++) {
			if (showNum[randxH[j]][randyH[j]] == false) { // if already false
				randxH[j] = rand() % 9; // makes new rand nums
				randyH[j] = rand() % 9;
				j--; // step back
			}
			else {
				showNum[randxH[j]][randyH[j]] = false;
				isFixedValue[randxH[j]][randyH[j]] = false;// sets others to false
			}
		}


	}
	bool returnVal(int i, int j) {	// returns true or false for each position		
		return showNum[i][j];
	}
	void drawBoard() { // draws sudoku board on graphics window

		setbkcolor(15);
		cleardevice();
		setbkcolor(0);

		setcolor(0);

		setlinestyle(2, 1, 3);

		setcolor(8);
		// horizontal block lines
		line(810, 55, 810, 955);
		line(1110, 55, 1110, 955);


		// vertical block lines
		line(510, 355, 1410, 355);
		line(510, 655, 1410, 655);


		setlinestyle(0, 1, 1);

		// internal vert lines
		line(610, 55, 610, 955);
		line(710, 55, 710, 955);
		line(910, 55, 910, 955);
		line(1010, 55, 1010, 955);
		line(1210, 55, 1210, 955);
		line(1310, 55, 1310, 955);

		// internal hor lines
		line(510, 155, 1410, 155);
		line(510, 255, 1410, 255);
		line(510, 455, 1410, 455);
		line(510, 555, 1410, 555);
		line(510, 755, 1410, 755);
		line(510, 855, 1410, 855);

		setlinestyle(2, 1, 3);
		setcolor(0);

		// outer box
		rectangle(510, 55, 1410, 955);



		settextstyle(3, 0, 8);
		return;
	}
	void twoplayerscreen() {
		setbkcolor(15);
		cleardevice();

		setlinestyle(0, 1, 3);
		setcolor(7);
		line(348, 75, 348, 945);
		line(639, 75, 639, 945);

		line(57, 366, 930, 366);
		line(57, 657, 930, 657);
		line(1281, 75, 1281, 945);
		line(1572, 75, 1572, 945);
		line(990, 366, 1863, 366);
		line(990, 657, 1863, 657);

		// internal vert lines
		setlinestyle(0, 1, 1);
		line(154, 75, 154, 945);
		line(251, 75, 251, 945);
		line(445, 75, 445, 945);
		line(542, 75, 542, 945);
		line(736, 75, 736, 945);
		line(833, 75, 833, 945);
		//internal hor lines
		line(57, 172, 930, 172);
		line(57, 269, 930, 269);
		line(57, 463, 930, 463);
		line(57, 560, 930, 560);
		line(57, 754, 930, 754);
		line(57, 851, 930, 851);

		line(1087, 75, 1087, 945);
		line(1184, 75, 1184, 945);
		line(1378, 75, 1378, 945);
		line(1475, 75, 1475, 945);
		line(1669, 75, 1669, 945);
		line(1766, 75, 1766, 945);

		line(990, 172, 1863, 172);
		line(990, 269, 1863, 269);
		line(990, 463, 1863, 463);
		line(990, 560, 1863, 560);
		line(990, 754, 1863, 754);
		line(990, 851, 1863, 851);

		setcolor(0);
		setbkcolor(0);
		setlinestyle(0, 1, 3);

		rectangle(57, 75, 930, 948);
		rectangle(990, 75, 1863, 948);
	}
	int nubL(int x) {
		return log10(x) + 1;
	};
	string convertToString(int x) {// converts int to string (Brock's code)
		string nuber;
		int digit[10];
		int run = x;
		bool negative = false;
		if (x == 0) {
			return "0";
		}
		if (x < 0) {
			run = abs(x);
			negative = true;
		}
		int length = nubL(run);
		digit[0] = run % 10;
		for (int i = 0; i < length; i++) {
			int power = pow(10, (2 + i));
			digit[i + 1] = ((run % power) - digit[i]) / (power / 10);
		};
		for (int i = 0; i < length; i++) {
			nuber = (char)(digit[i] + 48) + nuber;
		};
		if (negative) {
			nuber = '-' + nuber;
		}
		return nuber;
	}
	void convertPuzzle() { //converts each position to a string and draws
		setbkcolor(15);
		setcolor(8);
		settextstyle(10, 0, 8);
		int xshift = 0;
		int yshift = 0;
		for (int i = 0; i < 9; i++) {
			xshift = 0;
			if (i != 0) {
				yshift += 100;
			}
			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = convertToString(basicPuzzle[i][j]);
				if (returnVal(i, j)) {

					outtextxy(537 + xshift, 64 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 100;

			}

		}
		return;
	}
	void convertPuzzleTwoP() {
		setbkcolor(15);
		setcolor(8);
		settextstyle(10, 0, 8);
		int xshift = 0;
		int yshift = 0;
		for (int i = 0; i < 9; i++) { // first board
			xshift = 0;
			if (i != 0) {

				yshift += 97;


			}
			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = convertToString(basicPuzzle[i][j]);
				if (returnVal(i, j)) {

					outtextxy(84 + xshift, 77 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 97;

			}

		}
		xshift = 0;
		yshift = 0;
		for (int i = 0; i < 9; i++) { //second board
			xshift = 0;

			if (i != 0) {
				yshift += 97;
			}
			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = convertToString(basicPuzzle[i][j]);
				if (returnVal(i, j)) {

					outtextxy(1017 + xshift, 77 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 97;

			}

		}

		return;

	}
	void convertPuzzleLetterTwo() {
		setbkcolor(15);
		setcolor(8);
		settextstyle(10, 0, 8);
		int xshift = 0;
		int yshift = 0;
		for (int i = 0; i < 9; i++) { // first board
			xshift = 0;
			if (i != 0) {

				yshift += 97;


			}
			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = (char)basicPuzzle[i][j];
				if (returnVal(i, j)) {

					outtextxy(84 + xshift, 77 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 97;

			}

		}
		xshift = 0;
		yshift = 0;
		for (int i = 0; i < 9; i++) { //second board
			xshift = 0;

			if (i != 0) {
				yshift += 97;
			}
			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = (char)(basicPuzzle[i][j]);
				if (returnVal(i, j)) {

					outtextxy(1017 + xshift, 77 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 97;

			}

		}

		return;
	}
	void convertPuzzleLetter() { //converts each position to a string and draws for letter puzzles
		setbkcolor(15);
		setcolor(8);

		settextstyle(10, 0, 8);

		int xshift = 0;
		int yshift = 0;
		for (int i = 0; i < 9; i++) {
			xshift = 0;
			if (i != 0) {
				yshift += 100;
			}

			for (int j = 0; j < 9; j++) {
				stringPuzzle[i][j] = (char)basicPuzzle[i][j];
				if (returnVal(i, j)) {

					outtextxy(536 + xshift, 63 + yshift, stringPuzzle[i][j].c_str());

				}

				xshift += 100;

			}

		}
		return;
	}
	void convertToColor() { // for color mode. Colors are blue, green, cyan, red, magenta, brown, light gray, dark gray, yellow
		setbkcolor(15);
		int left = 512;
		int top = 57;
		int right = 611;
		int bottom = 156;

		for (int i = 0; i < 9; i++) {
			left = 512;
			right = 611;
			if (i != 0) {
				top = bottom;
				bottom += 100;
			}
			for (int j = 0; j < 9; j++) {

				if (returnVal(i, j)) {
					if (basicPuzzle[i][j] == 9) {
						setcolor(YELLOW);
					}
					else {
						setcolor(basicPuzzle[i][j]);
					}

					bar(left, top, right, bottom);

				}
				left = right + 1;
				right += 100;
			}
		}
	}
	void convertToColorTwo() {
		setbkcolor(15);
		int left = 63;

		int top = 78;
		int right = 152;
		int bottom = 170;

		for (int i = 0; i < 9; i++) {
			left = 60;
			right = 152;
			if (i != 0) {
				top = bottom;
				bottom += 97;
			}
			for (int j = 0; j < 9; j++) {

				if (returnVal(i, j)) {
					if (basicPuzzle[i][j] == 9) {
						setcolor(YELLOW);
					}
					else {
						setcolor(basicPuzzle[i][j]);
					}

					bar(left, top, right, bottom);

				}
				left = right + 1;
				right += 97;
			}
		}
		left = 993;

		top = 78;
		right = 1085;
		bottom = 170;

		for (int i = 0; i < 9; i++) {
			left = 993;
			right = 1085;
			if (i != 0) {
				top = bottom;
				bottom += 97;
			}
			for (int j = 0; j < 9; j++) {

				if (returnVal(i, j)) {
					if (basicPuzzle[i][j] == 9) {
						setcolor(YELLOW);
					}
					else {
						setcolor(basicPuzzle[i][j]);
					}

					bar(left, top, right, bottom);

				}
				left = right + 1;
				right += 97;
			}
		}
	}
	void colorReference() { // shows user the 9 possible colors
							/*int currentColor = 49;
							int currTop = 45;
							int currBottom = 135;
							int currentNumber = 1;

							for (int i = 0; i < 9; i++) {
							if (i != 8) {
							setcolor(currentColor);
							}
							else {
							setcolor(YELLOW);
							}
							//bar(1600, currTop, 1690, currBottom);
							outtextxy(1720, currTop, convertToString(currentNumber).c_str());
							setbkcolor(15);
							setcolor(8);

							//setcolor(currentColor);
							if (currentColor != 8) {
							currentColor++;

							}
							else {
							currentColor += 6; // for yellow
							}
							currTop = currBottom + 15;
							currBottom += 105;
							currentNumber++;
							}*/


		setcolor(4);
		bar(1600, 45, 1690, 135);
		setcolor(5);
		bar(1600, 150, 1690, 240);
		setcolor(14);
		bar(1600, 255, 1690, 345);
		setcolor(2);
		bar(1600, 360, 1690, 450);
		setcolor(3);
		bar(1600, 465, 1690, 555);
		setcolor(1);
		bar(1600, 570, 1690, 660);
		setcolor(6);
		bar(1600, 675, 1690, 765);
		setcolor(7);
		bar(1600, 780, 1690, 870);
		setcolor(8);
		bar(1600, 885, 1690, 975);
	}

	void selSquare(int mode, int level) {// draws magenta selection square, moves it around in response to key press
		bool entered;
		int left = 613;

		int top = 58;
		int right = 707;
		int bottom = 152;
		int count = 0;
		int limit;
		int penalty = 0; // number of wrong tries
		signed int shifterR = 100;
		signed int shifterL = 100;
		signed int shifterT = 100;
		signed int shifterB = 100;
		if (level == 0) {// easy
			limit = 43;
		}
		else if (level == 1) {// medium
			limit = 58;
		}
		else {
			limit = 57;
		}
		while (count <limit) { // while the user is still playing the game
			settextstyle(8, 0, 8);

			shifterR = 100;
			shifterL = 100;
			shifterT = 100;
			shifterB = 100;

			if (KEYBOARD(VK_LEFT)) {
				if (left != 513) {
					shifterR = -100;
					shifterL = -100;
					right += shifterR;
					left += shifterL;
					shifterT = 0;
					shifterB = 0;


				}
			}
			else if (KEYBOARD(VK_RIGHT)) {
				if (right != 1407) {
					shifterR = 100;
					shifterL = 100;
					right += shifterR;
					left += shifterL;
					shifterT = 0;
					shifterB = 0;

				}
			}

			else if (KEYBOARD(VK_UP)) {
				if (top != 58) {
					shifterT = -100;
					shifterB = -100;
					top += shifterT;
					bottom += shifterB;
					shifterR = 0;
					shifterL = 0;


				}
			}
			else if (KEYBOARD(VK_DOWN)) {
				if (bottom != 952) {
					shifterT = 100;
					shifterB = 100;
					top += shifterT;
					bottom += shifterB;
					shifterR = 0;
					shifterL = 0;

				}
			}
			entered = true;
			if (mode == 0) {// numbers 
				if (KEYBOARD(VK_1)) { // these are the entry checks

					if (!(isFixedValue[(top - 58) / 100][(left - 513) / 100])) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "1";
						outtextxy(left + 23, top + 10, "1");
					}
				}
				else if (KEYBOARD(VK_2)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "2";
						outtextxy(left + 23, top + 10, "2");
					}
				}
				else if (KEYBOARD(VK_3)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "3";
						outtextxy(left + 23, top + 10, "3");
					}
				}
				else if (KEYBOARD(VK_4)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "4";
						outtextxy(left + 23, top + 10, "4");
					}
				}
				else if (KEYBOARD(VK_5)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "5";
						outtextxy(left + 23, top + 10, "5");
					}
				}
				else if (KEYBOARD(VK_6)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "6";
						outtextxy(left + 23, top + 10, "6");
					}
				}
				else if (KEYBOARD(VK_7)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "7";
						outtextxy(left + 23, top + 10, "7");
					}
				}
				else if (KEYBOARD(VK_8)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "8";
						outtextxy(left + 23, top + 10, "8");
					}
				}
				else	if (KEYBOARD(VK_9)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "9";
						outtextxy(left + 23, top + 10, "9");
					}

				}

				else {
					entered = false;
				}
			}
			else if (mode == 1) {// letters
				if (KEYBOARD(VK_A)) { // these are the entry checks

					if (!(isFixedValue[(top - 58) / 100][(left - 513) / 100])) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "a";
						outtextxy(left + 20, top, "a");
					}
				}
				else if (KEYBOARD(VK_B)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "b";
						outtextxy(left + 20, top, "b");
					}
				}
				else if (KEYBOARD(VK_C)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "c";
						outtextxy(left + 20, top, "c");
					}
				}
				else if (KEYBOARD(VK_D)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "d";
						outtextxy(left + 20, top, "d");
					}
				}
				else if (KEYBOARD(VK_E)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "e";
						outtextxy(left + 20, top, "e");
					}
				}
				else if (KEYBOARD(VK_F)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "f";
						outtextxy(left + 20, top, "f");
					}
				}
				else if (KEYBOARD(VK_G)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "g";
						outtextxy(left + 20, top, "g");
					}
				}
				else if (KEYBOARD(VK_H)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "h";
						outtextxy(left + 20, top, "h");
					}
				}
				else	if (KEYBOARD(VK_I)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "i";
						outtextxy(left + 20, top, "i");
					}

				}

				else {
					entered = false;
				}
			}
			else { //colors

				if (KEYBOARD(VK_1)) { // these are the entry checks

					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "1";
						setcolor(1);
						bar(left, top, right, bottom);
						setcolor(1);
						bar(left, top, right, bottom);
						setcolor(1);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_2)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "2";
						setcolor(2);
						bar(left, top, right, bottom);
						setcolor(2);
						bar(left, top, right, bottom);
						setcolor(2);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_3)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "3";
						setcolor(3);
						bar(left, top, right, bottom);
						setcolor(3);
						bar(left, top, right, bottom);
						setcolor(3);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_4)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "4";
						setcolor(4);
						bar(left, top, right, bottom);
						setcolor(4);
						bar(left, top, right, bottom);
						setcolor(4);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_5)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "5";
						setcolor(5);
						bar(left, top, right, bottom);
						setcolor(5);
						bar(left, top, right, bottom);
						setcolor(5);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_6)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "6";
						setcolor(6);
						bar(left, top, right, bottom);
						setcolor(6);
						bar(left, top, right, bottom);
						setcolor(6);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_7)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "7";
						setcolor(7);
						bar(left, top, right, bottom);
						setcolor(7);
						bar(left, top, right, bottom);
						setcolor(7);
						bar(left, top, right, bottom);
					}
				}
				else if (KEYBOARD(VK_8)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "8";
						setcolor(8);
						bar(left, top, right, bottom);
						setcolor(8);
						bar(left, top, right, bottom);
						setcolor(8);
						bar(left, top, right, bottom);
					}
				}
				else	if (KEYBOARD(VK_9)) {
					if (!isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
						currentPuzzle[(top - 58) / 100][(left - 513) / 100] = "9";
						setcolor(YELLOW);
						bar(left, top, right, bottom);
						setcolor(YELLOW);
						bar(left, top, right, bottom);
						setcolor(YELLOW);
						bar(left, top, right, bottom);
					}

				}

				else {
					entered = false;
				}
			}

			setcolor(getpixel(left - shifterL + 10, top - shifterT + 10)); // set color to previous square's color


			rectangle(left - shifterL, top - shifterT, right - shifterR, bottom - shifterB); // draws white or properly colored square over old one to erase it
			setcolor(13); // light magenta

			rectangle(left, top, right, bottom); // draws new selection square
			if (mode == 0) {//numbers
				if (entered && !isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
					settextstyle(0, 0, 6);
					if (currentPuzzle[(top - 58) / 100][(left - 513) / 100] != convertToString(basicPuzzle[(top - 58) / 100][(left - 513) / 100])) {


						outtextxy(25, 50, "Wrong!");
						isFixedValue[(top - 58) / 100][(left - 513) / 100] = false;
						settextstyle(8, 0, 8);
						outtextxy(left + 23, top + 10, currentPuzzle[(top - 58) / 100][(left - 513) / 100].c_str());
						penalty++;
					}
					else {
						setcolor(GREEN);
						outtextxy(25, 50, "Right!");

						isFixedValue[(top - 58) / 100][(left - 513) / 100] = true;
						settextstyle(8, 0, 8);
						outtextxy(left + 23, top + 10, currentPuzzle[(top - 58) / 100][(left - 513) / 100].c_str());
						count++;
					}
				}
			}
			else if (mode == 1) {//letters
				if (entered && !isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
					settextstyle(0, 0, 6);
					if (currentPuzzle[(top - 58) / 100][(left - 513) / 100] != stringPuzzle[(top - 58) / 100][(left - 513) / 100]) {


						outtextxy(25, 50, "Wrong!");
						isFixedValue[(top - 58) / 100][(left - 513) / 100] = false;
						settextstyle(8, 0, 8);
						outtextxy(left + 23, top + 10, currentPuzzle[(top - 58) / 100][(left - 513) / 100].c_str());
						penalty++;

					}
					else {
						setcolor(GREEN);
						outtextxy(25, 50, "Right!");

						isFixedValue[(top - 58) / 100][(left - 513) / 100] = true;
						settextstyle(8, 0, 8);
						outtextxy(left + 23, top + 10, currentPuzzle[(top - 58) / 100][(left - 513) / 100].c_str());
						count++;
					}
				}
			}
			else {//colors
				if (entered && !isFixedValue[(top - 58) / 100][(left - 513) / 100]) {
					settextstyle(0, 0, 6);
					if (currentPuzzle[(top - 58) / 100][(left - 513) / 100] != convertToString(basicPuzzle[(top - 58) / 100][(left - 513) / 100])) {


						outtextxy(25, 50, "Wrong!");
						isFixedValue[(top - 58) / 100][(left - 513) / 100] = false;
						penalty++;

					}
					else {
						setcolor(GREEN);
						outtextxy(25, 50, "Right!");

						isFixedValue[(top - 58) / 100][(left - 513) / 100] = true;
					}
				}

			}

			setbkcolor(15);
			setcolor(8);




			Sleep(10);
		}
		Sleep(1000);
		cleardevice();
		outtextxy(550, 500, "Puzzle Complete!");
		outtextxy(550, 600, convertToString(penalty).c_str());
		outtextxy(700, 600, "penalties!");
		
		outtextxy(50, 950, "Back to Main Menu");
	}

} ourPuzzle;
void selSquareTwo(int mode, int level) {


	bool entered;
	int left = 60;

	int top = 78;
	int right = 152;
	int bottom = 170;
	int count = 0;
	int limit;
	int penalty = 0; // number of wrong tries
	signed int shifterR = 97;
	signed int shifterL = 97;
	signed int shifterT = 97;
	signed int shifterB = 97;
	if (level == 0) {// easy
		limit = 43;
	}
	else if (level == 1) {// medium
		limit = 58;
	}
	else {
		limit = 57;
	}
	while (count <limit) { // while the user is still playing the game
		settextstyle(8, 0, 8);

		shifterR = 97;
		shifterL = 97;
		shifterT = 97;
		shifterB = 97;

		if (KEYBOARD(VK_LEFT)) {
			if (left != 60) {
				shifterR = -97;
				shifterL = -97;
				right += shifterR;
				left += shifterL;
				shifterT = 0;
				shifterB = 0;
				//cout << "Left: " << left;


			}
		}
		else if (KEYBOARD(VK_RIGHT)) {
			if (right != 928) {
				shifterR = 97;
				shifterL = 97;
				right += shifterR;
				left += shifterL;
				shifterT = 0;
				shifterB = 0;
				//cout << "Right" <<  right;

			}
		}

		else if (KEYBOARD(VK_UP)) {
			if (top != 78) {
				shifterT = -97;
				shifterB = -97;
				top += shifterT;
				bottom += shifterB;
				shifterR = 0;
				shifterL = 0;
				//cout << "Top" << top;

			}
		}
		else if (KEYBOARD(VK_DOWN)) {
			if (bottom != 946) {
				shifterT = 97;
				shifterB = 97;
				top += shifterT;
				bottom += shifterB;
				shifterR = 0;
				shifterL = 0;
				//cout << "Bottom" << bottom;

			}
		}
		entered = true;
		if (mode == 0) {// numbers 
			if (KEYBOARD(VK_1)) { // these are the entry checks

				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "1";
					outtextxy(left + 23, top + 10, "1");
				}
			}
			else if (KEYBOARD(VK_2)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "2";
					outtextxy(left + 23, top + 10, "2");
				}
			}
			else if (KEYBOARD(VK_3)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "3";
					outtextxy(left + 23, top + 10, "3");
				}
			}
			else if (KEYBOARD(VK_4)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "4";
					outtextxy(left + 23, top + 10, "4");
				}
			}
			else if (KEYBOARD(VK_5)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "5";
					outtextxy(left + 23, top + 10, "5");
				}
			}
			else if (KEYBOARD(VK_6)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "6";
					outtextxy(left + 23, top + 10, "6");
				}
			}
			else if (KEYBOARD(VK_7)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "7";
					outtextxy(left + 23, top + 10, "7");
				}
			}
			else if (KEYBOARD(VK_8)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "8";
					outtextxy(left + 23, top + 10, "8");
				}
			}
			else	if (KEYBOARD(VK_9)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "9";
					outtextxy(left + 23, top + 10, "9");
				}

			}

			else {
				entered = false;
			}
		}
		else if (mode == 1) {// letters
			if (KEYBOARD(VK_A)) { // these are the entry checks

				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "a";
					outtextxy(left + 20, top, "a");
				}
			}
			else if (KEYBOARD(VK_B)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "b";
					outtextxy(left + 20, top, "b");
				}
			}
			else if (KEYBOARD(VK_C)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "c";
					outtextxy(left + 20, top, "c");
				}
			}
			else if (KEYBOARD(VK_D)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "d";
					outtextxy(left + 20, top, "d");
				}
			}
			else if (KEYBOARD(VK_E)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "e";
					outtextxy(left + 20, top, "e");
				}
			}
			else if (KEYBOARD(VK_F)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "f";
					outtextxy(left + 20, top, "f");
				}
			}
			else if (KEYBOARD(VK_G)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "g";
					outtextxy(left + 20, top, "g");
				}
			}
			else if (KEYBOARD(VK_H)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "h";
					outtextxy(left + 20, top, "h");
				}
			}
			else	if (KEYBOARD(VK_I)) {
				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "i";
					outtextxy(left + 20, top, "i");
				}

			}

			else {
				entered = false;
			}
		}
		else { //colors

			if (KEYBOARD(VK_1)) { // these are the entry checks

				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "1";
					setcolor(1);
					bar(left, top, right, bottom);
					setcolor(1);
					bar(left, top, right, bottom);
					setcolor(1);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_2)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "2";
					setcolor(2);
					bar(left, top, right, bottom);
					setcolor(2);
					bar(left, top, right, bottom);
					setcolor(2);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_3)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "3";
					setcolor(3);
					bar(left, top, right, bottom);
					setcolor(3);
					bar(left, top, right, bottom);
					setcolor(3);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_4)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "4";
					setcolor(4);
					bar(left, top, right, bottom);
					setcolor(4);
					bar(left, top, right, bottom);
					setcolor(4);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_5)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "5";
					setcolor(5);
					bar(left, top, right, bottom);
					setcolor(5);
					bar(left, top, right, bottom);
					setcolor(5);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_6)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "6";
					setcolor(6);
					bar(left, top, right, bottom);
					setcolor(6);
					bar(left, top, right, bottom);
					setcolor(6);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_7)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "7";
					setcolor(7);
					bar(left, top, right, bottom);
					setcolor(7);
					bar(left, top, right, bottom);
					setcolor(7);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_8)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "8";
					setcolor(8);
					bar(left, top, right, bottom);
					setcolor(8);
					bar(left, top, right, bottom);
					setcolor(8);
					bar(left, top, right, bottom);
				}
			}
			else	if (KEYBOARD(VK_9)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] = "9";
					setcolor(YELLOW);
					bar(left, top, right, bottom);
					setcolor(YELLOW);
					bar(left, top, right, bottom);
					setcolor(YELLOW);
					bar(left, top, right, bottom);
				}

			}

			else {
				entered = false;
			}
		}

		setcolor(getpixel(left - shifterL + 10, top - shifterT + 10)); // set color to previous square's color


		rectangle(left - shifterL, top - shifterT, right - shifterR, bottom - shifterB);// draws white or properly colored square over old one to erase it
		setcolor(13); // light magenta

		rectangle(left, top, right, bottom); // draws new selection square
		if (mode == 0) {//numbers
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] != ourPuzzle.convertToString(ourPuzzle.basicPuzzle[(top - 78) / 97][(left - 60) / 97])) {


					outtextxy(25, 20, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = false;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97].c_str());
					penalty++;
				}
				else {
					setcolor(GREEN);
					outtextxy(25, 20, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = true;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97].c_str());
					count++;
				}
			}
		}
		else if (mode == 1) {//letters
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] != ourPuzzle.stringPuzzle[(top - 78) / 97][(left - 60) / 97]) {


					outtextxy(25, 20, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = false;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97].c_str());
					penalty++;

				}
				else {
					setcolor(GREEN);
					outtextxy(25, 20, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = true;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97].c_str());
					count++;
				}
			}
		}
		else {//colors
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 60) / 97] != ourPuzzle.convertToString(ourPuzzle.basicPuzzle[(top - 78) / 97][(left - 60) / 97])) {


					outtextxy(25, 20, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = false;
					penalty++;

				}
				else {
					setcolor(GREEN);
					outtextxy(25, 20, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 60) / 97] = true;
				}
			}

		}

		setbkcolor(15);
		setcolor(8);




		Sleep(10);
	}

	Sleep(1000);
	cleardevice();
	outtextxy(550, 500, "Puzzle Complete!");
	outtextxy(550, 600, ourPuzzle.convertToString(penalty).c_str());
	outtextxy(580, 600, "penalties!");
}
void selSquareThree(int mode, int level) {  // for second player
	bool entered;
	int left = 993;

	int top = 78;
	int right = 1085;
	int bottom = 170;
	int count = 0;
	int limit;
	int penalty = 0; // number of wrong tries
	signed int shifterR = 97;
	signed int shifterL = 97;
	signed int shifterT = 97;
	signed int shifterB = 97;
	if (level == 0) {// easy
		limit = 43;
	}
	else if (level == 1) {// medium
		limit = 58;
	}
	else {
		limit = 57;
	}
	while (count <limit) { // while the user is still playing the game
		settextstyle(8, 0, 8);

		shifterR = 97;
		shifterL = 97;
		shifterT = 97;
		shifterB = 97;

		if (KEYBOARD(VK_LEFT)) {
			if (left != 993) {
				shifterR = -97;
				shifterL = -97;
				right += shifterR;
				left += shifterL;
				shifterT = 0;
				shifterB = 0;
				//cout << left;


			}
		}
		else if (KEYBOARD(VK_RIGHT)) {
			if (right != 1861) {
				shifterR = 97;
				shifterL = 97;
				right += shifterR;
				left += shifterL;
				shifterT = 0;
				shifterB = 0;
				//cout << right;

			}
		}

		else if (KEYBOARD(VK_UP)) {
			if (top != 78) {
				shifterT = -97;
				shifterB = -97;
				top += shifterT;
				bottom += shifterB;
				shifterR = 0;
				shifterL = 0;
				//cout << top;

			}
		}
		else if (KEYBOARD(VK_DOWN)) {
			if (bottom != 946) {
				shifterT = 97;
				shifterB = 97;
				top += shifterT;
				bottom += shifterB;
				shifterR = 0;
				shifterL = 0;
				cout << bottom;

			}
		}
		entered = true;
		if (mode == 0) {// numbers 
			if (KEYBOARD(VK_1)) { // these are the entry checks

				if (!(ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "1";
					outtextxy(left + 23, top + 10, "1");
				}
			}
			else if (KEYBOARD(VK_2)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "2";
					outtextxy(left + 23, top + 10, "2");
				}
			}
			else if (KEYBOARD(VK_3)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "3";
					outtextxy(left + 23, top + 10, "3");
				}
			}
			else if (KEYBOARD(VK_4)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "4";
					outtextxy(left + 23, top + 10, "4");
				}
			}
			else if (KEYBOARD(VK_5)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "5";
					outtextxy(left + 23, top + 10, "5");
				}
			}
			else if (KEYBOARD(VK_6)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "6";
					outtextxy(left + 23, top + 10, "6");
				}
			}
			else if (KEYBOARD(VK_7)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "7";
					outtextxy(left + 23, top + 10, "7");
				}
			}
			else if (KEYBOARD(VK_8)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "8";
					outtextxy(left + 23, top + 10, "8");
				}
			}
			else	if (KEYBOARD(VK_9)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "9";
					outtextxy(left + 23, top + 10, "9");
				}

			}

			else {
				entered = false;
			}
		}
		else if (mode == 1) {// letters
			if (KEYBOARD(VK_A)) { // these are the entry checks

				if (!(ourPuzzle.isFixedValue[(top - 58) / 100][(left - 513) / 100])) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "a";
					outtextxy(left + 20, top, "a");
				}
			}
			else if (KEYBOARD(VK_B)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "b";
					outtextxy(left + 20, top, "b");
				}
			}
			else if (KEYBOARD(VK_C)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "c";
					outtextxy(left + 20, top, "c");
				}
			}
			else if (KEYBOARD(VK_D)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "d";
					outtextxy(left + 20, top, "d");
				}
			}
			else if (KEYBOARD(VK_E)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "e";
					outtextxy(left + 20, top, "e");
				}
			}
			else if (KEYBOARD(VK_F)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "f";
					outtextxy(left + 20, top, "f");
				}
			}
			else if (KEYBOARD(VK_G)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "g";
					outtextxy(left + 20, top, "g");
				}
			}
			else if (KEYBOARD(VK_H)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "h";
					outtextxy(left + 20, top, "h");
				}
			}
			else	if (KEYBOARD(VK_I)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "i";
					outtextxy(left + 20, top, "i");
				}

			}

			else {
				entered = false;
			}
		}
		else { //colors

			if (KEYBOARD(VK_1)) { // these are the entry checks

				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "1";
					setcolor(1);
					bar(left, top, right, bottom);
					setcolor(1);
					bar(left, top, right, bottom);
					setcolor(1);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_2)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "2";
					setcolor(2);
					bar(left, top, right, bottom);
					setcolor(2);
					bar(left, top, right, bottom);
					setcolor(2);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_3)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "3";
					setcolor(3);
					bar(left, top, right, bottom);
					setcolor(3);
					bar(left, top, right, bottom);
					setcolor(3);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_4)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "4";
					setcolor(4);
					bar(left, top, right, bottom);
					setcolor(4);
					bar(left, top, right, bottom);
					setcolor(4);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_5)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "5";
					setcolor(5);
					bar(left, top, right, bottom);
					setcolor(5);
					bar(left, top, right, bottom);
					setcolor(5);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_6)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "6";
					setcolor(6);
					bar(left, top, right, bottom);
					setcolor(6);
					bar(left, top, right, bottom);
					setcolor(6);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_7)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "7";
					setcolor(7);
					bar(left, top, right, bottom);
					setcolor(7);
					bar(left, top, right, bottom);
					setcolor(7);
					bar(left, top, right, bottom);
				}
			}
			else if (KEYBOARD(VK_8)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "8";
					setcolor(8);
					bar(left, top, right, bottom);
					setcolor(8);
					bar(left, top, right, bottom);
					setcolor(8);
					bar(left, top, right, bottom);
				}
			}
			else	if (KEYBOARD(VK_9)) {
				if (!ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
					ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] = "9";
					setcolor(YELLOW);
					bar(left, top, right, bottom);
					setcolor(YELLOW);
					bar(left, top, right, bottom);
					setcolor(YELLOW);
					bar(left, top, right, bottom);
				}

			}

			else {
				entered = false;
			}
		}

		setcolor(getpixel(left - shifterL + 10, top - shifterT + 10)); // set color to previous square's color


		rectangle(left - shifterL, top - shifterT, right - shifterR, bottom - shifterB);// draws white or properly colored square over old one to erase it
		setcolor(13); // light magenta

		rectangle(left, top, right, bottom); // draws new selection square
		if (mode == 0) {//numbers
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] != ourPuzzle.convertToString(ourPuzzle.basicPuzzle[(top - 78) / 97][(left - 993) / 97])) {


					outtextxy(1600, 20, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = false;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97].c_str());
					penalty++;
				}
				else {
					setcolor(GREEN);
					outtextxy(1600, 20, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = true;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97].c_str());
					count++;
				}
			}
		}
		else if (mode == 1) {//letters
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] != ourPuzzle.stringPuzzle[(top - 78) / 97][(left - 993) / 97]) {


					outtextxy(25, 50, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = false;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97].c_str());
					penalty++;

				}
				else {
					setcolor(GREEN);
					outtextxy(25, 50, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = true;
					settextstyle(8, 0, 8);
					outtextxy(left + 23, top + 10, ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97].c_str());
					count++;
				}
			}
		}
		else {//colors
			if (entered && !ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97]) {
				settextstyle(0, 0, 6);
				if (ourPuzzle.currentPuzzle[(top - 78) / 97][(left - 993) / 97] != ourPuzzle.convertToString(ourPuzzle.basicPuzzle[(top - 78) / 97][(left - 993) / 97])) {


					outtextxy(25, 50, "Wrong!");
					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = false;
					penalty++;

				}
				else {
					setcolor(GREEN);
					outtextxy(25, 50, "Right!");

					ourPuzzle.isFixedValue[(top - 78) / 97][(left - 993) / 97] = true;
				}
			}

		}

		setbkcolor(15);
		setcolor(8);




		Sleep(10);
	}

	Sleep(1000);
	cleardevice();
	outtextxy(550, 500, "Puzzle Complete!");
	outtextxy(550, 600, ourPuzzle.convertToString(penalty).c_str());
	outtextxy(580, 600, "penalties!");
}


void SecondPlayer() {


	hCur1 = LoadCursorFromFile("aero_link.cur");
	hCur3 = LoadCursorFromFile("Jolt-Arrow-Normal-Select.cur");
	visible = LoadCursorFromFile("Chill Working.ani");
	SetCursor(hCur1);
	cursorVisible = true;



	while (true) {

		if (KEYBOARD(VK_LEFT)) {
			cout << "Left Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_RIGHT)) {
			cout << "Right Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_UP)) {
			cout << "Up Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_DOWN)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD1)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD2)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD3)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD4)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD5)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD6)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD7)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD8)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_NUMPAD9)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}


	}

}

void KEY_LISTENER() {

	hCur1 = LoadCursorFromFile("aero_link.cur");
	hCur3 = LoadCursorFromFile("Jolt-Arrow-Normal-Select.cur");
	visible = LoadCursorFromFile("Chill Working.ani");
	SetCursor(hCur1);
	cursorVisible = true;

	while (true) {

		if (MOUSE(VK_LBUTTON)) {
			cout << "Left Button\n";
			SetCursor(visible);
			v;
			GetCursorPos(&v);
			cout << v.x << ", " << v.y << endl;

			if (v.x >= 750 && v.x <= 1175 && v.y >= 460 && v.y <= 520 && screen == startingscreen) {
				players = P1;
				screen = choosemode;
				cleardevice();
				choosethemode();
			}
			if (v.x >= 750 && v.x <= 1175 && v.y >= 540 && v.y <= 590 && screen == startingscreen) {
				players = P2;
				screen = choosemode;
				cleardevice();
				choosethemode();
			}
			if (v.x >= 750 && v.x <= 1175 && v.y >= 612 && v.y <= 667 && screen == startingscreen) {
				cleardevice();
				instructions();
				screen = instructionspage;
			}
			if (screen == instructionspage && v.x >= 455 && v.x <= 1530 && v.y >= 740 && v.y <= 800) {
				screen = startingscreen;
				cleardevice();
				startscreen();
			}
			if (screen == choosemode && v.x >= 200 && v.x <= 675 && v.y >= 500 && v.y <= 580) {
				mode = numbers;
				screen = choosedifficulty;
				cleardevice();
				choosethedifficulty();
			}
			if (screen == choosemode && v.x >= 1260 && v.x <= 1560 && v.y >= 500 && v.y <= 580) {
				mode = letters;
				screen = choosedifficulty;
				cleardevice();
				choosethedifficulty();
			}
			if (screen == choosemode && v.x >= 730 && v.x <= 1180 && v.y >= 690 && v.y <= 815) {
				mode = colors;
				screen = choosedifficulty;
				cleardevice();
				choosethedifficulty();
			}
			if ((screen == choosemode || screen == choosedifficulty) && v.x >= 40 && v.x <= 300 && v.y >= 940 && v.y <= 970) {

				screen = startingscreen;
				cleardevice();
				setlinestyle(0, 1, 1);
				startscreen();
			}

			if (screen == choosedifficulty && v.x >= 60 && v.x <= 345 && v.y >= 295 && v.y <= 372) {

				difficulty = easy;
				cleardevice();

				if (players == P2) {
					twoplayerscreen();
					ourPuzzle.swapNum();
					ourPuzzle.swapCol();
					ourPuzzle.swapRow();
					ourPuzzle.setValE();
					if (mode == numbers) {


						selSquareTwo(0, 0);

						ourPuzzle.convertPuzzleTwoP();
						setlinestyle(0, 0, 3);


					}
					if (mode == letters) {
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetterTwo();
						setlinestyle(0, 0, 3);



					}
					if (mode == colors) {
						ourPuzzle.convertToColorTwo();
						ourPuzzle.colorReference();
						setlinestyle(0, 0, 3);



					}


				}
				else {
					screen = playingscreen;
					drawboard();


					if (mode == numbers) {
						\

							ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValE();
						ourPuzzle.convertPuzzle();

						ourPuzzle.selSquare(0, 0);
					}
					if (mode == letters) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValE();
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetter();
						ourPuzzle.selSquare(1, 0);
					}
					if (mode == colors) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValE();
						ourPuzzle.convertToColor();
						ourPuzzle.colorReference();
						ourPuzzle.selSquare(2, 0);
					}

				}


			}

			if (screen == choosedifficulty && v.x >= 535 && v.x <= 1010 && v.y >= 535 && v.y <= 590) {

				difficulty = medium;
				cleardevice();

				if (players == P2) {
					twoplayerscreen();
					ourPuzzle.swapNum();
					ourPuzzle.swapCol();
					ourPuzzle.swapRow();
					ourPuzzle.setValM();
					if (mode == numbers) {




						ourPuzzle.convertPuzzleTwoP();
						setlinestyle(0, 0, 3);


					}
					if (mode == letters) {
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetterTwo();
						setlinestyle(0, 0, 3);



					}
					if (mode == colors) {
						ourPuzzle.convertToColorTwo();
						ourPuzzle.colorReference();
						setlinestyle(0, 0, 3);



					}


				}
				else {
					screen = playingscreen;
					drawboard();

					if (mode == numbers) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValM();
						ourPuzzle.convertPuzzle();
						ourPuzzle.selSquare(0, 1);
					}
					if (mode == letters) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValM();
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetter();
						ourPuzzle.selSquare(1, 1);
					}
					if (mode == colors) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValM();
						ourPuzzle.convertToColor();
						ourPuzzle.colorReference();
						ourPuzzle.selSquare(2, 1);
					}
				}


			}
			if (screen == choosedifficulty && v.x >= 1205 && v.x <= 1840 && v.y >= 733 && v.y <= 1008) {
				difficulty = hard;
				cleardevice();

				if (players == P2) {
					twoplayerscreen();
					ourPuzzle.swapNum();
					ourPuzzle.swapCol();
					ourPuzzle.swapRow();
					ourPuzzle.setValH();
					if (mode == numbers) {




						ourPuzzle.convertPuzzleTwoP();
						setlinestyle(0, 0, 3);


					}
					if (mode == letters) {
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetterTwo();
						setlinestyle(0, 0, 3);



					}
					if (mode == colors) {
						ourPuzzle.convertToColorTwo();
						ourPuzzle.colorReference();
						setlinestyle(0, 0, 3);



					}


				}

				else {
					screen = playingscreen;
					drawboard();
					ourPuzzle.swapNum();
					ourPuzzle.swapCol();
					ourPuzzle.swapRow();

					if (mode == numbers) {

						ourPuzzle.setValH();
						ourPuzzle.convertPuzzle();
						ourPuzzle.selSquare(0, 2);
					}
					if (mode == letters) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValH();
						ourPuzzle.convertToLetter();
						ourPuzzle.convertPuzzleLetter();
						ourPuzzle.selSquare(1, 2);
					}
					if (mode == colors) {
						ourPuzzle.swapNum();
						ourPuzzle.swapCol();
						ourPuzzle.swapRow();
						ourPuzzle.setValH();
						ourPuzzle.convertToColor();
						ourPuzzle.colorReference();
						ourPuzzle.selSquare(2, 2);
					}

				}


			}
			if (screen == playingscreen && v.x >= 55 && v.x <= 840 && v.y >= 990 && v.y <= 1030) {
				cleardevice();
				screen = startingscreen;
				startscreen();
			}
		}

	}

}


#include<iostream>
#include<winbgi.cpp>
#include<ctime>
#include<vector>
#include<Windows.h> // CURSOR
#include<graphics.h>
#include<cstdlib>
#include<vdmctxt.h>
#include"VirtualKeys.h"
#include<cmath>
#include<string>
#include<thread> // THREADS
#include <stdio.h> 
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND

using namespace std;

#pragma region GLOBALVARs
int /*GrDriver, GrMode,*/ ErrorCode;
bool cursorVisible;
int centerX, centerY;
char c; //ascii values
BOOL curVis;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HCURSOR visible, hCur1, hCur3;
#pragma region Function_Prototypes
//void gr_Start(int&, int&, int&); // Starts the graphics window
void getCursor(POINT &p); // uses struct POINT
bool MOUSE(int); // if mouse pressed
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
					 //void playSound(string, int);  // sound effect
					 //void gameThread();
#pragma endregion

int GrDriver = VGA;
int GrMode = VGAMAX;
int VirtualKey;
//bool cursorVisible;
//BOOL curVis;
//HCURSOR visible, hCur1, hCur3;
//void Gr_Start(int&, int&, int&); // Starts the graphics window
const int x = 0;
const int y = 0; //cartesian coordinates

INPUT_RECORD irInBuf;
struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
}global;

/* Dont need??????????????????
void main()
{

srand(time(NULL));


thread g(gameThread); // Thread definiton
thread t(KEY_LISTENER);

global.press = global.hold = false;
t.join(); // thread t start
g.join();
return;
}

*/

#pragma region Functions

//Dont know if this does something mine doesnt already do
/*
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
*/

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

void KEY_LISTENER() {

	//gr_Start(GrDriver, GrMode, ErrorCode); // initi of graphics window 
	centerX = getmaxx() / 2;
	centerY = getmaxy() / 2;
	hCur1 = LoadCursorFromFile("aero_link.cur");
	hCur3 = LoadCursorFromFile("Jolt-Arrow-Normal-Select.cur");
	visible = LoadCursorFromFile("Chill Working.ani");
	SetCursor(hCur1);

	cursorVisible = true;

	while (true) {
		if (MOUSE(VK_LBUTTON)) {
			cout << "Left Button\n";
			SetCursor(visible);
			POINT v;
			GetCursorPos(&v);
			cout << v.x << ", " << v.y << endl;
		}
		if (MOUSE(VK_RBUTTON)) {
			cout << "Right Button\n";
			SetCursor(visible);
		}
		if (MOUSE(VK_MBUTTON))
		{
			//playSound("starwars.wav", 2100);
			cout << "Mouse Wheel\n";
			SetCursor(visible);
		}
		if (MOUSE(VK_SCROLL)) {
			cout << "SCROLL \n";
		}
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
		if (KEYBOARD(VK_LSHIFT)) {
			cout << "Left Shift\n";
		}
		if (KEYBOARD(VK_RSHIFT))
		{
			cout << "Right Shift\n";
		}
		if (KEYBOARD(VK_ESCAPE)) {
			cout << "Escape Pressed\n";
			Sleep(1000);

			Sleep(500);
			return;
		}
		if (KEYBOARD(VK_RETURN))
		{
			cout << "Return Pressed\n";
		}
		if (KEYBOARD(VK_F1))
		{
			cout << "F1 Pressed \n";
			SetCursor(hCur1);

		}
		if (KEYBOARD(VK_SPACE)) {
			cout << "Spacebar Pressed \n";
		}
		if (KEYBOARD(VK_A)) {
			cout << "A Key Pressed \n";
		}
		if (KEYBOARD(VK_W)) {
			cout << "W Key Pressed \n";
		}
		if (KEYBOARD(VK_S)) {
			cout << "S Key Pressed \n";
		}
		if (KEYBOARD(VK_D)) {
			cout << "D Key Pressed \n";
		}
		if (KEYBOARD(VK_1)) {
			cout << "1 Key Pressed \n";
		}
		// Room For More Ifs specified keys act in a specific way.
		// look through the VirtualKeys.h list to have other specific keys
	}
}
// Only need if doing sound/music
/*
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
*/

//Not sure if i need this
/*
void gameThread() {

Sleep(300);

settextstyle(3, 0, 72);
setcolor(3);
moveto(300, 500);
outtext("We Begin");
while (!global.press);

global.press = global.hold = false;
cleardevice();
setcolor(4);

while (true) {

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

closegraph();


}

*/

#pragma endregion

int getch(void);

#define KEY_HOME       71

#define KEY_UP         72

#define KEY_PGUP       73

#define KEY_LEFT       75

#define KEY_CENTER     76

#define KEY_RIGHT      77

#define KEY_END        79

#define KEY_DOWN       80

#define KEY_PGDN       81

#define KEY_INSERT     82

#define KEY_DELETE     83

#define KEY_F1         59

#define KEY_F2         60

#define KEY_F3         61

#define KEY_F4         62

#define KEY_F5         63

#define KEY_F6         64

#define KEY_F7         65

#define KEY_F8         66

#define KEY_F9         67

#define KEY_SPACE      20


void outintxy(int x, int y, int value);

/*
void dog() {

int i;

char c;


for (i = 10; i <= 100; i += 10)


do{

c = (char)getch();

if (c != 0)

cout << "That is ASCII value: " << (int)c << endl;

else {   // Process one of the special keys:

c = (char)getch();

switch (c){

case KEY_HOME:    cout << "Home key." << endl; break;

case KEY_UP:      cout << "Up key." << endl; break;

case KEY_PGUP:    cout << "PgUp key." << endl; break;

case KEY_LEFT:    cout << "Left key." << endl; break;

case KEY_CENTER:  cout << "Center key." << endl; break;

case KEY_RIGHT:   cout << "Right key." << endl; break;

case KEY_END:     cout << "End key." << endl; break;

case KEY_DOWN:    cout << "Down key." << endl; break;

case KEY_PGDN:    cout << "PgDn key." << endl; break;

case KEY_INSERT:  cout << "Insert key." << endl; break;

case KEY_DELETE:  cout << "Delete key." << endl; break;

case KEY_F1:      cout << "F1 key." << endl; break;

case KEY_F2:      cout << "F2 key." << endl; break;

case KEY_F3:      cout << "F3 key." << endl; break;

case KEY_F4:      cout << "F4 key." << endl; break;

case KEY_F5:      cout << "F5 key." << endl; break;

case KEY_F6:      cout << "F6 key." << endl; break;

case KEY_F7:      cout << "F7 key." << endl; break;

case KEY_F8:      cout << "F8 key." << endl; break;

case KEY_F9:      cout << "F9 key." << endl; break;

default: cout << "Unknown extended key." << endl;

}

}

} while ((c != 'x') && (c != 'X'));



closegraph();

}

*/
void outintxy(int x, int y, int value) {

	outtextxy(x, y, to_string(value).c_str());

}

int maxX, maxY;

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
	}point;
	struct Rect {
		int x, y, h, w;
		Point TopLeft, BottomRight;
		int bColor, outline;
		void construct(int xc, int yc, int r) {
			TopLeft.init(xc - r, yc - r);
			BottomRight.init(xc + r, yc + r);
		}
		void init() {

			settextstyle((4), (0), (7));
			w = (rand() % 20) + (12 * textheight("M"));
			h = textheight("M")*2.5;
			x = (maxX - w) / 2;
			y = (maxY - h) / 2;

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
		bool intersect(Rect check) {
		}
	}rect;
};


//need to change variables to fit into code, then test and fix the following problems
void main() {
	string StringBuilder() {
		string flag = "";
		isflag = true;
		string BufferReader = "";
		int left, top, right, bottom;
		left = top = right = bottom = 0;
		int OFFSET = UNIT * 2;
		settextstyle(0, 0, 72);
		while (BufferedReader != "RETURN") {
			if (GLOBAL.isPressed) {
				BufferedReader = GLOBAL.Significance;
				if (BufferedReader != "RETURN" && BufferedReader != "Left Mouse Click"
					&& BufferedReader != "LEFT" && BufferedReader != "RIGHT"
					&& BufferedReader != "UP" && BufferedReader != "DOWN") {
					if (BufferedReader != "BACK") {
						flag += BufferedReader;
					}
					else {
						flag.substr(0,flag.length() - 1);
					}
				}

		string one = "1";
		string two = "2";
		string three = "3";
		string four = "4";
		string five = "5";
		string blank = "B";
		string flag = "f";
		string bomb = "F";
		string six = "6";
		string seven = "7";
		string eight = "8";
		string nine = "9";
		string ten = "10";
		string eleven = "11";
		string twelve = "12";
		string thirteen = "13";
		string fourteen = "14";
		string fifteen = "15";
		string sixteen = "16";
		string seventeen = "17";
		string eighteen = "18";
		string nineteen = "19";
		string twenty = "20";
		string twentyone = "21";
		string twentytwo = "22";
		string twentythree = "23";
		string twentyfour = "24";
		string twentyfive = "25";
		string twentysix = "26";
		string twentyseven = "27";
		string twentyeight = "28";
		string twentynine = "29";
		string thirty = "30";
		string thirtyone = "31";
		string thirtytwo = "32";
		string thirtythree = "33";
		string thirtyfour = "34";
		string thirtyfive = "35";
		string thirtysix = "36";
		string thirtyseven = "37";
		string thirtyeight = "38";
		string thirtynine = "39";
		string fourty = "40";
		string fourtyone = "41";
		string fourtytwo = "42";
		string fourtythree = "43";
		string fourtyfour = "44";
		string fourtyfive = "45";
		string fourtysix = "46";
		string fourtyseven = "47";
		string fourtyeight = "48";
		string fourtynine = "49";
		string fifty = "50";
		string fiftyone = "51";
		string fiftytwo = "52";
		string fiftythree = "53";
		string fiftyfour = "54";
		string fiftyfive = "55";
		string fiftysix = "56";
		string fiftyseven = "57";
		string fiftyeight = "58";
		string fiftynine = "59";
		string sixty = "60";
		string sixtyone = "61";
		string sixtytwo = "62";
		string sixtythree = "63";
		string sixtyfour = "64";
		string sixtyfive = "65";
		string sixtysix = "66";
		string sixtyseven = "67";
		string sixtyeight = "68";
		string sixtynine = "69";
		string seventy = "70";
		string seventyone = "71";
		string seventytwo = "72";
		string seventythree = "73";
		string seventyfour = "74";
		string seventyfive = "75";
		string seventysix = "76";
		string seventyseven = "77";
		string seventyeight = "78";
		string seventynine = "79";
		string eighty = "80";
		string eightyone = "81";

		srand((unsigned int)time(NULL));
		gr_Start(GrDriver, GrMode, ErrorCode);

		// Start screen ******************************************************************

		Shape startBox;
		startBox.rect.init();
		startBox.rect.render();
		startBox.rect.oL();

		string M = "M";
		setcolor(1);
		settextstyle((4), (0), (7));
		outtextxy(600, 200, M.c_str());
		putpixel(0, 0, 0);

		string i = "i";
		setcolor(2);
		settextstyle((4), (0), (7));
		outtextxy(675, 200, i.c_str());
		putpixel(0, 0, 0);

		string n = "n";
		setcolor(3);
		settextstyle((4), (0), (7));
		outtextxy(700, 200, n.c_str());
		putpixel(0, 0, 0);

		string e2 = "e";
		setcolor(4);
		settextstyle((4), (0), (7));
		outtextxy(750, 200, e2.c_str());
		putpixel(0, 0, 0);

		string s = "s";
		setcolor(5);
		settextstyle((4), (0), (7));
		outtextxy(807, 200, s.c_str());
		putpixel(0, 0, 0);

		string w = "w";
		setcolor(6);
		settextstyle((4), (0), (7));
		outtextxy(855, 200, w.c_str());
		putpixel(0, 0, 0);

		string e = "e";
		setcolor(7);
		settextstyle((4), (0), (7));
		outtextxy(926, 200, e.c_str());
		putpixel(0, 0, 0);

		string e1 = "e";
		setcolor(8);
		settextstyle((4), (0), (7));
		outtextxy(981, 200, e1.c_str());
		putpixel(0, 0, 0);

		string p = "p";
		setcolor(14);
		settextstyle((4), (0), (7));
		outtextxy(1036, 200, p.c_str());
		putpixel(0, 0, 0);

		string e3 = "e";
		setcolor(13);
		settextstyle((4), (0), (7));
		outtextxy(1091, 200, e3.c_str());
		putpixel(0, 0, 0);

		string r = "r";
		setcolor(11);
		settextstyle((4), (0), (7));
		outtextxy(1146, 200, r.c_str());
		putpixel(0, 0, 0);

		string Start = "Start";
		setcolor(15);
		settextstyle((4), (0), (7));
		outtextxy(850, 450, Start.c_str());
		putpixel(0, 0, 0);

		string instruct = "Press";
		setcolor(15);
		settextstyle((2), (0), (5));
		outtextxy(850, 200, instruct.c_str());
		putpixel(0, 0, 0);

		string instruct2 = "space";
		setcolor(15);
		settextstyle((2), (0), (5));
		outtextxy(900, 200, instruct2.c_str());
		putpixel(0, 0, 0);

		string instruct3 = "2 play";
		setcolor(15);
		settextstyle((2), (0), (5));
		outtextxy(955, 200, instruct3.c_str());
		putpixel(0, 0, 0);
	
	//dog();

	//system("pause");

	//Didnt work
	/*
	bool fish = true;
	if (fish = true) {

	if (MOUSE(VK_LBUTTON)) {
	cout << "Left Button\n";
	SetCursor(visible);
	POINT v;
	GetCursorPos(&v);
	cout << v.x << ", " << v.y << endl;
	cout << " " << GetCursorPos(&v) << endl;

	if (KEYBOARD(VK_1)) {

	setcolor(1);
	settextstyle((4), (0), (7));
	outtextxy(100, 100, one.c_str());


	}

	}

	}


	system("pause");

	*/
	bool start;

	int b;

	char c;

	c = (char)getch();
	for (b = 10; b <= 100; b += 10)

		while ((c != 'x') && (c != 'X')) {
			c = (char)getch();
			//}
			if (c != 0) {

				cout << "That is ASCII value: " << (int)c << endl;
				cleardevice();
				start = true;

			}
			if (start = true) {
				/*
				else {   // Process one of the special keys:

				c = (char)getch();

				switch (c) {

				case KEY_HOME:    cout << "Home key." << endl; break;

				case KEY_UP:      cout << "Up key." << endl; break;

				case KEY_PGUP:    cout << "PgUp key." << endl; break;

				case KEY_LEFT:    cout << "Left key." << endl; break;

				case KEY_CENTER:  cout << "Center key." << endl; break;

				case KEY_RIGHT:   cout << "Right key." << endl; break;

				case KEY_END:     cout << "End key." << endl; break;

				case KEY_DOWN:    cout << "Down key." << endl; break;

				case KEY_PGDN:    cout << "PgDn key." << endl; break;

				case KEY_INSERT:  cout << "Insert key." << endl; break;

				case KEY_DELETE:  cout << "Delete key." << endl; break;

				case KEY_F1:      cout << "F1 key." << endl; break;

				case KEY_F2:      cout << "F2 key." << endl; break;

				case KEY_F3:      cout << "F3 key." << endl; break;

				case KEY_F4:      cout << "F4 key." << endl; break;

				case KEY_F5:      cout << "F5 key." << endl; break;

				case KEY_F6:      cout << "F6 key." << endl; break;

				case KEY_F7:      cout << "F7 key." << endl; break;

				case KEY_F8:      cout << "F8 key." << endl; break;

				case KEY_F9:      cout << "F9 key." << endl; break;

				default: cout << "Unknown extended key." << endl;

				}
				*/

				/*
				if((char)c = 32) {

				cleardevice();
				}

				*/

				/*



				//int b;

				char c;


				//for (b = 10; b <= 100; b += 10)


				c = (char)getch();

				//if (c != 0) {

				//cout << "That is ASCII value: " << (int)c << endl;

				if ((int)c == 32) {

				//dog();
				cleardevice();

				}

				//}



				*/

				/*
				srand((unsigned int) time(NULL));


				thread g(gameThread); // Thread definiton
				thread t(KEY_LISTENER);

				global.press = global.hold = false;
				t.join(); // thread t start
				g.join();
				return;


				*/

				//I dont think it does anything ; maybe something related to clicking
				/*
				SetCursorPos(100, 400);
				for (int i = 0; i < 200000; i++) {
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}

				*/

				setcolor(7);
				bar(100, 100, 175, 175);
				bar(100, 200, 175, 275);
				bar(100, 300, 175, 375);
				bar(100, 400, 175, 475);
				bar(100, 500, 175, 575);
				bar(100, 600, 175, 675);
				bar(100, 700, 175, 775);
				bar(100, 800, 175, 875);
				bar(100, 900, 175, 975);

				bar(200, 100, 275, 175);
				bar(200, 200, 275, 275);
				bar(200, 300, 275, 375);
				bar(200, 400, 275, 475);
				bar(200, 500, 275, 575);
				bar(200, 600, 275, 675);
				bar(200, 700, 275, 775);
				bar(200, 800, 275, 875);
				bar(200, 900, 275, 975);

				bar(300, 100, 375, 175);
				bar(300, 200, 375, 275);
				bar(300, 300, 375, 375);
				bar(300, 400, 375, 475);
				bar(300, 500, 375, 575);
				bar(300, 600, 375, 675);
				bar(300, 700, 375, 775);
				bar(300, 800, 375, 875);
				bar(300, 900, 375, 975);

				bar(400, 100, 475, 175);
				bar(400, 200, 475, 275);
				bar(400, 300, 475, 375);
				bar(400, 400, 475, 475);
				bar(400, 500, 475, 575);
				bar(400, 600, 475, 675);
				bar(400, 700, 475, 775);
				bar(400, 800, 475, 875);
				bar(400, 900, 475, 975);

				bar(500, 100, 575, 175);
				bar(500, 200, 575, 275);
				bar(500, 300, 575, 375);
				bar(500, 400, 575, 475);
				bar(500, 500, 575, 575);
				bar(500, 600, 575, 675);
				bar(500, 700, 575, 775);
				bar(500, 800, 575, 875);
				bar(500, 900, 575, 975);

				bar(600, 100, 675, 175);
				bar(600, 200, 675, 275);
				bar(600, 300, 675, 375);
				bar(600, 400, 675, 475);
				bar(600, 500, 675, 575);
				bar(600, 600, 675, 675);
				bar(600, 700, 675, 775);
				bar(600, 800, 675, 875);
				bar(600, 900, 675, 975);

				bar(700, 100, 775, 175);
				bar(700, 200, 775, 275);
				bar(700, 300, 775, 375);
				bar(700, 400, 775, 475);
				bar(700, 500, 775, 575);
				bar(700, 600, 775, 675);
				bar(700, 700, 775, 775);
				bar(700, 800, 775, 875);
				bar(700, 900, 775, 975);

				bar(800, 100, 875, 175);
				bar(800, 200, 875, 275);
				bar(800, 300, 875, 375);
				bar(800, 400, 875, 475);
				bar(800, 500, 875, 575);
				bar(800, 600, 875, 675);
				bar(800, 700, 875, 775);
				bar(800, 800, 875, 875);
				bar(800, 900, 875, 975);

				bar(900, 100, 975, 175);
				bar(900, 200, 975, 275);
				bar(900, 300, 975, 375);
				bar(900, 400, 975, 475);
				bar(900, 500, 975, 575);
				bar(900, 600, 975, 675);
				bar(900, 700, 975, 775);
				bar(900, 800, 975, 875);
				bar(900, 900, 975, 975);

				string pressx = "Press the x key once";
				setcolor(15);
				settextstyle((2), (0), (5));
				outtextxy(1010, 200, pressx.c_str());
				putpixel(0, 0, 0);

				string click = "Click on the output box tab at the bottom";
				setcolor(15);
				settextstyle((2), (0), (5));
				outtextxy(1010, 300, click.c_str());
				putpixel(0, 0, 0);

				string inputnums = "Input box number to reveal underlying figure (may need to be entered several times)";
				setcolor(15);
				settextstyle((2), (0), (5));
				outtextxy(1010, 400, inputnums.c_str());
				putpixel(0, 0, 0);

				string logic = "Use logic to discover where the mines are without clicking them";
				setcolor(15);
				settextstyle((2), (0), (5));
				outtextxy(1010, 500, logic.c_str());
				putpixel(0, 0, 0);

				string win = "Win the game";
				setcolor(15);
				settextstyle((2), (0), (5));
				outtextxy(1010, 600, win.c_str());
				putpixel(0, 0, 0);

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 100, one.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 100, two.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 100, three.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 100, four.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 100, five.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 100, six.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 100, seven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 100, eight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 100, nine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 200, ten.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 200, eleven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 200, twelve.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 200, thirteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 200, fourteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 200, fifteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 200, sixteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 200, seventeen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 200, eighteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 300, nineteen.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 300, twenty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 300, twentyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 300, twentytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 300, twentythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 300, twentyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 300, twentyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 300, twentysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 300, twentyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 400, twentyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 400, twentynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 400, thirty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 400, thirtyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 400, thirtytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 400, thirtythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 400, thirtyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 400, thirtyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 400, thirtysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 500, thirtyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 500, thirtyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 500, thirtynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 500, fourty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 500, fourtyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 500, fourtytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 500, fourtythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 500, fourtyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 500, fourtyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 600, fourtysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 600, fourtyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 600, fourtyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 600, fourtynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 600, fifty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 600, fiftyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 600, fiftytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 600, fiftythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 600, fiftyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 700, fiftyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 700, fiftysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 700, fiftyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 700, fiftyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 700, fiftynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 700, sixty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 700, sixtyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 700, sixtytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 700, sixtythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 800, sixtyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 800, sixtyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 800, sixtysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 800, sixtyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 800, sixtyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 800, sixtynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 800, seventy.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 800, seventyone.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 800, seventytwo.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(100, 900, seventythree.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(200, 900, seventyfour.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(300, 900, seventyfive.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(400, 900, seventysix.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(500, 900, seventyseven.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(600, 900, seventyeight.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(700, 900, seventynine.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(800, 900, eighty.c_str());

				setcolor(15);
				settextstyle((4), (0), (4));
				outtextxy(900, 900, eightyone.c_str());

				//	dog();

				//system("pause");
			
			}
		}

	/*string one = "1";
	string two = "2";
	string three = "3";
	string four = "4";
	string five = "5";
	string blank = "\n";
	string bomb = "F";*/

	int planet;
	cout << "start screen: enter in the coordinates of the square you would like to delete" << endl;
	cin >> planet;

	//flag

	//setcolor(4);
	//bar(25, 50, 100, 100);

	for (int i = 0; i < 71; i++) {



		cin >> planet;

		switch (planet) {
			//line1
		case 1: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(100, 100, one.c_str());
		}
				break;
		case 2: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(200, 100, two.c_str());
		}
				break;
		case 3: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(300, 100, one.c_str());
		}
				break;
		case 4: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 100, one.c_str());
		}
				break;

		case 5: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(500, 100, one.c_str());
		}
				break;
		case 6: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(600, 100, bomb.c_str());
		}
				break;
		case 7: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(700, 100, one.c_str());
		}
				break;
		case 8: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 100, blank.c_str());

		}
				break;
		case 9: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 100, blank.c_str());

		}
				break;
				//line 2
		case 10: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(100, 200, bomb.c_str());
		}
				 break;
		case 11: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(200, 200, two.c_str());
		}
				 break;
		case 12: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(300, 200, bomb.c_str());
		}
				 break;
		case 13: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 200, one.c_str());
		}
				 break;
		case 14: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(500, 200, one.c_str());
		}
				 break;
		case 15: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(600, 200, one.c_str());
		}
				 break;
		case 16: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(700, 200, one.c_str());
		}
				 break;
		case 17: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 200, blank.c_str());
		}
				 break;
		case 18: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 200, blank.c_str());
		}
				 break;
				 //line 3
		case 19: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(100, 300, one.c_str());
		}
				 break;
		case 20: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(200, 300, two.c_str());
		}
				 break;
		case 21: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(300, 300, one.c_str());
		}
				 break;
		case 22: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(400, 300, two.c_str());
		}
				 break;
		case 23: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(500, 300, one.c_str());
		}
				 break;
		case 24: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(600, 300, one.c_str());
		}
				 break;
		case 25: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(700, 300, blank.c_str());
		}
				 break;
		case 26: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 300, blank.c_str());
		}
				 break;
		case 27: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 300, blank.c_str());
		}
				 break;
				 //line 4
		case 28: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(100, 400, blank.c_str());
		}
				 break;
		case 29: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(200, 400, blank.c_str());
		}
				 break;
		case 30: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(300, 400, blank.c_str());
		}
				 break;
		case 31: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 400, one.c_str());
		}
				 break;
		case 32: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(500, 400, bomb.c_str());
		}
				 break;
		case 33: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(600, 400, one.c_str());
		}
				 break;
		case 34: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(700, 400, blank.c_str());
		}
				 break;
		case 35: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 400, blank.c_str());
		}
				 break;
		case 36: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 400, blank.c_str());
		}
				 break;
				 //line 5
		case 37: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(100, 500, blank.c_str()); }
				 break;
		case 38: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(200, 500, blank.c_str()); }
				 break;
		case 39: {
			setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(300, 500, blank.c_str()); }
				 break;
		case 40: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 500, one.c_str()); }
				 break;
		case 41: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(500, 500, two.c_str()); }
				 break;
		case 42: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(600, 500, two.c_str()); }
				 break;
		case 43: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(700, 500, one.c_str()); }
				 break;
		case 44: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 500, blank.c_str()); }
				 break;
		case 45: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 500, blank.c_str()); }
				 break;
				 //line 6 
		case 46: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(100, 600, one.c_str()); }
				 break;
		case 47: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(200, 600, one.c_str()); }
				 break;
		case 48: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(300, 600, two.c_str()); }
				 break;
		case 49: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 600, one.c_str()); }
				 break;
		case 50: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(500, 600, two.c_str()); }
				 break;
		case 51: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(600, 600, bomb.c_str()); }
				 break;
		case 52: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(700, 600, one.c_str()); }
				 break;
		case 53: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(800, 600, blank.c_str()); }
				 break;
		case 54: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 600, blank.c_str()); }
				 break;
				 //  line 7
		case 55: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(100, 700, one.c_str()); }
				 break;
		case 56: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(200, 700, bomb.c_str()); }
				 break;
		case 57: {
			setcolor(4);
			settextstyle((4), (0), (7));
			outtextxy(300, 700, three.c_str()); }
				 break;
		case 58: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(400, 700, bomb.c_str()); }
				 break;
		case 59: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(500, 700, two.c_str()); }
				 break;
		case 60: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(600, 700, two.c_str()); }
				 break;
		case 61: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(700, 700, two.c_str()); }
				 break;
		case 62: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(800, 700, one.c_str()); }
				 break;
		case 63: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 700, blank.c_str()); }
				 break;
				 //line 8 
		case 64: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(100, 800, two.c_str()); }
				 break;
		case 65: {
			setcolor(4);
			settextstyle((4), (0), (7));
			outtextxy(200, 800, three.c_str()); }
				 break;
		case 66: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(300, 800, bomb.c_str()); }
				 break;
		case 67: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(400, 800, two.c_str()); }
				 break;
		case 68: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(500, 800, one.c_str()); }
				 break;
		case 69: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(600, 800, one.c_str()); }
				 break;
		case 70: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(700, 800, bomb.c_str()); }
				 break;
		case 71: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(800, 800, one.c_str()); }
				 break;
		case 72: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 800, blank.c_str()); }
				 break;
				 //line 9
		case 73: {
			setcolor(15);
			settextstyle((4), (0), (7));
			outtextxy(100, 900, bomb.c_str()); }
				 break;
		case 74: {
			setcolor(2);
			settextstyle((4), (0), (7));
			outtextxy(200, 900, two.c_str()); }
				 break;
		case 75: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(300, 900, one.c_str()); }
				 break;
		case 76: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(400, 900, one.c_str()); }
				 break;
		case 77: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(500, 900, blank.c_str()); }
				 break;
		case 78: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(600, 900, one.c_str()); }
				 break;
		case 79: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(700, 900, one.c_str()); }
				 break;
		case 80: {
			setcolor(1);
			settextstyle((4), (0), (7));
			outtextxy(800, 900, one.c_str()); }
				 break;
		case 81: {setcolor(8);
			settextstyle((4), (0), (7));
			outtextxy(900, 900, blank.c_str()); }
				 break;

		}
		int end = rand() % 6 + 1;

		if (planet == 6 || planet == 10 || planet == 12 || planet == 32 || planet == 51 || planet == 56 || planet == 58 || planet == 66 || planet == 70 || planet == 73) {

			cleardevice(); //clears screen to losing screen once one hits a bomb
			if (end == 1) {
				string yousuckandyoulose = "YOU SUCK (you lose)";
				setcolor(15);
				settextstyle((4), (0), (8));
				outtextxy(100, 450, yousuckandyoulose.c_str());
				putpixel(0, 0, 0);
			}
			if (end == 2) {

				string yourparentsdontloveyou = "YOUR PARENTS DON'T LOVE YOU";
				setcolor(15);
				settextstyle((4), (0), (7));
				outtextxy(100, 450, yourparentsdontloveyou.c_str());
				putpixel(0, 0, 0);
			}
			if (end == 3) {

				string youreshamingyourancestors = "YOU'RE SHAMING YOUR ANCESTORS";
				setcolor(15);
				settextstyle((4), (0), (7));
				outtextxy(100, 450, youreshamingyourancestors.c_str());
				putpixel(0, 0, 0);
			}
			if (end == 4) {

				string computersciencehatesyou = "COMPUTER SCIENCE HATES YOU";
				setcolor(15);
				settextstyle((4), (0), (7));
				outtextxy(100, 450, computersciencehatesyou.c_str());
				putpixel(0, 0, 0);
			}
			if (end == 5) {

				string neverleaveyourhouseagain = "NEVER LEAVE YOUR HOUSE AGAIN";
				setcolor(15);
				settextstyle((4), (0), (7));
				outtextxy(100, 450, neverleaveyourhouseagain.c_str());
				putpixel(0, 0, 0);
			}
			if (end == 6) {

				string youreafailure = "DROP OUT NOW (you lose)";
				setcolor(15);
				settextstyle((4), (0), (7));
				outtextxy(100, 450, youreafailure.c_str());
				putpixel(0, 0, 0);
			}
		}
		/*if (i = 71) {

		string youwin = "you win";
		setcolor(15);
		settextstyle((4), (0), (7));
		outtextxy(100, 450, youwin.c_str());
		putpixel(0, 0, 0);
		}*/
	}

	system("pause");
}

//explosion noise when you lose???
//EASTER EGGS, when you enter specifc numbers Ex:420,666. Special things are outputtd onto the screen.
//Change from pressing buttons to clicking with the mouse

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
#pragma region GLOBALVARs
int GrDriver, GrMode, ErrorCode;
bool cursorVisible;
int centerX, centerY;
BOOL curVis;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HCURSOR visible, hCur1, hCur3;
#pragma region Function_Prototypes
void gr_Start(int&, int&, int&); // Starts the graphics window
void getCursor(POINT &p); // uses struct POINT
bool MOUSE(int); // if mouse pressed
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
void playSound(string, int);  // sound effect
void PlayerITS();
void gameThread();
void mainmenu();
void mainmenuI(); // main menu interact
void help();
void helpI();
void Play(); // Draws the movment of the players
void CLine(); // Draws the center line
void SpeedIC(); // Increases the speed of the ball every X milliseconds 
void scoreboard();
void pauseMD(); // pause menue draw
void pauseMI(); // pause menue interact
void settingD(); // draws the settings menu 
void settingI(); // settings interact 
void CountDown(); // counts down to game start 
void P1Vic(); // player 1 victory 
void P2Vic(); // player 2 victory
void TestC();
void GameR(); // game reset
void tri(int,int,int,int,int,int, int);
void soundT(); // sound thread
void soundPT(); // player sounds
void soundWT(); // wall sounds
void NumberS(int); // converts int to string for outtext 
void pong();
void soundVT();

bool P1Score = false;
bool P2Score = false;
int P1Count = 0;
int P2Count = 0; 
enum GameTime{ MainMenu, Setting, Playing, Gameover, PAUSE, EXIT, P1V, P2V, Help};


#pragma endregion
INPUT_RECORD irInBuf;
struct PASS {
	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
	bool W;
	bool S;
	bool UP;
	bool DOWN;
	bool exit = false;
	bool esc;
	int eschold;
	int PL2C; // center of player 2's line
	int PL1C; // center of player 1's line
	bool RS; // right shift
	bool LS; // left shift
	int P1S;	// player one shift 
	int P2S; // player two shift 
	GameTime ping;
	int MX; // mouse x
	int MY; // mouse y 
	bool go = false; // bool to determin if "go" has been initated. Playing will be propted to press space in order to "serve"
	bool P1V; // player 1 victory
	bool P2V; // player 2 victory
	bool PL1HS; // player 1 hit sound
	bool PL2HS; // player 2 hit sound
	double SpeedUp; // value by which ball speed is increased 
	int PL1T; // player one turbo
	int PL2T; // player two turbo
	bool wallC = 0;
	int bsod = 0;
	int ballcolor = 2;
	int bColor = 4;
	int bColor2 = 1;
	bool SideHit;
	bool VS = false;
	bool WS = false;
	bool loop = true;
	int startupcount = 0;
}global;
struct Circle {
	int StartSpeed;
	int x;
	int mx;
	int y;
	int my;
	int radius;
	int color;
	int speed;
	bool side;
	bool its = false;
	int TY; //top y
	int BY; // bottom y
	int LX; // left x
	int RX; // right x
	int SY; // Speed y
	double SX; // Speed x
	int top;
	int bottom;
	int left;
	int right;
	

	void Start() {
		StartSpeed = (rand() % 2);
		if (StartSpeed == 1) {
			side = true;
		}
	}


	void init() {
	generateCircle();
	draw();
	
	/*if (startcheck == false) {
		if (StartSpeed == 0) {
		side = false;
		}
		if (StartSpeed == 1) {
		side = true;
		}
	}*/
	setSpeed();
	mx = x;
	my = y;
	TY = y - radius;
	BY = y + radius;
	RX = x + radius;
	LX = x - radius;
	SX = speed;
	SY = speed;

	cout << "PRESS SPACE TO SERVE" << endl;
	cout << global.go << endl;
	if (global.go == false) {
		setcolor(color);
		fillellipse(x, y, radius, radius);
	}
		if (myCircle.its == false) {
			myCircle.Move();
		}
		else if (myCircle.its == true) {
			myCircle.Bounce();
			//	Manipulate();
		}
		global.go = false;
	
	
}
void generateCircle() {
	x = 960;
	y = 540;
	radius = 31;

}
void draw() {
	/*cout << "New Circle" << "\n";
	cout << "X = " << x << "\n";
	cout << "Y = " << y << "\n";
	cout << "Radius = " << radius << "\n";
	cout << "Color = " << color << "\n";
	cout << "Intersection" << its << "\n";
	cout << "Speed Y = " << SY << "\n";
	cout << "Speed X = " << SX << "\n";*/
	setcolor(global.ballcolor);
	fillellipse(mx, my, radius, radius);
}
void setSpeed() {
	if (side == false) {
		speed = 10;
	}
	if (side == true) {
		speed = -10;
	}
}
void Move() {
	
	

	mx = mx + SX;
	my = my + SY;
	/*system("cls");
	*cout << "New Circle" << "\n";
	cout << "X = " << mx << "\n";
	cout << "Y = " << my << "\n";
	cout << "Radius = " << radius << "\n";
	cout << "Color = " << color << "\n";
	cout << "Intersection = " << its << "\n";
	cout << "Speed Y = " << SY << "\n";
	cout << "Speed X = " << SX << "\n";*/
	setcolor(global.ballcolor);
	fillellipse(mx, my, radius, radius);
	Its();
}
void delCircle() {
	setcolor(0);
	fillellipse(mx, my, radius, radius);
}
void Its() {

	right = mx + 4;
	left = mx - 4;
	top = my - 4;
	bottom = my + 4;
	if (top < 0 || bottom > 1080 || left > 1920 || right < 0) {
		its = true;
	}
}
void Bounce() {
	if (left > 1920 && its == true) {
		side = false;
		ResetLeft();
		global.go = false; 
		global.SideHit = true;
	}
	if (right < 0 && its == true) {
		side = true;
		ResetRight();
		global.go = false;
		global.SideHit = true;
	}
	if ((bottom > 1080 || top < 0) && its == true) {
		SY = SY * -1;
		global.wallC = 1;
		its = false;
	}

}
void ResetLeft() {
	//set ball back in center and go to the left, straight at the paddle;
	its = false;
	P1Score = true;
	init();
}
void ResetRight() {
	//set ball back in center and go to the right, straight at the paddle;
	its = false;
	P2Score = true;
	init();
}
/*	void Manipulate() {
SX = SX + (rand() % 20 - 9);
SY = SY + (rand() % 20 - 9);
}
*/

void ball() {
	if (global.go == false) {
		string Serve = "Press Space to Serve";
		//outtextxy(100, 100, Serve.c_str());
		draw();
	}
	
	if (global.go == true) {
		if (myCircle.its == false) {
			myCircle.Move();
		}
		else if (myCircle.its == true) {
			myCircle.Bounce();
			//	Manipulate();
		}
	}
}
}myCircle;
struct Shape {
	int count;
	float poiX, poiY;
	bool intersect;
	char M = 0;
	char M2 = 0;

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
		int x2, y2, h2, w2;
		int s = 0;
		Point TopLeft, BottomRight;
		Point TopLeft2, BottomRight2;
		int outline;
		int outline2;
		void construct(int xc, int yc, int r) {
			TopLeft.init(xc - r, yc - r);
			BottomRight.init(xc + r, yc + r);
		}
		void init() {
			x = 1894;
			y = 500;
			w = 25;
			h = 200;
			global.bColor = 4;
			TopLeft.init(x, y);
			BottomRight.init(x + w, y + h);
			x2 = 0;
			y2 = 500;
			w2 = 25;
			h2 = 200;
			global.bColor2 = 1;
			cout << "Player 1: Blue" << endl;
			cout << "Player 2: Red" << endl;
			TopLeft.init(x2, y2);
			BottomRight.init(x2 + w2, y2 + h2);
			global.P1S = 20;
			global.P2S = 20;
		}

		void render() {
			setcolor(global.bColor);
			bar(x, y, x + w, y + h);
			setcolor(global.bColor2);
			bar(x2, y2, x2 + w2, y2 + h2);
		}
		void moveUP() {
			
			
			y = y - global.P1S;
			render();
		}
		void moveDown() {
			
			
			y = y + global.P1S;
			render();
		}
		void moveW() {
			
			
			y2 = y2 - global.P2S;
			render();
		}
		void moveS() {
			
			
			y2 = y2 + global.P2S;
			render();
		}



	}Rect;
	void Intersect_init() {
		intersect = false;
		count = 0;
	}
	void init() {
		Intersect_init();

	}

}assignment;


void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	global.bsod = rand() % 5;
	global.ping = MainMenu;
	global.SpeedUp = 0.3;
	global.PL1T = 50;
	global.PL2T = 50;
	assignment.Rect.init();
	assignment.Rect.render();
	myCircle.Start();
	myCircle.init();
	thread t(KEY_LISTENER);
	thread a(soundT);
	thread u(soundPT);
	thread m(soundWT);
	thread o(soundVT);
	while (global.ping != EXIT) {
		if (global.ping == P1V) {
			
			P1Vic();
		}
		if (global.ping == P2V) {
			
			P2Vic();
		}
		if (global.ping == PAUSE) {
			//Sleep(100);
			pauseMD();
			while (global.ping == PAUSE) {
				pauseMI();}}
		if (global.ping == MainMenu) {
			GameR();
			//Sleep(100);
			mainmenu();
			while (global.ping == MainMenu) {
				mainmenuI();}}
		if (global.ping == Setting) {
			settingD();
			while (global.ping == Setting) {
				settingI();
			}
		}
		if (global.ping == Help) {
			cleardevice();
			help();
			while (global.ping == Help) {
				helpI();
			}
		}
		
		if (global.ping == Playing) {
			thread q(Play);
			thread x(PlayerITS);
			
			q.join();
			x.join();
		
		
		}}
	if (global.ping == EXIT) {
		cleardevice();
		if (global.bsod != 0) {
			setcolor(1);
			bar(0, 0, 1920, 1080);
			setcolor(9);
			bar(0, 200, 1920, 880);
			setbkcolor(9);
			setcolor(15);
			moveto(448, 504);
			outtext("Ping is shutting down...");
		}
		if (global.bsod == 0) {
			setcolor(1);
			bar(0, 0, 1920, 1080);
			setbkcolor(1);
			setcolor(15);
			settextstyle(1, 0, 4);
			moveto(50, 50);
			outtext("A problem has been detected and Windows has been shut down to prevent damage");
			moveto(50, 100);
			outtext("to your computer");
			moveto(50, 175);
			settextstyle(2, 0, 9);
			outtext("UNMOUNTABLE_BOOT_VOLUME");
			settextstyle(1, 0, 4);
			moveto(50, 250);
			outtext("If this is the first time you've seen this error screen");
			moveto(50, 300);
			outtext("restart your computer. If this screen appears again, follow");
			moveto(50, 350);
			outtext("these steps:");
			moveto(50, 425);
			outtext("Check to make sure any new hardware or software is properly installed.");
			moveto(50, 475);
			outtext("If this is a new installation, ask your hardware or software manufacturer");
			moveto(50, 525);
			outtext("for any Windows updates you might need.");
			moveto(50, 600);
			outtext("If problems continue, disable or remove any newly installed hardware");
			moveto(50, 650);
			outtext("or software. Disable BIOS memory options such as caching or shadowing.");
			moveto(50, 700);
			outtext("If you need to use Safe Mode to remove or disable components, restart");
			moveto(50, 750);
			outtext("your computer, press F8 to select Advanced Startup Options, and then");
			moveto(50, 800);
			outtext("select Safe Mode.");
			moveto(50, 875);
			outtext("Technical Information:");
			moveto(50, 950);
			outtext("*** STOP: 0x000000ED (0x80F128D0, 0xc000009c, 0x00000000, 0x00000000)");
			Sleep(1000);
		}
	}
			a.join();
			u.join();
			m.join();
			t.join();
			o.join();
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
bool KEYBOARD1(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		global.press = true;
		global.VirtualKey = VirtualKey;
		int count = 0;
		if (global.VirtualKey == VK_UP) {
			global.UP = true;
			
		}
		if (global.VirtualKey == VK_DOWN) {
			global.DOWN = true;
			
		}
		if (global.VirtualKey == VK_ESCAPE) {
			global.esc = true;
			cout << "ESC PRESSED" << endl;
		}
		if (global.VirtualKey == VK_RSHIFT) {
			global.RS = true;
		}
					
	}
	return false;
}
bool KEYBOARD2(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		global.press = true;
		global.VirtualKey = VirtualKey;
		int count = 0;
		
		if (global.VirtualKey == VK_W) {
			global.W = true;
		}
		if (global.VirtualKey == VK_S) {
			global.S = true;
		}
		if (global.VirtualKey == VK_LSHIFT) {
			global.LS = true;
		}
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

	while (global.ping != EXIT) {
		if (MOUSE(VK_LBUTTON)) {
			cout << "Left Button\n";
			SetCursor(visible);
			POINT v;
			GetCursorPos(&v);
			cout << v.x << ", " << v.y << endl;
			global.MX = v.x;
			global.MY = v.y;

		}
		if (MOUSE(VK_RBUTTON)) {
			cout << "Right Button\n";
			SetCursor(visible);
		}
		if (MOUSE(VK_MBUTTON))
		{
			playSound("starwars.wav", 2100);
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
		if (KEYBOARD1(VK_UP)) {
			cout << "Up Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD1(VK_DOWN)) {
			cout << "Down Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD2(VK_LSHIFT)) {
			cout << "Left Shift\n";
		}
		if (KEYBOARD1(VK_RSHIFT))
		{
			cout << "Right Shift\n";
		}
		if (KEYBOARD1(VK_ESCAPE)) {
			cout << "Escape Pressed\n";
			global.ping = PAUSE;
			global.eschold++;
			return;
		}
		if (KEYBOARD(VK_ESCAPE)) {
			if (global.ping != MainMenu) {
				if (global.ping == PAUSE) {
					CountDown();
					global.ping = Playing;
				}
				else {
					global.ping = PAUSE;
				}
			}
			
			
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
			global.go = true;
		}
		if (KEYBOARD(VK_A)) {
			cout << "A Key Pressed \n";
		}
		if (KEYBOARD2(VK_W)) {
			cout << "W Key Pressed \n";
		}
		if (KEYBOARD2(VK_S)) {
			cout << "S Key Pressed \n";
		}
		if (KEYBOARD(VK_D)) {
			cout << "D Key Pressed \n";
		}

		// Room For More Ifs specified keys act in a specific way.
		// look through the VirtualKeys.h list to have other specific keys
	}

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
void gameThread() {

	


}
void Play() {
	cleardevice();
	while (global.ping == Playing) {
		
			Sleep(25);
			cleardevice();
		if (global.go == false) {
			string Serve = "Press Space to Serve";
			scoreboard();
			CLine();
			myCircle.draw();
			assignment.Rect.render();
			settextstyle(3, 0, 6);
			setcolor(15);
			outtextxy(100, 200, Serve.c_str());
		}
			assignment.Rect.render();
			scoreboard();
			CLine();
			myCircle.ball();
			setcolor(15);
			//line(0, global.PL2C, 960, global.PL2C);
			if (assignment.Rect.y < 0) {
				assignment.Rect.y = assignment.Rect.y + 10;
			}
			if (assignment.Rect.y > 880) {						// Bounces Player 2 away from edge
				assignment.Rect.y = assignment.Rect.y - 10;
			}

			if (assignment.Rect.y >= 0 && assignment.Rect.y <= 880) { // Checks if Player 2 is on the edge
				if (global.RS == true) {
					//cout << "TESTY" << endl;
					if (global.UP == true) {
						assignment.Rect.y = assignment.Rect.y - global.PL2T; // "turbo" player2
						assignment.Rect.moveUP(); // Moves Player 2
						global.UP = false;
					}
					if (global.DOWN == true) {
						assignment.Rect.y = assignment.Rect.y + global.PL2T; // "turbo" player2
						assignment.Rect.moveDown();	// Moves Player 2
						global.DOWN = false;
					}
					global.RS = false;
				}
				else if (global.UP == true) {
					assignment.Rect.moveUP(); // Moves Player 2
					global.UP = false;
				}
				else if (global.DOWN == true) {
					assignment.Rect.moveDown();	// Moves Player 2
					global.DOWN = false;
				}
			}


			if (assignment.Rect.y2 < 0) {
				assignment.Rect.y2 = assignment.Rect.y2 + 10;
			}
			if (assignment.Rect.y2 > 880) {						// Bounces Player 1 away from edge
				assignment.Rect.y2 = assignment.Rect.y2 - 10;
			}
			 
			if (assignment.Rect.y2 >= 0 && assignment.Rect.y2 <= 880) {	// Checks if Player 1 is on the edge
				if (global.LS == true) {
					//cout << "TESTY" << endl;
					if (global.W == true) {
						assignment.Rect.y2 = assignment.Rect.y2 - global.PL1T; // "turbo" player2
						assignment.Rect.moveW(); // Moves Player 2
						global.W = false;
					}
					if (global.S == true) {
						assignment.Rect.y2 = assignment.Rect.y2 + global.PL1T; // "turbo" player2
						assignment.Rect.moveS();	// Moves Player 2
						global.S = false;
					}
					global.LS = false;
				}
				else if (global.W == true) {
					assignment.Rect.moveW();	// Moves Player 1
					global.W = false;
				}
				else if (global.S == true) {
					assignment.Rect.moveS();	// Moves Player 1
					global.S = false;
				}
			}
		}
	}
void CLine() {
	//for (int i = 0; i < 10; i++) {
		/*Sleep(100);
		setcolor(15);
		int n1 = 0;
		int n2 = -123;
		n1 = (i * 123) + 108;
		n2 = (i * 123) - 123;
		bar(958, n1, 962, n2);
		cout << n1 << endl;
		cout << n2 << endl;
	}*/
	setcolor(15);
	bar(958, 96, 962, 0);
	//Sleep(20);
	bar(958, 210, 962, 111);
	//Sleep(20);
	bar(958, 342, 962, 234);
	//Sleep(20);
	bar(958, 465, 962, 357);
	//Sleep(20);
	bar(958, 588, 962, 480);

	bar(958, 711, 962, 603);

	bar(958, 834, 962, 726);

	bar(958, 957, 962, 849);

	bar(958, 1080, 962, 972);
	

}
void PlayerITS() {
	while (global.ping == Playing) {
		global.PL1C = assignment.Rect.y + (assignment.Rect.h / 2);
		global.PL2C = assignment.Rect.y2 + (assignment.Rect.h2 / 2);
		//Sleep(100);
		if ((myCircle.mx - myCircle.radius) < (assignment.Rect.x2 + assignment.Rect.w2)) {
			if (((myCircle.my) > assignment.Rect.y2 - 10) && ((myCircle.my < (assignment.Rect.y2 + assignment.Rect.h2 + 10)))) {
				global.PL2C = assignment.Rect.y2 + (assignment.Rect.h2 / 2); // blue
				global.PL2HS = true;
				/*if (myCircle.SY <= global.PL2C) {
					myCircle.SY = myCircle.SY * (-1);
				}
				else {
					myCircle.SY = myCircle.SY * (1);
				}*/

				myCircle.mx = assignment.Rect.x2 + myCircle.radius + assignment.Rect.w2; // resets ball to edge of player to prevent warp glitch
				myCircle.SX = myCircle.SX * -1;
				
				if (myCircle.SX > 0) {
					myCircle.SX = myCircle.SX + 5; // increases speed of ball on player hit
				}
				if (myCircle.SX < 0) {
					myCircle.SX = myCircle.SX - 5;}
				if (myCircle.SY > 0) {
					myCircle.SY = myCircle.SY + 3; // increases speed of ball on player hit
				}
				if (myCircle.SY < 0) {
					myCircle.SY = myCircle.SY - 3;
				}
							
			}}
		if ((myCircle.mx + myCircle.radius) > (assignment.Rect.x + assignment.Rect.w)) {
			if (((myCircle.my) > assignment.Rect.y - 10) && ((myCircle.my < (assignment.Rect.y + assignment.Rect.h + 10)))) {
				global.PL1C = assignment.Rect.y + (assignment.Rect.h / 2); // red
				global.PL1HS = true;
				/*if (myCircle.SY > global.PL1C) {
					myCircle.SY = myCircle.SY * (-1);
				}*/
				

				myCircle.mx = assignment.Rect.x - myCircle.radius - assignment.Rect.w; // resets ball to edge of player to prevent warp glitch
				myCircle.SX = myCircle.SX * -1;
				
				if (myCircle.SX > 0) {
					myCircle.SX = myCircle.SX + 5; // increases speed of ball on player hit
				}
				if (myCircle.SX < 0) {
					myCircle.SX = myCircle.SX - 5;
				}
				if (myCircle.SY > 0) {
					myCircle.SY = myCircle.SY + 3; // increases speed of ball on player hit
				}
				if (myCircle.SY < 0) {
					myCircle.SY = myCircle.SY - 3;
				}
			}}}}
void SpeedIC() {
	while (global.ping == Playing) {
		Sleep(10);
		if (myCircle.SX > 0) {
			myCircle.SX = myCircle.SX + global.SpeedUp;
		}
		if (myCircle.SX < 0) {
			myCircle.SX = myCircle.SX - global.SpeedUp;
		}}}
void scoreboard() {
	settextstyle(3, 0, 72);
	setcolor(15);	
	//P1 Scores
		if (P1Score == true) {
			P1Count++;
			P1Score = false;}
		moveto(604, 20);
		if (P1Count == 0) {
			//moveto(604, 20);
			outtext("0");
		}
		if (P1Count == 1) {
			//moveto(604, 20);
			outtext("1");
			
		}
		if (P1Count == 2) {
			//moveto(604, 20);
			outtext("2");
	
		}
		if (P1Count == 3) {
			//moveto(604, 20);
			outtext("3");
		
		}
		if (P1Count == 4) {
			//moveto(604, 20);
			outtext("4");
		
		}
		if (P1Count == 5) {
			//moveto(604, 20);
			outtext("5");
		
		}
		if (P1Count == 6) {
			//moveto(604, 20);
			outtext("6");
			
		}
		if (P1Count == 7) {
			//moveto(604, 20);
			outtext("7");
			global.ping = P1V;
		}
		//P2 Scores
		if (P2Score == true) {
			P2Count++;
			P2Score = false;
			
		}
		moveto(1220, 20);
		if (P2Count == 0) {
			//moveto(1220, 20);
			outtext("0");
		}
		if (P2Count == 1) {
			//moveto(1220, 20);
			outtext("1");
		}
		if (P2Count == 2) {
			//moveto(1220, 20);
			outtext("2");
		}
		if (P2Count == 3) {
			//moveto(1220, 20);
			outtext("3");
		}
		if (P2Count == 4) {
			//moveto(1220, 20);
			outtext("4");
		}
		if (P2Count == 5) {
			//moveto(1220, 20);
			outtext("5");
		}
		if (P2Count == 6) {
			//moveto(1220, 20);
			outtext("6");
		}
		if (P2Count == 7) {
			//moveto(1220, 20);
			outtext("7");
			global.ping = P2V;
		}
		if (global.SideHit == true && (P1Count <= 6 && P2Count <=6)) {
			global.VS = true;
		}
		if (global.SideHit == true && (P1Count == 7 || P2Count == 7)) {
			global.WS = true;
		}
	}
void pauseMD() {
	string resume = "Resume";
	string settings = "Settings";
	string Main = "Main";
	string Menu = "Menu";
	string exit = "Exit";
	int RC = 1; // resume color
	int SC = 5; // settings color
	int MC = 3; // menu color 
	int EC = 14; // exit color
	Sleep(40);
	settextstyle(4, 0, 7);
	setcolor(15);
	bar(758, 786, 1162, 140); // background block
	cleardevice();
	bar(758, 786, 1162, 140); // background block

	setcolor(RC);
	bar(768, 299, 1152, 150); // Resume Button
	setcolor(SC);
	bar(768, 458, 1152, 309); // Settings Button
	setcolor(MC);
	bar(768, 617, 1152, 468); // Main Menu Button
	setcolor(EC);
	bar(768, 776, 1152, 627); // Exit Button

	setbkcolor(RC);
	setcolor(15); // Resume Button text 
	outtextxy(778, 187.25, resume.c_str());
	setbkcolor(SC);
	setcolor(15); // Settings button text 
	outtextxy(778, 346.25, settings.c_str());
	setbkcolor(MC);
	setcolor(15); // Menu Button text
	outtextxy(778, 478, Main.c_str());
	outtextxy(778, 537, Menu.c_str());
	setbkcolor(EC);
	setcolor(15); // Exit Button text
	outtextxy(778, 664.25, exit.c_str());

	setbkcolor(0);
}
void pauseMI() {
	if (global.MX > 768 && global.MX < 1152) {
		if (global.MY > 150 && global.MY < 299) { // checks to see if inside resume button 
			Sleep(100);
			CountDown();
			global.ping = Playing;
			
		}
		if (global.MY > 309 && global.MY < 458) { // checks to see if inside settings button
			Sleep(100);
			global.ping = Setting;
			
		}
		if (global.MY > 468 && global.MY < 617) { // checks to see if inside mainmenu button
			Sleep(100);
			global.ping = MainMenu;
			
		}
		if (global.MY > 627 && global.MY < 776) { // checks to see if inside exit button
			Sleep(100);
			global.ping = EXIT;
			
		}
		global.MX = 0;
		global.MY = 0;


	}
}
void CountDown() {
	if (global.go == false) {
		return;
	}
	string Start = "Start";
	settextstyle(3, 0, 7);

	cleardevice();
	
	scoreboard();
	CLine();
	myCircle.draw();
	assignment.Rect.render();
	setcolor(15);
	outtextxy(100, 100, "3");
	

	Sleep(500);
	cleardevice();
	
	setcolor(15);
	outtextxy(100, 100, "2");
	scoreboard();
	CLine();
	myCircle.draw();
	assignment.Rect.render();

	Sleep(500);
	cleardevice();
	
	setcolor(15);
	outtextxy(100, 100, "1");
	scoreboard();
	CLine();
	myCircle.draw();

	assignment.Rect.render();
	Sleep(500);
	cleardevice();
	
	setcolor(15);
	outtextxy(100, 100, Start.c_str());
	scoreboard();
	CLine();
	myCircle.draw();
	assignment.Rect.render();

	Sleep(500);

}
void mainmenu() {
	
	string PingT = "Ping!";
	string play = "Play";
	string settings = "Settings";
	string Help = "Help";
	string exit = "Exit";
	int RC = 1; // resume color
	int SC = 5; // settings color
	int MC = 3; // menu color 
	int EC = 14; // exit color
	int HC = 2; // header color
	//Sleep(40);
	settextstyle(4, 0, 7);
	setcolor(15);
	bar(758, 986, 1162, 340); // background block
	cleardevice();
	bar(758, 986, 1162, 340); // background block

	bar(688, 300, 1232, 50); // header background white
	setcolor(HC);
	bar(698, 290, 1222, 60); // header background color 

	setcolor(RC);
	bar(768, 499, 1152, 350); // Resume Button
	setcolor(SC);
	bar(768, 658, 1152, 509); // Settings Button
	setcolor(MC);
	bar(768, 817, 1152, 668); // Helo Menu Button
	setcolor(EC);
	bar(768, 976, 1152, 827); // Exit Button

	settextstyle(4, 0, 37);
	setbkcolor(HC);
	setcolor(15);
	outtextxy(725, 97.25, PingT.c_str()); // Print game name
	settextstyle(4, 0, 7);
	setbkcolor(RC);
	setcolor(15); // Resume Button text 
	outtextxy(778, 387.25, play.c_str());
	setbkcolor(SC);
	setcolor(15); // Settings button text 
	outtextxy(778, 546.25, settings.c_str());
	setbkcolor(MC);
	setcolor(15); // Help Button text
	outtextxy(778, 705.25, Help.c_str());
	setbkcolor(EC);
	setcolor(15); // Exit Button text
	outtextxy(778, 864.25, exit.c_str());

	setbkcolor(0);
	
}
void mainmenuI() {
	if (global.MX > 768 && global.MX < 1152) {
		if (global.MX >= 688 && global.MX <= 1232) {
			if (global.MY >= 50 && global.MY <= 300) {
				pong();
			}										// "PONG" easter egg
		}
		if (global.MY > 350 && global.MY < 599) { // checks to see if inside resume button 
			Sleep(100);
			CountDown();
			global.ballcolor = 2;
			global.ping = Playing;

		}
		if (global.MY > 509 && global.MY < 658) { // checks to see if inside settings button
			Sleep(100);
			global.ping = Setting;

		}
		if (global.MY > 668 && global.MY < 817) { // checks to see if inside mainmenu button
			Sleep(100);
			global.ping = Help;

		}
		if (global.MY > 827 && global.MY < 976) { // checks to see if inside exit button
			Sleep(100);
			global.ping = EXIT;

		}
		global.MX = 0;
		global.MY = 0;


	}
}
void help() {
	string back = "Back";
	string help = "Help";
	string play = "Play";
	string PL1 = "Player One"; // blue (w/s)
	string PL2 = "Player Two"; // red (arrow keys) 
	setcolor(15);
	bar(720, 25, 1200, 175);
	setcolor(3);
	bar(730, 35, 1190, 165);
	setbkcolor(3);                // "HELP" header 
	setcolor(15);
	settextstyle(4, 0, 9);
	outtextxy(795, 45, help.c_str());

	bar(20, 200, 1900, 225);			// draws the center T structure 
	bar(947.5, 225, 972.5, 1060);
	
	settextstyle(4, 0, 4.9);
	setcolor(15);
	bar(303.75, 250, 643.75, 375);
	setcolor(1);						// player 1 header
	bar(313.75, 260, 633.75, 365);
	setcolor(15);
	setbkcolor(1);
	outtextxy(345, 290, PL1.c_str());

	setcolor(15);
	bar(1286.25, 250, 1626.25, 375);
	setcolor(4);						// player 2 header
	bar(1295.25, 260, 1616.25, 365);
	setcolor(15);
	setbkcolor(4);
	outtextxy(1330, 290, PL2.c_str());

	setcolor(15);
	bar(75, 400, 872.5, 1005); // player one information screen 
	setcolor(1);
	bar(85, 410, 862.6, 995);

	setcolor(15);
	bar(1047.5, 400, 1845, 1005); // player two information screen 
	setcolor(4);
	bar(1057.5, 410, 1835, 995);

	setcolor(15);
	setbkcolor(1);
	settextstyle(4, 0, 7);
	moveto(100, 450);
	outtext("W");
	moveto(250, 450);
	outtext("=");
	moveto(350, 450);
	outtext("Move Up");
	moveto(100, 600);
	outtext("S");				// player one information text
	moveto(200, 600);
	outtext("=");
	moveto(300, 600);
	outtext("Move Down");
	moveto(100, 800);
	settextstyle(4, 0, 6.5);
	outtext("Left Shift = Turbo");
	setcolor(4);
	moveto(1000, 50);

	setbkcolor(4);
	setcolor(15);
	settextstyle(4, 0, 7);
	moveto(1000, 200);
	line(1080, 470, 1180, 470);
	line(1080, 470, 1130, 420);
	line(1130, 420, 1180, 470);
	setfillstyle(1, 15);
	floodfill(1130, 445, 15);
	bar(1110, 470, 1150, 520);
	moveto(1222.5, 450);
	outtext("=");
	moveto(1322.5, 450);
	outtext("Move Up");
	moveto(1000, 400);
	bar(1090, 600, 1130, 650);
	line(1060, 650, 1160, 650);
	line(1060, 650, 1110, 700);		// player two information screen 
	line(1110, 700, 1160, 650);
	floodfill(1110, 675, 15);
	moveto(1172.5, 600);
	outtext("=");
	moveto(1272.5, 600);
	outtext("Move Down");
	
	settextstyle(4, 0, 6.5);
	moveto(1072.5, 800);
	outtext("Right Shift = Turbo");
	setcolor(15);
	

	/*settextstyle(3, 0, 8);
	moveto(600, 900);
	outtext("Space");
	moveto(930, 900);
	outtext("=");
	moveto(1020, 900);
	outtext("Serve Ball");
	setfillstyle(1, 15);*/

	setcolor(15);
	settextstyle(4, 0, 8);
	bar(100, 25, 480, 175);
	setcolor(3);				// backbutton
	bar(110, 35, 470, 165);
	setcolor(15);
	setbkcolor(3);
	outtextxy(136, 55, back.c_str());
	setbkcolor(0);

	setcolor(15);
	settextstyle(4, 0, 8);
	bar(1440, 25, 1820, 175);
	setcolor(1);				// play button
	bar(1450, 35, 1810, 165);
	setcolor(15);
	setbkcolor(1);
	outtextxy(1500, 55, play.c_str());


	setbkcolor(0);

	
}
void helpI() {
	if (global.MX > 100 && global.MX < 480) {
		if (global.MY > 25 && global.MY < 175) { // checks to see if inside back button 
			Sleep(100);
			global.ping = MainMenu;
		}
	}
	if (global.MX > 1440 && global.MX < 1820) {
		if (global.MY > 25 && global.MY < 175) { // checks to see if inside play button 
			Sleep(100);
			global.ping = Playing;
		}
	}
}
void settingD() {
		string back = "Back";
		string setting = "Settings";
		string play = "Play";
		string PL1 = "Player One"; // blue (w/s)
		string PL2 = "Player Two"; // red (arrow keys) 
		string PL1S = "Speed of Player One";
		string Pl2S = "Speed of Player Two";
		string PL1ST = "Turbo Speed of Player One";
		string Pl2ST = "Turbo Speed of Player Two";
		int P1S = global.P1S;
		cleardevice();
		setcolor(15);
		bar(720, 25, 1200, 175);
		setcolor(5);
		bar(730, 35, 1190, 165);
		setbkcolor(5);                // "Settings" header 
		setcolor(15);
		settextstyle(4, 0, 8);
		outtextxy(735, 55, setting.c_str());

		bar(20, 200, 1900, 225);			// draws the center T structure 
		bar(947.5, 225, 972.5, 1060);
		bar(20, 780, 1900, 805);

		settextstyle(4, 0, 4.9);
		setcolor(15);
		bar(303.75, 250, 643.75, 375);
		setcolor(1);						// player 1 header
		bar(313.75, 260, 633.75, 365);
		setcolor(15);
		setbkcolor(1);
		outtextxy(345, 290, PL1.c_str());

		setcolor(15);
		bar(1286.25, 250, 1626.25, 375);
		setcolor(4);						// player 2 header
		bar(1295.25, 260, 1616.25, 365);
		setcolor(15);
		setbkcolor(4);
		outtextxy(1330, 290, PL2.c_str());

		setcolor(15);
		bar(75, 400, 872.5, 725); // player one information screen 
		setcolor(1);
		bar(85, 410, 862.6, 715);

		setcolor(15);
		bar(1047.5, 400, 1845, 725); // player two information screen 
		setcolor(4);
		bar(1057.5, 410, 1835, 715);

		setcolor(15);
		setbkcolor(1);
		settextstyle(4, 0, 5);
		moveto(100, 475);			// setting for speed of player one
		outtext(PL1S.c_str());
		outtextxy(730, 475, "=");
		setcolor(15);
		bar(780, 465, 840, 525);
		setcolor(5);
		bar(785, 470, 835, 520);
		setcolor(15);
		tri(775, 460, 845, 460, 810, 440, 15);
		
		tri(775, 530, 845, 530, 810, 550, 15);

		settextstyle(4, 0, 4);
		outtextxy(100, 600, PL1ST.c_str());
		outtextxy(730, 600, "=");
		bar(780, 590, 840, 650);
		setcolor(5);							// setting for turbo speed of player one
		bar(785, 595, 835, 645);
		setcolor(15);
		tri(775, 585, 845, 585, 810, 565, 15);
		
		tri(775, 655, 845, 655, 810, 675, 15);




		setcolor(15);
		settextstyle(4, 0, 8);
		bar(100, 25, 480, 175);
		setcolor(3);				// backbutton
		bar(110, 35, 470, 165);
		setcolor(15);
		setbkcolor(3);
		outtextxy(136, 55, back.c_str());
		setbkcolor(0);

		setcolor(15);
		settextstyle(4, 0, 8);
		bar(1440, 25, 1820, 175);
		setcolor(1);				// play button
		bar(1450, 35, 1810, 165);
		setcolor(15);
		setbkcolor(1);
		outtextxy(1500, 55, play.c_str());


		setbkcolor(0);

}
void settingI() {
		Sleep(25);
		if (global.MX > 100 && global.MX < 480) {
			if (global.MY > 25 && global.MY < 175) { // checks to see if inside back button 
				Sleep(100);
				global.ping = MainMenu;
			}
		}
		if (global.MX > 1440 && global.MX < 1820) {
			if (global.MY > 25 && global.MY < 175) { // checks to see if inside play button 
				Sleep(100);
				global.ping = Playing;
			}
		}
	
}
void GameR() {
	assignment.Rect.init();
	assignment.Rect.render();
	myCircle.Start();
	myCircle.init();
	P1Count = 0;
	P2Count = 0;
	myCircle.mx = myCircle.x;
	myCircle.my = myCircle.y;
}
void P1Vic() {
	Sleep(25);
	while (global.loop == true) {
		cleardevice();
		global.loop = false;
	}
	settextstyle(4, 0, 6);
	string P1W = "Player One Wins";
	string PG = "Press Space to"; 
	string PG1 = "Play Again";
	scoreboard();
	CLine();
	myCircle.draw();
	assignment.Rect.render();
	setcolor(15);
	outtextxy(200, 200, P1W.c_str());
	outtextxy(200, 400, PG.c_str());
	outtextxy(200, 600, PG1.c_str());
	if (global.go == true) {
		Sleep(25);
		GameR();
		global.ping = Playing;
	}
}
void P2Vic() {
	Sleep(25);
	while (global.loop == true) {
		cleardevice();
		global.loop = false;
	}
	settextstyle(4, 0, 6);
	string P2W = "Player Two Wins";
	string PG = "Press Space to";
	string PG2 = "Play Again";
	scoreboard();
	CLine();
	myCircle.draw();
	assignment.Rect.render();
	setcolor(15);
	outtextxy(200, 200, P2W.c_str());
	outtextxy(200, 400, PG.c_str());
	outtextxy(200, 600, PG2.c_str());
	if (global.go == true) {
		Sleep(100);
		GameR();
		global.ping = Playing;
	}
}
void TestC() {
	string Test = "";
	cin >> Test;
	if (Test == "Playing") {
		global.ping = Playing;
	}
	if (Test == "P1V") {
		global.ping = P1V;
	}

	

}

void soundT() {
	while (global.ping != EXIT) { Sleep(1); 
	if (global.ping == MainMenu && global.startupcount == 0) {
		playSound("win31.mp3", 2200);
		global.startupcount++;
	}
	}
		if (global.ping == EXIT && global.bsod != 0) {
			playSound("XPS.wav", 2200);
		}
		if (global.ping == EXIT && global.bsod == 0) {
			playSound("BSOD.wav", 2200);
		}
	
}
void soundWT() {
	while (global.ping != EXIT) {
		if (global.wallC == 1) {
			playSound("Beep.wav", 350);
			global.wallC = 0;}
	}
	Sleep(1);

}
void soundVT() {
	while (global.ping != EXIT) {
		if (global.VS == true) {
			playSound("Crash.wav", 400);
			global.VS = false;
			global.SideHit = false;
		}
		if (global.WS == true) {
			playSound("victory.mp3", 4500);
			global.WS = false;
			global.SideHit = false;
		}
	}
	Sleep(1);
}
void soundPT() {
	while (global.ping != EXIT) {
		if (global.PL1HS == true || global.PL2HS == true) {
			playSound("Ping.wav", 550);
			global.PL1HS = false;
			global.PL2HS = false;
		}
		Sleep(1);
	}
}
void tri(int leftx, int lefty, int rightx, int righty, int topx, int topy, int color) {
	line(leftx, lefty, rightx,righty);
	line(leftx, lefty, topx, topy);
	line(topx, topy, rightx, righty);
	setfillstyle(1, color);
	floodfill(((leftx)+((rightx - leftx) / 2)), (topy + ((righty - topy)) / 2), color);}
void NumberS(int N) {


}
void pong() {
	global.ballcolor = 15;
	global.bColor = 15;
	global.bColor2 = 15;
	myCircle.color = 15;
	global.ping = Playing;
}

#pragma endregion
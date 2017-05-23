#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h>
#include <ctime>
#include <stdlib.h> 
#include <thread>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
#pragma comment(lib, "winmm.lib") // SOUND
using namespace std;
void playSound(string, int);  // sound effect



bool isGameRunning = true;
int GrDriver, GrMode, ErrorCode;

void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode) {
	GrDriver = VGA;
	GrMode = VGAMAX;
	initgraph(&GrDriver, &GrMode, "");
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{

		cout << "Error:" << ErrorCode;

	}

}
int cloudone(int x, int y);
int cloudtwo(int x, int y);
int cloudthree(int x, int y);
int cloudfour(int x, int y);
int cloudfive(int x, int y);
int smiley(int x, int y);
int animationone();
int animationtwo();
int animationthree();
int startingplace();
int startplacetwo();
void CloudJump();
void Audio(){
	while (isGameRunning) {
		playSound("thefinalcountdown.mp3", 308000);
	}
}


int main() {
	//background and opening text of start screen
	//ints used: x,y,start,instructions,ix,iy,title,sx,sy. For when we put all parts of game together
	thread game(CloudJump);
	thread music(Audio);
	music.join();
	game.join();
	
}

void CloudJump() {
	while (isGameRunning) {

		cout << "Welcome to Cloud Jump." << endl;
		gr_Start(GrDriver, GrMode, ErrorCode);
		setbkcolor(9);
		cleardevice();
		int x = 650;
		int y = 650;
		setcolor(1);
		string start = "Start: Press 1";
		settextstyle(1, 0, 7);
		textheight(start.c_str());
		textwidth(start.c_str());
		outtextxy(x, y, start.c_str());

		string instructions = "Instructions: Press 2";
		int ix = 525;
		int iy = 750;
		settextstyle(1, 0, 7);
		textheight(instructions.c_str());
		textwidth(instructions.c_str());
		outtextxy(ix, iy, instructions.c_str());

		string title = "Cloud Jump";
		int sx = 625;
		int sy = 350;
		settextstyle(1, 0, 8);
		textheight(title.c_str());
		textwidth(title.c_str());
		outtextxy(sx, sy, title.c_str());


		int c1 = 49; // 1
		int c2 = 50; // 2
		int c3 = 50; //2

		int choice = 99;
		while (choice == 99) {
			int INPUT = getch();
			if (INPUT == 49) {
				choice = 1;
			}
			else if (INPUT == 50) {
				choice = 2;
			}
		}
		if (choice == 1) {
			setbkcolor(9);
			cleardevice();
			setcolor(1);
			int sleep = 4000;

			int i = 0;
			int scoretrack = 0;
			int anttracker = 0;

			while (i == 0) {


				string crap = "Number:";
				int cx = 275;
				int cy = 100;
				setcolor(1);
				settextstyle(1, 0, 5);
				textheight(crap.c_str());
				textwidth(crap.c_str());
				outtextxy(cx, cy, crap.c_str());
				putpixel(0, 0, CYAN);
				if (anttracker == 0)
					startingplace();

				string crappy = "Score:";
				int ccx = 875;
				int ccy = 100;
				settextstyle(1, 0, 5);
				setcolor(1);
				textheight(crappy.c_str());
				textwidth(crappy.c_str());
				outtextxy(ccx, ccy, crappy.c_str());

				string trackscore = to_string(scoretrack);
				settextstyle(1, 0, 5);
				setcolor(8);
				outtextxy(1075, 100, trackscore.c_str());

				int randnum = rand() % 10;
				string VISUALNUMBER = to_string(randnum);
				settextstyle(1, 0, 5);
				setcolor(8);
				outtextxy(575, 100, VISUALNUMBER.c_str());
				Sleep(sleep);
				cleardevice();
				if (anttracker == 0)
					startingplace();


				int inputnumber = 999;


				if (kbhit()) {
					//  doesn't pause but when a key is pressed it goes inside the if statement
					inputnumber = getch();
					inputnumber = inputnumber - 48;


					if (inputnumber == randnum) {
						if (anttracker % 2 == 0) {
							animationone();
							sleep = sleep - 100;
							scoretrack = scoretrack + 10;
							anttracker++;
						}

						else {
							cleardevice();
							animationtwo();
							sleep = sleep - 100;
							scoretrack = scoretrack + 10;
							anttracker++;
						}


					}
					else {
						animationthree();
						i++;
						//adds to i so it stops loop and ends game
					}

				}
				else {
					animationthree();
					i++;
					//adds to i so it stops loop and ends game
				}
			}


			system("pause");
		}

		else {
			//instructions screen. choice if loop
			//background and opening text of begin screen
			setbkcolor(9);
			cleardevice();
			setcolor(1);


			string poop = "Instructions";
			int sx = 475;
			int sy = 150;
			settextstyle(1, 0, 10);
			textheight(poop.c_str());
			textwidth(poop.c_str());
			outtextxy(sx, sy, poop.c_str());

			string cool = "After a number appears and dissapears on the screen,";
			int x = 150;
			int y = 450;
			settextstyle(1, 0, 5);
			textheight(cool.c_str());
			textwidth(cool.c_str());
			outtextxy(x, y, cool.c_str());

			string continued = "type in the number to move up.";
			settextstyle(1, 0, 5);
			textheight(continued.c_str());
			textwidth(continued.c_str());
			outtextxy(500, 550, continued.c_str());




			string returnstart = "Press 2 to go to game screen";
			int rx = 650;
			int ry = 650;
			settextstyle(1, 0, 4);
			textheight(returnstart.c_str());
			textwidth(returnstart.c_str());
			outtextxy(rx, ry, returnstart.c_str());


			int INPUT2 = getch();

			if (INPUT2 == 50) {
				int choicetwo = 2;
				if (choicetwo == 2) {
					setbkcolor(9);
					cleardevice();
					setcolor(1);
					int sleep = 4000;

					int i = 0;
					int scoretrack = 0;
					int anttracker = 0;

					while (i == 0) {


						string crap = "Number:";
						int cx = 275;
						int cy = 100;
						setcolor(1);
						settextstyle(1, 0, 5);
						textheight(crap.c_str());
						textwidth(crap.c_str());
						outtextxy(cx, cy, crap.c_str());
						putpixel(0, 0, CYAN);
						if (anttracker == 0)
							startingplace();

						string crappy = "Score:";
						int ccx = 875;
						int ccy = 100;
						settextstyle(1, 0, 5);
						setcolor(1);
						textheight(crappy.c_str());
						textwidth(crappy.c_str());
						outtextxy(ccx, ccy, crappy.c_str());

						string trackscore = to_string(scoretrack);
						settextstyle(1, 0, 5);
						setcolor(8);
						outtextxy(1075, 100, trackscore.c_str());

						int randnum = rand() % 10;
						string VISUALNUMBER = to_string(randnum);
						settextstyle(1, 0, 5);
						setcolor(8);
						outtextxy(575, 100, VISUALNUMBER.c_str());
						Sleep(sleep);
						cleardevice();
						if (anttracker == 0)
							startingplace();


						int inputnumber = 999;


						if (kbhit()) {
							//  doesn't pause but when a key is pressed it goes inside the if statement
							inputnumber = getch();
							inputnumber = inputnumber - 48;


							if (inputnumber == randnum) {
								if (anttracker % 2 == 0) {
									animationone();
									sleep = sleep - 100;
									scoretrack = scoretrack + 10;
									anttracker++;
								}

								else {
									cleardevice();
									animationtwo();
									sleep = sleep - 100;
									scoretrack = scoretrack + 10;
									anttracker++;
								}


							}
							else {
								animationthree();
								i++;
								//adds to i so it stops loop and ends game
							}

						}
						else {
							animationthree();
							i++;
							//adds to i so it stops loop and ends game
						}
					}

				}

				system("pause");
			}
		}
	}
}

int cloudone(int x, int y) {
	setfillstyle(1, 15);
	setcolor(15);
	int xRadius = 75;
	int yRadius = 75;
	fillellipse(300 + x, 275 + y, xRadius, yRadius);
	fillellipse(180 + x, 250 + y, xRadius, yRadius);
	fillellipse(100 + x, 275 + y, xRadius, yRadius);
	fillellipse(200 + x, 300 + y, xRadius, yRadius);
	return 0;
}

int cloudtwo(int x, int y)
{
	setfillstyle(1, 15);
	setcolor(15);
	int xRadius = 75;
	int yRadius = 75;
	fillellipse(900 + x, 450 + y, xRadius, yRadius);
	fillellipse(1080 + x, 450 + y, xRadius, yRadius);
	fillellipse(1000 + x, 450 + y, xRadius, yRadius);
	return 0;
}

int cloudthree(int x, int y) {
	setfillstyle(1, 15);
	setcolor(15);
	int xRadius = 75;
	int yRadius = 75;
	fillellipse(1200 + x, 800 + y, xRadius, yRadius);
	fillellipse(1380 + x, 790 + y, xRadius, yRadius);
	fillellipse(1300 + x, 815 + y, xRadius, yRadius);
	fillellipse(1300 + x, 765 + y, xRadius, yRadius);
	return 0;
}

int cloudfour(int x, int y) {

	setfillstyle(1, 15);
	setcolor(15);
	int xRadius = 75;
	int yRadius = 75;
	fillellipse(600 + x, 775 + y, xRadius, yRadius);
	fillellipse(480 + x, 750 + y, xRadius, yRadius);
	fillellipse(400 + x, 775 + y, xRadius, yRadius);
	fillellipse(500 + x, 800 + y, xRadius, yRadius);
	return 0;
}

int cloudfive(int x, int y) {
	int xRadius = 75;
	int yRadius = 75;
	fillellipse(1600 + x, 350 + y, xRadius, yRadius);
	fillellipse(1600 + x, 300 + y, xRadius, yRadius);
	fillellipse(1500 + x, 350 + y, xRadius, yRadius);
	fillellipse(1700 + x, 320 + y, xRadius, yRadius);
	return 0;
}

int smiley(int x, int y) {
	int xRadius = 75;
	int yRadius = 75;
	setfillstyle(1, 14);
	setcolor(14);
	fillellipse(20 + x, 10 + y, xRadius, yRadius);

	setfillstyle(1, 11);
	setcolor(11);
	int smxradius = 40;
	int smyradius = 40;
	fillellipse(0 + x, 0 + y, smxradius, smyradius);
	fillellipse(50 + x, 0 + y, smxradius, smyradius);


	setfillstyle(1, 0);
	setcolor(0);
	int eexradius = 20;
	int rryradius = 20;
	fillellipse(0 + x, 0 + y, eexradius, rryradius);
	fillellipse(50 + x, 0 + y, eexradius, rryradius);

	/*setcolor(0);
	setlinestyle(2, 4, 7);
	line(540, 630, 550, 640);*/

	return 0;
}

int animationone() {

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(510, 675);
	Sleep(100);

	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(900, 350);
	Sleep(500);

	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(1600, 250);
	Sleep(500);

	cleardevice();


	cloudone(0, 100);
	cloudtwo(0, 100);
	cloudthree(0, 100);
	cloudfour(0, 100);
	cloudfive(0, 100);
	smiley(1600, 325);
	Sleep(500);

	cleardevice();


	cloudone(0, 250);
	cloudtwo(0, 250);
	cloudthree(0, 250);
	cloudfour(0, 250);
	cloudfive(0, 250);
	smiley(1600, 475);
	Sleep(500);

	cleardevice();

	cloudone(0, 500);
	cloudtwo(0, 500);
	cloudthree(0, 500);
	cloudfour(0, 500);
	cloudfive(0, 500);
	smiley(1600, 725);
	Sleep(500);

	cleardevice();


	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(175, -650);
	cloudfour(0, 0);
	cloudfive(0, 500);
	smiley(1600, 725);
	Sleep(500);

	//cleardevice();

	return 0;


}

int animationtwo() {

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(175, -650);
	cloudfour(0, 0);
	cloudfive(0, 500);
	smiley(1600, 725);
	Sleep(500);

	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(175, -650);
	cloudfour(0, 0);
	cloudfive(0, 500);
	smiley(1000, 375);
	Sleep(500);

	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(175, -650);
	cloudfour(0, 0);
	cloudfive(0, 500);
	smiley(250, 175);
	Sleep(500);

	cleardevice();

	cloudone(0, 200);
	cloudtwo(0, 200);
	cloudthree(175, -450);
	cloudfour(0, 200);
	cloudfive(0, 700);
	smiley(250, 375);
	Sleep(500);

	cleardevice();

	cloudone(0, 400);
	cloudtwo(0, 400);
	cloudthree(175, -250);
	cloudfour(0, 400);
	cloudfive(0, 900);
	smiley(250, 575);
	Sleep(500);

	cleardevice();

	cloudone(0, 600);
	cloudtwo(0, 600);
	cloudthree(175, -50);
	cloudfour(0, 600);
	cloudfive(0, 1100);
	smiley(250, 775);
	Sleep(500);

	cleardevice();
	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(510, 675);
	Sleep(500);




	//system("pause");


	return 0;
}

int animationthree() {
	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(510, 675);
	Sleep(100);
	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(710, 450);
	Sleep(500);
	cleardevice();

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(710, 850);
	Sleep(500);


	cleardevice();
	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	Sleep(500);

	string lost = "You lost!";
	int lx = 700;
	int ly = 500;
	setcolor(4);
	settextstyle(1, 0, 8);
	textheight(lost.c_str());
	textwidth(lost.c_str());
	outtextxy(lx, ly, lost.c_str());



	return 0;
}

int startingplace() {

	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(0, 0);
	cloudfour(0, 0);
	cloudfive(0, 0);
	smiley(200, 900);
	return 0;
}

int startplacetwo() {
	cloudone(0, 0);
	cloudtwo(0, 0);
	cloudthree(-175, -650);
	cloudfour(0, 0);
	cloudfive(0, 500);
	smiley(510, 675);
	return 0;
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




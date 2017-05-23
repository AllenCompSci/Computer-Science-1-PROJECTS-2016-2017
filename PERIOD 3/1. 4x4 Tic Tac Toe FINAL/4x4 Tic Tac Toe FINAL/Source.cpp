/*
Andrew Hsu and Josh Cho
4x4 Tic Tac Toe
*/
#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
using namespace std;

string square[17] = { "o","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16" };

int checkwin();
void board();
int choose;
int midx;
int midy;
int GrDriver, GrMode, ErrorCode;
int sizer = 1;

void board() {
}


int main()
{
	int player = 1, i, choice;

	extern ostringstream bgiout;

	void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
	GrDriver = VGA; //800x600 by monitor
	GrMode = VGAMAX;//set graphics mode
	initgraph(&GrDriver, &GrMode, "");

	midx = getmaxx() / 2;
	midy = getmaxy() / 2;


	setcolor(15);
	sizer = 8;
	settextstyle(8, 0, sizer);
	outtextxy(1150, 100, "Tic-Tac-Toe");


	sizer = 5;
	settextstyle(0, 0, sizer);
	outtextxy(285, 175, "1");
	outtextxy(485, 175, "2");
	outtextxy(685, 175, "3");
	outtextxy(885, 175, "4");

	outtextxy(285, 375, "5");
	outtextxy(485, 375, "6");
	outtextxy(685, 375, "7");
	outtextxy(885, 375, "8");

	outtextxy(260, 575, "9");
	outtextxy(460, 575, "10");
	outtextxy(660, 575, "11");
	outtextxy(860, 575, "12");

	outtextxy(260, 775, "13");
	outtextxy(460, 775, "14");
	outtextxy(660, 775, "15");
	outtextxy(860, 775, "16");


	setcolor(15);
	setlinestyle(2, 1, 10);
	//horizontal lines
	line(200, 100, 1000, 100);
	line(200, 300, 1000, 300);
	line(200, 500, 1000, 500);
	line(200, 700, 1000, 700);
	line(200, 900, 1000, 900);
	//vertical lines
	line(200, 100, 200, 900);
	line(400, 100, 400, 900);
	line(600, 100, 600, 900);
	line(800, 100, 800, 900);
	line(1000, 100, 1000, 900);


	cout << " " << endl;
	cout << "Welcome to 4x4 Tic Tac Toe! " << endl;
	cout << "To play, simply choose a number where you would like to place your X or O. " << endl;
	cout << "Player 1 is X and Player 2 is O. " << endl;
	cout << " " << endl;


	bool ValidTurn;
	char mark;
	do {
		board();
		player = (player % 2) ? 1 : 2;


		cout << "Player " << player << ", please enter a number:  ";
		cin >> choice;
		mark = (player == 1) ? 'X' : 'O';


		if (choice == 1 && square[1] == "1" && player == 1) {
			square[1] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(260, 140, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 1 && square[1] == "1" && player == 2) {
			square[1] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(260, 140, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 2 && square[2] == "2" && player == 1) {
			square[2] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(460, 140, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 2 && square[2] == "2" && player == 2) {
			square[2] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(460, 140, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 3 && square[3] == "3" && player == 1) {
			square[3] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(660, 140, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 3 && square[3] == "3" && player == 2) {
			square[3] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(660, 140, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 4 && square[4] == "4" && player == 1) {
			square[4] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(860, 140, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 4 && square[4] == "4" && player == 2) {
			square[4] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(860, 140, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 5 && square[5] == "5" && player == 1) {
			square[5] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(260, 340, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 5 && square[5] == "5" && player == 2) {
			square[5] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(260, 340, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 6 && square[6] == "6" && player == 1) {
			square[6] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(460, 340, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 6 && square[6] == "6" && player == 2) {
			square[6] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(460, 340, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 7 && square[7] == "7" && player == 1) {
			square[7] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(660, 340, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 7 && square[7] == "7" && player == 2) {
			square[7] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(660, 340, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 8 && square[8] == "8" && player == 1) {
			square[8] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(860, 340, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 8 && square[8] == "8" && player == 2) {
			square[8] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(860, 340, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 9 && square[9] == "9" && player == 1) {
			square[9] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(260, 540, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 9 && square[9] == "9" && player == 2) {
			square[9] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(260, 540, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 10 && square[10] == "10" && player == 1) {
			square[10] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(460, 540, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 10 && square[10] == "10" && player == 2) {
			square[10] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(460, 540, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 11 && square[11] == "11" && player == 1) {
			square[11] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(660, 540, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 11 && square[11] == "11" && player == 2) {
			square[11] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(660, 540, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 12 && square[12] == "12" && player == 1) {
			square[12] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(860, 540, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 12 && square[12] == "12" && player == 2) {
			square[12] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(860, 540, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 13 && square[13] == "13" && player == 1) {
			square[13] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(260, 740, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 13 && square[13] == "13" && player == 2) {
			square[13] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(260, 740, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 14 && square[14] == "14" && player == 1) {
			square[14] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(460, 740, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 14 && square[14] == "14" && player == 2) {
			square[14] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(460, 740, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 15 && square[15] == "15" && player == 1) {
			square[15] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(660, 740, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 15 && square[15] == "15" && player == 2) {
			square[15] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(660, 740, "O");
			putpixel(1, 1, 0);
		}


		else if (choice == 16 && square[16] == "16" && player == 1) {
			square[16] = mark;
			setcolor(5);
			sizer = 50;
			settextstyle(8, 0, sizer);
			outtextxy(860, 740, "X");
			putpixel(1, 1, 0);
		}
		else if (choice == 16 && square[16] == "16" && player == 2) {
			square[16] = mark;
			setcolor(4);
			sizer = 80;
			settextstyle(8, 0, sizer);
			outtextxy(860, 740, "O");
			putpixel(1, 1, 0);
		}


		else {
			cout << "That move is invalid. Please press enter and choose a valid number. ";
			player--;
			cin.ignore();
			cin.get();
		}


		i = checkwin();
		player++;
	}


	while (i == -1);
	board();
	if (i == 1)
		cout << "Player " << --player << " wins! ";

	else
		cout << "It's a Draw!";

	cin.ignore();
	cin.get();
	return 0;
}




int checkwin()
{
	if (square[1] == square[2] && square[2] == square[3] && square[3] == square[4])

		return 1;
	else if (square[5] == square[6] && square[6] == square[7] && square[7] == square[8])

		return 1;
	else if (square[9] == square[10] && square[10] == square[11] && square[11] == square[12])

		return 1;
	else if (square[13] == square[14] && square[14] == square[15] && square[15] == square[16])

		return 1;
	else if (square[1] == square[5] && square[5] == square[9] && square[9] == square[13])

		return 1;
	else if (square[2] == square[6] && square[6] == square[10] && square[10] == square[14])

		return 1;
	else if (square[3] == square[7] && square[7] == square[11] && square[11] == square[15])

		return 1;
	else if (square[4] == square[8] && square[8] == square[12] && square[12] == square[16])

		return 1;
	else if (square[1] == square[6] && square[6] == square[11] && square[11] == square[16])

		return 1;
	else if (square[4] == square[7] && square[7] == square[10] && square[10] == square[13])

		return 1;
	else if (square[1] != "1" && square[2] != "2" && square[3] != "3" && square[4] != "4"
		  && square[5] != "5" && square[6] != "6" && square[7] != "7" && square[8] != "8"
	 	  && square[9] != "9" && square[10] != "10" && square[11] != "11" && square[12] != "12"
		&& square[13] != "13" && square[14] != "14" && square[15] != "15" && square[16] != "16")

		return 0;
	else
		return -1;
}
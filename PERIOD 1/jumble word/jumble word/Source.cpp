#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Letters.h"
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <thread>
#include "VirtualKeys.h"
#include <array>
#include <winbgi.cpp>

using namespace std;

class StringBuilder {
private:
	std::string main;
	std::string scratch;

	const std::string::size_type ScratchSize = 1024;  // or some other arbitrary number

public:
	StringBuilder & append(const std::string & str) {
		scratch.append(str);
		if (scratch.size() > ScratchSize) {
			main.append(scratch);
			scratch.resize(0);
		}
		return *this;
	}

	const std::string & str() {
		if (scratch.size() > 0) {
			main.append(scratch);
			scratch.resize(0);
		}
		return main;
	}
};
struct KeyState {
	int VirtualKey;
	bool isAlpha;
	bool isNumeric;
	bool isMove;
	bool isClicked;
	string Significance;
	bool isPressed;
	POINT Cursor;
	void reset() {
		Significance = "";
		isPressed = false;
		isClicked = false;
		isAlpha = false;
		isNumeric = false;
		VirtualKey = 0;
		Cursor = POINT();
	}
	void resetKey() {
		Significance = "";
		isPressed = false;
		isAlpha = false;
		isNumeric = false;
		VirtualKey = 0;
	}
}GLOBAL;
struct RGB {
	int r;
	int g;
	int b;
	int colorVal;
	void init(int R, int G, int B) {
		r = R;
		g = G;
		b = B;
	}
	void init(int R, int G, int B, int c) {
		r = R;
		g = G;
		b = B;
		colorVal = c;
	}
	bool isEqual(RGB t) {
		return r == t.r && g == t.g && b == t.b;
	}
};
const int NUMVECTOR = 8;
//declaring variables
int i, maxX, maxY, w, h;
int GrDriver, GrMode, GrErrorCode;
bool isRunning = true;
bool isName = false;
int UNIT = 20;
string FINAL = "";
vector <int> scores; //array for scores of found words
vector <string> wordlist; //array for found matched words
vector <string> word; //array of strings for dictionary words about to be read it
string tester;//string for scrambled letters that will be read in
vector <RGB> colors(NUMVECTOR);

#define WINDOWS 1

/// READBMP Utility
string toUpper(string s) {
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] >= 97 && s[i] <= 122)
			s[i] -= 32;
	}
	return s;
}
/// Main Function LOADBMP
unsigned char* ReadBMP(char* filename)
{
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
		throw "Argument Exception";
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	int width, height;
	// extract image height and width from header
	if (w == 0 || h == 0) {
		width = *(int*)&info[18];
		height = *(int*)&info[22];
	}
	else {
		width = w;
		height = h;
	}
	string n(filename);
	n = n.substr(0, n.length() - 4);
	cout << "FILE : " << n << endl;
	cout << endl;
	cout << "  Name: " << filename << endl;
	cout << " Width: " << width << endl;
	cout << "Height: " << height << endl;
	ofstream files, paint;
	files.open("RGB.txt");
	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[row_padded];
	unsigned char tmp;
	paint.open("paint.txt");
	for (int i = 0; i < height; i++)
	{
		fread(data, sizeof(unsigned char), row_padded, f);
		paint << "{ ";
		for (int j = 0; j < width * 3; j += 3)
		{
			// Convert (B, G, R) to (R, G, B)
			tmp = data[j];
			data[j] = data[j + 2];
			data[j + 2] = tmp;
			files << "[" << (int)data[j] << ", " << (int)data[j + 1] << "," << (int)data[j + 2] << "] ";
			RGB n;
			n.init(data[j], data[j + 1], data[j + 2]);
			bool exits = false;
			for (int index = 0; !exits && index < (int)colors.size(); index++)
				if (colors.at(index).isEqual(n))
				{
					exits = true;
					paint << colors.at(index).colorVal;
				}
			if (j + 3 >= (width * 3)) {
				paint << "}," << endl;
			}
			else
				paint << ", ";
			if (!exits)
				colors.push_back(n);
		}
		files << '\n';
	}
	files.close();
	paint.close();
	files.open("vectorBuild.txt");
	for (int i = 0; i < (int)colors.size(); i++)
		files << "colors.at(" << i << ").init( " << colors.at(i).r << ", " << colors.at(i).g << ", " << colors.at(i).b << ", ); \n";
	files.close();
	vector <string> hold;
	ifstream reverse;
	reverse.open("paint.txt");
	while (!reverse.eof()) {
		string line;
		getline(reverse, line);
		hold.push_back(line);
	}
	reverse.close();
	paint.open("paint.txt");
	paint << "const int " << n << "_Height = " << height << "; \n";
	paint << "const int " << n << "_Width = " << width << "; \n";
	paint << "#pragma region " << toUpper(n) << "_DRAW \n";
	paint << "const int " << n << "_ARRY [" << height << "][" << width << "] = { \n";
	while (!hold.empty()) {
		paint << hold.back() << "\n";
		hold.pop_back();
	}
	paint << "}; \n \n #pragma endregion \n";
	paint.close();
	fclose(f);
	return data;
}
/// Start/Setup Graphics Window
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode) {
	GrDriver = VGA;
	GrMode = VGAMAX;
	initgraph(&GrDriver, &GrMode, "");
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
		system("pause");
		exit(0);
	}
	/// HIDE CONSOLE
	maxX = getmaxx();
	maxY = getmaxy();
	return;
}
/// AsynKeyState
bool ActionListener(int VirtualKey) {
	return ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
}
void drawLetter(int x, int y, string LETTER) {
	int letter = (int)LETTER[0] - (int)'A';
	if (LETTER[0] == ' ') {
		letter = 26;
	}
		for(int j = 0; j < 5; j++)
			for (int i = 0; i < 5; i++) {
				if (NEW_ALPHA[letter][j][i]) {
					setcolor(WHITE);
				}
				else {
					setcolor(DARKGRAY);
				}
				fillellipse(x + (UNIT * (i)) + (UNIT / 2), y + (UNIT * (j)) + (UNIT / 2), UNIT / 2, UNIT / 2);
			}
}
void drawFLASHWORD(int x, int y, string WORD) {
	for (int l = 0; l < 195; l++) {
		for (int k = 0; k < (int)WORD.length(); k++) {
			int letter = (int)WORD[k] - (int)'A';
			if (WORD[k] == ' ') {
				letter = 26;
			}
			for (int j = 0; j < 5; j++)
				for (int i = 0; i < 5; i++) {
					if (NEW_ALPHA[letter][j][i]) {
						if (l % 2 == 0)
							setcolor(GREEN);
						else
							setcolor(LIGHTGREEN);
					}
					else {
						setcolor(DARKGRAY);
					}
					fillellipse(x + (UNIT * (i+(k*5))) + (UNIT / 2), y + (UNIT * (j)) + (UNIT / 2), UNIT / 2, UNIT / 2);
				}
		}
		Sleep(150);
		if (FINAL != "") {
			setcolor(WHITE);
			outtextxy((maxX - textwidth(FINAL.c_str())) / 2, y + (7 * UNIT), FINAL.c_str());
		}

	}
	return;
}
void drawLetter(int x, int y, char LETTER) {
	int letter = (int)LETTER - (int)'A';
	if (LETTER == ' ') {
		letter = 26;
	}
	for (int j = 0; j < 5; j++)
		for (int i = 0; i < 5; i++) {
			if (NEW_ALPHA[letter][j][i]) {
				setcolor(WHITE);
			}
			else {
				setcolor(DARKGRAY);
			}
			fillellipse(x + (UNIT * (i)) + (UNIT / 2), y + (UNIT * (j)) + (UNIT / 2), UNIT / 2, UNIT / 2);
		}
}
void LetterJumble(int x, int y) {
	setcolor(DARKGRAY);
	for (int j = 0; j < 5; j++)
		for (int i = 0; i < 5; i++) {
			fillellipse(x + (UNIT * (i)) + (UNIT / 2), y + (UNIT * (j)) + (UNIT / 2), UNIT / 2, UNIT / 2);
		}
}
/// LOAD BMP Call Function
void CREATE(string test) {
	w = 0;
	h = 0;
	/*Copy all the vector values color.at() HERE*/
#pragma region example

	
	/*
	*/
#pragma endregion
	/*Make sure the *.bmp file is located in the same directory as the Source.cpp file*/
	ReadBMP(TEXT((LPTSTR)test.c_str())); // 24 bit depth .bmp
										 /*
										 Creates multiple files, find the vector
										 use this to normalize the RGB values from what they are to
										 the 16 valid choices with WINBGI
										 copy and paste all those values.
										 colors.at(0).init(#,#,#, );
										 colors.at(1).init(#,#,#, );
										 ...
										 colors.at(#).init(#,#,#, );
										 replace the variable NUMVECTOR Value with the last # + 1;
										 also after each 3rd number in the parameter list of
										 init()
										 i.e. init(#, #, #, _HERE_);
										 Use the number value for the associated color from the
										 WINBGI List and the value must coorespond.
										 Run this program again. After copying and pasting all those values above where
										 you call ReadBMP(*);
										 This will creat a text file called paintByNum.
										 Copy the information from there.
										 */
	system("pause");
}

/// GET INPUT KEY LISTENER
void StringBuilderZ() {
	string NAME = "";
	isName = true;
	string BufferedReader = "";
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
					NAME += BufferedReader;
				}
				else {
					NAME = NAME.substr(0, NAME.length() - 1);
				}
			}
			do { Sleep(3); } while (ActionListener(GLOBAL.VirtualKey));
			GLOBAL.resetKey();
			setcolor(BLACK);
			bar(left, top, right, bottom);
			setcolor(WHITE);
			left = (maxX - textwidth(NAME.c_str())) / 2;
			right = left + textwidth(NAME.c_str());
			top = (maxY - OFFSET - textheight(NAME.c_str())) / 2;
			bottom = top + textheight(NAME.c_str());
			outtextxy(left, top, NAME.c_str());
			//cout << NAME << "\n";

		}

		Sleep(15);
	}
	isName = false;
	isRunning = false;
	tester = NAME;
}

void Listener() {
	GLOBAL.reset();
	bool Konami = false;
	while (isRunning) {
		if (!GLOBAL.isPressed) {
			/// Mouse Listener
			if (ActionListener(VK_LBUTTON)) {
				// Left Mouse Button
				GetCursorPos(&GLOBAL.Cursor);
				GLOBAL.VirtualKey = VK_LBUTTON;
				GLOBAL.Significance = "Left Mouse Click";
				do { Sleep(100); } while (ActionListener(VK_LBUTTON));
				GLOBAL.isClicked = true;
			}
			/// Irregular KeyListener Build String
			if (isName) {
				if (ActionListener(VK_A)) {
					GLOBAL.VirtualKey = VK_A;
					GLOBAL.Significance = "A";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_B)) {
					GLOBAL.VirtualKey = VK_B;
					GLOBAL.Significance = "B";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_C)) {
					GLOBAL.VirtualKey = VK_C;
					GLOBAL.Significance = "C";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_D)) {
					GLOBAL.VirtualKey = VK_D;
					GLOBAL.Significance = "D";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_E)) {
					GLOBAL.VirtualKey = VK_E;
					GLOBAL.Significance = "E";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_F)) {
					GLOBAL.VirtualKey = VK_F;
					GLOBAL.Significance = "F";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_G)) {
					GLOBAL.VirtualKey = VK_G;
					GLOBAL.Significance = "G";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_H)) {
					GLOBAL.VirtualKey = VK_H;
					GLOBAL.Significance = "H";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_I)) {
					GLOBAL.VirtualKey = VK_I;
					GLOBAL.Significance = "I";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_J)) {
					GLOBAL.VirtualKey = VK_J;
					GLOBAL.Significance = "J";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_K)) {
					GLOBAL.VirtualKey = VK_K;
					GLOBAL.Significance = "K";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_L)) {
					GLOBAL.VirtualKey = VK_L;
					GLOBAL.Significance = "L";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_M)) {
					GLOBAL.VirtualKey = VK_M;
					GLOBAL.Significance = "M";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_N)) {
					GLOBAL.VirtualKey = VK_N;
					GLOBAL.Significance = "N";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_O)) {
					GLOBAL.VirtualKey = VK_O;
					GLOBAL.Significance = "O";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_P)) {
					GLOBAL.VirtualKey = VK_P;
					GLOBAL.Significance = "P";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_Q)) {
					GLOBAL.VirtualKey = VK_Q;
					GLOBAL.Significance = "Q";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_R)) {
					GLOBAL.VirtualKey = VK_R;
					GLOBAL.Significance = "R";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_S)) {
					GLOBAL.VirtualKey = VK_S;
					GLOBAL.Significance = "S";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_T)) {
					GLOBAL.VirtualKey = VK_T;
					GLOBAL.Significance = "T";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_U)) {
					GLOBAL.VirtualKey = VK_U;
					GLOBAL.Significance = "U";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_V)) {
					GLOBAL.VirtualKey = VK_V;
					GLOBAL.Significance = "V";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_W)) {
					GLOBAL.VirtualKey = VK_W;
					GLOBAL.Significance = "W";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_X)) {
					GLOBAL.VirtualKey = VK_X;
					GLOBAL.Significance = "X";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_Y)) {
					GLOBAL.VirtualKey = VK_Y;
					GLOBAL.Significance = "Y";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_Z)) {
					GLOBAL.VirtualKey = VK_Z;
					GLOBAL.Significance = "Z";
					GLOBAL.isAlpha = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_1) || ActionListener(VK_NUMPAD1)) {
					GLOBAL.VirtualKey = VK_1;
					GLOBAL.Significance = "1";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_2) || ActionListener(VK_NUMPAD2)) {
					GLOBAL.VirtualKey = VK_2;
					GLOBAL.Significance = "2";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_3) || ActionListener(VK_NUMPAD3)) {
					GLOBAL.VirtualKey = VK_3;
					GLOBAL.Significance = "3";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_4) || ActionListener(VK_NUMPAD4)) {
					GLOBAL.VirtualKey = VK_4;
					GLOBAL.Significance = "4";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_5) || ActionListener(VK_NUMPAD5)) {
					GLOBAL.VirtualKey = VK_5;
					GLOBAL.Significance = "5";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_6) || ActionListener(VK_NUMPAD6)) {
					GLOBAL.VirtualKey = VK_6;
					GLOBAL.Significance = "6";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_7) || ActionListener(VK_NUMPAD7)) {
					GLOBAL.VirtualKey = VK_7;
					GLOBAL.Significance = "7";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_8) || ActionListener(VK_NUMPAD8)) {
					GLOBAL.VirtualKey = VK_8;
					GLOBAL.Significance = "8";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_9) || ActionListener(VK_NUMPAD9)) {
					GLOBAL.VirtualKey = VK_9;
					GLOBAL.Significance = "9";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_0) || ActionListener(VK_NUMPAD0)) {
					GLOBAL.VirtualKey = VK_0;
					GLOBAL.Significance = "0";
					GLOBAL.isNumeric = true;
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_RETURN)) {
					GLOBAL.VirtualKey = VK_RETURN;
					GLOBAL.Significance = "RETURN";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_SPACE)) {
					GLOBAL.VirtualKey = VK_SPACE;
					GLOBAL.Significance = " ";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_BACK)) {
					GLOBAL.VirtualKey = VK_BACK;
					GLOBAL.Significance = "BACK";
					GLOBAL.isPressed = true;
				}
			}
			/// Regular Movements for FROGGER
			else {
				if (ActionListener(VK_LEFT)) {
					GLOBAL.VirtualKey = VK_LEFT;
					GLOBAL.Significance = "LEFT";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_RIGHT)) {
					GLOBAL.VirtualKey = VK_RIGHT;
					GLOBAL.Significance = "RIGHT";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_UP)) {
					GLOBAL.VirtualKey = VK_UP;
					GLOBAL.Significance = "UP";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_DOWN)) {
					GLOBAL.VirtualKey = VK_DOWN;
					GLOBAL.Significance = "DOWN";
					GLOBAL.isPressed = true;
				}
				else if (ActionListener(VK_F6)) {
					GLOBAL.VirtualKey = VK_F6;
					GLOBAL.Significance = "F6";
					Konami = true;
				}  /// Novelty EASTER EGG insta kill yourself button
				else if (ActionListener(VK_ESCAPE)) {
					isRunning = false;
					exit(0);
				}
			
			}
		}
		Sleep(15);
	}
}

string trim(string t) {
	if (t == "")
		return t;
	else if (t[0] == ' ')
		return trim(t.substr(1));
	else if (t[(int)t.length() - 1] == ' ')
		return trim(t.substr(0, (int)t.length() - 1));
	return t;
}
string to_lower(string t) {
	for (int i = 0; i < (int)t.length(); i++)
		t[i] += (97 - 65);
	return t;
}
void animation() {

	string temp = "JWODRBLMUE ";
	int titleX = (maxX - (temp.length() * 5 * UNIT)) / 2;
	int titleY = (maxY - (5 * UNIT)) / 2;

	/// RESET
	for (int i = 0; i < (int)temp.length(); i++) {
		if (temp[i] != ' ') {
			LetterJumble(titleX + (i * (5 * UNIT)), titleY);
		}
	}
	temp = "WORD JUMBLE";
	for (int i = 0; i < (int)temp.length(); i++) {
		drawLetter(titleX + (i * (5 * UNIT)), titleY, temp[i]);
	}

	sort(temp.begin(), temp.end());
	while (isRunning && next_permutation(temp.begin(), temp.end())) {
		/// RESET
		for (int i = 0; i < (int)temp.length(); i++) {
			
				drawLetter(titleX + (i * (5 * UNIT)), titleY, temp[i]);
		
		}
		Sleep(5);
		if (temp == "WORD JUMBLE") {
			break;
		}
	}
	temp = "WORD JUMBLE";
	drawFLASHWORD(titleX, titleY, temp);
	while (FINAL == "") {
		Sleep(100);
	}
	setcolor(WHITE);
	outtextxy((maxX - textwidth(FINAL.c_str())) / 2, titleY + (7 * UNIT), FINAL.c_str());
	do {
		Sleep(15);
	} while (!ActionListener(VK_RETURN));
	getch();
}

void console_clear_screen() {
#ifdef WINDOWS
	system("cls");
#endif
#ifdef LINUX
	system("clear");
#endif
}

int scorefinder(string scrab) //SCORE FINDER FUNCTION
{
	int score = 0;
	int x = 0;
	int j = 0;
	while (j < (int)scrab.length())
	{
		char ltr = toupper(scrab[j]); //converts to all caps

									  //assings values to each letter and adds it to itself
		if (ltr == 'A' || ltr == 'E' || ltr == 'I' || ltr == 'L' || ltr == 'N' || ltr == 'O' || ltr == 'R' || ltr == 'S' || ltr == 'T' || ltr == 'U')
			x += 1;
		else if (ltr == 'D' || ltr == 'G')
			x += 2;
		else if (ltr == 'B' || ltr == 'C' || ltr == 'M' || ltr == 'P')
			x += 3;
		else if (ltr == 'F' || ltr == 'H' || ltr == 'V' || ltr == 'W' || ltr == 'Y')
			x += 4;
		else if (ltr == 'K')
			x += 5;
		else if (ltr == 'J' || ltr == 'X')
			x += 8;
		else if (ltr == 'Q' || ltr == 'Z')
			x += 10;
		++j;
	}
	score = x;
	return score;
}

void brain() {
	tester = trim(tester);
	tester = to_lower(tester);
	sort(tester.begin(), tester.end()); //sorts scrambled letters for next_permutation
	bool special = true;
	// Create a sum variable.
	int sum = 0;
	int testLEN = (int)tester.length();
	for (int i = 0; i < (int)word.size(); i++) {
		int wordLen = (int)word[i].length();
		
		if (wordLen == testLEN) {
			if (tester == word[i]) {//is_permutation(word[i].begin(), word[i].end(), tester.begin())) {
				word[i]; //assigns found word to foundword array
				scores[i] = scorefinder(tester); //assigns found word score to foundscore array
				//sum += scores[i];
			}
		}
	}
	while (next_permutation(tester.begin(), tester.end())) {  //while there are still permutations available
		special = false;
		//cout << tester << "\n";
		for (int i = 0; i < (int)word.size(); i++) {
			int wordLen = (int)word[i].length();
			
			if (wordLen == testLEN) {
				if (tester == word[i]) {//is_permutation(word[i].begin(), word[i].end(), tester.begin())) {
					word[i]; //assigns found word to foundword array
					scores[i] = scorefinder(tester); //assigns found word score to foundscore array
					//sum += scores[i];
				}
			}
		}
	}
	sum = 0;
	//PRINTS OUT ONLY MATCHED WORDS AND SCORES
	for (i = 0; i < (int)word.size(); i++) {
		if (scores[i] != 0) {
			sum += scores[i];
			cout << "Found word: " << word[i] << " " << scores[i] << "\n";
		}
	}
	string value = "FINAL SCORE : " + to_string(sum);
	cout << "FINAL SCORE : " << sum << "\n";
	FINAL = value;
	isRunning = false;
}

int main() {

	//NO GO TOO IRREGULAR
	/*
	for (int i = 0; i < 26; i++)
	{
		string temp = "A";
		temp[0] += i;
		temp += ".bmp";
		CREATE(temp);
	}
	*/
	//READS IN DICTIONARY
	ifstream file("dictionary.txt"); //reads in dictionary
	if (!file.is_open()) { //checks if file is being NOT read correctly
		cout << "BROKEN \n"; //prints error message if so
	}
	if (file.is_open()) { //checks if file IS being read correctly
		string temp;
		while (!file.eof()) {
			file >> temp; //read in each word from the file and 
			word.push_back(temp);
			scores.push_back(0);
		}   //assigns each to it's position in the words array
	}
	//END OF READ IN DICTIONARY


	///Incorporated with WinBGI
	int gd = DETECT, gm;

	//initgraph(&gd, &gm, "C:\\TC\\BGI");
	gr_Start(GrDriver, GrMode, GrErrorCode);
	while (true) {
		FINAL = "";
		/*
		for (int i = 0; i < 26; i++) {
			string temp = "A";
			temp[0] += i;
			drawLetter(maxX / 2 - (2.5 * UNIT), maxY / 2 - (2.5 * UNIT), temp);
			getch();
		}
		*/

		/*

		string temp = "JWODRBLMUE";
		int titleX =(maxX - (temp.length() * 5 * UNIT))/2;
		int titleY = (maxY - (5*UNIT))/2;
		/// RESET
		for (int i = 0; i < (int)temp.length(); i++) {
			if (temp[i] != ' ') {
				LetterJumble(titleX + (i * (5 * UNIT)), titleY);
			}
		}
		for (int i = 0; i < (int)temp.length(); i++) {
				drawLetter(titleX + (i * (5 * UNIT)), titleY, temp[i]);
		}

		//sort(temp.begin(), temp.end());
		while (next_permutation(temp.begin(), temp.end())) {
			/// RESET
			for (int i = 0; i < (int)temp.length() + 1; i++) {
				if (i == 4) {
					drawLetter(titleX + (i * (5 * UNIT)), titleY, ' ');
				}
				else {
					drawLetter(titleX + (i * (5 * UNIT)), titleY, temp[i]);
				}
			}
			Sleep(5);
			if (temp == "WORDJUMBLE") {
				break;
			}
		}
		*/
		settextstyle(1, HORIZ_DIR, 7);
		//1, serif
		//4, sans serif
		//2, small reg font
		//setcolor(1);
		//setbkcolor(9);
		//outtextxy(100, 100, "WORD JUMBLE");
		string temp = "WORD JUMBLE";
		int titleX = (maxX - (temp.length() * 5 * UNIT)) / 2;
		int titleY = (maxY - (5 * UNIT)) / 2;
		for (int i = 0; i < (int)temp.length(); i++) {
			drawLetter(titleX + (i * (5 * UNIT)), titleY, temp[i]);
		}

		getch();
		//closegraph();
		//return 0;
		//system("pause");

		///END

		//system("clear");
		cleardevice();
		setcolor(WHITE);
		string QUESTION = "ENTER SCRAMBLED LETTERS : ";
		outtextxy((maxX - textwidth(QUESTION.c_str())) / 2, (maxY - textheight(QUESTION.c_str())) / 2, QUESTION.c_str());
		outtextxy((maxX - textwidth(QUESTION.c_str())) / 2, (maxY - textheight(QUESTION.c_str())) / 2, QUESTION.c_str());
		putpixel(0, 0, 0);
		Sleep(1500);
		cleardevice();

		thread QUEST(Listener);
		thread test(StringBuilderZ);
		QUEST.join();
		test.join();

		Sleep(100);
		cleardevice();
		isRunning = true;
		thread VISUAL(animation);
		thread BRAIN(brain);

		VISUAL.join();
		BRAIN.join();

		//cout << "Enter scrambled letters: ";
		//cin >> tester; //reads in scrambled letters
		cleardevice();
	}
	system("pause");
}


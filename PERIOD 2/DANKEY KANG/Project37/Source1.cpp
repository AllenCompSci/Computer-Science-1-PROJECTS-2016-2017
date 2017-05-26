#include "test.h"


#pragma region GLOBALVARs

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
//void gameThread();
enum GAMESTATE { START_MENU, PLAYER_1, GAME, END };
enum DIRECTION { UP, RIGHT, DOWN, LEFT, PAUSE, SELECT, LEFTCLICK };
bool isRunning = true;
bool debug = false;
GAMESTATE DK = START_MENU;

const int NUMVECTOR = 734; /// HERE 
struct pass {
	int VirtualKey;
	bool isPressed;
	bool isHeld;
	DIRECTION move;
	void reset() {
		isPressed = false;
		isHeld = false;
	}
	POINT p;
}playerInput1, mouseInput;

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
void KEY_LISTENER() {


	centerX = getmaxx() / 2;
	centerY = getmaxy() / 2;
	
	
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

		// Room For More Ifs specified keys act in a specific way.
		// look through the VirtualKeys.h list to have other specific keys
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
		GetCursorPos(&mouseInput.p);
		mouseInput.isPressed = true;
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
		
		playerInput1.isPressed = true;
		playerInput1.VirtualKey = VirtualKey;
		int count = 0;
		do {
			if (count++ > 200) {
				playerInput1.isHeld = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}
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
int w, h;
/*
0  BLACK
1  BLUE
2  GREEN
3  CYAN
4  RED
5  MAGENTA
6  BROWN
7  LIGHTGRAY
8  DARKGRAY
9  LIGHTBLUE
10 LIGHTGREEN
11 LIGHTCYAN
12 LIGHTRED
13 LIGHTMAGENTA
14 YELLOW
15 WHITE
*/

vector <RGB> colors(NUMVECTOR);

string toUpper(string s) {
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] >= 97 && s[i] <= 122)
			s[i] -= 32;
	}
	return s;
}
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
void main() {
	w = 0;
	h = 0;
	/*Copy all the vector values color.at() HERE*/
	
#pragma region RGB Values
	/// PASTE VECTOR BUILD HERE
	
	//DK Front
	colors.at(0).init(252, 252, 252, 15);
	colors.at(1).init(0, 0, 0, 0);
	colors.at(2).init(255, 255, 255, 15);
	colors.at(3).init(243, 216, 190, 4);
	colors.at(4).init(29, 239, 34, 99);
	colors.at(5).init(168, 16, 0, 6);
	colors.at(6).init(240, 208, 176, 4);
	colors.at(7).init(30, 239, 35, 99);
	colors.at(8).init(31, 239, 36, 99);
	colors.at(9).init(0, 91, 127, 1);
	//Mario Run
	colors.at(10).init(252, 252, 252, 15);
	colors.at(11).init(0, 0, 0, 0);
	colors.at(12).init(255, 255, 255, 15);
	colors.at(13).init(243, 216, 190, 14);
	colors.at(14).init(29, 239, 34, 99);
	colors.at(15).init(168, 16, 0, 4);
	colors.at(16).init(240, 208, 176, 14);
	colors.at(17).init(30, 239, 35, 99);
	colors.at(18).init(31, 239, 36, 99);
	colors.at(19).init(0, 91, 127, 1);
	colors.at(20).init(12, 249, 56, 99);
	colors.at(21).init(0, 0, 188, 1);
	colors.at(22).init(248, 56, 0, 4);
	//Girl
	colors.at(23).init(252, 252, 252, 15);
	colors.at(24).init(0, 0, 0, 0);
	colors.at(25).init(255, 255, 255, 15);
	colors.at(26).init(243, 216, 190, 14);
	colors.at(27).init(29, 239, 34, 99);
	colors.at(28).init(168, 16, 0, 13);
	colors.at(29).init(240, 208, 176, 14);
	colors.at(30).init(30, 239, 35, 99);
	colors.at(31).init(31, 239, 36, 99);
	colors.at(32).init(0, 91, 127, 1);
	colors.at(33).init(252, 252, 252, 15);
	colors.at(34).init(0, 0, 0, 0);
	colors.at(35).init(255, 255, 255, 15);
	colors.at(36).init(243, 216, 190, 14);
	colors.at(37).init(29, 239, 34, 99);
	colors.at(38).init(168, 16, 0, 13);
	colors.at(39).init(240, 208, 176, 14);
	colors.at(40).init(30, 239, 35, 99);
	colors.at(41).init(31, 239, 36, 99);
	colors.at(42).init(0, 91, 127, 1);
	colors.at(43).init(12, 249, 56, 99);
	colors.at(44).init(0, 0, 188, 1);
	colors.at(45).init(248, 56, 0, 13);
	colors.at(46).init(252, 252, 252, 15);
	colors.at(47).init(243, 216, 190, 14);
	colors.at(48).init(29, 239, 34, 99);
	colors.at(49).init(168, 16, 0, 13);
	colors.at(50).init(30, 239, 35, 99);
	colors.at(51).init(31, 239, 36, 99);
	colors.at(52).init(0, 91, 127, 1);
	colors.at(53).init(29, 239, 34, 99);
	colors.at(54).init(30, 239, 35, 99);
	colors.at(55).init(31, 239, 36, 99);
	colors.at(56).init(12, 249, 56, 99);
	colors.at(57).init(60, 255, 0, 99);
	colors.at(58).init(55, 241, 11, 99);
	colors.at(59).init(56, 243, 9, 99);
	colors.at(60).init(59, 253, 1, 99);
	colors.at(61).init(252, 160, 68, 13);
	colors.at(62).init(248, 120, 248, 13);
	colors.at(63).init(1, 94, 125, 1);
	colors.at(64).init(1, 93, 126, 1);
	colors.at(65).init(0, 92, 127, 1);
	//levelONE
	colors.at(66).init(252, 252, 252, 15);
	colors.at(67).init(0, 0, 0, 0);
	colors.at(68).init(255, 255, 255, 15);
	colors.at(69).init(243, 216, 190, 6);
	colors.at(70).init(29, 239, 34, 99);
	colors.at(71).init(168, 16, 0, 5);
	colors.at(72).init(240, 208, 176, 6);
	colors.at(73).init(30, 239, 35, 99);
	colors.at(74).init(31, 239, 36, 99);
	colors.at(75).init(0, 91, 127, 3);
	colors.at(76).init(252, 252, 252, 15);
	colors.at(77).init(0, 0, 0, 0);
	colors.at(78).init(255, 255, 255, 15);
	colors.at(79).init(243, 216, 190, 6);
	colors.at(80).init(29, 239, 34, 99);
	colors.at(81).init(168, 16, 0, 5);
	colors.at(82).init(240, 208, 176, 6);
	colors.at(83).init(30, 239, 35, 99);
	colors.at(84).init(31, 239, 36, 99);
	colors.at(85).init(0, 91, 127, 3);
	colors.at(86).init(12, 249, 56, 99);
	colors.at(87).init(0, 0, 188, 1);
	colors.at(88).init(248, 56, 0, 5);
	colors.at(89).init(252, 252, 252, 15);
	colors.at(90).init(0, 0, 0, 0);
	colors.at(91).init(255, 255, 255, 15);
	colors.at(92).init(243, 216, 190, 6);
	colors.at(93).init(29, 239, 34, 99);
	colors.at(94).init(168, 16, 0, 5);
	colors.at(95).init(240, 208, 176, 6);
	colors.at(96).init(30, 239, 35, 99);
	colors.at(97).init(31, 239, 36, 99);
	colors.at(98).init(0, 91, 127, 1);
	colors.at(99).init(252, 252, 252, 15);
	colors.at(100).init(0, 0, 0, 0);
	colors.at(101).init(255, 255, 255, 15);
	colors.at(102).init(243, 216, 190, 6);
	colors.at(103).init(29, 239, 34, 99);
	colors.at(104).init(168, 16, 0, 5);
	colors.at(105).init(240, 208, 176, 6);
	colors.at(106).init(30, 239, 35, 99);
	colors.at(107).init(31, 239, 36, 99);
	colors.at(108).init(0, 91, 127, 1);
	colors.at(109).init(12, 249, 56, 99);
	colors.at(110).init(0, 0, 188, 1);
	colors.at(111).init(248, 56, 0, 5);
	colors.at(112).init(252, 252, 252, 15);
	colors.at(113).init(243, 216, 190, 6);
	colors.at(114).init(29, 239, 34, 99);
	colors.at(115).init(168, 16, 0, 5);
	colors.at(116).init(30, 239, 35, 99);
	colors.at(117).init(31, 239, 36, 99);
	colors.at(118).init(0, 91, 127, 3);
	colors.at(119).init(29, 239, 34, 99);
	colors.at(120).init(30, 239, 35, 99);
	colors.at(121).init(31, 239, 36, 99);
	colors.at(122).init(12, 249, 56, 99);
	colors.at(123).init(60, 255, 0, 99);
	colors.at(124).init(55, 241, 11, 99);
	colors.at(125).init(56, 243, 9, 99);
	colors.at(126).init(59, 253, 1, 99);
	colors.at(127).init(252, 160, 68, 6);
	colors.at(128).init(248, 120, 248, 5);
	colors.at(129).init(1, 94, 125, 3);
	colors.at(130).init(1, 93, 126, 3);
	colors.at(131).init(0, 92, 127, 3);
	colors.at(132).init(0, 255, 18, 99);
	colors.at(133).init(228, 0, 88, 5);
	colors.at(134).init(0, 232, 216, 3);
	colors.at(135).init(1, 255, 19, 99);
	colors.at(136).init(228, 92, 16, 5);
	//Mario Ladder
	colors.at(137).init(252, 252, 252, 15);
	colors.at(138).init(0, 0, 0, 0);
	colors.at(139).init(255, 255, 255, 15);
	colors.at(140).init(243, 216, 190, 6);
	colors.at(141).init(29, 239, 34, 99);
	colors.at(142).init(168, 16, 0, 4);
	colors.at(143).init(240, 208, 176, 6);
	colors.at(144).init(30, 239, 35, 99);
	colors.at(145).init(31, 239, 36, 99);
	colors.at(146).init(0, 91, 127, 1);
	colors.at(147).init(252, 252, 252, 15);
	colors.at(148).init(0, 0, 0, 0);
	colors.at(149).init(255, 255, 255, 15);
	colors.at(150).init(243, 216, 190, 6);
	colors.at(151).init(29, 239, 34, 99);
	colors.at(152).init(168, 16, 0, 4);
	colors.at(153).init(240, 208, 176, 6);
	colors.at(154).init(30, 239, 35, 99);
	colors.at(155).init(31, 239, 36, 99);
	colors.at(156).init(0, 91, 127, 1);
	colors.at(157).init(12, 249, 56, 99);
	colors.at(158).init(0, 0, 188, 1);
	colors.at(159).init(248, 56, 0, 4);
	colors.at(160).init(252, 252, 252, 15);
	colors.at(161).init(0, 0, 0, 0);
	colors.at(162).init(255, 255, 255, 15);
	colors.at(163).init(243, 216, 190, 6);
	colors.at(164).init(29, 239, 34, 99);
	colors.at(165).init(168, 16, 0, 4);
	colors.at(166).init(240, 208, 176, 6);
	colors.at(167).init(30, 239, 35, 99);
	colors.at(168).init(31, 239, 36, 99);
	colors.at(169).init(0, 91, 127, 4);
	colors.at(170).init(252, 252, 252, 15);
	colors.at(171).init(0, 0, 0, 0);
	colors.at(172).init(255, 255, 255, 15);
	colors.at(173).init(243, 216, 190, 6);
	colors.at(174).init(29, 239, 34, 99);
	colors.at(175).init(168, 16, 0, 4);
	colors.at(176).init(240, 208, 176, 6);
	colors.at(177).init(30, 239, 35, 99);
	colors.at(178).init(31, 239, 36, 99);
	colors.at(179).init(0, 91, 127, 4);
	colors.at(180).init(12, 249, 56, 99);
	colors.at(181).init(0, 0, 188, 1);
	colors.at(182).init(248, 56, 0, 4);
	colors.at(183).init(252, 252, 252, 15);
	colors.at(184).init(243, 216, 190, 6);
	colors.at(185).init(29, 239, 34, 99);
	colors.at(186).init(168, 16, 0, 4);
	colors.at(187).init(30, 239, 35, 99);
	colors.at(188).init(31, 239, 36, 99);
	colors.at(189).init(0, 91, 127, 4);
	colors.at(190).init(29, 239, 34, 99);
	colors.at(191).init(30, 239, 35, 99);
	colors.at(192).init(31, 239, 36, 99);
	colors.at(193).init(12, 249, 56, 99);
	colors.at(194).init(60, 255, 0, 99);
	colors.at(195).init(55, 241, 11, 99);
	colors.at(196).init(56, 243, 9, 99);
	colors.at(197).init(59, 253, 1, 99);
	colors.at(198).init(252, 160, 68, 4);
	colors.at(199).init(248, 120, 248, 6);
	colors.at(201).init(1, 94, 125, 1);
	colors.at(202).init(1, 93, 126, 1);
	colors.at(203).init(0, 92, 127, 1);
	colors.at(204).init(252, 252, 252, 15);
	colors.at(205).init(0, 0, 0, 0);
	colors.at(206).init(255, 255, 255, 15);
	colors.at(207).init(243, 216, 190, 6);
	colors.at(208).init(29, 239, 34, 99);
	colors.at(209).init(168, 16, 0, 4);
	colors.at(210).init(240, 208, 176, 6);
	colors.at(211).init(30, 239, 35, 99);
	colors.at(212).init(31, 239, 36, 99);
	colors.at(213).init(0, 91, 127, 1);
	colors.at(214).init(252, 252, 252, 15);
	colors.at(215).init(0, 0, 0, 0);
	colors.at(216).init(255, 255, 255, 15);
	colors.at(217).init(243, 216, 190, 6);
	colors.at(218).init(29, 239, 34, 99);
	colors.at(219).init(168, 16, 0, 1);
	colors.at(220).init(240, 208, 176, 6);
	colors.at(221).init(30, 239, 35, 99);
	colors.at(222).init(31, 239, 36, 99);
	colors.at(223).init(0, 91, 127, 1);
	colors.at(224).init(12, 249, 56, 99);
	colors.at(225).init(0, 0, 188, 1);
	colors.at(226).init(248, 56, 0, 4);
	colors.at(227).init(252, 252, 252, 15);
	colors.at(228).init(0, 0, 0, 0);
	colors.at(229).init(255, 255, 255, 15);
	colors.at(230).init(243, 216, 190, 6);
	colors.at(231).init(29, 239, 34, 99);
	colors.at(232).init(168, 16, 0, 1);
	colors.at(233).init(240, 208, 176, 6);
	colors.at(234).init(30, 239, 35, 99);
	colors.at(235).init(31, 239, 36, 99);
	colors.at(236).init(0, 91, 127, 1);
	colors.at(237).init(252, 252, 252, 15);
	colors.at(238).init(0, 0, 0, 0);
	colors.at(239).init(255, 255, 255, 15);
	colors.at(240).init(243, 216, 190, 6);
	colors.at(241).init(29, 239, 34, 99);
	colors.at(242).init(168, 16, 0, 1);
	colors.at(243).init(240, 208, 176, 6);
	colors.at(244).init(30, 239, 35, 99);
	colors.at(245).init(31, 239, 36, 99);
	colors.at(246).init(0, 91, 127, 1);
	colors.at(247).init(12, 249, 56, 99);
	colors.at(248).init(0, 0, 188, 1);
	colors.at(249).init(248, 56, 0, 4);
	colors.at(250).init(252, 252, 252, 15);
	colors.at(251).init(243, 216, 190, 6);
	colors.at(252).init(29, 239, 34, 99);
	colors.at(253).init(168, 16, 0, 1);
	colors.at(254).init(30, 239, 35, 99);
	colors.at(255).init(31, 239, 36, 99);
	colors.at(256).init(0, 91, 127, 1);
	colors.at(257).init(29, 239, 34, 99);
	colors.at(258).init(30, 239, 35, 99);
	colors.at(259).init(31, 239, 36, 99);
	colors.at(260).init(12, 249, 56, 99);
	colors.at(261).init(60, 255, 0, 99);
	colors.at(262).init(55, 241, 11, 99);
	colors.at(263).init(56, 243, 9, 99);
	colors.at(264).init(59, 253, 1, 99);
	colors.at(265).init(252, 160, 68, 4);
	colors.at(266).init(248, 120, 248, 4);
	colors.at(267).init(1, 94, 125, 1);
	colors.at(268).init(1, 93, 126, 1);
	colors.at(269).init(0, 92, 127, 1);
	colors.at(270).init(0, 255, 18, 99);
	colors.at(271).init(228, 0, 88, 4);
	colors.at(272).init(0, 232, 216, 1);
	colors.at(273).init(1, 255, 19, 99);
	colors.at(274).init(228, 92, 16, 4);
	colors.at(275).init(36, 255, 0, 99);
	//STARTscreen
	colors.at(276).init(252, 252, 252, 15);
	colors.at(277).init(0, 0, 0, 0);
	colors.at(278).init(255, 255, 255, 15);
	colors.at(279).init(243, 216, 190, 6);
	colors.at(280).init(29, 239, 34, 99);
	colors.at(281).init(168, 16, 0, 4);
	colors.at(282).init(240, 208, 176, 6);
	colors.at(283).init(30, 239, 35, 99);
	colors.at(284).init(31, 239, 36, 99);
	colors.at(285).init(0, 91, 127, 1);
	colors.at(286).init(252, 252, 252, 15);
	colors.at(287).init(0, 0, 0, 0);
	colors.at(288).init(255, 255, 255, 15);
	colors.at(289).init(243, 216, 190, 6);
	colors.at(290).init(29, 239, 34, 99);
	colors.at(291).init(168, 16, 0, 4);
	colors.at(292).init(240, 208, 176, 6);
	colors.at(293).init(30, 239, 35, 99);
	colors.at(294).init(31, 239, 36, 99);
	colors.at(295).init(0, 91, 127, 1);
	colors.at(296).init(12, 249, 56, 99);
	colors.at(297).init(0, 0, 188, 1);
	colors.at(298).init(248, 56, 0, 4);
	colors.at(299).init(252, 252, 252, 15);
	colors.at(300).init(0, 0, 0, 0);
	colors.at(301).init(255, 255, 255, 15);
	colors.at(302).init(243, 216, 190, 6);
	colors.at(303).init(29, 239, 34, 99);
	colors.at(304).init(168, 16, 0, 4);
	colors.at(305).init(240, 208, 176, 6);
	colors.at(306).init(30, 239, 35, 99);
	colors.at(307).init(31, 239, 36, 99);
	colors.at(308).init(0, 91, 127, 1);
	colors.at(309).init(252, 252, 252, 15);
	colors.at(310).init(0, 0, 0, 0);
	colors.at(311).init(255, 255, 255, 15);
	colors.at(312).init(243, 216, 190, 6);
	colors.at(313).init(29, 239, 34, 99);
	colors.at(314).init(168, 16, 0, 1);
	colors.at(315).init(240, 208, 176, 15);
	colors.at(316).init(30, 239, 35, 99);
	colors.at(317).init(31, 239, 36, 99);
	colors.at(318).init(0, 91, 127, 1);
	colors.at(319).init(12, 249, 56, 15);
	colors.at(320).init(0, 0, 188, 1);
	colors.at(321).init(248, 56, 0, 4);
	colors.at(322).init(252, 252, 252, 15);
	colors.at(323).init(243, 216, 190, 6);
	colors.at(324).init(29, 239, 34, 99);
	colors.at(325).init(168, 16, 0, 4);
	colors.at(326).init(30, 239, 35, 99);
	colors.at(327).init(31, 239, 36, 99);
	colors.at(328).init(0, 91, 127, 1);
	colors.at(329).init(29, 239, 34, 99);
	colors.at(330).init(30, 239, 35, 9);
	colors.at(331).init(31, 239, 36, 99);
	colors.at(332).init(12, 249, 56, 99);
	colors.at(333).init(60, 255, 0, 99);
	colors.at(334).init(55, 241, 11, 99);
	colors.at(335).init(56, 243, 9, 99);
	colors.at(336).init(59, 253, 1, 99);
	colors.at(337).init(252, 160, 68, 12);
	colors.at(338).init(248, 120, 248, 5);
	colors.at(339).init(1, 94, 125, 1);
	colors.at(340).init(1, 93, 126, 1);
	colors.at(341).init(0, 92, 127, 1);
	colors.at(342).init(252, 252, 252, 15);
	colors.at(343).init(0, 0, 0, 0);
	colors.at(344).init(255, 255, 255, 15);
	colors.at(345).init(243, 216, 190, 1);
	colors.at(346).init(29, 239, 34, 99);
	colors.at(347).init(168, 16, 0, 4);
	colors.at(348).init(240, 208, 176, 12);
	colors.at(349).init(30, 239, 35, 99);
	colors.at(350).init(31, 239, 36, 99);
	colors.at(351).init(0, 91, 127, 1);
	colors.at(352).init(252, 252, 252, 15);
	colors.at(353).init(0, 0, 0, 0);
	colors.at(354).init(255, 255, 255, 15);
	colors.at(355).init(243, 216, 190, 12);
	colors.at(356).init(29, 239, 34, 99);
	colors.at(357).init(168, 16, 0, 4);
	colors.at(358).init(240, 208, 176, 12);
	colors.at(359).init(30, 239, 35, 99);
	colors.at(360).init(31, 239, 36, 99);
	colors.at(361).init(0, 91, 127, 1);
	colors.at(362).init(12, 249, 56, 99);
	colors.at(363).init(0, 0, 188, 1);
	colors.at(364).init(248, 56, 0, 4);
	colors.at(365).init(252, 252, 252, 15);
	colors.at(366).init(0, 0, 0, 0);
	colors.at(367).init(255, 255, 255, 15);
	colors.at(368).init(243, 216, 190, 12);
	colors.at(369).init(29, 239, 34, 99);
	colors.at(370).init(168, 16, 0, 4);
	colors.at(371).init(240, 208, 176, 12);
	colors.at(372).init(30, 239, 35, 99);
	colors.at(373).init(31, 239, 36, 99);
	colors.at(374).init(0, 91, 127, 1);
	colors.at(375).init(252, 252, 252, 15);
	colors.at(376).init(0, 0, 0, 0);
	colors.at(377).init(255, 255, 255, 15);
	colors.at(378).init(243, 216, 190, 12);
	colors.at(379).init(29, 239, 34, 99);
	colors.at(380).init(168, 16, 0, 4);
	colors.at(381).init(240, 208, 176, 6);
	colors.at(382).init(30, 239, 35, 99);
	colors.at(383).init(31, 239, 36, 99);
	colors.at(384).init(0, 91, 127, 1);
	colors.at(385).init(12, 249, 56, 99);
	colors.at(386).init(0, 0, 188, 1);
	colors.at(387).init(248, 56, 0, 4);
	colors.at(388).init(252, 252, 252, 15);
	colors.at(389).init(243, 216, 190, 12);
	colors.at(390).init(29, 239, 34, 99);
	colors.at(391).init(168, 16, 0, 4);
	colors.at(392).init(30, 239, 35, 99);
	colors.at(393).init(31, 239, 36, 99);
	colors.at(394).init(0, 91, 127, 1);
	colors.at(395).init(29, 239, 34, 99);
	colors.at(396).init(30, 239, 35, 99);
	colors.at(397).init(31, 239, 36, 99);
	colors.at(398).init(12, 249, 56, 99);
	colors.at(399).init(60, 255, 0, 99);
	colors.at(400).init(55, 241, 11, 99);
	colors.at(401).init(56, 243, 9, 99);
	colors.at(402).init(59, 253, 1, 99);
	colors.at(403).init(252, 160, 68, 6);
	colors.at(404).init(248, 120, 248, 5);
	colors.at(405).init(1, 94, 125, 1);
	colors.at(406).init(1, 93, 126, 1);
	colors.at(407).init(0, 92, 127, 1);
	colors.at(408).init(0, 255, 18, 99);
	colors.at(409).init(228, 0, 88, 4);
	colors.at(410).init(0, 232, 216, 1);
	colors.at(411).init(1, 255, 19, 99);
	colors.at(412).init(228, 92, 16, 4);
	colors.at(413).init(252, 252, 252, 15);
	colors.at(414).init(0, 0, 0, 0);
	colors.at(415).init(255, 255, 255, 15);
	colors.at(416).init(243, 216, 190, 6);
	colors.at(417).init(29, 239, 34, 99);
	colors.at(418).init(168, 16, 0, 4);
	colors.at(419).init(240, 208, 176, 6);
	colors.at(420).init(30, 239, 35, 15);
	colors.at(421).init(31, 239, 36, 15);
	colors.at(422).init(0, 91, 127, 1);
	colors.at(423).init(252, 252, 252, 15);
	colors.at(424).init(0, 0, 0, 0);
	colors.at(425).init(255, 255, 255, 15);
	colors.at(426).init(243, 216, 190, 12);
	colors.at(427).init(29, 239, 34, 99);
	colors.at(428).init(168, 16, 0, 4);
	colors.at(429).init(240, 208, 176, 6);
	colors.at(430).init(30, 239, 35, 99);
	colors.at(431).init(31, 239, 36, 99);
	colors.at(432).init(0, 91, 127, 1);
	colors.at(433).init(12, 249, 56, 99);
	colors.at(434).init(0, 0, 188, 1);
	colors.at(435).init(248, 56, 0, 4);
	colors.at(436).init(252, 252, 252, 15);
	colors.at(437).init(0, 0, 0, 0);
	colors.at(438).init(255, 255, 255, 15);
	colors.at(439).init(243, 216, 190, 12);
	colors.at(440).init(29, 239, 34, 99);
	colors.at(441).init(168, 16, 0, 4);
	colors.at(442).init(240, 208, 176, 6);
	colors.at(443).init(30, 239, 35, 99);
	colors.at(444).init(31, 239, 36, 99);
	colors.at(445).init(0, 91, 127, 1);
	colors.at(446).init(252, 252, 252, 15);
	colors.at(447).init(0, 0, 0, 0);
	colors.at(448).init(255, 255, 255, 15);
	colors.at(449).init(243, 216, 190, 12);
	colors.at(450).init(29, 239, 34, 99);
	colors.at(451).init(168, 16, 0, 4);
	colors.at(452).init(240, 208, 176, 12);
	colors.at(453).init(30, 239, 35, 99);
	colors.at(454).init(31, 239, 36, 99);
	colors.at(455).init(0, 91, 127, 1);
	colors.at(456).init(12, 249, 56, 99);
	colors.at(457).init(0, 0, 188, 1);
	colors.at(458).init(248, 56, 0, 4);
	colors.at(459).init(252, 252, 252, 15);
	colors.at(460).init(243, 216, 190, 6);
	colors.at(461).init(29, 239, 34, 99);
	colors.at(462).init(168, 16, 0, 4);
	colors.at(463).init(30, 239, 35, 99);
	colors.at(464).init(31, 239, 36, 99);
	colors.at(465).init(0, 91, 127, 1);
	colors.at(466).init(29, 239, 34, 99);
	colors.at(467).init(30, 239, 35, 99);
	colors.at(468).init(31, 239, 36, 99);
	colors.at(469).init(12, 249, 56, 99);
	colors.at(470).init(60, 255, 0, 99);
	colors.at(471).init(55, 241, 11, 99);
	colors.at(472).init(56, 243, 9, 99);
	colors.at(473).init(59, 253, 1, 99);
	colors.at(474).init(252, 160, 68, 6);
	colors.at(475).init(248, 120, 248, 5);
	colors.at(476).init(0, 0, 0, 0);
	colors.at(477).init(1, 94, 125, 1);
	colors.at(478).init(1, 93, 126, 1);
	colors.at(479).init(0, 92, 127, 1);
	colors.at(480).init(252, 252, 252, 15);
	colors.at(481).init(0, 0, 0, 0);
	colors.at(482).init(255, 255, 255, 15);
	colors.at(483).init(243, 216, 190, 12);
	colors.at(484).init(29, 239, 34, 99);
	colors.at(485).init(168, 16, 0, 4);
	colors.at(486).init(240, 208, 176, 6);
	colors.at(487).init(30, 239, 35, 99);
	colors.at(488).init(31, 239, 36, 99);
	colors.at(489).init(0, 91, 127, 1);
	colors.at(490).init(252, 252, 252,15 );
	colors.at(491).init(0, 0, 0, 0);
	colors.at(492).init(255, 255, 255, 15);
	colors.at(493).init(243, 216, 190, 4);
	colors.at(494).init(29, 239, 34, 99);
	colors.at(495).init(168, 16, 0, 4);
	colors.at(496).init(240, 208, 176, 12);
	colors.at(497).init(30, 239, 35, 99);
	colors.at(498).init(31, 239, 36, 99);
	colors.at(499).init(0, 91, 127, 1);
	colors.at(500).init(12, 249, 56, 99);
	colors.at(501).init(0, 0, 188, 1);
	colors.at(502).init(248, 56, 0, 4);
	colors.at(503).init(252, 252, 252, 15);
	colors.at(504).init(0, 0, 0, 0);
	colors.at(505).init(255, 255, 255, 15);
	colors.at(506).init(243, 216, 190, 12);
	colors.at(507).init(29, 239, 34, 99);
	colors.at(508).init(168, 16, 0, 4);
	colors.at(509).init(240, 208, 176, 12);
	colors.at(510).init(30, 239, 35, 99);
	colors.at(511).init(31, 239, 36, 99);
	colors.at(512).init(0, 91, 127, 1);
	colors.at(513).init(252, 252, 252, 15);
	colors.at(514).init(0, 0, 0, 0);
	colors.at(515).init(255, 255, 255, 15);
	colors.at(516).init(243, 216, 190, 6);
	colors.at(517).init(29, 239, 34, 99);
	colors.at(518).init(168, 16, 0, 4);
	colors.at(519).init(240, 208, 176, 6);
	colors.at(520).init(30, 239, 35, 99);
	colors.at(521).init(31, 239, 36, 99);
	colors.at(522).init(0, 91, 127, 1);
	colors.at(523).init(12, 249, 56, 99);
	colors.at(524).init(0, 0, 188, 1);
	colors.at(525).init(248, 56, 0, 4);
	colors.at(526).init(252, 252, 252, 15);
	colors.at(527).init(243, 216, 190, 6);
	colors.at(528).init(29, 239, 34, 99);
	colors.at(529).init(168, 16, 0, 4);
	colors.at(530).init(30, 239, 35, 99);
	colors.at(531).init(31, 239, 36, 99);
	colors.at(532).init(0, 91, 127, 1);
	colors.at(533).init(29, 239, 34, 99);
	colors.at(534).init(30, 239, 35, 99);
	colors.at(535).init(31, 239, 36, 99);
	colors.at(536).init(12, 249, 56, 99);
	colors.at(537).init(60, 255, 0, 99);
	colors.at(538).init(55, 241, 11, 99);
	colors.at(539).init(56, 243, 9, 99);
	colors.at(540).init(59, 253, 1, 99);
	colors.at(541).init(252, 160, 68, 6);
	colors.at(542).init(248, 120, 248, 5);
	colors.at(543).init(1, 94, 125, 1);
	colors.at(544).init(1, 93, 126, 1);
	colors.at(545).init(0, 92, 127, 1);
	colors.at(546).init(0, 255, 18, 99);
	colors.at(547).init(228, 0, 88, 4);
	colors.at(548).init(0, 232, 216, 1);
	colors.at(549).init(1, 255, 19, 99);
	colors.at(550).init(228, 92, 16, 4);
	colors.at(551).init(36, 255, 0, 99);
	colors.at(552).init(12, 255, 0, 99);
	colors.at(553).init(20, 1, 255, 1);
	colors.at(554).init(0, 30, 255, 1);
	colors.at(555).init(245, 228, 208, 12);
	colors.at(556).init(11, 255, 0, 99);
	colors.at(557).init(9, 255, 0, 99);
	colors.at(558).init(14, 254, 2, 99);
	colors.at(559).init(13, 255, 0, 99);
	colors.at(560).init(198, 255, 197, 15);
	colors.at(561).init(181, 255, 180, 15);
	colors.at(562).init(81, 255, 76, 99);
	colors.at(563).init(234, 255, 233, 15);
	colors.at(564).init(111, 255, 107, 99);
	colors.at(565).init(244, 255, 244, 15);
	colors.at(566).init(128, 255, 125, 99);
	colors.at(567).init(158, 255, 156, 99);
	colors.at(568).init(47, 255, 38, 99);
	colors.at(569).init(222, 255, 220, 15);
	colors.at(570).init(144, 255, 141, 99);
	colors.at(571).init(210, 255, 209, 15);
	colors.at(572).init(6, 255, 0, 99);
	colors.at(573).init(18, 255, 3, 99);
	colors.at(574).init(16, 255, 0, 99);
	colors.at(575).init(29, 254, 1, 99);
	colors.at(576).init(39, 255, 0, 99);
	colors.at(577).init(52, 255, 0, 99);
	colors.at(578).init(14, 255, 0, 99);
	colors.at(579).init(18, 255, 0, 99);
	colors.at(580).init(11, 253, 3, 99);
	colors.at(581).init(12, 247, 9, 99);
	colors.at(582).init(24, 253, 10,99);
	colors.at(583).init(38, 251, 12, 99);
	colors.at(584).init(12, 254, 1, 99);
	colors.at(585).init(13, 251, 6, 99);
	colors.at(586).init(8, 254, 4, 99);
	colors.at(587).init(13, 254, 5,99 );
	colors.at(588).init(17, 252, 7, 99);
	colors.at(589).init(16, 255, 1, 99);
	colors.at(590).init(13, 253, 6, 99);
	colors.at(591).init(13, 250, 9, 99);
	colors.at(592).init(14, 253, 2, 99);
	colors.at(593).init(13, 252, 5, 99);
	colors.at(594).init(14, 252, 7, 99);
	colors.at(595).init(12, 253, 3, 99);
	colors.at(596).init(13, 254, 2, 99);
	colors.at(597).init(13, 254, 7, 99);
	colors.at(598).init(1, 25, 236, 1);
	colors.at(599).init(1, 27, 234, 1);
	colors.at(600).init(6, 82, 176, 1);
	colors.at(601).init(23, 255, 0, 99);
	colors.at(602).init(6, 135, 127, 1);
	colors.at(603).init(0, 29, 232, 1);
	colors.at(604).init(0, 74, 255, 1);
	colors.at(605).init(0, 22, 238, 1);
	colors.at(606).init(1, 52, 207, 1);
	colors.at(607).init(1, 36, 234, 1);
	colors.at(608).init(3, 89, 177, 1);
	colors.at(609).init(2, 75, 188, 1);
	colors.at(610).init(3, 33, 220, 1);
	colors.at(611).init(4, 83, 184, 1);
	colors.at(612).init(1, 45, 222, 1);
	colors.at(613).init(4, 20, 255, 1);
	colors.at(614).init(18, 253, 2, 99);
	colors.at(615).init(1, 27, 255, 1);
	colors.at(616).init(1, 18, 255, 1);
	colors.at(617).init(6, 24, 255, 1);
	colors.at(618).init(14, 252, 5, 99);
	colors.at(619).init(0, 23, 249, 1);
	colors.at(620).init(5, 89, 167, 1);
	colors.at(621).init(11, 255, 3, 99);
	colors.at(622).init(126, 138, 253, 1);
	colors.at(623).init(120, 132, 253, 1);
	colors.at(624).init(113, 132, 241, 1);
	colors.at(625).init(132, 144, 251, 1);
	colors.at(626).init(100, 112, 252, 1);
	colors.at(627).init(120, 135, 251, 1);
	colors.at(628).init(100, 127, 232, 1);
	colors.at(629).init(136, 155, 235, 1);
	colors.at(630).init(89, 102, 250, 1);
	colors.at(631).init(123, 141, 244, 1);
	colors.at(632).init(119, 141, 233, 1);
	colors.at(633).init(181, 187, 254, 1);
	colors.at(634).init(255, 255, 245, 15);
	colors.at(635).init(254, 255, 214, 15);
	colors.at(636).init(178, 183, 231, 1);
	colors.at(637).init(149, 156, 254, 1);
	colors.at(638).init(255, 255, 240, 15);
	colors.at(639).init(215, 220, 252, 15);
	colors.at(640).init(177, 199, 217, 1);
	colors.at(641).init(243, 255, 195, 15);
	colors.at(642).init(215, 248, 201, 15);
	colors.at(643).init(146, 167, 236, 1);
	colors.at(644).init(203, 210, 251, 15);
	colors.at(645).init(52, 11, 255, 1);
	colors.at(646).init(186, 194, 251, 1);
	colors.at(647).init(167, 175, 250, 1);
	colors.at(648).init(17, 253, 2, 99);
	colors.at(649).init(236, 244, 251, 15);
	colors.at(650).init(0, 26, 244, 1);
	colors.at(651).init(177, 183, 249, 1);
	colors.at(652).init(141, 149, 252, 1);
	colors.at(653).init(194, 209, 235, 1);
	colors.at(654).init(251, 254, 227, 15);
	colors.at(655).init(197, 193, 237, 1);
	colors.at(656).init(230, 235, 251, 15);
	colors.at(657).init(252, 255, 255, 15);
	colors.at(658).init(249, 255, 254, 15);
	colors.at(659).init(247, 250, 253, 15);
	colors.at(660).init(242, 251, 251, 15);
	colors.at(661).init(218, 228, 247, 15);
	colors.at(662).init(16, 251, 3, 99);
	colors.at(663).init(242, 245, 253, 15);
	colors.at(664).init(21, 254, 9, 99);
	colors.at(665).init(8, 253, 0, 99);
	colors.at(666).init(147, 174, 208, 1);
	colors.at(667).init(80, 255, 0, 99);
	//DKleft
	colors.at(668).init( 0, 0, 0, 0);
	colors.at(669).init( 12, 255, 0, 99);
	colors.at(670).init( 240, 208, 176, 6);
	colors.at(671).init( 168, 16, 0, 14);
	colors.at(672).init( 0, 91, 127, 1);
	colors.at(673).init( 255, 255, 255, 15);
	//STARTscreen
	colors.at(674).init(0, 255, 54, 99);
	colors.at(675).init(252, 160, 68, 14);
	colors.at(676).init(252, 252, 252, 15);
	colors.at(677).init(248, 120, 248, 5);
	colors.at(678).init(240, 208, 176, 12);
	colors.at(679).init(168, 16, 0, 4);
	colors.at(680).init(45, 0, 255, 1);
	colors.at(681).init(248, 56, 0, 4);
	colors.at(682).init(255, 255, 255, 15);
	//DKhold
	colors.at(683).init( 0, 0, 0, 0);
	colors.at(684).init( 30, 255, 0, 99);
	colors.at(685).init( 243, 216, 190, 14);
	colors.at(686).init( 168, 16, 0, 1);
	colors.at(687).init( 240, 208, 176, 14);
	colors.at(688).init( 89, 8, 88, 5);
	colors.at(689).init( 252, 160, 68, 14);
	colors.at(690).init( 135, 135, 223, 13);
	colors.at(691).init( 0, 0, 188, 1);
	colors.at(692).init( 253, 255, 253, 15);
	colors.at(693).init( 0, 91, 127, 3);
	colors.at(694).init( 32, 255, 2, 99);
	colors.at(695).init( 34, 255, 5, 99);
	colors.at(696).init( 33, 255, 3, 99);
	//DKright
	colors.at(697).init( 0, 0, 0, 0);
	colors.at(698).init( 6, 255, 0, 99);
	colors.at(699).init( 243, 216, 190, 14);
	colors.at(700).init( 168, 16, 0, 1);
	colors.at(701).init( 240, 208, 176, 14);
	colors.at(702).init( 255, 255, 255, 15);
	colors.at(703).init( 0, 91, 127, 3);
	colors.at(704).init( 12, 255, 6, 99);
	colors.at(705).init( 247, 255, 247, 15);
	colors.at(706).init( 106, 255, 102, 99);
	colors.at(707).init( 38, 255, 33, 99);
	colors.at(708).init( 9, 255, 3, 99);
	colors.at(709).init( 79, 255, 76, 99);
	colors.at(710).init( 26, 255, 20, 99);
	colors.at(711).init( 7, 255, 1, 99);
	colors.at(712).init( 111, 255, 106, 99);
	colors.at(713).init( 48, 255, 43, 99);
	colors.at(714).init( 52, 255, 47, 99);
	colors.at(715).init( 19, 255, 13, 99);
	colors.at(716).init( 15, 255, 9, 99);
	colors.at(717).init( 42, 255, 37, 99);
	colors.at(718).init( 21, 255, 15, 99);
	colors.at(719).init( 11, 255, 5, 99);
	colors.at(720).init( 29, 255, 23, 99);
	colors.at(721).init( 32, 255, 26, 99);
	colors.at(722).init( 31, 255, 25, 99);
	colors.at(723).init( 22, 255, 16, 99);
	//Heart
	colors.at(724).init(0, 255, 18, 99);
	colors.at(725).init(248, 120, 248, 13);
	//MarioJumpRight
	colors.at(726).init( 0, 255, 30, 99);
	colors.at(727).init( 248, 56, 0, 4);
	colors.at(728).init( 0, 0, 188, 1);
	colors.at(729).init( 240, 208, 176, 14);
	//MarioLeft
	colors.at(730).init( 24, 255, 0, 99);
	colors.at(731).init( 0, 0, 188, 1);
	colors.at(732).init( 248, 56, 0, 4);
	colors.at(733).init( 240, 208, 176, 14);
#pragma endregion
	
	/*Make sure the *.bmp file is located in the same directory as the Source.cpp file*/
	ReadBMP(TEXT("marioLeft.bmp")); // 24 bit depth .bmp ///HERE
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
	thread t(test);
	thread key(KEY_LISTENER);
	
	key.join();
	t.join();
	system("pause");
}
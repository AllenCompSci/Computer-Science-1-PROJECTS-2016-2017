/*Game Project
Eric Blake
April 19th, 2017*/
#include <iostream>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h> // Sleep()
#include <ctime>
#include <thread>
#include <vector>
#include "VirtualKeys.h"
#include <chrono>



using namespace std;
enum DIRECTION { UP, RIGHT, DOWN, LEFT, FIRE, LEFTCLICK, RIGHTCLICK, NONE };
bool art = false;
bool updateTime = true;
int Freq = 70;
int SHOOTPRESS;
string TIMERVAL = "";
class Bullet {
public:
	int top, left, right, bottom;
	int dx, color;
	bool remove;

	void shoot(int t, int l, int r, int b, int VK){
		top = t + (b-t - 5)/2;
		left = r;
		right = left + 5;
		bottom = top+5;
		dx = 18;
		if (VK == VK_LBUTTON){
			dx *= -1;
			right = l;
			left = right - 5;
		}
		remove = false;
		color = RED;
	}
	void render(){
		setcolor(color);
		bar(left, top, right, bottom);
	}
	void move(){
		setcolor(BLACK);
		bar(left, top, right, bottom);
		left += dx;
		right += dx;
	}
	void tick(){
		move();
		if (dx < 0)
		{
			if (left > 0){
				render();
			}
			else{
				remove = true;
			}
		}
		else{
			if (right < getmaxx())
				render();
			else
				remove = true;
		}
	}

};
class Character {

public:
	int top, left, right, bottom;
	int dy, ndy;
	bool ML, MR, J, SHOOT;
	int row, row2, col, col2;
	int **grid;
	vector <Bullet> fire;
	void create(int t, int l, int r, int b) {
		col = b - t;
		ndy = 0;
		col2 = (int)((col + 1) / 2);
		row = r - l;
		row2 = (int)((row + 1) / 2);
		grid = new int*[row];
		for (int i = 0; i < row; i++) {
			grid[i] = new int[col];
		}
		top = t;
		left = l;
		right = r;
		bottom = b;
		dy = -9;
		ML = false;
		MR = false;
		J = false;
		draw();
	}
	void jump();
	void fall();
	bool onGround();
	void remove();
	void draw();
	void moveLeft();
	void moveRight();
	void FIRE(){
		if ((int)fire.size() < 15){
			Bullet GENERIC;
			if (SHOOTPRESS != -1)
				GENERIC.shoot(top, left, right, bottom, SHOOTPRESS);
			fire.push_back(GENERIC);

			SHOOT = FALSE;
			SHOOTPRESS = -1;
		}
	}
	void handle(){
		if (!fire.empty())
		{
			for (int i = 0; i < (int)fire.size(); i++)
			{
				fire[i].tick();
				if (fire[i].remove)
					fire.erase(fire.begin() + i);
			}
		}
	}
};

class Enemy {

public:
	int left, right, top, bottom, color;
	bool remove;
	void generate(){
		remove = false;
		if (rand() % 3 != 0){
			left = getmaxx() - 50;
			top = 900;
			bottom = 1000;
			right = left + 50;
			color = GREEN;
		}
		else{
			left = getmaxx() - 100;
			right = left + 100;
			bottom = 850;
			top = 800;
			color = WHITE;
		}
		render();
	}
	void render(){
		setcolor(color);
		bar(left, top, right, bottom);
	}
	void move(){
		setcolor(BLACK);
		bar(left, top, right, bottom);
		left -= 9;
		right -= 9;
		if (color == WHITE){

		}
	}
	void tick(){
		move();
		if (right > 10)
			render();
		else
			remove = true;
	}
	bool COLLISION(Character player){
		if (player.right >= left && player.left <= right)
			if (player.bottom >= top && player.top <= bottom)
				return true;
		return false;
	}
	bool isSHOT(Bullet shell){

	}
	};


vector<Enemy> enemeylist;
Character mini;
int GrDriver, GrMode, ErrorCode;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
bool KEYBOARD(int VirtualKey);
void game();
void Key();
void TIME();
int main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	thread t(TIME);
	thread k(Key);
	thread g(game);
	t.join();
	k.join();
	g.join();

	exit(0);
	
		
}

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
void Character::draw() {
	if (ndy > 0) {
		jump();
	}
	if (art)
		for (int i = 0; i <= row2; i++)
		{
			for (int j = 0; j <= col2; j++) {
				grid[i][j] = getpixel(left + j, top + i);
				grid[i][col - j - 1] = getpixel(left + col - j - 1, top + 1);
				grid[row - i - 1][j] = getpixel(left + j, top + row - 1 + i);
				grid[row - i - 1][col - j - 1] = getpixel(left + col - j - 1, top + row - 1 + i);
			}
		}
	setcolor(WHITE);
	bar(left, top, right, bottom);
}
void Character::remove() {
	if (art)
		for (int i = 0; i <= row2; i++)
		{
			for (int j = 0; j <= col2; j++) {
				putpixel(left + j, top + i, grid[i][j]);
				putpixel(left + col - j - 1, top + i, grid[i][col - j - 1]);
				putpixel(left + j, top + row - i - 1, grid[row - i - 1][j]);
				putpixel(left + col - j - 1, top + row - i - 1, grid[row - i - 1][col - j - 1]);
			}
		}
	else {
		setcolor(BLACK);
		bar(left, top, right, bottom);
	}
}
void Character::jump() {
	ndy--;
	Character::top += (Character::dy - 8);
	Character::bottom += (Character::dy - 8);
}
void Character::fall() {
	if (!Character::onGround() && ndy == 0) {
		Character::top -= Character::dy;
		Character::bottom -= Character::dy;
	}
}
void Character::moveLeft() {
	Character::left -= 8;
	Character::right -= 8;
}
void Character::moveRight() {
	Character::left += 8;
	Character::right += 8;
}
bool Character::onGround() {
	/// Check if they are on a platform at all.
	return bottom >= 1000;
}
void Key() {
	while (true) {
		if (KEYBOARD(VK_A)) {
			mini.ML = true;
		}
		if (KEYBOARD(VK_W)) {
			if (mini.onGround())
				mini.J = true;
			
		}
		if (KEYBOARD(VK_D)) {
			mini.MR = true;
		}
		if (KEYBOARD(VK_SPACE)) {
			if (mini.ndy < 12)
				mini.ndy += 4;
		}
		if (KEYBOARD(VK_LBUTTON)){
			mini.SHOOT = true;
			SHOOTPRESS = VK_LBUTTON;
		}
		if (KEYBOARD(VK_RBUTTON)){
			mini.SHOOT = true;
			SHOOTPRESS = VK_RBUTTON;
		}
		Sleep(15);
	}
}
void game() {
	
	
	Sleep(100);
	mini.create(40, 720, 800, 120);
	Sleep(100);
	
	int timer = 0;
	while (true) {
		if (updateTime){
			settextstyle(0, 0, 7);
			setcolor(WHITE);
			outtextxy(getmaxx() - textwidth(TIMERVAL.c_str()) - 5 , 10, TIMERVAL.c_str());
			updateTime = false;
		}
		if (!enemeylist.empty()){
			for (int i = 0; i < (int)enemeylist.size(); i++){
				enemeylist[i].tick();
				if (enemeylist[i].remove)
					enemeylist.erase(enemeylist.begin() + i);
				else
					if (enemeylist[i].COLLISION(mini)){
						
						cleardevice();
						
						
						enemeylist.erase(enemeylist.begin() + i); /// For testing removes enemy that you make contact with 

					}
			}

		}
		if (timer == Freq){
			Enemy Generic;
			Generic.generate();
			enemeylist.push_back(Generic);
			timer = 0;
			Freq = 30 + rand() % 80;
		}
		mini.remove();
		mini.fall();
		if (mini.ML) {
			mini.moveLeft();
			mini.ML = false;
		}
		if (mini.MR) {
			mini.moveRight();

			mini.MR = false;
		}
		if (mini.J) {
			mini.ndy = 15;
			mini.J = false;
		}
		if (mini.SHOOT){
			mini.FIRE();
		}
		mini.handle();
		mini.draw();
		Sleep(62);
		timer++;
	}
}
bool KEYBOARD(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		int count = 0;
		do {
			if (count++ > 200) {
				return true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);

		return true;
	}
	return false;

}
void TIME(){
	int milliseconds = 0;
	int seconds = 0;
	int minutes = 0;
	int hours = 0;
	string HH, MM, SS, MS;
	HH = "00";
	MM = "00";
	SS = "00";
	MS = "00";
	TIMERVAL = HH + ":" + MM + ":" + SS;
	bool local = true;
	while (true) {
		if (milliseconds >= 10){
			++seconds;
			local = true;
			milliseconds = 0;
			Sleep(20);
		}
		if (seconds >= 60){
			++minutes;
			seconds = 0;
			Sleep(20);
		}
		if (minutes >= 60){
			++hours;
			minutes = 0;
			Sleep(20);
		}
		if (local){
			local = false;
			HH = (9 < hours) ? to_string(hours) : "0" + to_string(hours);
			MM = (9 < minutes) ? to_string(minutes) : "0" + to_string(minutes);
			SS = (9 < seconds) ? to_string(seconds) : "0" + to_string(seconds);

			TIMERVAL = HH + ":" + MM + ":" + SS;
			updateTime = true;
		}
		//cout << hours << ":" << minutes << ":" << seconds << "." << milliseconds << endl;
		++milliseconds;
		Sleep(99);
	}

}
void SOUND(){
	if (KEYBOARD(VK_W)) {
		if (mini.onGround());

	}
}
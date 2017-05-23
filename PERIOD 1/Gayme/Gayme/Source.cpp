/*
Richard Noeske
Period 1 Compsci
*/


#include <iostream>
#include<cmath>
#include <winbgi.cpp>
#include <graphics.h>
#include <string>
#include <Windows.h> // Sleep()
#include <ctime>
#include <stdio.h> 
#include <algorithm>
#include <thread>
#include <vector>
#include <math.h>       //Trig functions, etc.
#include "VirtualKeys.h" // CUSTOM Virtual key list
//
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
#pragma comment (lib, "winmm.lib") //sound
#include <iomanip>
#include <fstream>
#include <sstream>

#define PI 3.14159265
using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
string tempstr;
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, pencolor;
int steplength = 30;
int centerX, centerY;
bool cursorVisible;
INPUT_RECORD irInBuf;
BOOL curVis;
HCURSOR visible, hCur1, hCur3;
POINT v;
float cursorX;
float cursorY;
bool Wkey;
bool Akey;
bool Skey;
bool Dkey;
bool Lshiftkey;
bool leftMouse;
bool pastleftMouse;
bool playmusic = false;
int i;
int rangedtimer = 0;
int rangedspawn = 300;
int currentranged = 0;
int rangedlimit = 1;
int meleetimer = 0;
int meleespawn = 100;
int currentmelee = 0;
int meleelimit = 0;
int rangedselector;
int meleeselector;
int score = 0;
int coinselector;
bool spawncoin;
bool pause;
bool shopisopen;
bool isRunning = true;
const int playerbulletlimit = 200;
int wepcost = 100;
int hpregencost = 50;
int hpregenTimer = 0;
int hpregenupgrades = 0;
int maxhpcost = 50;
int speedcost = 50;
int maxstamcost = 50;
int maxstamupgrades = 0;
int speedupgrades = 0;
int maxhpupgrades = 0;
int temp = 0;
int strobecolor = 4;
int strobecount = 0;
int hppackcost = 10;

string scorecarry = "";
string scoredisp = "Score: ";
string moneydisp = "Money: $";
struct Cursor {
	int x;
	int y;

	void draw() {
	
		setcolor(4);
		x = (int)cursorX;
		y = (int)cursorY;
		//fillellipse(x, y, 5, 5);
		line(x + 5, y, x + 10, y);
		line(x - 5, y, x - 10, y);
		line(x, y + 5, x, y + 10);
		line(x, y - 5, x, y - 10);
		bar(x, y, x + 1, y + 1);
	}





}cursorIcon;

struct PlayerShip {

	int x;
	int y;
	int hspd;
	int vspd;
	double xoffset;
	double yoffset;
	int color;
	float targetx;
	float targety;
	int size;
	double width;
	double dir;
	double lowerangle;
	double upperangle;
	int money;
	
	int firetype;
	/*
	1. Standard Bullet
	2. Double Shot
	3. Spread Shot
	4. Faster Shot
	5. Machine Shotgun
	6. Triple Shot
	7. Heavy Shot
	8. Assault Shot
	9. Fasterer Shot
	10. Shotgun
	11. Spread Shot 2
	12. Septuple Shot
	13. Shockwave Shot
	14. Faster Triple Shot
	15. Super Heavy Shot
	16. Heavy Assault Shot
	17. Rocket Gun
	18. Laser
	19. Super Spray
	20. Faster Spread Shot
	21. Flamethrower
	22. Surround Shot
	*/
	int canFire;
	int bulletselector;
	int bullettype;
	int hp;
	float isDashing;
	bool canDash;
	float stamina;
	float angleoffset = 0;
	bool sprayswitch = false;
	bool exists;
	struct PlayerBullet {
		int x;
		int y;
		int size;
		bool exists = false;
		int type;  //  1 = standard bullet,
		float hspd;
		float vspd;
		int color;
		int dmg;
		int lifetime;
		bool exploded;


		void init() {
			switch (player.firetype) {
			case 0:
				size = 5;
				dmg = 50;
				type = 0;
				lifetime = 999;
				//color = rand() % 14 + 1;
				color = rand() % 14+1;;
				exists = true;
				break;
			case 1: 
				x = (int)player.xoffset;
				y = (int)player.yoffset;
				hspd =(float)( 65 * ((cos(player.dir*PI / 180)) / 2));
				vspd = (float)(-65 * ((sin(player.dir*PI / 180)) / 2));
				size = 4;
				dmg = 15;
				type = 1;
				lifetime = 999;
				exists = true;
				break;
			case 2:
				hspd =(float)( 65 * ((cos(player.dir*PI / 180)) / 2));
				vspd = (float)(-65 * ((sin(player.dir*PI / 180)) / 2));
				size = 4;
				dmg = 15;
				type = 2;
				lifetime = 999;
				exists = true;
				break;
			case 3:
				size = 4;
				dmg = 10;
				type = 3;
				lifetime = 999;
				exists = true;
				break;
			case 4:
				size = 3;
				dmg = 7;
				type = 4;
				lifetime = 999;
				exists = true;
				break;
			case 5:
				size = 4;
				dmg = 5;
				type = 5;
				lifetime = 9;
				exists = true;
				break;
			case 6:
				hspd =(float)( 65 * ((cos(player.dir*PI / 180)) / 2));
				vspd =(float)( -65 * ((sin(player.dir*PI / 180)) / 2));
				size = 4;
				dmg = 15;
				type = 6;
				lifetime = 999;
				exists = true;
				break;
			case 7:
				if (!exploded) {
					x = (int)player.xoffset;
					y = (int)player.yoffset;
					
					size = 10;
					dmg = 15;
					type = 7;
					lifetime = 999;
					exists = true;
				}
				else {
					size = 75;
					dmg = 5;
					type = 7;
					lifetime = 6;
					exists = true;
				}
				break;
			case 8:
				size = 5;
				dmg = 10;
				type = 8;
				lifetime = 999;
				exists = true;
				break;
			case 9:
				size = 2;
				dmg = 5;
				type = 9;
				lifetime = 999;
				exists = true;
				break;
			case 10:
				size = 5;
				dmg = 15;
				type = 10;
				lifetime = 16;
				exists = true;
				break;
			case 11:
				size = 6;
				dmg = 15;
				type = 11;
				lifetime = 999;
				exists = true;
				break;
			case 12:
				hspd = (float)(65 * ((cos(player.dir*PI / 180)) / 2));
				vspd = (float)(-65 * ((sin(player.dir*PI / 180)) / 2));
				size = 4;
				dmg = 15;
				type = 12;
				lifetime = 999;
				exists = true;
				break;
			case 13:
				size = 10;
				dmg = 10;
				type = 13;
				lifetime = 999;
				exists = true;
				break;
			case 14:
				size = 4;
				dmg = 10;
				type = 14;
				lifetime = 999;
				exists = true;
				break;
			case 15:
				if (!exploded) {
					x = (int)player.xoffset;
					y = (int)player.yoffset;
					hspd = (float)(45 * ((cos(player.dir*PI / 180)) / 2));
					vspd = (float)(-45 * ((sin(player.dir*PI / 180)) / 2));
					size = 20;
					dmg = 40;
					type = 15;
					lifetime = 999;
					exists = true;
				}
				else {
					size = 200;
					dmg = 15;
					type = 15;
					lifetime = 6;
					exists = true;
				}
					break;
			case 16:
				size = 8;
				dmg = 15;
				type = 16;
				lifetime = 999;
				exists = true;
				break;
			case 17:
				if (!exploded) {
					x = (int)player.xoffset;
					y = (int)player.yoffset;

					size = 10;
					dmg = 5;
					type = 17;
					lifetime = 999;
					exists = true;
				}
				else {
					size = 75;
					dmg = 2;
					type = 17;
					lifetime = 6;
					exists = true;
				}
				break;
			case 18:
				size = 35;
				dmg = 8;
				type = 18;
				lifetime = 999;
				exists = true;
				break;
			case 19:
				size = 3;
				dmg = 8;
				type = 19;
				lifetime = 999;
				exists = true;
				break;
			case 20:
				size = 6;
				dmg = 15;
				type = 20;
				lifetime = 999;
				exists = true;
				break;
			case 21:
				size = 60;
				dmg = 2;
				type = 21;
				lifetime = 12;
				exists = true;
				break;
			case 22:
				size = 6;
				dmg = 15;
				type = 22;
				lifetime = 999;
				exists = true;
				break;
				}

			}






		
		void stepEvent() {
			if (exists == true) {
				CollisionCheck();
				switch (type) {
				case 0:
					x = x + hspd;
					y = y + vspd;
					setcolor(color);
					fillellipse(x, y, size, size);

					//Collision check goes here
					break;
				case 1: 
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					//Collision check goes here
					break;
				case 2:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 3:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 4:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 5:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 6:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 7:
					if (!exploded) {
						x = x + hspd;
						y = y + vspd;
						setcolor(15);
						
					} else if (lifetime >= 4) {
							setcolor(15);
						}
						else if (lifetime >= 2) {
							setcolor(14);
						}
						else {
							setcolor(4);
						}
						fillellipse(x, y, size, size);
					
					
					break;
				case 8:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 9:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 10:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 11:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 12:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 13:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 14:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 15:
					if (!exploded) {
						x = x + hspd;
						y = y + vspd;
						setcolor(15);

					}
					else if (lifetime >= 4) {
						setcolor(15);
					}
					else if (lifetime >= 2) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					fillellipse(x, y, size, size);


					break;
				case 16:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 17:
					if (!exploded) {
						x = x + hspd;
						y = y + vspd;
						hspd = min(hspd *1.2, 100);
						vspd = min(vspd * 1.2, 100);
						setcolor(15);

					}
					else if (lifetime >= 4) {
						setcolor(15);
					}
					else if (lifetime >= 2) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					fillellipse(x, y, size, size);


					break;
				case 18:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 19:
					x = x + hspd;
					y = y + vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 20:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 21:
					x += hspd;
					y += vspd;
					if (lifetime >= 8) {
						setcolor(15);
					}
					else if (lifetime >= 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					fillellipse(x, y, size, size);


					break;
				case 22:
					x += hspd;
					y += vspd;
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				}

				lifetime--;
				if (lifetime <= 0) {
					exists = false;
				}

			}
		}
		void CollisionCheck() {
			if (x >= maxX || y >= maxY || x <= 0 || y <= 0) {
				exists = false;
			}







		}

		void drawSelf() {
			if (exists) {
				switch (type) {
				case 0:
					setcolor(color);
					fillellipse(x, y, size, size);
					break;
				case 1:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 2:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 3:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 4:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 5:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 6:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 7:
					if (!exploded) {
						setcolor(15);
						fillellipse(x, y, size, size);
					}
					else {
						setcolor(4);
						fillellipse(x, y, size, size);
					}
					break;
				case 8:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 9:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 10:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 11:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 12:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 13:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 14:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 15:
					if (!exploded) {
						setcolor(15);
						fillellipse(x, y, size, size);
					}
					else {
						setcolor(4);
						fillellipse(x, y, size, size);
					}
					break;
				case  16:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 17:
					if (!exploded) {
						setcolor(15);
						fillellipse(x, y, size, size);
					}
					else {
						setcolor(4);
						fillellipse(x, y, size, size);
					}
					break;
				case  18:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case  19:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 20:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 21:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				case 22:
					setcolor(15);
					fillellipse(x, y, size, size);
					break;
				}
			}
		}



	}projectile[playerbulletlimit];
	void init() {
		x = centerX;
		y = centerY;
		hspd = 10;
		vspd = 10;
		width = 60;
		lowerangle = 180-(width*.5);
		upperangle =180+(width*.5);
		color = 15;
		targetx = cursorX;
		targety = cursorY;
		size = 40;
		bulletselector = 0;
		firetype = 1;
		exists = true;
		money = 0;
		canFire = 0;
		findDir(cursorX, cursorY);
		
		hp = 100;
		stamina = 100;
	}
	void findDir(double objX, double objY) {
		if (objX == x) {
			if (objY == y) {
				return;
			}
			dir = 90 * ((y-objY) / abs(y-objY));
			xoffset = x;
			yoffset = y - (.5*size*(y - objY) / abs(y - objY));
				
		
			
		}
		else if (objX > x){
			dir = (atan((y-objY) / (x-objX))) * 180 / PI;
			dir = -dir;
			yoffset = y - (size*sin(dir*PI / 180)/2);
			
		}
		else if (objX < x) {
			dir = 180+((atan((y-objY) / (x-objX))) * 180 / PI);
			dir = -dir;
			yoffset = y - (size*(sin(dir*PI / 180))/2);
			
		}
		if (objY > y) {
			xoffset = x + (size*cos(dir*PI/180)/2);
		}
		else {
			xoffset = x + (size*(cos(dir*PI / 180)) / 2);
		}
		
	}
	void move() {
		if (Lshiftkey == true && canDash == true) {
			isDashing = 1.5;
			
		}
		else {
			isDashing = 1;
			
		}
		x = max(0,min(x+(isDashing*(hspd+(2*speedupgrades))*(-Akey + Dkey)),maxX));
		y = max(0,min(maxY,y+(isDashing*(vspd+(2*speedupgrades))*(-Wkey + Skey))));




	}
	void Stamina() {
		if (isDashing == 1.5) {
			stamina = max(stamina-2.4,0);
		}
		if (isDashing == 1) {
			stamina = min(stamina + 1.4, 100+(maxstamupgrades * 10));
		}
		if (stamina <= 0) {
			canDash = false;
		}
		if (stamina >= 100) {
			canDash = true;
		}
	}
	void shoot() {
		if (leftMouse == true) {
			
			if (canFire >= 0) {
				switch (firetype) {
				case 0:
					for (int g = 0; g < 8; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 0;


						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].hspd = 190 * ((cos((dir + 45)*PI / 180)) / 2);
							projectile[bulletselector + g].vspd = -190 * ((sin((dir + 45) * PI / 180)) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir)* PI / 180)) / 2);
						}
						else  if (g == 2) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir - 45)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir - 45) * PI / 180)) / 2);
						}
						else if (g == 3) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir - 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir - 90) * PI / 180)) / 2);
						}
						else if (g == 4) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir + 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir + 90) * PI / 180)) / 2);
						}
						else if (g == 5) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir + 135)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir + 135) * PI / 180)) / 2);
						}
						else if (g == 6) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir - 135)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir - 135) * PI / 180)) / 2);
						}
						else if (g == 7) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 180)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 180)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 190 * ((cos((dir - 180)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -190 * ((sin((dir - 180) * PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 1;
					bulletselector = ((bulletselector + 8) % playerbulletlimit);
					break;
				case 1:
					projectile[bulletselector].type = 1;
					projectile[bulletselector].init();
					canFire -= 20;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);

					break;
				case 2:
					for (int g = 0; g < 2; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 2;
						if (g == 0) {
							projectile[(bulletselector + g)].y = y - (size*sin((dir + 15)*PI / 180) / 2);
							projectile[(bulletselector + g)].x = x + (size*cos((dir + 15)*PI / 180) / 2);
						}
						else {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 15)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 15)*PI / 180) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 30;
					bulletselector = ((bulletselector + 2) % playerbulletlimit);
					break;
				case 3:
					for (int g = 0; g < 3; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 3;
						
						
						if (g == 0) {
							projectile[(bulletselector + g)].y = y - (size*sin((dir + 45)*PI / 180) / 2);
							projectile[(bulletselector + g)].x = x + (size*cos((dir + 45)*PI / 180) / 2);
							projectile[(bulletselector + g)].hspd = 65 * ((cos((dir + 45)*PI / 180)) / 2);
							projectile[(bulletselector + g)].vspd = -65 * ((sin((dir + 45) * PI / 180)) / 2);
						}else if (g == 1) {
							projectile[(bulletselector + g) %  playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].hspd = 65 * ((cos((dir)*PI / 180)) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].vspd = -65 * ((sin((dir) * PI / 180)) / 2);
						}else {
							projectile[(bulletselector + g) %  playerbulletlimit].y = y - (size*sin((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].x = x + (size*cos((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].hspd = 65 * ((cos((dir - 45)*PI / 180)) / 2);
							projectile[(bulletselector + g) %  playerbulletlimit].vspd = -65 * ((sin((dir - 45) * PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 10;
					bulletselector = ((bulletselector + 3) % playerbulletlimit);
					break;
				case 4:
					projectile[bulletselector].type = 4;
					projectile[bulletselector].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 65 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir+angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 3;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					angleoffset = (rand() % 30) - 15;
					break;
				case 5:
					for (int g = 0; g < 6; g++) {
						angleoffset = (rand() % 50) - 25;
						projectile[(bulletselector+g)% playerbulletlimit].type = 5;
						projectile[(bulletselector+g)% playerbulletlimit].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector+g)% playerbulletlimit].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector+g)% playerbulletlimit].hspd = 80 * ((cos((dir + angleoffset)*PI / 180)) / 2);
						projectile[(bulletselector+g)% playerbulletlimit].vspd = -80 * ((sin((dir + angleoffset)* PI / 180)) / 2);
						projectile[(bulletselector+g)% playerbulletlimit].init();
						
						bulletselector = ((bulletselector + 6) % playerbulletlimit);
					}
					canFire -= 5;
				/*	if (sprayswitch == false) {
						angleoffset += 4;
					}
					else {
						angleoffset -= 4;
					}
					if (angleoffset >= 15 && sprayswitch == false) {
						sprayswitch = true;
					}
					if (angleoffset <= -15 && sprayswitch == true) {
						sprayswitch = false;
					}
					*/


					break;
				case 6:
					for (int g = 0; g < 3; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 6;
						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 25)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 25)*PI / 180) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 25)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 25)*PI / 180) / 2);
						}
						else {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 25;
					bulletselector = ((bulletselector + 3) % playerbulletlimit);
					break;
				case 7:
					projectile[bulletselector].type = 7;
					projectile[bulletselector].exploded = false;
					projectile[bulletselector].hspd = 65 * ((cos((dir)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 40;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);

					break;
				case 8:
					projectile[bulletselector].type = 8;
					projectile[bulletselector].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 65 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir + angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 3;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
						if (sprayswitch == false) {
					angleoffset += 4;
					}
					else {
					angleoffset -= 4;
					}
					if (angleoffset >= 10 && sprayswitch == false) {
					sprayswitch = true;
					}
					if (angleoffset <= -10 && sprayswitch == true) {
					sprayswitch = false;
					}
					
					//angleoffset = (rand() % 24) - 12;
					break;
				case 9:
					projectile[bulletselector].type = 9;
					projectile[bulletselector].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 65 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir + angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 1;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					angleoffset = (rand() % 20) - 10;
					break;
				case 10:
					for (int g = 0; g < 15; g++) {
						angleoffset = (rand() % 50) - 25;
						projectile[(bulletselector + g) % playerbulletlimit].type = 10;
						projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].hspd = 80 * ((cos((dir + angleoffset)*PI / 180)) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].vspd = -80 * ((sin((dir + angleoffset)* PI / 180)) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].init();

						bulletselector = ((bulletselector + 15) % playerbulletlimit);
					}
					canFire -= 40;
					break;
				case 11:
					for (int g = 0; g < 5; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 11;


						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].hspd = 65 * ((cos((dir + 45)*PI / 180)) / 2);
							projectile[bulletselector + g].vspd = -65 * ((sin((dir + 45) * PI / 180)) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir)* PI / 180)) / 2);
						}
						else  if (g == 2){
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 45)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 45) * PI / 180)) / 2);
						}
						else if (g == 3) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 90) * PI / 180)) / 2);
						}
						else if (g == 4) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir + 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir + 90) * PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 10;
					bulletselector = ((bulletselector + 5) % playerbulletlimit);
					break;
				case 12:
					for (int g = 0; g < 7; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 12;
						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 25)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 25)*PI / 180) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 25)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 25)*PI / 180) / 2);
						}
						else if (g == 2){
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
						}
						else if (g == 3) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 50)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 50)*PI / 180) / 2);
						}
						else if (g == 4) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir + 50)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir + 50)*PI / 180) / 2);
						}
						else if (g == 5) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 75)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 75)*PI / 180) / 2);
						}
						else if (g == 6) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir + 75)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir + 75)*PI / 180) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 20;
					bulletselector = ((bulletselector + 7) % playerbulletlimit);
					break;
				case 13:
					for (int g = 0; g < 40; g++) {
						angleoffset = (rand() % 70) - 35;
						projectile[(bulletselector + g) % playerbulletlimit].type = 13;
						projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].hspd = 80 * ((cos((dir + angleoffset)*PI / 180)) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].vspd = -80 * ((sin((dir + angleoffset)* PI / 180)) / 2);
						projectile[(bulletselector + g) % playerbulletlimit].init();

						bulletselector = ((bulletselector + 40) % playerbulletlimit);
					}
					canFire -= 70;
					break;
				case 14:
					angleoffset = (rand() % 40) - 20;
					for (int g = 0; g < 3; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 14;
						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 25 + angleoffset)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 25 + angleoffset)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].hspd = 80 * ((cos((dir+ angleoffset)*PI / 180)) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].vspd = -80 * ((sin((dir+ angleoffset)* PI / 180)) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir - 25 + angleoffset)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir - 25 + angleoffset)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].hspd = 80 * ((cos((dir+ angleoffset)*PI / 180)) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].vspd = -80 * ((sin((dir+ angleoffset)* PI / 180)) / 2);
						}
						else {
							projectile[(bulletselector + g) % playerbulletlimit].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].hspd = 80 * ((cos((dir + angleoffset)*PI / 180)) / 2);
							projectile[(bulletselector + g) % playerbulletlimit].vspd = -80 * ((sin((dir + angleoffset)* PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 6;
					bulletselector = ((bulletselector + 3) % playerbulletlimit);
					break;
				case 15:
					projectile[bulletselector].type = 15;
					projectile[bulletselector].exploded = false;
					projectile[bulletselector].init();
					canFire -= 65;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);

					break;
				case 16:
					projectile[bulletselector].type = 16;
					projectile[bulletselector].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 65 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir + angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 3;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					if (sprayswitch == false) {
						angleoffset += 4;
					}
					else {
						angleoffset -= 4;
					}
					if (angleoffset >= 5 && sprayswitch == false) {
						sprayswitch = true;
					}
					if (angleoffset <= -5 && sprayswitch == true) {
						sprayswitch = false;
					}

					//angleoffset = (rand() % 24) - 12;
					break;
				case 17:
					for (i = 0; i < 1; i++) {
						angleoffset = (rand() % 10) - 5;
						projectile[bulletselector+i].type = 17;
						projectile[bulletselector+i].exploded = false;
						projectile[bulletselector+i].hspd = 2 * ((cos((dir + angleoffset)*PI / 180)) / 2);
						projectile[bulletselector+i].vspd = -2 * ((sin((dir + angleoffset)* PI / 180)) / 2);
						projectile[bulletselector+i].init();
					}
					canFire -= 4;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);

					break;
				case 18:
					projectile[bulletselector].type = 18;
					projectile[bulletselector].y = y - (size*sin((dir )*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir )*PI / 180) / 2);
					projectile[bulletselector].hspd = 150 * ((cos((dir )*PI / 180)) / 2);
					projectile[bulletselector].vspd = -150 * ((sin((dir )* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 2;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					break;
				case 19:
					projectile[bulletselector].type = 19;
					projectile[bulletselector].y = y - (size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + (size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 65 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -65 * ((sin((dir + angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 0;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					angleoffset = (rand() % 20) - 10;
					break;
				case 20:
					for (int g = 0; g < 5; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 20;


						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].hspd = 65 * ((cos((dir + 45)*PI / 180)) / 2);
							projectile[bulletselector + g].vspd = -65 * ((sin((dir + 45) * PI / 180)) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir)* PI / 180)) / 2);
						}
						else  if (g == 2) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 45)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 45) * PI / 180)) / 2);
						}
						else if (g == 3) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 90) * PI / 180)) / 2);
						}
						else if (g == 4) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir + 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir + 90) * PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 5;
					bulletselector = ((bulletselector + 5) % playerbulletlimit);
					break;
				case 21:
					projectile[bulletselector].type = 21;
					projectile[bulletselector].y = y - 3*(size*sin((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].x = x + 3*(size*cos((dir + angleoffset)*PI / 180) / 2);
					projectile[bulletselector].hspd = 50 * ((cos((dir + angleoffset)*PI / 180)) / 2);
					projectile[bulletselector].vspd = -50 * ((sin((dir + angleoffset)* PI / 180)) / 2);
					projectile[bulletselector].init();
					canFire -= 3;
					bulletselector = ((bulletselector + 1) % playerbulletlimit);
					angleoffset = (rand() % 30) - 15;
					break;
				case 22:
					for (int g = 0; g < 8; g++) {
						projectile[(bulletselector + g) % playerbulletlimit].type = 22;


						if (g == 0) {
							projectile[bulletselector + g].y = y - (size*sin((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].x = x + (size*cos((dir + 45)*PI / 180) / 2);
							projectile[bulletselector + g].hspd = 65 * ((cos((dir + 45)*PI / 180)) / 2);
							projectile[bulletselector + g].vspd = -65 * ((sin((dir + 45) * PI / 180)) / 2);
						}
						else if (g == 1) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir)* PI / 180)) / 2);
						}
						else  if (g == 2) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 45)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 45)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 45) * PI / 180)) / 2);
						}
						else if (g == 3) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 90) * PI / 180)) / 2);
						}
						else if (g == 4) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 90)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir + 90)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir + 90) * PI / 180)) / 2);
						}
						else if (g == 5) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir + 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir + 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir + 135)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir + 135) * PI / 180)) / 2);
						}
						else if (g == 6) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 135)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 135)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 135) * PI / 180)) / 2);
						}
						else if (g == 7) {
							projectile[(bulletselector)+g %  playerbulletlimit].y = y - (size*sin((dir - 180)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].x = x + (size*cos((dir - 180)*PI / 180) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].hspd = 65 * ((cos((dir - 180)*PI / 180)) / 2);
							projectile[(bulletselector)+g %  playerbulletlimit].vspd = -65 * ((sin((dir - 180) * PI / 180)) / 2);
						}
						projectile[(bulletselector + g) % playerbulletlimit].init();
					}
					canFire -= 9;
					bulletselector = ((bulletselector + 8) % playerbulletlimit);
					break;


				}
				

			}
		}
		canFire = min((canFire + 1), 0);
	}
	void stepEvent() {
		//offsets: x+(size*cos(dir)), y+(size*sin(dir))
		//setcolor(0);
		//pieslice(xoffset, yoffset, dir + lowerangle, dir + upperangle, size);
		if (exists = true) {
			findDir(cursorX, cursorY);
			Stamina();
			move();
			shoot();
			setcolor(color);
			pieslice(xoffset, yoffset, dir + lowerangle, dir + upperangle, size);
			
			
			
			if (isDashing == 1.5) {
				setcolor(4);
				arc(x, y, dir + lowerangle, dir + upperangle, size*1.3);
				setcolor(14);
				arc(x, y, dir + lowerangle, dir + upperangle, size*1.2);
				setcolor(15);
				arc(x, y, dir + lowerangle, dir + upperangle, size*1.1);
			}
		}


		


	}

	void drawSelf() {
		if (exists) {
			setcolor(color);
			pieslice(xoffset, yoffset, dir + lowerangle, dir + upperangle, size);
		}
}







}player;
struct Coin {
	int value;
	int color;
	int x;
	int y;
	int size;
	bool exists;
	void init() {
		size = (.5 * value)+5;
		if (value < 5) {
			color = 6;
		}
		else if (value <= 14) {
			color = 7;
		}
		if (value > 14) {
			color = 14;
		}
		exists = true;

	}
	void stepEvent() {
		if (exists) {
			if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) < (size)+(player.size / 2)) {
				player.money += value+(score/100);
				exists = false;
			}
			if (color == 14) {
				setcolor(6);
				pieslice(x + (1.7 * size), y, 160, 200, size*.8);
			}
			setcolor(color);
			fillellipse(x, y, size, size);
			if (color == 14) {
				setcolor(0);
				fillellipse(x + (.35*size), y - (.35*size), size / 4, size / 4);
			
			}

		}


	}
	void drawSelf() {
		if (exists) {
			if (color == 14) {
				setcolor(6);
				pieslice(x + (1.7 * size), y, 160, 200, size*.8);
			}
			setcolor(color);
			fillellipse(x, y, size, size);
			if (color == 14) {
				setcolor(0);
				fillellipse(x + (.35*size), y - (.35*size), size / 4, size / 4);
			}
		}
	}

}coins[40];
struct EnemyShipRanged{
	int x;
	int y;
	int hspd;
	int vspd;
	double xoffset;
	double yoffset;
	double angle;
	int color;
	float targetx;
	float targety;
	int size;
	double width;
	double dir;
	int state; 
	/*
	1= move to and shoot at player, 
	2= move away form player while shooting, 
	3= remain stationary while shooting, 
	4= move to random location while shooting, 
	5= find random location for state 4,
	*/
	int canFire;
	int bulletselector;
	int bullettype;
	int timer = 0;
	int hp;
	int maxhp;
	bool exists;
	int spawnside;
	struct EnemyBullet {
		int x;
		int y;
		int size;
		bool exists = false;
		int type;  //  1 = standard bullet,
		float hspd;
		int color;
		float vspd;
		int dmg;
		int creatorid;


		void init() {
			
			switch (rangedfoe[creatorid].bullettype) {
			case 1:
				x = rangedfoe[creatorid].xoffset;
				y = rangedfoe[creatorid].yoffset;
				color = rangedfoe[creatorid].color;
				hspd = 50 * ((cos(rangedfoe[creatorid].dir*PI / 180)) / 2);
				vspd = -50 * ((sin(rangedfoe[creatorid].dir*PI / 180)) / 2);
				size = 4;
				dmg = 15;
				exists = true;
				break;
			case 2:
				x = rangedfoe[creatorid].xoffset;
				y = rangedfoe[creatorid].yoffset;
				color = rangedfoe[creatorid].color;
				hspd = 40 * ((cos((rangedfoe[creatorid].dir+(rand() % 20-10))*PI / 180)) / 2);
				vspd = -40 * ((sin((rangedfoe[creatorid].dir+ (rand() % 20 - 10))*PI / 180)) / 2);
				size = 3;
				dmg = 5;
				exists = true;
				break;


			}






		}
		void stepEvent() {
			if (exists == true) {
				switch (rangedfoe[creatorid].bullettype) {
				case 1: 
					x = x + hspd;
					y = y + vspd;
					setcolor(color);
					fillellipse(x, y, size, size);
					CollisionCheck();
					break;
				case 2: 
					x += hspd;
					y += vspd;
					setcolor(color);
					fillellipse(x, y, size, size);
					CollisionCheck();
				}


			}
		}
		void CollisionCheck() {
			if (x >= maxX || y >= maxY || x <= 0 || y <= 0) {
				exists = false;
			}
			if (sqrt(pow(player.x-x, 2) + pow(player.y-y, 2)) < (player.size/1.5)) {
			player.hp -= dmg;
				exists = false;
				
				

			}






		}

		void drawSelf() {
			if (exists) {
				switch (rangedfoe[creatorid].bullettype) {
				case 1:
					setcolor(color);
					fillellipse(x, y, size, size);
					break;
				case 2:
					setcolor(color);
					fillellipse(x, y, size, size);
					break;




				}
			}
		}



	}Eprojectile[20];
	void init() {
		spawnside = rand() % 2;
		if (spawnside == 1) {
			x = 0;
		}
		else {
			x = maxX;
		}
	
		y = rand() % maxY;
		width = (rand() % 25) + 15;
		color = (rand() % 5) + 1;
		size = (rand() % 30) + 30;
		findDir(player.x, player.y);
		state = 5;
		canFire = -20;
		bulletselector = 0;
		bullettype = rand() % 2 + 1;
		hp = size;
		maxhp = hp;
		currentranged += 1;
		exists = true;




	}
	void findDir(double objX, double objY) {
		if (objX == x) {
			if (objY == y) {
				return;
			}
			dir = 90 * ((y - objY) / abs(y - objY));
			xoffset = x;
			yoffset = y - (.5*size*(y - objY) / abs(y - objY));



		}
		else if (objX > x) {
			dir = (atan((y - objY) / (x - objX))) * 180 / PI;
			dir = -dir;
			yoffset = y - (size*sin(dir*PI / 180) / 2);

		}
		else if (objX < x) {
			dir = 180 + ((atan((y - objY) / (x - objX))) * 180 / PI);
			dir = -dir;
			yoffset = y - (size*(sin(dir*PI / 180)) / 2);

		}
		if (objY > y) {
			xoffset = x + (size*cos(dir*PI / 180) / 2);
		}
		else {
			xoffset = x + (size*(cos(dir*PI / 180)) / 2);
		}

	}


	void StepEvent() {
		if (exists == true) {
		
			if (hp >= 1) {
				collisionCheck();
				shoot();
				switch (state) {
				case 1:
					findDir(player.x, player.y);
					hspd = 25 * ((cos(dir*PI / 180)) / 2);
					vspd = -25 * ((sin(dir*PI / 180)) / 2);
					x += hspd;
					y += vspd;
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) < 400) {
						state = 3;
					}
					break;
				case 2:
					findDir(player.x, player.y);
					hspd = 25 * ((cos(dir*PI / 180)) / 2);
					vspd = -25 * ((sin(dir*PI / 180)) / 2);
					x = max(0, min(maxX, x - hspd));
					y = max(0, min(maxY, y - vspd));
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2); 
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) > 500) {

						state = 3;

					}
					break;
				case 3:
					findDir(player.x, player.y);
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					timer++;
					if (timer > 100) {
						timer = 0;
						state = 5;
					}
					if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) < 200) {
						timer = 0;
						state = 2;
					}
					if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) > 500) {
						timer = 0;
						state = 1;
					}
					break;
				case 5:
					targetx = rand() % maxX;
					targety = rand() % maxY;
					state = 4;
				//No break here	
					
				case 4:
					findDir(targetx, targety);
					hspd = 25 * ((cos(dir*PI / 180)) / 2);
					vspd = -25 * ((sin(dir*PI / 180)) / 2);
					x = max(0, min(maxX, x + hspd));
					y = max(0, min(maxY, y + vspd));
					findDir(player.x, player.y);
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					if (sqrt(pow(x - targetx, 2) + pow(y - targety, 2)) < 30) {
						state = 1;
					}




					break;
				




				}
			}
			else {
				exists = false;
				score += size;
				currentranged -= 1;
				if (rand() % 2 == 1) {
					coins[coinselector].value = rand() % 19 + 1;
					coins[coinselector].x = x + (rand() % 10) - 10;
					coins[coinselector].y = y + (rand() % 10) - 10;
					coins[coinselector].init();
					coinselector = (coinselector + 1) % 40;
				}
			}
		}
	}
	void collisionCheck() {
		for (int f = 0; f < playerbulletlimit; f++) {
			if (player.projectile[f].exists == true) {
				if (sqrt(pow(x - player.projectile[f].x, 2) + pow(y - player.projectile[f].y, 2)) < (size / 2) + (player.projectile[f].size)) {



					if (player.projectile[f].type == 15 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}
					if (player.projectile[f].type == 17 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}


					if (player.projectile[f].type == 7 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}
					else if (player.projectile[f].type == 7) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 15) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 17) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 21) {
						hp -= player.projectile[f].dmg;
					}
					else {
						hp -= player.projectile[f].dmg;
						player.projectile[f].exists = false;
					}

					

					state = 5;
				}
			}
		}
	}
	void shoot() {
		
			if (canFire >= 0) {
				switch (bullettype) {
				case 1:
					Eprojectile[bulletselector].type = 1;
					Eprojectile[bulletselector].creatorid = i;
					Eprojectile[bulletselector].init();


					canFire -= ((rand() % 20) + 20);
					bulletselector = ((bulletselector + 1) % 20);

					break;
				case 2: 
					Eprojectile[bulletselector].type = 1;
					Eprojectile[bulletselector].creatorid = i;
					Eprojectile[bulletselector].init();

					canFire -= ((rand() % 10) + 5);
					bulletselector = ((bulletselector + 1) % 20);
					break;
				}


			}
		
		canFire = min((canFire + 1), 0);
	}
	void drawSelf() {
		if (exists) {
			setcolor(color);
			pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
			if (hp >= maxhp / 2) {
				setcolor(2);
			}
			else if (hp >= maxhp / 4) {
				setcolor(14);
			}
			else {
				setcolor(4);
			}
			bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
		}
	}
}rangedfoe[20];
struct EnemyShipMelee {
	int x;
	int y;
	int hspd;
	int vspd;
	double xoffset;
	double yoffset;
	double angle;
	int color;
	float targetx;
	float targety;
	int size;
	double width;
	double dir;
	int state;
	/*
	1. Charge at player
	2. Find location to dodge
	3. Remain Stationary, prepare to charge
	4. Charge in straight line at elevated speed
	5. Move to random location quickly
	6. Choose the random location
	7. dodge a bullet
	*/
	int canHit;
	int canDodge;
	int timer = 0; //For dodge
	int timer2 = 0; //for standing still before dash and for dash
	int hp;
	int maxhp;
	bool exists;
	int spawnside;

	void init() {
		spawnside = rand() % 2;
		if (spawnside == 1) {
			x = 0;
		}
		else {
			x = maxX;
		}
		y = rand() % maxY;
		width = (rand() % 25) + 15;
		color = (rand() % 5) + 9;
		size = (rand() % 30) + 30;
		findDir(player.x, player.y);
		state = 6;
		canHit = -20;
		canDodge = -20;
		hp = size;
		maxhp = hp;
		currentmelee += 1;
		exists = true;




	}
	void findDir(double objX, double objY) {
		if (objX == x) {
			if (objY == y) {
				return;
			}
			dir = 90 * ((y - objY) / abs(y - objY));
			xoffset = x;
			yoffset = y - (.5*size*(y - objY) / abs(y - objY));



		}
		else if (objX > x) {
			dir = (atan((y - objY) / (x - objX))) * 180 / PI;
			dir = -dir;
			yoffset = y - (size*sin(dir*PI / 180) / 2);

		}
		else if (objX < x) {
			dir = 180 + ((atan((y - objY) / (x - objX))) * 180 / PI);
			dir = -dir;
			yoffset = y - (size*(sin(dir*PI / 180)) / 2);

		}
		if (objY > y) {
			xoffset = x + (size*cos(dir*PI / 180) / 2);
		}
		else {
			xoffset = x + (size*(cos(dir*PI / 180)) / 2);
		}

	}
	void collisionCheck() {
		for (int f = 0; f < playerbulletlimit; f++) {
			if (player.projectile[f].exists == true) {
				if (sqrt(pow(x - player.projectile[f].x, 2) + pow(y - player.projectile[f].y, 2)) < (size / 2) + (player.projectile[f].size) && canDodge < 0) {
					


					if (player.projectile[f].type == 15 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}
					if (player.projectile[f].type == 17 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}


					if (player.projectile[f].type == 7 && player.projectile[f].exploded != true) {
						player.projectile[f].exploded = true;
						hp -= player.projectile[f].dmg;
						player.projectile[f].init();
					}
					else if (player.projectile[f].type == 7) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 15) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 17) {
						hp -= player.projectile[f].dmg;
					}
					else if (player.projectile[f].type == 21) {
						hp -= player.projectile[f].dmg;
					}
					else {
						hp -= player.projectile[f].dmg;
						player.projectile[f].exists = false;
					}

					

					state = 6;
				}
				if (sqrt(pow(x - player.projectile[f].x, 2) + pow(y - player.projectile[f].y, 2)) < (size / 2) + (player.projectile[f].size) && canDodge >= 0) {
					canDodge -= 100;
					state = 2;

				}
			}
			if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) < (size / 2) + (player.size / 2) && canHit >= 0) {
				player.hp -= 15;
				canHit = -50;
				state = 6;
			}
			else if (sqrt(pow(x - player.x, 2) + pow(y - player.y, 2)) < (size / 2) + (player.size / 2)) {
				if (state != 5) { state = 6; }
			}
		}
	}
	void StepEvent() {
		if (exists == true) {
			if (hp >= 1) {
				if (state != 2 && state != 7) {
					collisionCheck();
				}
				canDodge = min(canDodge + 1, 0);
				canHit = min(canHit + 1, 0);
				switch (state) {
				case 1:
					findDir(player.x, player.y);
					hspd = 25 * ((cos(dir*PI / 180)) / 2);
					vspd = -25 * ((sin(dir*PI / 180)) / 2);
					x = max(0, min(maxX, x + hspd));
					y = max(0, min(maxY, y + vspd));
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					break;
				case 2:
					targetx = rand() % maxX;
					targety = rand() % maxY;
					findDir(targetx, targety);
					hspd = 50 * ((cos(dir*PI / 180)) / 2);
					vspd = -50 * ((sin(dir*PI / 180)) / 2);
					
					state = 7;
					break;
				case 3:
					break;
				case 4:
					break;
				case 6:
					targetx = rand() % maxX;
					targety = rand() % maxY;

					state = 5;
				
					//No break here
				case 5:
					findDir(targetx, targety);
					hspd = 30 * ((cos(dir*PI / 180)) / 2);
					vspd = -30 * ((sin(dir*PI / 180)) / 2);
					x = max(0, min(maxX, x + hspd));
					y = max(0, min(maxY, y + vspd));
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					if (sqrt(pow(x - targetx, 2) + pow(y - targety, 2)) < 50) {
						state = 1;
					}
					break;
				
				case 7:
					findDir(targetx, targety);
				//	hspd = 50 * ((cos(dir*PI / 180)) / 2);
				//	vspd = -50 * ((sin(dir*PI / 180)) / 2);
					x = max(0, min(maxX, x + hspd));
					y = max(0, min(maxY, y + vspd));
					setcolor(color);
					pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
					arc(x, y, dir -width+180, 180+dir + width, size*1.3);
					arc(x, y, dir - width + 180, 180 + dir + width, size*1.2);
					arc(x, y, dir - width + 180, 180 + dir + width, size*1.1);
					if (hp >= maxhp / 2) {
						setcolor(2);
					}
					else if (hp >= maxhp / 4) {
						setcolor(14);
					}
					else {
						setcolor(4);
					}
					bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
					timer++;
					if (timer >= 25) {
						timer = 0;
						state = 1;
					}
					break;
				}

			}
			else {
				if (rand() % 2 == 1) {
					coins[coinselector].value = rand() % 19 + 1;
					coins[coinselector].x = x + (rand() % 10) - 10;
					coins[coinselector].y = y + (rand() % 10) - 10;
					coins[coinselector].init();
					coinselector = (coinselector + 1) % 40;
				}
				exists = false;
				currentmelee -= 1;
				score += size;
			}

		}

	}

	void drawSelf() {
		if (exists) {
			setcolor(color);
			pieslice(xoffset, yoffset, dir - width + 180, 180 + dir + width, size);
			if (hp >= maxhp / 2) {
				setcolor(2);
			}
			else if (hp >= maxhp / 4) {
				setcolor(14);
			}
			else {
				setcolor(4);
			}
			bar(x - (hp / 2), y + 20, x + (hp / 2), y + 25);
		}
	}





}meleefoe[20];
struct Button {

	int x;
	int y;
	int color;
	int selectcolor;
	int length;
	int width;
	int textfont;//0-4
	int textdirection;//0-1
	int textsize;//0-8
	string text;
	bool canPress;
	bool pressed;
	bool click;
	bool lastclicked;
	int specialvalue;

	void init() {
		textfont = 0;
		textdirection = 0;
		textsize = 0;
		text = "";
	}

	void stepEvent() {
		lastclicked = click;
		click = leftMouse;
		if (min(max(cursorX, x), x + width) == cursorX && min(max(cursorY, y), y + length) == cursorY) {
			setcolor(selectcolor);
			canPress = true;
		}
		else {
			setcolor(color);
			canPress = false;
		}
	
		bar(x, y, x + width, y + length);
		settextstyle(textfont, textdirection, textsize);
		int calcX = (int)(x + (width - textwidth(text.c_str())) / 2);
		int calcY = (int)(y + (length - textheight(text.c_str())) / 2);
     	outtextxy(calcX, calcY, text.c_str());
		if (click && canPress && click != lastclicked) {
			pressed = true;
		}
		else {
			pressed = false;
		}

	
	}


}shopbutton, wep1, wep2, wep3, hpregen1, maxhp1, speed1, maxstam1, retry, hppack;

struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
}global;
void getCursor(POINT &p); // uses struct POINT
bool MOUSE(int); // if mouse pressed
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
void gamethread(); // meat of the game
void mousedata(); //Gets curor x and y
void spawnEnemies();
void centerText(int, int, string);
void music();
void playSound(string, int);


void main() {
	srand((unsigned int)time(NULL));

	thread k(KEY_LISTENER);
	thread g(gamethread);
	thread c(mousedata);
	thread m(music);
	m.join();
	k.join(); // thread t start
	g.join();
	c.join();
	
	global.press = global.hold = false;




	return;


	
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
void KEY_LISTENER() {

	gr_Start(GrDriver, GrMode, ErrorCode); // initi of graphics window 
	maxX = getmaxx();
	maxY = getmaxy();
	centerX = getmaxx() / 2;
	centerY = getmaxy() / 2;
	SetCursor(hCur1);



	cursorVisible = true;

	while (isRunning) {
	
	



		if ((GetAsyncKeyState(VK_SPACE) & 0x01) != 0) {
			//cout << "Spacebar Pressed \n";
			if (pause == false) {
				pause = true;
			}
			else { pause = false; }
		}
		else {  }
		if (GetAsyncKeyState(VK_A) != 0 ) {
			//cout << "A Key Pressed \n";
			Akey = true;
		} else { Akey = false; }
		if (GetAsyncKeyState(VK_W) != 0 ) {
			//cout << "W Key Pressed \n";
			Wkey = true;
		} else { Wkey = false; }
		if (GetAsyncKeyState(VK_S) != 0 ) {
			//cout << "S Key Pressed \n";
			Skey = true;
		} else { Skey = false; }
		if (GetAsyncKeyState(VK_D) != 0) {
			//cout << "D Key Pressed \n";
			Dkey = true;
		} else { Dkey = false; }
		if (GetAsyncKeyState(VK_LSHIFT) != 0) {
			//cout << "D Key Pressed \n";
			Lshiftkey = true;
		}
		else { Lshiftkey = false; }
		if (GetAsyncKeyState(VK_0) != 0) {		
			player.money += 10000;
		}
		if (GetAsyncKeyState(VK_9) != 0) {
			score += 5000;
		}
		if (GetAsyncKeyState(VK_8) != 0) {
			player.firetype = 0;
			while (GetAsyncKeyState(VK_8) != 0) {
				//wait
			}
		}


		Sleep(10);
		// Room For More Ifs specified keys act in a specific way.
		// look through the VirtualKeys.h list to have other specific keys
	}

}
void mousedata() {
	while (isRunning) {
		pastleftMouse = leftMouse;
		GetCursorPos(&v);
		cursorX = (float)v.x;
		cursorY = (float)v.y;
		
		if (GetAsyncKeyState(VK_LBUTTON) != 0) {
			//cout << "Left Button\n";
			leftMouse = true;

			//cout << v.x << ", " << v.y << endl;
		}
		else { leftMouse = false; }
		
		Sleep(12);

	}
}
void gamethread() {
	Sleep(300);
	
	
	srand((unsigned int)time(NULL));
	//Setup Shop Button
	shopbutton.init();
	shopbutton.color = 7;
	shopbutton.selectcolor = 14;
	shopbutton.text = "SHOP";
	shopbutton.textfont = 1;
	shopbutton.textdirection = 0;
	shopbutton.textsize = 4;
	shopbutton.width = 150;
	shopbutton.x = maxX - 100 - shopbutton.width;
	shopbutton.length = 75;
	shopbutton.y = 50;
	//
	wep1.x = 150;
	wep1.y = 420;
	wep1.width = 250;
	wep1.length = 60;
	wep1.color = 15;
	wep1.selectcolor = 14;
	wep1.text = "Buy: $100";
	wep1.textfont = 1;
	wep1.textdirection = 0;
	wep1.textsize = 2;
	wep1.specialvalue = 2;
	//
	wep2.x = 550;
	wep2.y = 420;
	wep2.width = 250;
	wep2.length = 60;
	wep2.color = 15;
	wep2.selectcolor = 14;
	wep2.text = "Buy: $100";
	wep2.textfont = 1;
	wep2.textdirection = 0;
	wep2.textsize = 2;
	wep2.specialvalue = 3;
	//
	wep3.x = 950;
	wep3.y = 420;
	wep3.width = 250;
	wep3.length = 60;
	wep3.color = 15;
	wep3.selectcolor = 14;
	wep3.text = "Buy: $100";
	wep3.textfont = 1;
	wep3.textdirection = 0;
	wep3.textsize = 2;
	wep3.specialvalue = 4;
	// 1650, 150, 1850, 350
	hpregen1.x = 1650;
	hpregen1.y = 360;
	hpregen1.width = 200;
	hpregen1.length = 60;
	hpregen1.color = 15;
	hpregen1.selectcolor = 14;
	hpregen1.text = "Buy: $50";
	hpregen1.textfont = 1;
	hpregen1.textdirection = 0;
	hpregen1.textsize = 2;
	//
	maxhp1.x = 1350;
	maxhp1.y = 360;
	maxhp1.width = 200;
	maxhp1.length = 60;
	maxhp1.color = 15;
	maxhp1.selectcolor = 14;
	maxhp1.text = "Buy: $50";
	maxhp1.textfont = 1;
	maxhp1.textdirection = 0;
	maxhp1.textsize = 2;
	//
	speed1.x = 1350;
	speed1.y = 660;
	speed1.width = 200;
	speed1.length = 60;
	speed1.color = 15;
	speed1.selectcolor = 14;
	speed1.text = "Buy: $50";
	speed1.textfont = 1;
	speed1.textdirection = 0;
	speed1.textsize = 2;
	//
	maxstam1.x = 1650;
	maxstam1.y = 660;
	maxstam1.width = 200;
	maxstam1.length = 60;
	maxstam1.color = 15;
	maxstam1.selectcolor = 14;
	maxstam1.text = "Buy: $50";
	maxstam1.textfont = 1;
	maxstam1.textdirection = 0;
	maxstam1.textsize = 2;
	//
	hppack.x = 150;
	hppack.y = 820;
	hppack.width = 250;
	hppack.length = 60;
	hppack.color = 15;
	hppack.selectcolor = 14;
	hppack.text = "Buy: $50";
	hppack.textfont = 1;
	hppack.textdirection = 0;
	hppack.textsize = 2;
	hppack.specialvalue = 2;
	//Opening Screen
	i = 1;

	setcolor(15);
	while (i < maxX + 75 && i < maxY + 75) {

		
		setcolor((rand() % 15) + 1);
		circle(centerX, centerY, i);


		setcolor(0);
		circle((int)(centerX - .1), (int)(centerY - .1), i - 2);
		i++;
		
	}
	settextstyle(3, 0, 8);
	setcolor(15);
	int titleoffset = (textwidth("Space Survival") / 2);
	moveto(centerX - titleoffset, centerY - (centerY / 2));
	outtext("Space Survival");

	settextstyle(3, 0, 6);
	titleoffset = (textwidth("Click to Start") / 2);
	moveto(centerX - titleoffset, centerY + (centerY / 2));
	outtext("Click to Start");

	
	while (leftMouse == 0)
	{
	}
	playmusic = true;
	while (isRunning) {
		cleardevice();
		
		player.init();
		while (player.hp >= 0) {
			cleardevice();
			strobecount++;
			if (strobecount >= 50) {
				strobecount = 0;
				strobecolor = rand() % 14 + 1;
			}
			shopbutton.stepEvent();
			hpregenTimer++;
			if (hpregenTimer >= 100-(hpregenupgrades*10)) {
				player.hp = min(player.hp+1,100+(10*maxhpupgrades));
				hpregenTimer = 0;
			}
			//Score Display
			settextstyle(3, 0, 4);
			setcolor(14);
			scorecarry = to_string(score);
			scoredisp = "Score: " + scorecarry;
			moveto(maxX - textwidth(scoredisp.c_str()) - 25, maxY - textheight(scoredisp.c_str()) - 25);
			outtext(scoredisp.c_str());
			//
			scorecarry = to_string(player.money);
			moneydisp = "Money: $" + scorecarry;
		
			moveto(textwidth(moneydisp.c_str())/2, maxY - textheight(moneydisp.c_str()) - 25);
			outtext(moneydisp.c_str());
			spawnEnemies();
			player.stepEvent();

			for (i = 0; i < playerbulletlimit; i++) {
				player.projectile[i].stepEvent();
			}
			for (i = 0; i < 20; i++) {
				rangedfoe[i].StepEvent();
				for (int f = 0; f < 20; f++) {
					rangedfoe[i].Eprojectile[f].stepEvent();
				}
				meleefoe[i].StepEvent();
				coins[i].stepEvent();
			}
			//Health Bar
			setcolor(4);
			bar(25, 25, 25+(5 * player.hp), (75));
			setcolor(15);
			temp = 525 + (maxhpupgrades * 50);
			rectangle(25, 25, temp, (75));
			//Stamina Bar
			if (player.canDash == true) {
				setcolor(2);
			}
			else {
				setcolor(7);
			}
			bar(25, 90, (int)(25+(3.5 * player.stamina)), (125));
			setcolor(15);
			temp = 375 + (35*maxstamupgrades);
			rectangle(25, 90, temp, (125));
			


			cursorIcon.draw();
			if (shopbutton.pressed == true) {
				shopisopen = true;
				shopbutton.pressed = false;
			
				shopbutton.text = "CLOSE";
				shopbutton.width += 50;
				Sleep(20);
				
			}
			while (shopisopen) {
				cleardevice();
				scorecarry = to_string(player.money);
				moneydisp = "Money: $" + scorecarry;

				moveto(textwidth(moneydisp.c_str()) / 2, maxY - textheight(moneydisp.c_str()) - 25);
				outtext(moneydisp.c_str());
				setcolor(15);
				rectangle(50, 50, maxX - 50, maxY - 50);
				settextstyle(0, 0, 7);
				outtextxy(55, 51, "Welcome to the shop!");
				rectangle(150, 150, 400, 400);
				
				rectangle(550, 150, 800, 400);
				rectangle(950, 150, 1200, 400);
				rectangle(150, 550, 400, 800);
				rectangle(550, 550, 800, 800);
				rectangle(950, 550, 1200, 800);
				rectangle(1350, 150, 1550, 350);
				rectangle(1650, 150, 1850, 350);
				rectangle(1350, 450, 1550, 650);
				rectangle(1650, 450, 1850, 650);
				shopbutton.stepEvent();
				settextstyle(3, 0, 4);
				setcolor(15);
				outtext("");
				wep1.stepEvent();
				settextstyle(3, 0, 3);
				setcolor(15);
				switch (wep1.specialvalue) {
				case 0:
					centerText(275, 275, "Beat the Game");
					break;
				case 1:
					centerText(275, 275, "Standard");
					break;
				case 2:
					centerText(275, 275, "Double");
					break;
				case 3:
					centerText(275, 275, "Spread");
					break;
				case 4:
					centerText(275, 275, "Fast");
					break;
				case 5:
					centerText(275, 275, "Fast Shotgun");
					break;
				case 6:
					centerText(275, 275, "Triple");
					break;
				case 7:
					centerText(275, 275, "Heavy");
					break;
				case 8:
					centerText(275, 275, "Assault");
					break;
				case 9:
					centerText(275, 275, "Fast v2");
					break;
				case 10:
					centerText(275, 275, "Shotgun");
					break;
				case 11:
					centerText(275, 275, "Spread v2");
					break;
				case 12:
					centerText(275, 275, "Septuple");
					break;
				case 13:
					centerText(275, 275, "Shockwave");
					break;
				case 14:
					centerText(275, 275, "Triple Fast");
					break;
				case 15:
					centerText(275, 275, "Super Heavy");
					break;
				case 16:
					centerText(275, 275, "Assault v2");
					break;
				case 17:
					centerText(275, 275, "Rocket Gun");
					break;
				case 18:
					centerText(275, 275, "Laser");
					break;
				case 19:
					centerText(275, 275, "Spray");
					break;
				case 20:
					centerText(275, 275, "Fast Spread");
					break;
				case 21:
					centerText(275, 275, "Flame");
					break;
				case 22:
					centerText(275, 275, "Surround");
					break;

				}
				wep2.stepEvent();
				settextstyle(3, 0, 3);
				setcolor(15);
				switch (wep2.specialvalue) {
				case 0:
					centerText(675, 275, "Beat the Game");
					break;
				case 1:
					centerText(675, 275, "Standard");
					break;
				case 2:
					centerText(675, 275, "Double");
					break;
				case 3:
					centerText(675, 275, "Spread");
					break;
				case 4:
					centerText(675, 275, "Fast");
					break;
				case 5:
					centerText(675, 275, "Fast Shotgun");
					break;
				case 6:
					centerText(675, 275, "Triple");
					break;
				case 7:
					centerText(675, 275, "Heavy");
					break;
				case 8:
					centerText(675, 275, "Assault");
					break;
				case 9:
					centerText(675, 275, "Fast v2");
					break;
				case 10:
					centerText(675, 275, "Shotgun");
					break;
				case 11:
					centerText(675, 275, "Spread v2");
					break;
				case 12:
					centerText(675, 275, "Septuple");
					break;
				case 13:
					centerText(675, 275, "Shockwave");
					break;
				case 14:
					centerText(675, 275, "Triple Fast");
					break;
				case 15:
					centerText(675, 275, "Super Heavy");
					break;
				case 16:
					centerText(675, 275, "Assault v2");
					break;
				case 17:
					centerText(675, 275, "Rocket Gun");
					break;
				case 18:
					centerText(675, 275, "Laser");
					break;
				case 19:
					centerText(675, 275, "Spray");
					break;
				case 20:
					centerText(675, 275, "Fast Spread");
					break;
				case 21:
					centerText(675, 275, "Flame");
					break;
				case 22:
					centerText(675, 275, "Surround");
					break;

				}
				wep3.stepEvent();
				settextstyle(3, 0, 3);
				setcolor(15);
				switch (wep3.specialvalue) {
				case 0:
					centerText(1075, 275, "Beat the Game");
					break;
				case 1:
					centerText(1075, 275, "Standard");
					break;
				case 2:
					centerText(1075, 275, "Double");
					break;
				case 3:
					centerText(1075, 275, "Spread");
					break;
				case 4:
					centerText(1075, 275, "Fast");
					break;
				case 5:
					centerText(1075, 275, "Fast Shotgun");
					break;
				case 6:
					centerText(1075, 275, "Triple");
					break;
				case 7:
					centerText(1075, 275, "Heavy");
					break;
				case 8:
					centerText(1075, 275, "Assault");
					break;
				case 9:
					centerText(1075, 275, "Fast v2");
					break;
				case 10:
					centerText(1075, 275, "Shotgun");
					break;
				case 11:
					centerText(1075, 275, "Spread v2");
					break;
				case 12:
					centerText(1075, 275, "Septuple");
					break;
				case 13:
					centerText(1075, 275, "Shockwave");
					break;
				case 14:
					centerText(1075, 275, "Triple Fast");
					break;
				case 15:
					centerText(1075, 275, "Super Heavy");
					break;
				case 16:
					centerText(1075, 275, "Assault v2");
					break;
				case 17:
					centerText(1075, 275, "Rocket Gun");
					break;
				case 18:
					centerText(1075, 275, "Laser");
					break;
				case 19:
					centerText(1075, 275, "Spray");
					break;
				case 20:
					centerText(1075, 275, "Fast Spread");
					break;
				case 21:
					centerText(1075, 275, "Flame");
					break;
				case 22:
					centerText(1075, 275, "Surround");
					break;

				}
				if (wep1.pressed) {
					if (player.money >= wepcost) {
						player.money -= wepcost;
						player.firetype = wep1.specialvalue;
						wepcost = wepcost * 4 + 200;
						switch (player.firetype) {
						case 0:
							break;
						case 1:
							wep1.specialvalue = 2;
							wep2.specialvalue = 4;
							wep3.specialvalue = 3;
							break;
						case 2:
							wep1.specialvalue = 6;
							wep2.specialvalue = 7;
							wep3.specialvalue = 8;
							break;
						case 3:
							wep1.specialvalue = 5;
							wep2.specialvalue = 10;
							wep3.specialvalue = 11;
							break;
						case 4:
							wep1.specialvalue = 8;
							wep2.specialvalue = 9;
							wep3.specialvalue = 5;
							break;
						case 5:
							wep1.specialvalue = 19;
							wep2.specialvalue = 21;
							wep3.specialvalue = 13;
							break;
						case 6:
							wep1.specialvalue = 14;
							wep2.specialvalue = 13;
							wep3.specialvalue = 12;
							break;
						case 7:
							wep1.specialvalue = 15;
							wep2.specialvalue = 13;
							wep3.specialvalue = 16;
							break;
						case 8:
							wep1.specialvalue = 16;
							wep2.specialvalue = 14;
							wep3.specialvalue = 17;
							break;
						case 9:
							wep1.specialvalue = 16;
							wep2.specialvalue = 18;
							wep3.specialvalue = 19;
							break;
						case 10:
							wep1.specialvalue = 13;
							wep2.specialvalue = 21;
							wep3.specialvalue = 20;
							break;
						case 11:
							wep1.specialvalue = 13;
							wep2.specialvalue = 20;
							wep3.specialvalue = 22;
							break;
						case 12:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 13:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 14:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 15:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 16:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 17:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 18:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 19:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 20:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 21:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 22:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;

						}
						if (wep1.specialvalue == 0) {
							wepcost = 0;
						}
						wep1.text = "Buy: $"+to_string(wepcost);
						wep2.text = "Buy: $" + to_string(wepcost);
						wep3.text = "Buy: $" + to_string(wepcost);
					}
				}
				if (wep2.pressed) {
					if (player.money >= wepcost) {
						player.money -= wepcost;
						player.firetype = wep2.specialvalue;
						wepcost = wepcost * 4 + 200;
						switch (player.firetype) {
						case 0:
							break;
						case 1:
							wep1.specialvalue = 2;
							wep2.specialvalue = 4;
							wep3.specialvalue = 3;
							break;
						case 2:
							wep1.specialvalue = 6;
							wep2.specialvalue = 7;
							wep3.specialvalue = 8;
							break;
						case 3:
							wep1.specialvalue = 5;
							wep2.specialvalue = 10;
							wep3.specialvalue = 11;
							break;
						case 4:
							wep1.specialvalue = 8;
							wep2.specialvalue = 9;
							wep3.specialvalue = 5;
							break;
						case 5:
							wep1.specialvalue = 19;
							wep2.specialvalue = 21;
							wep3.specialvalue = 13;
							break;
						case 6:
							wep1.specialvalue = 14;
							wep2.specialvalue = 13;
							wep3.specialvalue = 12;
							break;
						case 7:
							wep1.specialvalue = 15;
							wep2.specialvalue = 13;
							wep3.specialvalue = 17;
							break;
						case 8:
							wep1.specialvalue = 16;
							wep2.specialvalue = 14;
							wep3.specialvalue = 17;
							break;
						case 9:
							wep1.specialvalue = 16;
							wep2.specialvalue = 18;
							wep3.specialvalue = 19;
							break;
						case 10:
							wep1.specialvalue = 13;
							wep2.specialvalue = 21;
							wep3.specialvalue = 20;
							break;
						case 11:
							wep1.specialvalue = 13;
							wep2.specialvalue = 20;
							wep3.specialvalue = 22;
							break;
						case 12:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 13:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 14:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 15:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 16:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 17:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 18:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 19:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 20:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 21:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 22:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;

						}
						if (wep1.specialvalue == 0) {
							wepcost = 0;
						}
						wep1.text = "Buy: $" + to_string(wepcost);
						wep2.text = "Buy: $" + to_string(wepcost);
						wep3.text = "Buy: $" + to_string(wepcost);
					}
				}
				if (wep3.pressed) {
					if (player.money >= wepcost) {
						player.money -= wepcost;
						player.firetype = wep3.specialvalue;
						wepcost = wepcost * 4 + 200;
						switch (player.firetype) {
						case 0:
							break;
						case 1:
							wep1.specialvalue = 2;
							wep2.specialvalue = 4;
							wep3.specialvalue = 3;
							break;
						case 2:
							wep1.specialvalue = 6;
							wep2.specialvalue = 7;
							wep3.specialvalue = 8;
							break;
						case 3:
							wep1.specialvalue = 5;
							wep2.specialvalue = 10;
							wep3.specialvalue = 11;
							break;
						case 4:
							wep1.specialvalue = 8;
							wep2.specialvalue = 9;
							wep3.specialvalue = 5;
							break;
						case 5:
							wep1.specialvalue = 19;
							wep2.specialvalue = 21;
							wep3.specialvalue = 13;
							break;
						case 6:
							wep1.specialvalue = 14;
							wep2.specialvalue = 13;
							wep3.specialvalue = 12;
							break;
						case 7:
							wep1.specialvalue = 15;
							wep2.specialvalue = 13;
							wep3.specialvalue = 16;
							break;
						case 8:
							wep1.specialvalue = 16;
							wep2.specialvalue = 14;
							wep3.specialvalue = 17;
							break;
						case 9:
							wep1.specialvalue = 16;
							wep2.specialvalue = 18;
							wep3.specialvalue = 19;
							break;
						case 10:
							wep1.specialvalue = 13;
							wep2.specialvalue = 21;
							wep3.specialvalue = 20;
							break;
						case 11:
							wep1.specialvalue = 13;
							wep2.specialvalue = 20;
							wep3.specialvalue = 22;
							break;
						case 12:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 13:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 14:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 15:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 16:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 17:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 18:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 19:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 20:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 21:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;
						case 22:
							wep1.specialvalue = 0;
							wep2.specialvalue = 0;
							wep3.specialvalue = 0;
							break;

						}
						if (wep1.specialvalue == 0) {
							wepcost = player.money+1;
						}
						wep1.text = "Buy: $" + to_string(wepcost);
						wep2.text = "Buy: $" + to_string(wepcost);
						wep3.text = "Buy: $" + to_string(wepcost);
					}
				
				}
				if (wep1.specialvalue == 0) {
					wepcost = player.money + 1;
				}
				hpregen1.stepEvent();
				hpregen1.text = "Buy: $" + to_string(hpregencost);
				if (hpregen1.pressed) {
					if (player.money >= hpregencost) {
						player.money -= hpregencost;
						hpregenupgrades++;
						hpregencost *= 2;

					}

				}
				if (hpregenupgrades < 10) {
					centerText(1750, 250, "HP Regen");
				}
				else {
					centerText(1750, 250, "MAXED");
				}
				
				maxhp1.stepEvent();
				maxhp1.text = "Buy: $" + to_string(maxhpcost);
				if (maxhp1.pressed) {
					if (player.money >= maxhpcost) {
						player.money -= maxhpcost;
						maxhpupgrades += 1;
						player.hp += 10;
						maxhpcost *= 2;

					}

				}
				centerText(1450, 250, "Max HP");
				speed1.stepEvent();
				speed1.text = "Buy: $" + to_string(speedcost);
				if (speed1.pressed) {
					if (player.money >= speedcost) {
						player.money -= speedcost;
						speedupgrades += 1;
						speedcost *= 2;

					}

				}
				centerText(1450, 550, "Speed");
				maxstam1.stepEvent();
				maxstam1.text = "Buy: $" + to_string(maxstamcost);
				if (maxstam1.pressed) {
					if (player.money >= maxstamcost) {
						player.money -= maxstamcost;
						maxstamupgrades += 1;
						player.stamina += 10;
						maxstamcost *= 2;

					}

				}
				centerText(1750, 550, "Max Stamina");
				hppack.stepEvent();
				hppackcost = (score / 20) + 10;
				hppack.text = "Buy: $" + to_string(hppackcost);
				centerText(275, 675, "Heal");
				if (hppack.pressed) {
					if (player.money >= hppackcost) {
						player.money -= hppackcost;
						player.hp = min(100 + (10 * maxhpupgrades), player.hp + 100);;
						player.stamina = 100 + (10 * maxstamupgrades);
						

					}

				}
				

				wep1.text = "Buy: $" + to_string(wepcost);
				wep2.text = "Buy: $" + to_string(wepcost);
				wep3.text = "Buy: $" + to_string(wepcost);


			
				cursorIcon.draw();
				Sleep(40);
				if (shopbutton.pressed) {
					shopisopen = false;
					shopbutton.pressed = false;
					shopbutton.text = "SHOP";
					shopbutton.width -= 50;
					Sleep(20);
					pause = true;
				}
			}
			while (pause) {
				cleardevice();
				/*
				//Score Display
				setcolor(14);
				settextstyle(3, 0, 4);
				scorecarry = to_string(score);
				scoredisp = "Score: " + scorecarry;
				moveto(maxX - textwidth(scoredisp.c_str()) - 25, maxY - textheight(scoredisp.c_str()) - 25);
				outtext(scoredisp.c_str());
				//
				scorecarry = to_string(player.money);
				moneydisp = "Money: $" + scorecarry;
				moveto(textwidth(moneydisp.c_str())/2, maxY - textheight(moneydisp.c_str()) - 25);
				outtext(moneydisp.c_str());
				*/
				player.drawSelf();
				for (i = 0; i < playerbulletlimit; i++) {
					player.projectile[i].drawSelf();
				}
				for (i = 0; i < 20; i++) {
					rangedfoe[i].drawSelf();
					for (int f = 0; f < 20; f++) {
						rangedfoe[i].Eprojectile[f].drawSelf();
					}
					meleefoe[i].drawSelf();
					coins[i].drawSelf();
				}
				/*
				//Health Bar
				setcolor(4);
				bar(25, 25, 25 + (5 * player.hp), (75));
				setcolor(15);
				rectangle(25, 25, (525), (75));
				//Stamina Bar
				if (player.canDash == true) {
					setcolor(2);
				}
				else {
					setcolor(7);
				}
				bar(25, 90, 25 + (3.5 * player.stamina), (125));
				setcolor(15);
				rectangle(25, 90, (375), (125));
				*/
				cursorIcon.draw();
				Sleep(30);


			}

			//	cout << player.dir << endl;
			Sleep(20);
		}
		cleardevice();
		settextstyle(3, 0, 8);
		setcolor(15);
		titleoffset = (textwidth("Game Over!") / 2);
		moveto(centerX - titleoffset, centerY - (centerY / 2));
		outtext("Game Over!");
		tempstr = to_string(score);
		tempstr = "Your Score: " + tempstr;
		centerText(centerX, centerY + 100, tempstr.c_str());
		//
		retry.x = centerX - 250;
		retry.y = centerY + 300;
		retry.color = 15;
		retry.selectcolor = 14;
		retry.length = 150;
		retry.width = 500;
		retry.textfont = 0;//0-4
		retry.textdirection = 0;//0-1
		retry.textsize = 5;//0-8
		retry.text = "Retry?";
		//
		Sleep(500);
		while (retry.pressed != true)
		{
			if (cursorX < 5 && cursorY < 5) {
				isRunning = false;
			}
			cleardevice();
			settextstyle(3, 0, 8);
			setcolor(15);
			titleoffset = (textwidth("Game Over!") / 2);
			moveto(centerX - titleoffset, centerY - (centerY / 2));
			outtext("Game Over!");
			tempstr = to_string(score);
			tempstr = "Your Score: " + tempstr;
			centerText(centerX, centerY + 100, tempstr.c_str());
			
			settextstyle(3, 0, 4);
			setcolor(15);
			outtext("");
			retry.stepEvent();
			cursorIcon.draw();
			Sleep(30);
		
		}
		// Reset Game Data
		

		for (i = 0; i < playerbulletlimit; i++) {
			player.projectile[i].exists = false;
		}
		for (i = 0; i < 20; i++) {
			rangedfoe[i].exists = false;
			for (int f = 0; f < 20; f++) {
				rangedfoe[i].Eprojectile[f].exists = false;
			}
			meleefoe[i].exists = false;
			coins[i].exists = false;
		}

		 rangedtimer = 0;
		 rangedspawn = 300;
		 currentranged = 0;
		 rangedlimit = 1;
		 meleetimer = 0;
		 meleespawn = 100;
		 currentmelee = 0;
		 meleelimit = 0;
		
		 score = 0;
		
		
		 isRunning = true;
	
		 wepcost = 100;
		 hpregencost = 50;
		 hpregenTimer = 0;
		 hpregenupgrades = 0;
		 maxhpcost = 50;
		 speedcost = 50;
		 maxstamcost = 50;
		 maxstamupgrades = 0;
		 speedupgrades = 0;
		 maxhpupgrades = 0;
		 wep1.specialvalue = 0;
		 wep2.specialvalue = 0;
		 wep2.specialvalue = 0;
		 strobecolor = 4;
		 strobecount = 0;







		//
	}



//	system("pause");



	return;

}
void spawnEnemies() {
	if (rangedtimer >= rangedspawn && currentranged < rangedlimit ) {
		rangedfoe[rangedselector].init();
		rangedselector = (rangedselector + 1) % 20;
		rangedtimer = 0;
	}
	if (meleetimer >= meleespawn && currentmelee < meleelimit) {
		meleefoe[meleeselector].init();
		meleeselector = (meleeselector + 1) % 20;
		meleetimer = 0;
	}
	if (score < 200)
	{
		rangedspawn = 300;
		rangedlimit = 0;
		meleespawn = 300;
		meleelimit = 1;
	}
	else if (score < 500) {
		rangedspawn = 300;
		rangedlimit = 1;
		meleespawn = 270;
		meleelimit = 1;
	}
	else if (score < 1250) {
		rangedspawn = 290;
		rangedlimit = 1;
		meleespawn = 270;
		meleelimit = 2;
	}
	else if (score < 1750) {
		rangedspawn = 280;
		rangedlimit = 2;
		meleespawn = 270;
		meleelimit = 2;
	}
	else if (score < 2500) {
		rangedspawn = 280;
		rangedlimit = 2;
		meleespawn = 260;
		meleelimit = 3;
	}
	else if (score < 3000) {
		rangedspawn = 270;
		rangedlimit = 3;
		meleespawn = 250;
		meleelimit = 3;
	}
	else if (score < 3000) {
		rangedspawn = 260;
		rangedlimit = 4;
		meleespawn = 240;
		meleelimit = 3;
	}
	else if (score < 4000) {
		rangedspawn = 250;
		rangedlimit = 4;
		meleespawn = 240;
		meleelimit = 4;
	}
	else if (score < 5000) {
		rangedspawn = 240;
		rangedlimit = 5;
		meleespawn = 230;
		meleelimit = 5;
	}
	else if (score < 6000) {
		rangedspawn = 230;
		rangedlimit = 7;
		meleespawn = 210;
		meleelimit = 7;
	}
	else if (score < 7000) {
		rangedspawn = 210;
		rangedlimit = 9;
		meleespawn = 190;
		meleelimit = 9;
	}
	else if (score < 10000) {
		rangedspawn = 190;
		rangedlimit = 13;
		meleespawn = 170;
		meleelimit = 13;
	}
	else if (score < 15000) {
		rangedspawn = 170;
		rangedlimit = 15;
		meleespawn = 150;
		meleelimit = 15;
	}
	else if (score < 20000) {
		rangedspawn = 140;
		rangedlimit = 16;
		meleespawn = 120;
		meleelimit = 16;
	}
	else if (score < 30000) {
		rangedspawn = 100;
		rangedlimit = 18;
		meleespawn = 80;
		meleelimit = 18;
	}
	else if (score < 50000) {
		rangedspawn = 75;
		rangedlimit = 20;
		meleespawn = 50;
		meleelimit = 20;
	}
	else if (score < 75000) {
		rangedspawn = 45;
		rangedlimit = 20;
		meleespawn = 20;
		meleelimit = 20;
	}
	else if (score < 100000) {
		rangedspawn = 25;
		rangedlimit = 20;
		meleespawn = 10;
		meleelimit = 20;
	}
	else {
		rangedspawn = 0;
		rangedlimit = 20;
		meleespawn = 0;
		meleelimit = 20;
	}










	meleetimer++;
	rangedtimer++;
}
void centerText(int x,int y,string text){
	outtextxy(x - (textwidth(text.c_str()) / 2), y - (textheight(text.c_str()) / 2), text.c_str());
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
	return;
}
void music() {
	while (true) {
		playSound("easy.mp3", 421000);
	}
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
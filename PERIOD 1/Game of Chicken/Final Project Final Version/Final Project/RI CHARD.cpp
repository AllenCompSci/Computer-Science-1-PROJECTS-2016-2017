/*
Ayy the project
Ishi Tripathi, Anna & Ethan Tran
Computer Science
*/

//2. Libraries
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
#pragma region GLOBALVARs;

//3. Namespace
using namespace std;

//4. Functions
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
void greatChicken(int x, int y, int howGreat);
void chickenMOVE(int, int);
int maxX, maxY;
int GrDriver, GrMode, ErrorCode;
int R;
int XR, YR;
const int chicken_Height = 64;
const int chicken_Width = 63;
#pragma region CHICKEN_DRAW 
const int chicken_ARRY[64][63] = {

	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 15, 15, 15, 15, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 15, 15, 15, 15, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 0, 0, 0, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 0, 0, 0, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 0, 0, 0, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 0, 0, 0, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
};
#pragma endregion 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
void playSound(string, int);  // sound effect
void gameThread();
void music();
void lines();
bool keypress = false;
int screenX, screenY, halfX, halfY;
INPUT_RECORD irInBuf;
struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
}global;

int X, Y;
int egg = 0;
int X2, Y2, X3, Y3, X4, Y4, X5, Y5, X6, Y6, X7, Y7, X8, Y8, X9, Y9, X10, Y10, X11, Y11, X12, Y12, X13, Y13, X14, Y14, X15, Y15, X16, Y16, X17, Y17, X18, Y18, X19, Y19, X20, Y20 = -1;
int X[100];
int Y[100];
int Xsmol, Ysmol;
int Xegg, Yegg;
int Xfirst = 60;
int Yfirst = 60;
int blankX, blankY;
string WIN = "Win";
string score = "0";

struct ayyEgg {
	int XR, YR;
	int randx;
	int	randy;
	int EggColor;
	bool collision = false;
	void init() {
		randx= rand() % 16;
		randy = rand() % 8;
		Xegg = 60 + (randx* 120);
		Yegg = 60 + (randy * 120);
		XR = 14;
		YR = 20;
		EggColor = 15;
		setcolor(EggColor);
		draw();
		cout << "Xegg and Yegg: " << Xegg << ", " << Yegg << endl;
	}
	void draw() {
		fillellipse(Xegg, Yegg, XR, YR);
	}

	void respawn() {
		if (X[1]== Xegg && Y == Yegg) {
			init();
		}
	}
	void GODComplex() {
		if (KEYBOARD(VK_0)) {
			system("pause");
		}
	}
}smolegg;

struct MAMAchicken {
	int Chickcolor;
	int radius;
	int radiusI;
	int radiusB;
	string End = "LOSER";
	void init() {
		radius = 50;
		radiusI = 5;
		radiusB = 30;
		X[1]= 180;
		Y = 60;
		Chickcolor = 14;
		setcolor(Chickcolor);
		drawB();
		drawC();
		drawI();
	}
	void drawC() {
		setcolor(YELLOW);
		fillellipse(X, Y, radius, radius);
	}
	void drawI() {
		setcolor(6);
		fillellipse((X[1]+ 20), Y, radiusI, radiusI);
	}
	void drawB() {
		setcolor(13);
		// reverse pieslice
		pieslice((X[1]+ 60), Y, 145, 210, radiusB);
	}
	void MamaMove(){
			
			if (global.VirtualKey == VK_A) {
			X20 = X19;
			Y20 = Y19; 
			X19 = X18;
			Y19 = Y18;
			X18 = X17;
			Y18 = Y17;
			X17 = X16;
			Y17 = Y16;
			X16 = X15;
			Y16 = Y15;
			X15 = X14;
			Y15 = Y14;
			X14 = X13;
			Y14 = Y13;
			X13 = X12;
			Y13 = Y12;
			X12 = X11;
			Y12 = Y11; 
			X11 = X10;
			Y11 = Y10;
			X10 = X9;
			Y10 = Y9;
			X9 = X8;
			Y9 = Y8;
			X8 = X7;
			Y8 = Y7;
			X7 = X6;
			Y7 = Y6;
			X6 = X5;
			Y6 = Y5;
			X5 = X4;
			Y5 = Y4;
			X4 = X3;
			Y4 = Y3;
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			X[1]= X[1]- 120;
			drawB();
			drawC();
			drawI();
			cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_D) {
			X20 = X19;
			Y20 = Y19;
			X19 = X1
			Y19 = Y18;
			X18 = X17;
			Y18 = Y17;
			X17 = X16;
			Y17 = Y16;
			X16 = X15;
			Y16 = Y15;
			X15 = X14;
			Y15 = Y14;
			X14 = X13;
			Y14 = Y13;
			X13 = X12;
			Y13 = Y12;
			X12 = X11;
			Y12 = Y11;
			X11 = X10;
			Y11 = Y10;
			X10 = X9;
			Y10 = Y9;
			X9 = X8;
			Y9 = Y8;
			X8 = X7;
			Y8 = Y7;
			X7 = X6;
			Y7 = Y6;
			X6 = X5;
			Y6 = Y5;
			X5 = X4;
			Y5 = Y4;
			X4 = X3;
			Y4 = Y3;
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			X[1]= X[1]+ 120;
			drawB();
			drawC();
			drawI();
			cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_W) {
			X20 = X19;
			Y20 = Y19;
			X19 = X18;
			Y19 = Y18;
			X18 = X17;
			Y18 = Y17;
			X17 = X16;
			Y17 = Y16;
			X16 = X15;
			Y16 = Y15;
			X15 = X14;
			Y15 = Y14;
			X14 = X13;
			Y14 = Y13;
			X13 = X12;
			Y13 = Y12;
			X12 = X11;
			Y12 = Y11;
			X11 = X10;
			Y11 = Y10;
			X10 = X9;
			Y10 = Y9;
			X9 = X8;
			Y9 = Y8;
			X8 = X7;
			Y8 = Y7;
			X7 = X6;
			Y7 = Y6;
			X6 = X5;
			Y6 = Y5;
			X5 = X4;
			Y5 = Y4;
			X4 = X3;
			Y4 = Y3;
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			Y = Y - 120;
			drawB();
			drawC();
			drawI();
			cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_S) {
			X20 = X19;
			Y20 = Y19;
			X19 = X18;
			Y19 = Y18;
			X18 = X17;
			Y18 = Y17;
			X17 = X16;
			Y17 = Y16;
			X16 = X15;
			Y16 = Y15;
			X15 = X14;
			Y15 = Y14;
			X14 = X13;
			Y14 = Y13;
			X13 = X12;
			Y13 = Y12;
			X12 = X11;
			Y12 = Y11;
			X11 = X10;
			Y11 = Y10;
			X10 = X9;
			Y10 = Y9;
			X9 = X8;
			Y9 = Y8;
			X8 = X7;
			Y8 = Y7;
			X7 = X6;
			Y7 = Y6;
			X6 = X5;
			Y6 = Y5;
			X5 = X4;
			Y5 = Y4;
			X4 = X3;
			Y4 = Y3;
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			Y = Y + 120;
			drawB();
			drawC();
			drawI();
			cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_0) {
			cleardevice();
			lines();
			drawB();
			drawC();
			drawI();

			keypress = false;
		}

		if (X[1]== Xegg && Y == Yegg) {
			smolegg.init();
			cout << "Xegg and Yegg: " << Xegg << ", " << Yegg << endl;
			egg = egg + 1;
			score = to_string(egg*100);
			cout << "SCORE : " << score << endl;
		}


		Sleep(40);
	}

	void EndGame(){
		//if ((X[1]== Xfirst || X[1]== X2 || X[1]== X3 || X[1]== X4 || X[1]== X5 || X[1]== X6 || X[1]== X7 || X[1]== X8 || X[1]== X9 || X[1]== X10 || X[1]== X11 || X[1]== X12 || X[1]== X13 || X[1]== X14 || X[1]== X15 || X[1]== X16 || X[1]== X17 || X[1]== X18 || X[1]== X19) && (Y == Yfirst || Y == Y2 || Y == Y3 || Y == Y4 || Y == Y5 || Y == Y6 || Y == Y7 || Y == Y8 || Y == Y9 || Y == Y10 || Y == Y11 || Y == Y12 || Y == Y13 || Y == Y14 || Y == Y15 || Y == Y16 || Y == Y17 || Y == Y18 || Y == Y19)) {
		if ((X[1]== Xfirst && Y == Yfirst) || (X[1]== X2 && Y == Y2) || (X[1]== X3 && Y == Y3) || (X[1]== X4 && Y == Y4) || (X[1]== X5 && Y == Y5) || (X[1]== X6 && Y == Y6) || (X[1]== X7 && Y == Y7)){
			//|| (X[1]== X9 && Y == Y9) || (X[1]== X10 && Y == Y10) || (X[1]== X11 && Y == Y11) || (X[1]== X12 && Y == Y12) || (X[1]== X13 && Y == Y13) || (X[1]== X14 && Y == Y14) || (X[1]== X15 && Y == Y15) || (X[1]== X16 && Y == Y16) || (X[1]== X17 && Y == Y17) || (X[1]== X18 && Y == Y18) || (X[1]== X19 && Y == Y19)) {
			cout << "END GAME : " << endl;
			cout << "X[1]and Y : " << X[1]<< ", " << Y << endl;
			cout << "Xfirst and Yfirst : " << Xfirst << ", " << Yfirst << endl;
			cout << "X2 and Y2 : " << X2 << ", " << Y2 << endl;
			cout << "X3 and Y3 : " << X3 << ", " << Y3 << endl; 
			cout << "X4 and Y4 : " << X4 << ", " << Y4 << endl;
			cout << "X5 and Y5 : " << X5 << ", " << Y5 << endl;
			cout << "X6 and Y6 : " << X6 << ", " << Y6 << endl;
			cout << "X7 and Y7 : " << X7 << ", " << Y7 << endl;
			cout << "X8 and Y8 : " << X8 << ", " << Y8 << endl;
			cout << "X9 and Y9 : " << X9 << ", " << Y9 << endl;
			cout << "X10 and Y10 : " << X10 << ", " << Y10 << endl;
			cout << "Score : " << score << endl;

			setcolor(RED);
			bar(0, 0, 1920, 1920);

			setcolor(WHITE);
			settextstyle(0, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());
			system("pause");
		}
		if (X[1]<= -60) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920,1920);

			setcolor(WHITE);
			settextstyle(4, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());

			cout << "SCORE : " << score << endl;

			system("pause");
		}
		else if (Y >= 960) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920, 1920);

			setcolor(WHITE);
			settextstyle(0, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());

			cout << "SCORE : " << score << endl;

			system("pause");
		}
		else if (X[1]>= 1920) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920, 1920);

			setcolor(WHITE);
			settextstyle(0, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());

			cout << "SCORE : " << score << endl;

			system("pause");
		}
		else if (Y <= -60) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920, 1920);

			setcolor(WHITE);
			settextstyle(0, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());

			cout << "SCORE : " << score << endl;

			system("pause");
		}
	}

}chicken;

struct SmolChick {
	int radius;
	int Chickcolor;
	int radiusI;
	int radiusB;
	void initchick() {
		radius = 25;
		radiusI = 3;
		radiusB = 15;
		Xsmol = 60;
		Ysmol = 60;
		Chickcolor = 14;
		setcolor(Chickcolor);
		drawBchick();
		drawCchick();
		drawIchick();
	}
	void drawCchick() {
		setcolor(YELLOW);
		fillellipse(Xfirst, Yfirst, radius, radius);
	}
	void drawIchick() {
		setcolor(6);
		fillellipse((Xfirst + 10), Yfirst, radiusI, radiusI);
	}
	void drawBchick() {
		setcolor(13);
		// reverse pieslice
		pieslice((Xfirst + 30), Yfirst, 145, 210, radiusB);
	}

	void drawCsecond() {
		setcolor(YELLOW);
		fillellipse(blankX, blankY, radius, radius);
	}
	void drawIsecond() {
		setcolor(6);
		fillellipse((blankX + 10), blankY, radiusI, radiusI);
	}
	void drawBsecond() {
		setcolor(13);
		// reverse pieslice
		pieslice((blankX + 30), blankY, 145, 210, radiusB);
	}

	void smolmove(){

		setcolor(GREEN);
		bar(Xfirst - 60, Yfirst - 60, Xfirst + 60, Yfirst + 60);
		lines();
		Sleep(30);

			if (global.VirtualKey == VK_A) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_D) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_W) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_S) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
		/*	else if (global.VirtualKey == VK_0) {
				cleardevice();
				lines();
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X[1]and Y: " << X[1]<< "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			*/

			if (egg == 0) {
				setcolor(GREEN);
				blankX= X[2];
				blankY = Y[2];
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 1) {
				setcolor(GREEN);
				blankX= X[3];
				blankY = Y[3];
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 2) {
				setcolor(GREEN);
				blankX= X4;
				blankY = Y4;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 3) {
				setcolor(GREEN);
				blankX= X5;
				blankY = Y5;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 4) {
				setcolor(GREEN);
				blankX= X6;
				blankY = Y6;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X2 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 5) {
				setcolor(GREEN);
				blankX= X7;
				blankY = Y7;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 6) {
				setcolor(GREEN);
				blankX= X8;
				blankY = Y8;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 7) {
				setcolor(GREEN);
				blankX= X9;
				blankY = Y9;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			//10 Chicks :
			else if (egg == 8) {
				setcolor(GREEN);
				blankX= X10;
				blankY = Y10;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 9) {
				setcolor(GREEN);
				blankX= X11;
				blankY = Y11;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 10) {
				setcolor(GREEN);
				blankX= X12;
				blankY = Y12;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 11) {
				setcolor(GREEN);
				blankX= X13;
				blankY = Y13;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 12) {
				setcolor(GREEN);
				blankX= X14;
				blankY = Y14;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X2 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 13) {
				setcolor(GREEN);
				blankX= X15;
				blankY = Y15;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 14) {
				setcolor(GREEN);
				blankX= X16;
				blankY = Y16;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 15) {
				setcolor(GREEN);
				blankX= X17;
				blankY = Y17;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 16) {
				setcolor(GREEN);
				blankX= X18;
				blankY = Y18;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 17) {
				setcolor(GREEN);
				blankX= X19;
				blankY = Y19;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			//20 chicks:
			else if (egg == 18) {
				setcolor(GREEN);
				blankX= X20;
				blankY = Y20;
				bar(blankX+ 60, blankY + 60, blankX- 60, blankY - 60);
				cout << "BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

			else if (egg == 19){
				cout << "WIN GAME" << endl;
				setcolor(RED);
				bar(0, 0, 1920, 1920);

				setcolor(WHITE);
				settextstyle(4, 0, 8);

				textheight(WIN.c_str());
				textwidth(WIN.c_str());
				outtextxy(815, 480, WIN.c_str());
				system("pause");
			}

			/*else if (VK_0) {
				cout << "WIN GAME" << endl;
				setcolor(RED);
				bar(0, 0, 1920, 1920);

				setcolor(WHITE);
				settextstyle(4, 0, 8);

				textheight(WIN.c_str());
				textwidth(WIN.c_str());
				outtextxy(815, 480, WIN.c_str());
				system("pause");
			}
			*/
			lines();
			Sleep(40);
		}

}smolchick;



//5. MAIN

void main() {

	gr_Start(GrDriver, GrMode, ErrorCode);
	srand((unsigned int)time(NULL));

	thread g(gameThread); // Thread definiton
	thread t(KEY_LISTENER);
	thread m(music);

	global.press = false;
	g.join();
	
	t.join(); // thread t start
	return;
}
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

	bool KEYBOARD(int VirtualKey) {
		if ((GetAsyncKeyState(VirtualKey) & 0x8100) != 0)
		{
			irInBuf.EventType = KEY_EVENT;
			global.press = true;
			global.VirtualKey = VirtualKey;
			int count = 0;
			do {
				if (count++ < 200) {
					global.hold = true;
					return true;
				}
			} while ((GetAsyncKeyState(VirtualKey) & 0x8100) != 0 );
			return true;
		}
		return false;
	}
	void KEY_LISTENER() {

		while (true) {
			
			if (keypress == false) {

				if (KEYBOARD(VK_A) || KEYBOARD(VK_LEFT)) {
					global.VirtualKey = VK_A;
					keypress = true;
					cout << "Left:" << endl;
				}
				if (KEYBOARD(VK_W) || KEYBOARD(VK_UP)) {
					global.VirtualKey = VK_W;
					keypress = true;
					cout << "Up:" << endl;
				}
				if (KEYBOARD(VK_S) || KEYBOARD(VK_DOWN)) {
					global.VirtualKey = VK_S;
					keypress = true;
					cout << "Down:" << endl;
				}
				if (KEYBOARD(VK_D) || KEYBOARD(VK_RIGHT)) {
					global.VirtualKey = VK_D;
					keypress = true;
					cout << "Right:" << endl;
				}
				if (KEYBOARD(VK_0)) {
					cout << "Zero:";
				}
			}
			Sleep(50);
		}

	}
	void music() {
	}

/*	void playSound(string Song, int 10000) {
		if (Song.substr(Song.length() - 2) == "v") {
			PlaySound(TEXT(Song.c_str()), NULL, SND_ASYNC);
			Sleep(10000);
			PlaySound(TEXT(Song.c_str()), 0, 0);
			return;
		}
		string concat = "open " + Song + " type mpegvideo alias MP3_Device";
		LPCSTR a = concat.c_str();
		mciSendString(a, NULL, 0, 0);

		mciSendString("play MP3_Device", NULL, 0, 0);
		Sleep(10000);
		mciSendString("stop MP3_Device", NULL, 0, 0);
		mciSendString("close MP3_Device", NULL, 0, 0);
	}
	*/

	void gameThread() {
		srand((unsigned int)time(NULL));

		string SCORE = "Score : ";

		maxX[1]= getmaxx();
		maxY = getmaxy();
		cout << "Max:" << maxX[1]<< " " << maxY << endl;
		cout << "Random " << rand() % maxX[1]<< endl;
		setbkcolor(2);
		cleardevice();
		smolegg.init();
		cout << X[1]<< endl;
		cout << Y << endl;
		chicken.init();
		smolchick.initchick();
		lines();
		setbkcolor(BLACK);
		setcolor(BLACK);
		bar(1560, 962, 1920, 1080);
		//greatChicken(0, 0,15);


		while (true) {
			if (global.press) {

				setcolor(WHITE);
				settextstyle(4, 0, 6);
				textheight(SCORE.c_str());
				textwidth(SCORE.c_str());
				outtextxy(1440, 962, SCORE.c_str());

				setcolor(WHITE);
				settextstyle(0, 0, 6);

				textheight(score.c_str());
				textwidth(score.c_str());
				outtextxy(1720, 968, score.c_str());

				smolegg.respawn();
				chicken.MamaMove();
				smolchick.smolmove();
				smolegg.GODComplex();
				chicken.EndGame();
				keypress = false;
			}

			Sleep(30);
		}
		closegraph();

	}

	void lines() {
		int lineX[1]= 0;
		int liney = 0;
		int linex2 = 0;
		int liney2 = 960;
		setcolor(15);
		for (int i = 0; i < 16; i++) {
			line(linex, liney, linex2, liney2);
			linex2 = 120 * (i + 1);
			lineX[1]= linex2;
		}
		lineX[1]= 0;
		liney = 0;
		linex2 = 1920;
		liney2 = 0;
		for (int i = 0; i < 9; i++) {
			line(linex, liney, linex2, liney2);
			liney2 = 120 * (i + 1);
			liney = liney2;
		}


	}
	/*void background() {
		bool toggle = true;
		int color1 = WHITE;
		int color2 = MAGENTA;
		int FREQ = 1;
		int FREQ0 = 1;
		intBAR;

		for (int j = 0; j <= t; j++) {
			for (int i = 0; i <= t; i++)
			{
				if (toggle) {
					if (rand() % FREQ0 == 0)
						putpixel(halfX[1]+ i, halfY, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY + j, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX[1]- i, halfY, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]+ i, halfY + j))
							putpixel(halfX[1]+ i, halfY + j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]- i, halfY - j))
							putpixel(halfX[1]- i, halfY - j, color1);
					if (rand() % FREQ == 0)  
						if (bar(halfX, halfY, t, halfX[1]+ i, halfY - j))
							putpixel(halfX[1]+ i, halfY - j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]- i, halfY + j))
							putpixel(halfX[1]- i, halfY + j, color2);

				}
				else {

					if (rand() % FREQ0 == 0)
						putpixel(halfX[1]+ i, halfY, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY + j, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX[1]- i, halfY, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY - j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]+ i, halfY + j))
							putpixel(halfX[1]+ i, halfY + j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]- i, halfY - j))
							putpixel(halfX[1]- i, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]+ i, halfY - j))
							putpixel(halfX[1]+ i, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX[1]- i, halfY + j))
							putpixel(halfX[1]- i, halfY + j, color1);

				}
				toggle = !toggle;
				//Sleep(2);
			}
		}

	}
	*/

	
	void chickenMOVE(int x, int y) {
		for (int i = 0; i < chicken_Height; i++)
			for (int j = 0; j < chicken_Width; j++)
				if (chicken_ARRY[i][j] != 99)
					putpixel(X[1]+ j, i + y, chicken_ARRY[i][j]);
	}
	void greatChicken(int x, int y, int howGreat) {
		for (int i = 0; i < chicken_Height; i++)
			for (int j = 0; j < chicken_Width; j++)
				if (chicken_ARRY[i][j] != 99) {
					setcolor(chicken_ARRY[i][j]);
					bar(X[1]+ j * howGreat, y + i * howGreat, X[1]+ (j + 1) * howGreat, y + (i + 1) * howGreat);
				}
	}
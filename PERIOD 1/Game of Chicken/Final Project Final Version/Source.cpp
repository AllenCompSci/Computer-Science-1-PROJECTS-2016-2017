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
int X2, Y2, X3, Y3, X4, Y4, X5, Y5, X6, Y6, X7, Y7, X8, Y8, X9, Y9, X10, Y10;
int Xsmol, Ysmol;
int Xegg, Yegg;
int Xfirst = 60;
int Yfirst = 60;
int egg = 0;
int blankX, blankY;

struct ayyEgg {
	int XR, YR;
	int randx;
	int	randy;
	int EggColor;
	bool collision = false;
	void init() {
		randx = rand() % 16;
		randy = rand() % 8;
		Xegg = 60 + (randx * 120);
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
		if (X == Xegg && Y == Yegg) {
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
	string End = "DEAD";
	void init() {
		radius = 50;
		radiusI = 5;
		radiusB = 30;
		X = 180;
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
		fillellipse((X + 20), Y, radiusI, radiusI);
	}
	void drawB() {
		setcolor(13);
		// reverse pieslice
		pieslice((X + 60), Y, 145, 210, radiusB);
	}
	void MamaMove(){
			
			if (global.VirtualKey == VK_A) {
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			X = X - 120;
			drawB();
			drawC();
			drawI();
			cout << "X and Y: " << X << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_D) {
			X3 = X2;
			Y3 = Y2;
			X2 = Xfirst;
			Y2 = Yfirst; 
			Xfirst = X;
			Yfirst = Y;
			X = X + 120;
			drawB();
			drawC();
			drawI();
			cout << "X and Y: " << X << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_W) {
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
			cout << "X and Y: " << X << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_S) {
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
			cout << "X and Y: " << X << "," << Y << endl;
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

		if (X == Xegg && Y == Yegg) {
			smolegg.init();
			cout << "Xegg and Yegg: " << Xegg << ", " << Yegg << endl;
			egg = egg + 1;
			cout << "Egg Count : " << egg << endl;
		}


		Sleep(40);
	}

	void EndGame(){
		if (X <= -60) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920,1920);

			setcolor(WHITE);
			settextstyle(4, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());
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
			system("pause");
		}
		else if (X >= 2040) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920, 1920);

			setcolor(WHITE);
			settextstyle(0, 0, 8);

			textheight(End.c_str());
			textwidth(End.c_str());
			outtextxy(815, 480, End.c_str());
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
				cout << "X and Y: " << X << "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_D) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X and Y: " << X << "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_W) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X and Y: " << X << "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_S) {
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X and Y: " << X << "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}
			else if (global.VirtualKey == VK_0) {
				cleardevice();
				lines();
				drawBchick();
				drawCchick();
				drawIchick();
				cout << "X and Y: " << X << "," << Y << endl;
				cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
				keypress = false;
			}


			if (egg == 1) {
				blankX = X3;
				blankY = Y3;
				drawBsecond();
				drawCsecond();
				drawIsecond();
			}

			if (egg = 1) {
				setcolor(GREEN);
				blankX = X2;
				blankY = Y2;
				bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
				cout << "BAR______________________________: " << X2 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}
			else if (egg = 2) {
				setcolor(GREEN);
				blankX = X3;
				blankY = Y3;
				bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
				cout << " BAR______________________________: " << X3 << endl;
				cout << "Egg______________________________: " << egg << endl;
			}

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

		maxX = getmaxx();
		maxY = getmaxy();
		cout << "Max:" << maxX << " " << maxY << endl;
		cout << "Random " << rand() % maxX << endl;
		setbkcolor(2);
		cleardevice();
		smolegg.init();
		cout << X << endl;
		cout << Y << endl;
		chicken.init();
		smolchick.initchick();
		lines();
		setbkcolor(BLACK);
		//greatChicken(0, 0,15);
		while (true) {
			if (global.press) {
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
		int linex = 0;
		int liney = 0;
		int linex2 = 0;
		int liney2 = 960;
		setcolor(15);
		for (int i = 0; i < 16; i++) {
			line(linex, liney, linex2, liney2);
			linex2 = 120 * (i + 1);
			linex = linex2;
		}
		linex = 0;
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
		int bar;

		for (int j = 0; j <= t; j++) {
			for (int i = 0; i <= t; i++)
			{
				if (toggle) {
					if (rand() % FREQ0 == 0)
						putpixel(halfX + i, halfY, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY + j, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX - i, halfY, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX + i, halfY + j))
							putpixel(halfX + i, halfY + j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX - i, halfY - j))
							putpixel(halfX - i, halfY - j, color1);
					if (rand() % FREQ == 0)  
						if (bar(halfX, halfY, t, halfX + i, halfY - j))
							putpixel(halfX + i, halfY - j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX - i, halfY + j))
							putpixel(halfX - i, halfY + j, color2);

				}
				else {

					if (rand() % FREQ0 == 0)
						putpixel(halfX + i, halfY, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY + j, color1);
					if (rand() % FREQ0 == 0)
						putpixel(halfX - i, halfY, color2);
					if (rand() % FREQ0 == 0)
						putpixel(halfX, halfY - j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX + i, halfY + j))
							putpixel(halfX + i, halfY + j, color1);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX - i, halfY - j))
							putpixel(halfX - i, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX + i, halfY - j))
							putpixel(halfX + i, halfY - j, color2);
					if (rand() % FREQ == 0)
						if (bar(halfX, halfY, t, halfX - i, halfY + j))
							putpixel(halfX - i, halfY + j, color1);

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
					putpixel(x + j, i + y, chicken_ARRY[i][j]);
	}
	void greatChicken(int x, int y, int howGreat) {
		for (int i = 0; i < chicken_Height; i++)
			for (int j = 0; j < chicken_Width; j++)
				if (chicken_ARRY[i][j] != 99) {
					setcolor(chicken_ARRY[i][j]);
					bar(x + j * howGreat, y + i * howGreat, x + (j + 1) * howGreat, y + (i + 1) * howGreat);
				}
	}
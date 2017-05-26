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
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
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
void music();
void playSound(string, int);
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
int Xsmol, Ysmol;
int Xegg, Yegg;
int Xfirst;
int Yfirst;
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
		else if ((0 <= egg <= 8) && (Xegg == X2 && Yegg == Y2) || (Xegg == X3 && Yegg == Y3) || (Xegg == X4 && Yegg == Y4) || (Xegg == X5 && Yegg == Y5) || (Xegg == X6 && Yegg == Y6) || (Xegg == X7 && Yegg == Y7)) {
				init();
			}
		else if ((7 <= egg <= 12) && (Xegg == X2 && Yegg == Y2) || (Xegg == X3 && Yegg == Y3) || (Xegg == X4 && Yegg == Y4) || (Xegg == X5 && Yegg == Y5) || (Xegg == X6 && Yegg == Y6) || (Xegg == X7 && Yegg == Y7) || (Xegg == X8 && Yegg == Y8) || (Xegg == X9 && Yegg == Y9) || (Xegg == X10 && Yegg == Y10) || (Xegg == X11 && Yegg == Y11) || (Xegg == X12 && Yegg == Y12) || (Xegg == X13 && Yegg == Y13) || (Xegg == X14 && Yegg == Y14))
			init();
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
	void MamaMove() {

		if (global.VirtualKey == VK_A) {
			if (egg >= 6) {
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
			}
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
			X = X - 120;
			drawB();
			drawC();
			drawI();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_D) {
			if (egg >= 6) {
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
			}
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
			X = X + 120;
			drawB();
			drawC();
			drawI();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_W) {
			if (egg >= 6) {
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
			}
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
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_S) {
			if (egg >= 6) {
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
			}
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
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
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
			score = to_string(egg * 100);
			cout << "SCORE : " << score << endl;
		}


		Sleep(40);
	}

	void EndGame() {

			if ((0 <= egg <= 8) && (X == X2 && Y == Y2) || (X == X3 && Y == Y3) || (X == X4 && Y == Y4) || (X == X5 && Y == Y5) || (X == X6 && Y == Y6) || (X == X7 && Y == Y7)) {

				cout << "END GAME : " << endl;
				cout << "X and Y : " << Xfirst << ", " << Y << endl;
				cout << "Xfirst and Yfirst : " << Xfirst << ", " << Yfirst << endl;
				cout << "X2 and Y2 : " << X2 << ", " << Y2 << endl;
				cout << "X3 and Y3 : " << X3 << ", " << Y3 << endl;
				cout << "X4 and Y4 : " << X4 << ", " << Y4 << endl;
				cout << "X5 and Y5 : " << X5 << ", " << Y5 << endl;
				cout << "X6 and Y6 : " << X6 << ", " << Y6 << endl;
				cout << "X7 and Y7 : " << X7 << ", " << Y7 << endl;
				cout << "Score : " << score << endl;
				cout << "Xegg and Yegg : " << Xegg << ", " << Yegg << endl;

				setcolor(RED);
				bar(0, 0, 1920, 1920);

				setcolor(WHITE);
				settextstyle(0, 0, 8);

				textheight(End.c_str());
				textwidth(End.c_str());
				outtextxy(815, 480, End.c_str());
				system("pause");
			}

			else if ((7 <= egg <= 12) && (X == X2 && Y == Y2) || (X == X3 && Y == Y3) || (X == X4 && Y == Y4) || (X == X5 && Y == Y5) || (X == X6 && Y == Y6) || (X == X7 && Y == Y7) || (X == X8 && Y == Y8) || (X == X9 && Y == Y9) || (X == X10 && Y == Y10) || (X == X11 && Y == Y11) || (X == X12 && Y == Y12) || (X == X13 && Y == Y13) || (X == X14 && Y == Y14)) {

				cout << "END GAME : " << endl;
				cout << "X and Y : " << Xfirst << ", " << Y << endl;
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
				cout << "X11 and Y11 : " << X11 << ", " << Y11 << endl;
				cout << "X12 and Y12 : " << X12 << ", " << Y12 << endl;
				cout << "X13 and Y13 : " << X13 << ", " << Y13 << endl;
				cout << "X14 and Y14 : " << X14 << ", " << Y14 << endl;
				cout << "Score : " << score << endl;
				cout << "Xegg and Yegg : " << Xegg << ", " << Yegg << endl;

				setcolor(RED);
				bar(0, 0, 1920, 1920);

				setcolor(WHITE);
				settextstyle(0, 0, 8);

				textheight(End.c_str());
				textwidth(End.c_str());
				outtextxy(815, 480, End.c_str());
				system("pause");
			}
	
		if (Xfirst <= -60) {
			cout << "END GAME" << endl;
			setcolor(RED);
			bar(0, 0, 1920, 1920);

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
		else if (Xfirst >= 1920) {
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
		Xfirst = 60;
		Yfirst = 60;
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

	void smolmove() {

		setcolor(GREEN);
		bar(Xfirst - 60, Yfirst - 60, Xfirst + 60, Yfirst + 60);
		lines();
		Sleep(30);

		if (global.VirtualKey == VK_A) {
			drawBchick();
			drawCchick();
			drawIchick();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_D) {
			drawBchick();
			drawCchick();
			drawIchick();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_W) {
			drawBchick();
			drawCchick();
			drawIchick();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}
		else if (global.VirtualKey == VK_S) {
			drawBchick();
			drawCchick();
			drawIchick();
			cout << "Xfirstand Y: " << Xfirst << "," << Y << endl;
			cout << "Xfirst and Yfirst: " << Xfirst << "," << Yfirst << endl;
			keypress = false;
		}

		if (egg == 0) {
			setcolor(GREEN);
			blankX = X2;
			blankY = Y2;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 1) {
			setcolor(GREEN);
			blankX = X3;
			blankY = Y3;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 2) {
			setcolor(GREEN);
			blankX = X4;
			blankY = Y4;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 3) {
			setcolor(GREEN);
			blankX = X5;
			blankY = Y5;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 4) {
			setcolor(GREEN);
			blankX = X6;
			blankY = Y6;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 5) {
			setcolor(GREEN);
			blankX = X7;
			blankY = Y7;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 6) {
			setcolor(GREEN);
			blankX = X8;
			blankY = Y8;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 7) {
			setcolor(GREEN);
			blankX = X9;
			blankY = Y9;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		//10 Chicks :
		else if (egg == 8) {
			setcolor(GREEN);
			blankX = X10;
			blankY = Y10;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 9) {
			setcolor(GREEN);
			blankX = X11;
			blankY = Y11;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 10) {
			setcolor(GREEN);
			blankX = X12;
			blankY = Y12;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 11) {
			setcolor(GREEN);
			blankX = X13;
			blankY = Y13;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 12) {
			setcolor(GREEN);
			blankX = X14;
			blankY = Y14;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 13) {
			setcolor(GREEN);
			blankX = X15;
			blankY = Y15;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 14) {
			setcolor(GREEN);
			blankX = X16;
			blankY = Y16;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 15) {
			setcolor(GREEN);
			blankX = X17;
			blankY = Y17;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 16) {
			setcolor(GREEN);
			blankX = X18;
			blankY = Y18;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 17) {
			setcolor(GREEN);
			blankX = X19;
			blankY = Y19;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		//20 chicks:
		else if (egg == 18) {
			setcolor(GREEN);
			blankX = X20;
			blankY = Y20;
			bar(blankX + 60, blankY + 60, blankX - 60, blankY - 60);
			 
			cout << "Egg______________________________: " << egg << endl;
		}

		else if (egg == 19) {
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

	setbkcolor(BLACK);
	setcolor(GREEN);
	bar(0, 0, 1920, 1920);
	greatChicken(1200, 300, 10);

	setbkcolor(GREEN);
	setcolor(DARKGRAY);
	settextstyle(3, 0, 8);
	string SNEK = "SNAKE : ";
	textheight(SNEK.c_str());
	textwidth(SNEK.c_str());
	outtextxy(695, 400, SNEK.c_str());
	string CHEEPCHEEP = "CHICKEN EDITION";
	textheight(CHEEPCHEEP.c_str());
	textwidth(CHEEPCHEEP.c_str());
	outtextxy(815, 480, CHEEPCHEEP.c_str());
	
	Sleep(2000);
	cleardevice();


	thread g(gameThread); // Thread definiton
	thread t(KEY_LISTENER);
	thread m(music);
	m.join();

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
		} while ((GetAsyncKeyState(VirtualKey) & 0x8100) != 0);
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
	while (true) {
		playSound("CDS.mp3", 421000);
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
	return;
}

void gameThread() {
	srand((unsigned int)time(NULL));

	string SCORE = "Score : ";

	maxX = getmaxx();
	maxY = getmaxy();
	cout << "Max:" << maxX << " " << maxY << endl;
	cout << "Random " << rand() % maxX << endl;
	setbkcolor(2);
	cleardevice();
	smolegg.init();
	cout << Xfirst << endl;
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
intBAR;

for (int j = 0; j <= t; j++) {
for (int i = 0; i <= t; i++)
{
if (toggle) {
if (rand() % FREQ0 == 0)
putpixel(halfXfirst+ i, halfY, color1);
if (rand() % FREQ0 == 0)
putpixel(halfX, halfY + j, color2);
if (rand() % FREQ0 == 0)
putpixel(halfXfirst- i, halfY, color1);
if (rand() % FREQ0 == 0)
putpixel(halfX, halfY - j, color2);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst+ i, halfY + j))
putpixel(halfXfirst+ i, halfY + j, color2);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst- i, halfY - j))
putpixel(halfXfirst- i, halfY - j, color1);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst+ i, halfY - j))
putpixel(halfXfirst+ i, halfY - j, color1);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst- i, halfY + j))
putpixel(halfXfirst- i, halfY + j, color2);

}
else {

if (rand() % FREQ0 == 0)
putpixel(halfXfirst+ i, halfY, color2);
if (rand() % FREQ0 == 0)
putpixel(halfX, halfY + j, color1);
if (rand() % FREQ0 == 0)
putpixel(halfXfirst- i, halfY, color2);
if (rand() % FREQ0 == 0)
putpixel(halfX, halfY - j, color1);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst+ i, halfY + j))
putpixel(halfXfirst+ i, halfY + j, color1);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst- i, halfY - j))
putpixel(halfXfirst- i, halfY - j, color2);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst+ i, halfY - j))
putpixel(halfXfirst+ i, halfY - j, color2);
if (rand() % FREQ == 0)
if (bar(halfX, halfY, t, halfXfirst- i, halfY + j))
putpixel(halfXfirst- i, halfY + j, color1);

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
				putpixel(Xfirst + j, i + y, chicken_ARRY[i][j]);
}

void greatChicken(int x, int y, int howGreat) {
	for (int i = 0; i < chicken_Height; i++)
		for (int j = 0; j < chicken_Width; j++)
			if (chicken_ARRY[i][j] != 99) {
				setcolor(chicken_ARRY[i][j]);
				bar(Xfirst + j * howGreat, y + i * howGreat, Xfirst + (j + 1) * howGreat, y + (i + 1) * howGreat);
			}
}
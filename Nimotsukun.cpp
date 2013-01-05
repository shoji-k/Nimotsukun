// Nimotsukun.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include<iostream>

using namespace System;
using namespace std;

const char gStateData[] = "\
########\n\
#      #\n\
# o    #\n\
#   P  #\n\
########";

const int gStateWidth = 8;
const int gStateHeight = 5;

enum StateObject {
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_MAN,
	OBJ_MAN_ON_GOAL,

	OBJ_UNKNOWN,
};

void draw(const StateObject* state, int width, int height);
void initialize(StateObject* state, int w, int h, const char* StateData);
char getInput();
void updateGame(StateObject* s, char input, int w, int h);
bool checkClear(const StateObject* state, int w, int h);

int main(array<System::String ^> ^args)
{
	/*
	char c;
	cin >> c;
	cout << "Input character is " << c;
	*/
	char input;

    Console::WriteLine(L"Start Game");

 	StateObject* state = new StateObject[gStateWidth * gStateHeight];
	initialize(state, gStateWidth, gStateHeight, gStateData);

	while (true) {
		draw(state, gStateWidth, gStateHeight);
		if(checkClear(state, gStateWidth, gStateHeight)) {
			break;
		}
		input = getInput();
		updateGame(state, input, gStateWidth, gStateHeight);
	}

	delete[] state;
	state = 0;

	Console::WriteLine(L"Clear!!");

    return 0;
}

char getInput()
{
	char c;
	cin >> c;
	return c;
}

void updateGame(StateObject* s, char input, int w, int h)
{
	int dx = 0;
	int dy = 0;
	switch ( input ) {
		case 'a': dx = -1; break; // left
		case 's': dx =  1; break; // right
		case 'w': dy = -1; break; // up
		case 'z': dy =  1; break; // down
	}

	// find player location
	int i = 0;
	for(i=0; i < w * h; ++i) {
		if(s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL) {
			break;
		}
	}
	int x = i % w;
	int y = i / w;

	// location after moving
	int tx = x + dx;
	int ty = y + dy;

	// check location
	if(tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}

	// move
	int p = y*w + x;
	int tp = ty*w + tx;

	// able to move
	if(s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
		s[tp] = (s[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
		s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;

	// find box in front
	} else if (s[tp] == OBJ_BLOCK || s[tp] ==OBJ_BLOCK_ON_GOAL) {
		// set two cells ahead
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		// check location
		if(tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) {
			return;
		}
		int tp2 = (ty+dy)*w + (tx+dx);
		if(s[tp2] == OBJ_SPACE || s[tp2] == OBJ_GOAL) {
			// move block
			s[tp2] = (s[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
			s[tp] = (s[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
			s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
		}
	}
}

bool checkClear(const StateObject* state, int w, int h)
{
	for(int i = 0; i < w*h; ++i) {
		if(state[i] == OBJ_BLOCK) {
			return false;
		}
	}
	return true;
}

void draw(const StateObject* state, int width, int height)
{
	const char font[] = {' ', '#', '.', 'o', 'O', 'p', 'P'};
	for ( int y = 0; y < height; ++y) {
		for ( int x = 0; x < width; ++x ) {
			StateObject o = state[y*width + x];
			cout << font[o];
		}
		cout << endl;
	}
}

void initialize(StateObject* state, int width, int height, const char* StateData) 
{
	const char* d = StateData;
	int x = 0;
	int y = 0;
	while ( *d != '\0') {
		StateObject t;
		switch ( *d ) {
		case '#': t = OBJ_WALL; break;
		case ' ': t = OBJ_SPACE; break;
		case 'o': t = OBJ_BLOCK; break;
		case 'O': t = OBJ_BLOCK_ON_GOAL; break;
		case '.': t = OBJ_GOAL; break;
		case 'p': t = OBJ_MAN; break;
		case 'P': t = OBJ_MAN_ON_GOAL; break;
		case '\n':
			x = 0;
			++y;
			t = OBJ_UNKNOWN;
			break;
		default: t = OBJ_UNKNOWN; break;
		}
	    ++d;
		if (t != OBJ_UNKNOWN) {
			state[y*width + x] = t;
			++x;
		}
	}

}
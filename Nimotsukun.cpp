// Nimotsukun.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include<iostream>

using namespace System;
using namespace std;

bool getInput();
bool updateGame();

const char gStateData[] = "\
########\n\
#  .   #\n\
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

int main(array<System::String ^> ^args)
{
	/*
	char c;
	cin >> c;
	cout << "Input character is " << c;
	*/

    Console::WriteLine(L"Start Game");

 	StateObject* state = new StateObject[gStateWidth * gStateHeight];
	initialize(state, gStateWidth, gStateHeight, gStateData);

	while (true) {
		draw(state, gStateWidth, gStateHeight);
		getInput();
		updateGame();
	}

	delete[] state;
	state = 0;

    return 0;
}

bool getInput()
{
	char c;
	cin >> c;
	return true;
}

bool updateGame()
{
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
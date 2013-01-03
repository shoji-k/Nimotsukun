// Nimotsukun.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include<iostream>

using namespace System;
using namespace std;

bool getInput();
bool updateGame();
bool draw();

int main(array<System::String ^> ^args)
{
	/*
	char c;
	cin >> c;
	cout << "Input character is " << c;
	*/

    Console::WriteLine(L"Start Game");

	while (true) {
		getInput();
		updateGame();
		draw();
	}
    return 0;
}

bool getInput()
{
	return true;
}

bool updateGame()
{
	return true;
}

bool draw()
{
	return true;
}

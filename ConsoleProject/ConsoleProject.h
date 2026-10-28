#pragma once

#include <iostream>
#include <windows.h>

#include <iostream>
#include <windows.h>
#include "ConsoleProject.h"
#include "Console.h"
#include "ScreenHandler.h"

#include <thread>
#include <chrono>
#include <atomic>
using namespace std;


/*it Features the following features

-Writing Text in different colors into the console

-Getting user input and giving output depending on the input

-For and while loops

-Different types of Type conversions

-Timers and number things

-Switch cases and If statements

-Arrays and pointers

-External files and text editing

-Classes and Obects and structsw

*/

class Introduction {
public:

	static void DrawClockIterations(int cycleDelay);

	void DrawScreen(int cycleDelay);

	void DrawRotatingCube(int cycleDelay);
	int Game();


};
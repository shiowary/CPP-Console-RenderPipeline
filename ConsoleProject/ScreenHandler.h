#pragma once
#include <array>
#include "Console.h" 
#include "Pixel.h"
#include "Vector.h"
#include "math.h"
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
# define M_PI           3.14159265358979323846  /* pi */
namespace Rendering {


	class ScreenHandler
	{

	public:
		int a_ConsoleWindowWidth;
		int a_ConsoleWindowHeight;
		int a_Refreshrate;



		ScreenHandler();
#pragma region Misc
		void DrawLineOnBuffer(Vector origin, Vector line, string px, const Console::rgb fc = Console::rgb(255, 255, 255), const Console::rgb bc = Console::rgb(0, 0, 0));
		void Drawclock(int iteration, int len, int x, int y, string px, Console::rgb fcol, Console::rgb bcol);
		void DrawCircle(int radius, string px, int x_, int y_, Console::rgb color);
		Vector Project(Vector point, float fov, float viewerDistance);
		void DrawRotatingCubeOnBuffer(float angle, float size = 5.0f, int x = 0, int y =0);

#pragma endregion

#pragma region Buffer
		


		//Updates what will be rendered on the next frame ahead of time for calculations
		void PassBufferToScreen();

		
		array<Pixel, 3600>* GetBufferPointer();

		void ClearBuffer() ;



#pragma endregion


#pragma region Screen
		void ClearScreen();
		bool DrawScreen();
		void InitPixels();


#pragma endregion
	private:



		//the default size for The developer console window is 120x30 = 3600
		//if you are not sure go to the console window->settings->startsize
		
		array<Pixel, 3600> ScreenPixels;
		array<Pixel, 3600> PreviousScreen;
		array<Pixel, 3600> BufferPixels;


		void GetConsoleSize();

		

#pragma region Buffer



#pragma endregion


#pragma region Screen



#pragma endregion
	protected:


#pragma region Buffer


#pragma endregion


#pragma region Screen


#pragma endregion
	};

}


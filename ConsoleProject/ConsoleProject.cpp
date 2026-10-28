
//The idea of this program is to test many different features of C++ to get more attached to it

/*it Features the following features

-Writing Text in different colors into the console

-Getting user input and giving output depending on the input

-Different types of Type conversions

-Timers and number things

-Arrays and pointers 

-External files and text editing

*/

#include <iostream>
#include <windows.h>
#include "ConsoleProject.h"
#include "Console.h"
#include "ScreenHandler.h"
#include "InputHandler.h"
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;
using namespace Rendering;

using std::string;



	void main() {
		Introduction intro;
		//intro.DrawClockIterations(3);
		intro.DrawRotatingCube(1);
        //intro.Game();
		
	}

	void Introduction::DrawClockIterations(int cycleDelay) {
		ScreenHandler screen;
		int i = 0;
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(cycleDelay));
			i++;
			screen.Drawclock(-i, 8, 16, 16, "X", Console::rgb(255, 0, 0), Console::rgb(0, 0, 0));
			screen.DrawCircle(9, "O", 16, 16, Console::rgb(255, 255, 255));
			screen.PassBufferToScreen();
			screen.DrawScreen();
		}
	}

	void Introduction::DrawRotatingCube(int cycleDelay) {
		ScreenHandler screen;
		int i = 0;
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(cycleDelay));
			i++;
				screen.DrawRotatingCubeOnBuffer(i, 8.0f, 16, 16);
				screen.PassBufferToScreen();
				screen.DrawScreen();
			
		}
	}

	void Introduction::DrawScreen(int cycleDelay) {
		int i = 0;
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(cycleDelay));
			i++;
		}
	}

    int Introduction::Game() {



        float fPlayerX = 7.0f;
        float fPlayerY = 6.0f;
        float fPlayerA = 0.0f;
        const int nMapWidth = 16;
        const int nMapHeight = 13;
        float fFOV = 3.14159f / 4.0f;
        float fDepth = 12.0f;
        ScreenHandler screenH;
        int nScreenWidth = screenH.a_ConsoleWindowWidth;
        int nScreenHeight = screenH.a_ConsoleWindowHeight;
        string shadeChars[] = { "","","","" };

        auto screen = std::make_unique<std::array<Pixel, 3600>>();



        std::wstring map;
        map += L"################";
        map += L"#..............#";
        map += L"#..............#";
        map += L"#..............#";
        map += L"#..........#...#";
        map += L"#..........#...#";
        map += L"#..............#";
        map += L"#..............#";
        map += L"#..............#";
        map += L"#......#########";
        map += L"#..............#";
        map += L"#..............#";
        map += L"################";

        auto tp1 = std::chrono::system_clock::now();
        auto tp2 = std::chrono::system_clock::now();

        while (true) {

            tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsedTime = tp2 - tp1;
            tp1 = tp2;
            float fElapsedTime = elapsedTime.count();

            int ch = InputHandler::getkey();
            if (ch == 'A' || ch == 'a')
            {
                fPlayerA -= (0.8f) * fElapsedTime;
            }

            if (ch == 'D' || ch == 'd')
            {
                fPlayerA += (0.8f) * fElapsedTime;;
            }

            if (ch == 'W' || ch == 'w')
            {
                fPlayerX += std::sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY += std::cosf(fPlayerA) * 5.0f * fElapsedTime;

                if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
                {
                    fPlayerX -= std::sinf(fPlayerA) * 5.0f * fElapsedTime;
                    fPlayerY -= std::cosf(fPlayerA) * 5.0f * fElapsedTime;
                }

            }


            if (ch == 'S' || ch == 's')
            {
                fPlayerX -= std::sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY -= std::cosf(fPlayerA) * 5.0f * fElapsedTime;

                if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
                {
                    fPlayerX += std::sinf(fPlayerA) * 5.0f * fElapsedTime;
                    fPlayerY += std::cosf(fPlayerA) * 5.0f * fElapsedTime;
                }
            }


            for (int x = 0; x < nScreenWidth; x++)
            {
                float fRayAngle = (fPlayerA - fFOV / 4.0f) + ((float)x / (float)nScreenWidth) * fFOV;

                float fDistanceToWall = 0;
                bool bHitWall = false;
                bool bBoundary = false;

                float fEyeX = std::sinf(fRayAngle);
                float fEyeY = std::cosf(fRayAngle);

                while (!bHitWall && fDistanceToWall < fDepth) {
                    fDistanceToWall += 0.1f;

                    int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                    int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                    if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                    {
                        bHitWall = true;
                        fDistanceToWall = fDepth;
                    }
                    else {
                        if (map[nTestY * nMapWidth + nTestX] == '#')
                        {
                            bHitWall = true;
                            Vector p;

                            for (int tx = 0; tx < 2; tx++)
                            {
                                for (int ty = 0; ty < 2; ty++)
                                {
                                    float vy = (float)nTestY + ty - fPlayerY;
                                    float vx = (float)nTestX + tx - fPlayerX;
                                    float d = sqrt(vx * vx + vy * vy);
                                    float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                    //p.push_back(std::make_pair(d, dot));
                                    p.x = d;
                                    p.y = dot;
                                }
                                float fBound = 0.1;
                                if (acos(p.x) < fBound) bBoundary = true;
                                if (acos(p.y) < fBound) bBoundary = true;
                            }
                        }
                    }
                }

                int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
                int nFloor = nScreenHeight - nCeiling;

                string nWallShade = "°";
                if (fDistanceToWall <= fDepth / 4.0f)        nWallShade = '#';
                else if (fDistanceToWall < fDepth / 3.0f)   nWallShade = '*';
                else if (fDistanceToWall < fDepth / 2.0f)   nWallShade = "@";
                else if (fDistanceToWall < fDepth)          nWallShade = ",";
                else                                        nWallShade = " ";
                if (bBoundary) nWallShade = "°";

                for (int y = 0; y < nScreenHeight; y++)
                {
                    if (y < nCeiling)
                    {
                        //
                        (*screen)[y * nScreenWidth + x].UpdatePixelInPlace();
                    }
                    else if (y > nCeiling && y <= nFloor)
                    {
                        //
                        (*screen)[y * nScreenWidth + x].UpdatePixelInPlace(nWallShade);
                    }
                    else
                    {
                        string nGroundShade = " ";
                        float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
                        if (b < 0.25) nGroundShade = "=";
                        else if (b < 0.5) nGroundShade = "-";
                        else if (b < 0.76) nGroundShade = ".";
                        else if (b < 0.9) nGroundShade = ",";
                        else nGroundShade = " ";
                        (*screen)[y * nScreenWidth + x].UpdatePixelInPlace(nGroundShade);
                    }
                }
            }


            //Clear console window
            *screenH.GetBufferPointer() = (*screen);
            screenH.PassBufferToScreen();
            screenH.DrawScreen();
            //draw new screen here - > using screen


            float fps = 1.0f / fElapsedTime;
            //Draw new console window
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }

        return 0;
    }
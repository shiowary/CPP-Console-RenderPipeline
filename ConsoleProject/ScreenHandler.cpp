#include "ScreenHandler.h"

namespace Rendering {

	#pragma region Helper Functions

		ScreenHandler::ScreenHandler() {
			InitPixels();
		};


		void ScreenHandler::GetConsoleSize() {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			a_ConsoleWindowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			a_ConsoleWindowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		}

		void ScreenHandler::InitPixels() {
			GetConsoleSize();
			for (int x = 0; x < a_ConsoleWindowWidth; x++) {
				for (int y = 0; y < a_ConsoleWindowHeight; y++) {
					int index = y * a_ConsoleWindowWidth + x;
					ScreenPixels[index].UpdatePixel(" ", x, y);
					PreviousScreen[index].UpdatePixel(" ", x, y);
				}
			}
		}



		void ScreenHandler::Drawclock(int iteration, int len,int x,int y, string px, Console::rgb fcol, Console::rgb bcol)
		{
			float angle = -(iteration % 360) * (float)(M_PI / 180.0);
			int length = len;
			int endX = x + (int)(length * cos(angle));
			int endY = y+ (int)(length * sin(angle));
			DrawLineOnBuffer(Vector(x, y),Vector(endX, endY), px, fcol, bcol);
		}

		void ScreenHandler::DrawLineOnBuffer(Vector origin, Vector line, string px, const Console::rgb fc, const Console::rgb bc)
		{
			int x0 = (int)origin.x;
			int y0 = (int)origin.y;
			int x1 = (int)line.x;
			int y1 = (int)line.y;
			int dx = abs(x1 - x0);
			int dy = abs(y1 - y0);
			int sx = x0 < x1 ? 1 : -1;
			int sy = y0 < y1 ? 1 : -1;
			int err = dx - dy;
			while (true)
			{
				int index = y0 * a_ConsoleWindowWidth + x0;
				if (index > 0 && index < BufferPixels.size()-1) {
					BufferPixels[index].UpdatePixel(px, x0 , y0,fc,bc);
				}
				if (x0 == x1 && y0 == y1) break;
				int e2 = 2 * err;
				if (e2 > -dy)
				{
					err -= dy;
					x0 += sx;
				}
				if (e2 < dx)
				{
					err += dx;
					y0 += sy;
				}
			}

		}

		void ScreenHandler::DrawCircle(int radius, string px,int x_,int y_, Console::rgb color)
		{


			for (int deg = 0; deg < 360; deg++)
			{
				float angle = deg * (float)(M_PI / 180.0);
				int x = x_ + (int)(radius * cos(angle));
				int y = y_ + (int)(radius * sin(angle));
				int index = y * a_ConsoleWindowWidth + x;
				if (index > 0 || index < BufferPixels.size()) {
					BufferPixels[index].UpdatePixel(px, x, y,color);
				}
			}
		}

		Vector ScreenHandler::Project(Vector point, float fov, float viewerDistance)
		{
			float factor = fov / (viewerDistance + point.z);
			float x = point.x * factor;
			float y = point.y * factor;
			return Vector(x, y, point.z);
		}

		void ScreenHandler::DrawRotatingCubeOnBuffer(float angle, float size,int x, int y)
		{
			array<Vector,8> vertices =
			{
				 Vector(-size, -size, -size),
				 Vector(size, -size, -size),
				 Vector(size,  size, -size),
				 Vector(-size,  size, -size),
				 Vector(-size, -size,  size),
				 Vector(size, -size,  size),
				 Vector(size,  size,  size),
				 Vector(-size,  size,  size),
			};

			
			array<Vector, vertices.size()> rotatedVertices;
			for (int i = 0; i < vertices.size(); i++)
			{
				rotatedVertices[i] = vertices[i].RotateY(vertices[i], angle);
				rotatedVertices[i] = vertices[i].RotateX(rotatedVertices[i], angle * 1.3f);
				rotatedVertices[i] = vertices[i].RotateZ(rotatedVertices[i], angle * 0.7f);
			}
			array<Vector, vertices.size()> screenVertices;
			
			for (int i = 0; i < rotatedVertices.size(); i++)
			{
				Vector translated = rotatedVertices[i] + Vector(0, 0, 15.0f);
				screenVertices[i] = Project(translated, 25.0f, 10.0f);
			}

			// Define cube edges
			std::array<std::pair<int, int>, 12> edges = { {
				{0, 1}, {1, 2}, {2, 3}, {3, 0},
				{4, 5}, {5, 6}, {6, 7}, {7, 4},
				{0, 4}, {1, 5}, {2, 6}, {3, 7}
			} };
			for (const auto& edge : edges) {
				int start = edge.first;
				int end = edge.second;
				Vector pointA = screenVertices[start];
				Vector pointB = screenVertices[end];
				DrawLineOnBuffer(x + Vector((int)pointA.x,y- (int)pointA.y, 0),x+ Vector((int)pointB.x, y-(int)pointB.y, 0),"°",Console::rgb(255,255,255));
			}
		}






	#pragma endregion


	#pragma region Buffer

		void ScreenHandler::PassBufferToScreen() {
			PreviousScreen = ScreenPixels;
			ScreenPixels = BufferPixels;

		};

		array<Pixel, 3600>* ScreenHandler::GetBufferPointer() {
			return &BufferPixels ;
		}

		void ScreenHandler::ClearBuffer() {
			GetConsoleSize();
			for (int x = 0; x < a_ConsoleWindowWidth; x++) {
				for (int y = 0; y < a_ConsoleWindowHeight; y++) {
					int index = y * a_ConsoleWindowWidth + x;
					BufferPixels[index].UpdatePixel(" ", x, y);
					
				}
			}

			//space reserved for potentially more functionality
			
		};
		


	#pragma endregion


	#pragma region Screen
		void ScreenHandler::ClearScreen() {
			Console::Clear();
		
		}


		bool ScreenHandler::DrawScreen() {
			//ClearScreen();
			ClearBuffer();
			Pixel P = Pixel(" ", 0, 0);
			for (int x = 0; x < a_ConsoleWindowWidth; x++) {
				for (int y = 0; y < a_ConsoleWindowHeight; y++) {
					int index = y * a_ConsoleWindowWidth + x;
					if (index >0 || index < ScreenPixels.size()) {
						P = ScreenPixels[index];
						if (P == PreviousScreen[index]) {
							//
						}else
						{
							Console::printAtC(P.GetPixel(), x, y, P.GetColor()[0], P.GetColor()[1]);
						}
					}
				}
			}
			return true;
		
		}



	#pragma endregion

}

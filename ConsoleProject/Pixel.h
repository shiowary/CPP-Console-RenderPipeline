#pragma once
#include <array>
#include "Console.h" 
using namespace std;
namespace Rendering {

	class Pixel
	{
	public:
		array<int, 2> GetPos();
		string GetPixel();
		Pixel(string P,int x, int y,const Console::rgb fc = Console::rgb(255, 255, 255), Console::rgb bc = Console::rgb(0, 0, 0)) : m_x(x), m_y(y), m_FColor(fc), m_BColor(bc),m_Character(P) {};
		Pixel() = default;
		void ClearPixel();
		void UpdatePixel(string P, int x, int y,const Console::rgb fc = Console::rgb(255, 255, 255),const Console::rgb bc = Console::rgb(0, 0, 0));
		void UpdatePixelInPlace(const string P = " " , const Console::rgb fc = Console::rgb(255, 255, 255), const Console::rgb bc = Console::rgb(0, 0, 0));
		array<Console::rgb, 2> GetColor();
	private:
		int m_x = 0;
		int m_y = 0;  
		string m_Character =" ";
		Console::rgb m_FColor = Console::rgb(255, 255, 255);
		Console::rgb m_BColor = Console::rgb(0, 0, 0);
	protected:

	};

	inline bool operator==(Pixel& a, Pixel& b) { return a.GetPixel() == b.GetPixel() && a.GetPos() == b.GetPos() && a.GetColor()[0] == b.GetColor()[0] &&a.GetColor()[1] == b.GetColor()[1]; };
	inline bool operator!=(Pixel& a, Pixel& b) { return !(a.GetPixel() == b.GetPixel() && a.GetPos() == b.GetPos() && a.GetColor()[0] == b.GetColor()[0] && a.GetColor()[1] == b.GetColor()[1]); };

};




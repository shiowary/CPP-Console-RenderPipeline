#include "Pixel.h"
#include "Console.h"
namespace Rendering {
	void Pixel::ClearPixel() {
		m_FColor = Console::rgb(255,255,255);
		m_BColor = Console::rgb(0, 0, 0);
		m_Character = " ";
	};

	array<int, 2> Pixel::GetPos() {
		array<int,2> a = { m_x,m_y };
		return a;
	}

	string Pixel::GetPixel() {
		return m_Character;
	}
	array<Console::rgb, 2> Pixel::GetColor() {
		array<Console::rgb, 2> a = { m_FColor, m_BColor };
		return a;
	}

	void Pixel::UpdatePixel(string P, int x, int y,const Console::rgb fc , const Console::rgb bc) {
		m_x = x;
		m_y = y;
		m_Character = P;
		m_FColor = fc;
		m_BColor = bc;
	
	
	}
	void Pixel::UpdatePixelInPlace(const string P, const Console::rgb fc, const Console::rgb bc) {
		m_Character = P;
		m_FColor = fc;
		m_BColor = bc;
	
	};
	

}
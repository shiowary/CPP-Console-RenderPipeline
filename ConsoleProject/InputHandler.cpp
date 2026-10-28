#include "InputHandler.h"

std::string InputHandler::GetStringLine() {
	std::string S_Input;
	std::getline(std::cin, S_Input);
	return S_Input;
};

std::string InputHandler::GetString() {
	 std::string S_Input;
	 std::cout << "Enter a number: ";
	 std::cin >> S_Input;
	 return S_Input;
};

void InputHandler::PrintRelativeMousePosition() {
	HWND console_wnd = GetConsoleWindow();
	POINT cursor_pos;

	if (GetCursorPos(&cursor_pos))
	{
		if (console_wnd && ScreenToClient(console_wnd, &cursor_pos));
		{
			std::cout << '(' << cursor_pos.x << ", " << cursor_pos.y << ")\n";

		}
	}
}

int InputHandler::getkey(){
			for (int i = 1; i < 255; ++i) {
				// The bitwise and selects the function behavior (look at doc)
				if (GetAsyncKeyState(i) & 0x07)
					return i;
			}
		}



#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
using namespace std;


class InputHandler
{
	public:
		std::string GetStringLine() ;
		std::string GetString() ;

		static void PrintRelativeMousePosition();
		static int getkey();

	private:
	protected:


	
};


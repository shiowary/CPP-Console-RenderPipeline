#pragma once


#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif


namespace Rendering {
    class Console
    {
    public:
        struct rgb
        {
            int r =0;
            int g = 0;
            int b = 0;
            //Console::rgb(0, 0, 0) = Black
            //Console::rgb(255, 255, 255) = White

            rgb(const int r_, const int g_, const int b_)
                : r(r_), g(g_), b(b_) {
            }
            rgb() = default;

           
        };
       


#pragma region Helper Functions
        static void init()
        {
#ifdef _WIN32
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

            if (handle != INVALID_HANDLE_VALUE)
            {
                DWORD mode = 0;

                if (GetConsoleMode(handle, &mode))
                {
                    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                    SetConsoleMode(handle, mode);
                }
            }
#endif

            std::cout << "\033[?25l";

            reset();

            std::cout.flush();
        }

        static void shutdown()
        {
            reset();
            std::cout << "\033[?25h";

            std::cout.flush();
        }

        static void setForeground(const rgb& color)
        {
            std::cout
                << "\033[38;2;"
                << color.r << ';'
                << color.g << ';'
                << color.b << 'm';
        }

        static void setBackground(const rgb& color)
        {
            std::cout
                << "\033[48;2;"
                << color.r << ';'
                << color.g << ';'
                << color.b << 'm';
        }

        static void setColors(const rgb& foreground,
            const rgb& background)
        {
            setForeground(foreground);
            setBackground(background);
        }

        static void reset()
        {
            std::cout << "\033[0m";
        }


        static void Clear()
        {
        #if defined _WIN32
                    system("cls");
                    //clrscr(); // including header file : conio.h
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
                    system("clear");
                    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
        #elif defined (__APPLE__)
                    system("clear");
        #endif
        }
#pragma endregion


#pragma region Print into Console
        static void print(const std::string& text)
        {
            std::cout << text;
        }

        static void printLine(const std::string& text)
        {
            std::cout << text << '\n';
        }

        static void printCLine(const std::string& text,
            const rgb& foreground = Console::rgb(255, 255, 255),
            const rgb& background = Console::rgb(0, 0, 0))
        {
            setColors(foreground, background);

            std::cout << text;

            reset();

            std::cout << '\n';
        }

        static void printC(const std::string& text,
            const rgb& foreground = Console::rgb(255, 255, 255),
            const rgb& background = Console::rgb(0, 0, 0))
        {
            setColors(foreground, background);
            std::cout << text;
            reset();
        }

        static void printAtC(const std::string& text, const int x = 0, const int y = 0, const rgb& foreground = Console::rgb(255, 255, 255), const rgb& background = Console::rgb(0, 0, 0))
        {
            moveCursor(x, y);
            setColors(foreground, background);
            std::cout << text;
            reset();
        }


        static void moveCursor(int x, int y)
        {
            std::cout
                << "\033["
                << (y + 1)
                << ';'
                << (x + 1)
                << 'H';
        }

        static void setCursorPosition(int x, int y)
        {
            moveCursor(x, y);
        }

        static void clearScreen()
        {
            std::cout << "\033[2J";
            moveCursor(0, 0);
        }

        static void clearLine()
        {
            std::cout << "\033[2K";
        }


        static void printCharAt(int x,
            int y,
            char character,
            const rgb& foreground,
            const rgb& background)
        {
            moveCursor(x, y);
            setColors(foreground, background);
            std::cout << character;
            reset();
        }

        static void setScreenColor(const rgb& color)
        {
            setBackground(color);
            std::cout << "\033[2J";

            moveCursor(0, 0);

            reset();
        }

#pragma endregion

#pragma region Get Console Params



        static std::pair<int, int> getSize()
        {
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO info{};

            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

            if (handle != INVALID_HANDLE_VALUE &&
                GetConsoleScreenBufferInfo(handle, &info))
            {
                int width =
                    info.srWindow.Right - info.srWindow.Left + 1;

                int height =
                    info.srWindow.Bottom - info.srWindow.Top + 1;

                return { width, height };
            }



#elif defined(__unix__) || defined(__APPLE__)
#endif

            return { 80, 24 };
        };

        static int getWidth()
        {
            return getSize().first;
        }

        static int getHeight()
        {
            return getSize().second;
        }

        static void flush()
        {
            std::cout.flush();
        }
    };
#pragma endregion
    inline bool operator ==(Console::rgb& a, Console::rgb& b) { return a.r == b.r && a.g == b.g && a.b == b.b; };

    
};

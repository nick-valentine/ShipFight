#ifndef LINUXIO_HPP
#define LINUXIO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Computer/ScreenIO/AbstractIO.hpp"
#include "lib/StrFunc.hpp"

class LinuxIO : public AbstractIO
{
public:
	LinuxIO();

	void putch(char x);
	char getch();

	void putint(int x);
	int getint();

	void clear();
	void putstr(std::string str);

private:
	static const char EMPTY_CHAR = ' ';

	void updateScreen();

	void cursorTestWrap(unsigned int addLength);

	std::string getTemplateEmptyString();

	const static unsigned int screen_width = 64;
	const static unsigned int screen_height = 28;

	std::vector<std::string> virtualScreen;

	unsigned int cursor_x;
	unsigned int cursor_y;
};

#endif //LINUXIO_HPP

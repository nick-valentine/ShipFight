#include "Computer/ScreenIO/LinuxIO.hpp"

LinuxIO::LinuxIO()
{
	this->clear();
}

void LinuxIO::putch(char x)
{
	if(x != '\n') {
		virtualScreen[cursor_y][cursor_x] = x;
		cursor_x++;
	} else {
		cursor_x = 0;
		cursor_y++;
	}
	cursorTestWrap(1);
	this->updateScreen();
}

char LinuxIO::getch()
{
	char x;
	//std::cin>>x;
	std::cin.get(x);
	return x;
}

void LinuxIO::putint(int x)
{
	int length = log10(x);
	char *buff = new char[length + 1];
	sprintf(buff, "%d", x);	
	cursorTestWrap(length);
	for(int i = 0; i < length; ++i) {
		virtualScreen[cursor_y][cursor_x++] = buff[i];	
	}
	delete[] buff;
	this->updateScreen();
}

int LinuxIO::getint()
{
	int x;
	std::cin>>x;
	return x;
}

void LinuxIO::clear()
{
	std::string templateRow = this->getTemplateEmptyString();

	this->virtualScreen = std::vector<std::string>(screen_height,"");
	for(unsigned int i = 0; i < virtualScreen.size(); ++i) {
		this->virtualScreen[i] = templateRow;
	}
	
	this->cursor_x = 0;
	this->cursor_y = 0;
	this->updateScreen();
}

std::string LinuxIO::getstr()
{
	std::string x;
	std::cin>>x;
	return x;
}

void LinuxIO::putstr(std::string str)
{
	std::vector<std::string> fstr = string::explode(str,'\n');
	for(int j = 0; j < fstr.size(); ++j) {
		this->cursorTestWrap(fstr[j].size());
		for(int i = 0; i < fstr[j].size(); ++i) {
			virtualScreen[cursor_y][cursor_x++] = fstr[j][i];
			if(cursor_x >= screen_width) {
				cursor_x = 0;
				cursor_y++;
				this->cursorTestWrap(0);
			}
		}
		if( j != fstr.size() - 1 ) {
			cursor_x = 0;
			cursor_y++;
		}
	}
	this->updateScreen();
}

void LinuxIO::updateScreen() 
{
	system("clear");
	for(unsigned int i = 0; i < screen_height; ++i) {
		std::cout<<virtualScreen[i]<<"\n";
	}
}

void LinuxIO::cursorTestWrap(unsigned int addLength)
{
	if(this->cursor_x + addLength >= screen_width) {
		this->cursor_x = 0;
		this->cursor_y++;
	}
	if(this->cursor_y >= screen_height) {
		for(int i = 0; i < screen_height - 1; ++i) {
			virtualScreen[i] = virtualScreen[i+1];
		}
		virtualScreen[screen_height - 1] = getTemplateEmptyString();
	}
}

std::string LinuxIO::getTemplateEmptyString()
{
	std::string templateRow = "";
	for(unsigned int i = 0; i < screen_width; ++i) {
		templateRow += EMPTY_CHAR;
	}
	return templateRow;
}

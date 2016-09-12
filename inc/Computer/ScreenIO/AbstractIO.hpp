#ifndef ABSTRACTIO_HPP
#define ABSTRACTIO_HPP

#include <string>

class AbstractIO
{
public:
	AbstractIO(){};
	virtual ~AbstractIO(){};

	//for use by virtual machine
	virtual void putch(char x) = 0;
	virtual char getch() = 0;

	virtual void putint(int x) = 0;
	virtual int getint() = 0;

	//for use by operating system
	virtual void clear() = 0;
	virtual std::string getstr() = 0;
	virtual void putstr(std::string str) = 0;

private:
};

#endif //ABSTRACTIO_HPP

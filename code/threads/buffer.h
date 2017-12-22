#ifndef BUFFER_H
#define BUFFER_H

#include "variable.h"

class buffer
{
	int ara[20];
	int currentIndex;
public:
	buffer();
	~buffer();
	void add(int x,int id);
	void remove(int id);
	void wait();
};
#endif 

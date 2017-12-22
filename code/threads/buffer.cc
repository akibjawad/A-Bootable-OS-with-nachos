#include <stdio.h>
#include "variable.h"
#include "buffer.h"

buffer::buffer()
{
	printf("Constructor of buffer\n");
	currentIndex=-1;
}
buffer::~buffer()
{
	printf("Destructor of buffer\n");
}

void
buffer::wait()
{
	int x=10000;
	while(x)
		x--;
}

void
buffer::add(int x,int id)
{
	wait();
	buffLock->Acquire();
	while (currentIndex>=19)
	{
		consumeLock->Broadcast(buffLock);
		proLock->Wait(buffLock);	
	}
	wait();
	currentIndex++;
	ara[currentIndex]=x;
	printf("Producer ID: %d Added: %d in %d\n",id,x,currentIndex);
	//consumeLock->Broadcast(buffLock);
	buffLock->Release();
}

void
buffer::remove(int id)
{
	wait();
	buffLock->Acquire();
	while (currentIndex<0)
	{
		proLock->Broadcast(buffLock);
		consumeLock->Wait(buffLock);
	}
	wait();
	int x=ara[currentIndex];
	printf("Consumer ID: %d Consumed: %d from %d\n",id,x,currentIndex);
	currentIndex--;
	//proLock->Signal(buffLock);
	buffLock->Release();
}

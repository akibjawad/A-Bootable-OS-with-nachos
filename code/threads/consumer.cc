#include "consumer.h"

consumer::consumer(int x,buffer* buff)
{
	id=x;
	b=buff;
	printf("consumer Constructor\n");
}

consumer::~consumer()
{
	printf("Consumer Destructor\n");
}

void
consumer::consume()
{
	int x=0;
	while(true)
	{
		//printf("------Consumer ID: %d------\n",id);
		b->remove(id);
		x++;
	}
}

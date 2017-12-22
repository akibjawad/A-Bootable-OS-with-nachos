#include "producer.h"

producer::producer(int x,buffer* buff)
{
	id=x;
	b=buff;
	printf("producer Constructor\n");
}

producer::~producer()
{
	printf("Producer Destructor\n");
}

void
producer::produce()
{
	int i=0;
	while(true)
	{
		//printf("------Producer ID: %d------\n",id);
		b->add(i,id);
		i++;
	}
}

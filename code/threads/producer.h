#include "buffer.h"

class producer
{
	int id;
	buffer* b;
public:
	producer(int id,buffer* buff);
	~producer();
	void produce();
	
};
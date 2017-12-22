#include "buffer.h"

class consumer
{
	int id;
	buffer* b;
public:
	consumer(int id,buffer* buff);
	~consumer();
	void consume();
	
};
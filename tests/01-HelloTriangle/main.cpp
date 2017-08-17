#include "graphics\Context.h"
#include <iostream>
int main()
{
	Context context;
	context.init();

	context.createCustomCursor();

	while (context.step())
	{
		//std::cout << context.getKey('K') << std::endl; 
		std::cout << context.getTime() << std::endl;
		
	}
	context.term();
	return 0;
}
#include "Header.h"

int main(void)
{
	srand(time(NULL));
	int status = -1;

	do
	{
		status = game();
	} while (status != 0);
	
	printf("Thanks for playing, go discover your own inspirations!");
}

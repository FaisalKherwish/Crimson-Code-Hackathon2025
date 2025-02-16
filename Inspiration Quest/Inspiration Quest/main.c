#include "Header.h"

int main(void)
{
	srand(time(NULL));
	int status = -1;
	double quota = 100;

	printMenu();

	do
	{
		status = game((int)quota);
		quota *= 1.2;
	} while (status != 0);
	
	printf("Thanks for playing, go discover your own inspirations!");
}

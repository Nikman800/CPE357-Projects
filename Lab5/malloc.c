#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	void* ptr = malloc(10000000);
	if (ptr == NULL)
	{
		printf("failed to malloc\n");
		return 0;
	}
	printf("malloc success\n");
	free(ptr);
	return 0;
	
}

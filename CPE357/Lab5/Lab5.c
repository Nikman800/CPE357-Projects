#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <time.h> 
#define BUFSIZE 1

int main()
{
	double time_spent = 0.0;

	
	int n, fd;
	char buf[2050];
	fd = open("/usr/lib/locale/locale-archive", O_RDONLY);
	if (fd == -1)
	{
		printf("file not found\n");
		return 0;
	}

	clock_t begin = clock();

	while(read(fd, buf, BUFSIZE) != 0)
	{
		/*printf("%s\n", buf);*/
	}

	clock_t end = clock();
	close(fd);
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time is %f seconds", time_spent);
	
	
}

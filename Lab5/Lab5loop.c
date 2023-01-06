#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <time.h> 
#define BUFSIZE 1

int fopenSingle(int bytesToRead) {
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

	while (read(fd, buf, bytesToRead) != 0)
	{
		/*printf("%s\n", buf);*/
	}

	clock_t end = clock();
	close(fd);
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time for %d bytes is %f seconds", bytesToRead, time_spent);
}


int main()
{
	int i = 1;
	while (i < 2049)
	{
		if (i == 4 || i == 8)
		{
			continue;
		}
		
		fopenSingle(i);
		i = i * 2;
	}
}
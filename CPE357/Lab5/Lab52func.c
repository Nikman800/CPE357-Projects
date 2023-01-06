#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <time.h> 
#define BUFSIZE 1

int fopenSingle(int bytesToRead, char * fpath) {
	double time_spent = 0.0;

	int i = 0;
	int n;
	FILE* fd;
	char buf[2050];
	printf("Running fopenSingle for %d", bytesToRead);
	fd = fopen(fpath, "r");
	if (fd == NULL)
	{
		printf("file not found\n");
		return 0;
	}

	clock_t begin = clock();

	while (fread(buf, sizeof(char),bytesToRead, fd) > 0)
	{
		/*printf("%s\n", buf);*/	
	}

	clock_t end = clock();
	fclose(fd);
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time for the function fopen by %d bytes is %f seconds\n", bytesToRead, time_spent);
}

int openSingle(int bytesToRead,char * fpath) {
	double time_spent = 0.0;


	int n, fd;
	char buf[2050];
	fd = open(fpath, O_RDONLY);
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
	printf("The elapsed time for the function open for %d bytes is %f seconds\n", bytesToRead, time_spent);
}


int main()
{
	int i = 1;
	/*char * fpath = "/home/nmandke/CPE357/Lab5/malloc.c";*/
	char * fpath = "/usr/lib/locale/locale-archive";
	while (i < 2049)
	{
		printf("---------------------------\n");
		if (i == 4 || i == 8)
		{
			i = i * 2;
			continue;
		}
		printf("printing openSingle %d\n", i);
		openSingle(i,fpath);
		printf("printing fopenSingle %d\n", i);
		fopenSingle(i,fpath);
		i = i * 2;
	}
}

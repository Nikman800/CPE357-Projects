#define _POSIX_SOURCE
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <time.h> 
#include <errno.h>



int get_child_max()
{
    errno = 0;
    int value = sysconf(_SC_CHILD_MAX);
    if (value < 0)
    {
        printf("error number for get_child_max: %d\n", errno);
    }
        
    return value;
}
int get_open_max()
{
    errno = 0;
    int value = sysconf(_SC_OPEN_MAX);
    if (value < 0)
    {
        printf("error number for get_open_max: %d\n", errno);
    }

    return value;
}
int get_page_size()
{
    errno = 0;
    int value = sysconf(_SC_PAGE_SIZE);
    if (value < 0)
    {
        printf("error number for get_page_size: %d\n", errno);
    }

    return value;
}

int main()
{
    printf("get_child max = %d\n", get_child_max);
    printf("get_open max = %d\n", get_open_max);
    printf("get_page size = %d\n", get_page_size);
}
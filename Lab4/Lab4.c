#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]) 
{
        int i;

        for (i=1; i<argc; i++) {
                struct stat sfile;

                if(stat(argv[i], &sfile)==-1){
                        printf("Error Occurred\n");
                }

                printf("File: '%s'\n", argv[i]);

                printf("Type: ");
                switch (sfile.st_mode & S_IFMT) {
                        case S_IFBLK:  printf("block device\n");        				break;
                        case S_IFCHR:  printf("character device\n");    				break;   
                        case S_IFDIR:  printf("directory\n");           				break;   
                        case S_IFIFO:  printf("FIFO/pipe\n");           				break;   
                        case S_IFLNK:  printf("symlink\n");             				break;    
                        case S_IFREG:  printf("regular file\n");        				break;    
                }

                printf("Size: %ld\n", sfile.st_size);
                printf("Inode: %ju\n", (uintmax_t) sfile.st_ino);
                printf("Links: %ju\n", (uintmax_t) sfile.st_nlink);

                printf("Access:");
                switch (sfile.st_mode & S_IFMT) {
                        case S_IFBLK:  printf("b");        break;
                        case S_IFCHR:  printf("c");        break;
                        case S_IFDIR:  printf("d");        break;
                        case S_IFIFO:  printf("p");        break;
                        case S_IFLNK:  printf("l");        break;
                        case S_IFREG:  printf("-");        break;
                }

                printf((sfile.st_mode & S_IRUSR)? "r":"-");
                printf((sfile.st_mode & S_IWUSR)? "w":"-");
                printf((sfile.st_mode & S_IXUSR)? "x":"-");
                printf((sfile.st_mode & S_IRGRP)? "r":"-");
                printf((sfile.st_mode & S_IWGRP)? "w":"-");
                printf((sfile.st_mode & S_IXGRP)? "x":"-");
                printf((sfile.st_mode & S_IROTH)? "r":"-");
                printf((sfile.st_mode & S_IWOTH)? "w":"-");
                printf((sfile.st_mode & S_IXOTH)? "x":"-");
                printf("\n");

        }

        return 0; 
}
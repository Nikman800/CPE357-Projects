#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <stdbool.h>

int printfile(char *filename, bool longer, bool hidden, struct stat sfile, int depth )
{  
   int d = depth;

   if(filename[0]=='.' && hidden == false)
   {
      return 0;
   }

   while( d-- > 0 )
   {
      printf("|-- ");
   }
   
   if (longer == true)
   {
      printf("[");
      
      printf((S_ISDIR(sfile.st_mode)) ? "d" : "-");
      printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
      printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
      printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
      printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
      printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
      printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
      printf((sfile.st_mode & S_IROTH) ? "r" : "-");
      printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
      printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
      printf("]");

      printf(" %s\n", filename);
      printf("\n");
   }
   else
   {
      printf("%s\n", filename);
   }
   return 0;
}

int printDirectory(char *dirname, bool longer, bool hidden, int depth)
{
    int i = 0;
    int n = 0;
    char fullPath[PATH_MAX];
    struct dirent **namelist;
    struct stat sfile;
    
    n = scandir(dirname, &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        return -1;
    }
    while (i < n) {
        if (i > 1){
            sprintf(fullPath, "%s/%s", dirname, namelist[i]->d_name);
             
            if (stat(fullPath, &sfile) == -1) {
                perror("Error: ");
            }
            printfile(namelist[i]->d_name, longer, hidden, sfile,depth+1);
            if (S_ISDIR(sfile.st_mode))
            {
               printDirectory(fullPath,longer,hidden, depth+1);
            }                                 
        }
        free(namelist[i]);
	    i++;
    }
    free(namelist);
    return 0;
}

int main(int argc, char * argv[])
{
   struct stat sfile;    
   /*int n;*/
   /*int i = 0;*/
   int depth = 0;
   int j;
   bool longer = false;
   bool hidden = false;

   for (j = 1;j < argc; j++)
   {
      
      if (argv[1][0] == '-' && j == 1)
      {
         if (argv[1][1] == 'l' || argv[1][2] == 'l')
         {
               longer = true;

         }
         if (argv[1][1] == 'a' || argv[1][2] == 'a')
         {
               hidden = true;
         }
         continue;
      }

      if (stat(argv[j], &sfile) == -1) {
         perror("Error Occurred\n");
      }

      printfile(argv[j],longer, hidden, sfile, depth);

      if ( S_ISDIR(sfile.st_mode) ) 
      {
         printDirectory(argv[j],longer,hidden, depth);
      }
      
   }
   
   exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> 
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sysmacros.h>
#include <linux/limits.h>

int IsRegFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int IsDirectory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int DoExec( int argLen, char* argList[], char* fullPath ){

    int currentInt = 0;
    int i;
    int pid1;
    
    for(i = 0; i < argLen; i++){
        if( strcmp( argList[i], "{}") == 0 ){
            currentInt = i;
            argList[i] = fullPath;
        }
        /* printf("-- %s\n", argList[i]);*/
    }
    
    pid1 = fork();

    if (pid1 == -1){
        perror("can't fork: ");
        exit(EXIT_FAILURE);
    }
    else if (pid1 > 0) 
    { 
        /*parent process 
        //printf("current process, pid1 = %u\n", getpid()); 

        //printf("parent waiting for children to exit \n");*/

        wait(NULL);
        argList[currentInt] = "{}";

    }
    else
    {        
        /*printf("first child process, pid = %u\n",getpid());                 

        // the execvp() only return if error occurred. The return value is -1*/
        execvp(argList[0], argList);

        /* The program should not reach here if execv is successful*/
        perror("something went wrong in execv:");             
    }
    return 0;
}

int ProcessFile( int argLen, bool isName, char* fullPath, char* nameFtr, bool isPrint, bool isExec, char* argList[] ){
    bool filterMatch = false;
    if(isName){
        char* p = strstr( fullPath, nameFtr );
        if( p ){
            filterMatch = true;
        } 
        else{
            filterMatch = false;
        }       
    }
    else{
        filterMatch = true;
    }

    if( filterMatch ){
        if( isPrint){
            printf( "- %s\n", fullPath);
        }
        else if(isExec){
            DoExec( argLen, argList, fullPath);
        }
    }
    return 0;
}

int ProcessDirectory( int argLen, bool isName, char* findPath, char* nameFtr, bool isPrint, bool isExec, char* argList[] ){
    struct dirent *d;
    DIR *dr;
    char fullPath[PATH_MAX];

    dr = opendir(findPath);
    if(dr!=NULL)
    {
        printf("D:=%s\n", findPath);
        
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            if( (strcmp( d->d_name, ".") == 0 ) || (strcmp( d->d_name, "..") == 0 ) ){
                continue;
            }
            sprintf(fullPath, "%s/%s", findPath, d->d_name);
            
            if( IsRegFile(fullPath)){
                ProcessFile( argLen, isName, fullPath, nameFtr, isPrint, isExec, argList);
            }
            else{
                ProcessDirectory( argLen, isName, fullPath, nameFtr, isPrint, isExec, argList);
            }

        }
        closedir(dr);
    }
    else{
        printf("\nError occurred while opening the current directory!");
    }
    return 0;
}

int main( int argc, char* argv[]){
    bool isName = false;
    bool isExec = false;
    bool isPrint = false;
    int argLen = 0;

    char* findPath = NULL;

    char* nameFtr = NULL;
    /*char* execCmd = NULL;*/

    /*char* arglist[argc];*/
    char* arglist[50];
    int i;
    int j;

    /* Parse the input*/
    for(i = 0; i < argc; i++) {
        /*printf( "parm:%d=%s\n", i, argv[i] );*/

        if( i == 1){
            findPath = argv[i];
            continue;
        }

        if( strcmp( argv[i], "-name") == 0 ){
            isName = true;
            nameFtr = argv[i+1];
            printf("isName==true: filter=%s\n", nameFtr);
            continue;
        }

         if( strcmp( argv[i], "-print") == 0 ){
            isPrint = true;
            printf("ïsPrint=true\n");
            continue;
        }

        if( strcmp( argv[i], "-exec") == 0){
            isExec = true;
            j = 0;
            argLen = argc - i -1;
           
             
            while( j < argLen)
            {
                arglist[j] = argv[i+j+1]; 
                printf("argument: %d for exec: %s\n", j, arglist[j]);
                j++;
            }
            arglist[j] = NULL;

            i+=j;
        }
    }

    /* input was a regular file*/
    if( IsRegFile(findPath) ){
        ProcessFile(argLen, isName, findPath, nameFtr, isPrint, isExec, arglist);
    }
    else{
        /* input is directory*/
        ProcessDirectory(argLen, isName, findPath, nameFtr, isPrint, isExec, arglist);
    }
    return 0;
}
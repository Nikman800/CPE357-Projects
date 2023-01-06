#include <stdio.h>
/*#include <conio.h>*/
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 150
#define MARKER -1

typedef enum depType {
	Rule,
	File,
	Both,
    Error,
} DepType;

/*struct for linkedlist node*/
typedef struct actionListNode {
    char* cmd;            
    struct actionListNode* next;
} ActionListNode;

/*struct for linkedlist node*/
typedef struct depListNode {
    char* dependency;  
	DepType depType;          
    struct depListNode* next;
} DepListNode;

typedef struct targetListNode {
	char* target;
	ActionListNode* actions;
	DepListNode* dependencies; 
	struct targetListNode* next;
} TargetListNode;

char* AllocString( char* s ){
    if( s == NULL ) return NULL;
    int t = strlen(s)+1;

    char* c = (char*)malloc( t );
    c[t] = '\0';

    return strcpy( c, s);
}

void trimWhitespace(char *s)
{
	int i,j;
    if( s == NULL) return;

	for(i=0; s[i]==' ' || s[i]=='\t' || s[i]=='\n'; i++);
 
	for(j=0; s[i]; i++){
		s[j++]=s[i];
	}

	s[j]='\0';

	for(i=0; s[i]!='\0'; i++){
		if(s[i] != ' ' && s[i] != '\t'  && s[i] != '\n')
				j=i;
	}

	s[j+1]='\0'; 
}
	
/* return linked list of actions*/
ActionListNode* getActions(char* target) {

}

/* return dependencyType*/
DepType getDependencyType(char* token) {
    char* tk = NULL;
    char* tk1 = NULL;
    char* rest = NULL;
    DepType dpType = Error;

    if( token == NULL ) 
        return Error;

    rest = token;
  
    tk = strtok_r( rest, ".", &rest);
    trimWhitespace(tk);

    tk1 = strtok_r( rest, ".", &rest);
    trimWhitespace(tk1);

   

    if( tk1 == NULL ){
        dpType = Rule;
        printf( "DepType: %s \n", "Rule");	
    }
        
    else if( strcmp( tk1,"o" ) == 0 ){
        dpType = Both;
        printf( "DepType: %s \n", "Both");	
    }
        
    else{
        dpType = File;
        printf( "DepType: %s \n", "File");	
    }
        
     return dpType;
}

/*returns true if updated*/
bool isDependencyUpdated(char* dependency, char* target) {

}

void AddDependencyListNodeToEnd( TargetListNode* trNode, DepListNode* dpNode ){
    if( trNode == NULL) 
        return;

    if( dpNode == NULL )
        return;

    if( trNode->dependencies == NULL ){
        trNode->dependencies = dpNode;
    }
    else {
        DepListNode* cur = trNode->dependencies;

        while( cur->next != NULL ){
            cur = cur->next;
        }

        cur->next = dpNode;
    }        
}

void AddDependencies( TargetListNode* trNode, char* token ){
    char* tk = NULL;
    char* rest = token;

    if( token == NULL ) return;

    tk = strtok_r( rest, " ", &rest);
    trimWhitespace(tk);
    printf( "dep: %s\n", tk);

    while( tk != NULL ){
        DepListNode* c = (DepListNode*)malloc( sizeof(DepListNode));
        c->next = NULL;
        c->dependency = AllocString(tk);
        c->depType = getDependencyType( tk);
        AddDependencyListNodeToEnd( trNode, c);     

        tk = strtok_r( rest, " ", &rest);
        trimWhitespace(tk);
        printf( "---: %s\n", tk);   
    }
    /* to put breakpoint*/
    tk = NULL;
}

void AddActionListNodeToEnd( TargetListNode* trNode, ActionListNode* acNode ){
    if( trNode == NULL) 
        return;

    if( acNode == NULL )
        return;

    if( trNode->actions == NULL ){
        trNode->actions = acNode;
    }
    else {
        ActionListNode* cur = trNode->actions;

        while( cur->next != NULL ){
            cur = cur->next;
        }

        cur->next = acNode;
    }        
}

void AddAction( TargetListNode* trNode, char* token ){
    
    if( token == NULL ) return;
    printf( "%s\n", token);

    ActionListNode* c = (ActionListNode*)malloc( sizeof(ActionListNode));
    c->next = NULL;
    c->cmd = AllocString(token);
    AddActionListNodeToEnd( trNode, c);   
}

TargetListNode* AddTargetListNodeToEnd( TargetListNode** trRoot, char* token, char* token1){

    /*TargetListNode* c = trRoot;*/

    TargetListNode* cur = (TargetListNode*)malloc( sizeof(TargetListNode));
    cur->next = NULL;
    cur->target = AllocString( token);
    cur->dependencies = NULL;
    cur->actions = NULL;
    AddDependencies( cur, token1 );

    if( *trRoot == NULL ){
        *trRoot = cur;
    }
    else {
        TargetListNode* cc = *trRoot;

        while( cc->next != NULL ){
            cc = cc->next;
        }

        cc->next = cur;
    }    

    return cur;
}

/*char* strsep(char** stringp, const char* delim) {

  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}*/

/* debug support*/
void printLine( char* line) {
	/* Print each line */
	printf("printLine: %s",  line);        
	/* Add a trailing newline to lines that don't already have one */
	if (line[strlen(line) - 1] != '\n')
		printf("\n");
}

/* reads Makefile
// target, default is empty:  runs on first target else on target specified
// returns zero for success, returns negative int for errors, 
// also returns the root node of dependency tree.*/ 
int parseMakefile(FILE* fp, char* target, TargetListNode* trRoot ) {

	char line[MAXLEN] = {0};
	char* token = NULL;
    char* token1 = NULL;
    char* rest = NULL;

    bool forTarget = false;
    TargetListNode* cur = NULL;

    while (fgets(line, MAXLEN, fp)) {
        token = NULL;
        token1 = NULL;

        printLine(line);

		if( strlen(line) < 2 ) {
            forTarget = false;
            cur = NULL;
            continue;
        }
        rest = line;

        if( forTarget ){
            token = strtok_r(rest, "\t\n", &rest);
            if( token == NULL ) {
                token1 = strtok_r(rest, "\t", &rest);
                if( token1 == NULL ) {
                    cur = NULL;
                    forTarget = false;
                }
            }   
            trimWhitespace(token);
            trimWhitespace(token1); 
            AddAction(cur, token);                  
        }
        else{
            token = strtok_r(rest, ":", &rest);
            if( token != NULL ) {
                trimWhitespace(token);
                token1 = strtok_r(rest, ":", &rest);
                trimWhitespace(token1);

                cur = AddTargetListNodeToEnd( &trRoot, token, token1);
                forTarget = true;                
            }            
        }

        printf( "++: token = %s, token1 = %s\n", token, token1);		
    }

}
	
/* run the actions*/
int runActions( char* action){
    printf("executing -%s\n", action);
}


/* builds dependency tree
// zero for success, negative for failiure*/
int buildDependency(TargetListNode* tarRoot, char* dep){
    /* find target*/
    char* tg = NULL;
    TargetListNode* cTar = NULL;
    DepListNode* cDep = NULL;
    ActionListNode* cAct = NULL;
    bool executeActions = false;

    if( tarRoot == NULL) 
        return -1;

    if( dep == NULL ){
        tg = tarRoot->target;
        cTar = tarRoot;
    }
    else {
        cTar = tarRoot;
        while( cTar != NULL ) {
            if( strcmp(cTar->target, dep ) == 0 ) {
                break;
            }
            cTar = cTar->next;
        }

        /* not found is not good*/
        if( cTar == NULL){
            return -2;
        }        
    }

    cDep = cTar->dependencies;
    while( cDep != NULL){
        if( cDep->depType == Both ){      
            executeActions = true;      
            buildDependency( tarRoot, cDep->dependency);
        }
        else if( cDep->depType == File ){                  
            executeActions = isDependencyUpdated( cTar->target, cDep->dependency );              
        }
         else if( cDep->depType == Rule ){                  
            executeActions = true;           
        }
    }
    if( executeActions){
        /* Execute all actions*/
        printf("making: %s\n", cTar->target);

        cAct = cTar->actions;
        while( cAct != NULL) {
            runActions(cAct->cmd);
            cAct = cAct->next;
        }

        printf("make complete: %s\n", cTar->target);
    }
}

void doCleanupActions( ActionListNode* node ){
	while( node != NULL) {
		free( node->cmd);
		node = node->next;
	}
}

void doCleanupDependencies( DepListNode* node) {
	while( node != NULL) {
		free( node->dependency);
		node = node->next;
	}
}

/* cleans up File* and memory allocations*/
void doCleanup(FILE* fp, TargetListNode* tarNode ) {
	if( fp != NULL ) {
		fclose(fp );
	}

	while( tarNode != NULL){
		doCleanupActions( tarNode->actions);
		doCleanupDependencies( tarNode->dependencies);
		free(tarNode->target);
		tarNode = tarNode->next;
	}	
}

int main(int argc, char *argv[]) {

    char* target = NULL;
    char* makeFile = "Smakefile";
    /*char* makeFile = "C:\\Users\\nikma\\Google Drive\\School\\Calpoly Year 2\\Spring Quarter\\CPE 357\\Projects\\smake\\smake\\workdiv\\Smakefile";*/
	FILE* fp = NULL;

	TargetListNode* tarRoot = NULL;
	DepListNode* depRoot = NULL;	
	
	/* Open makefile for reading*/
	fp = fopen(makeFile, "r");
    if (fp == NULL)  {
        printf("Could not open %s", makeFile );		
        return -1;
    }

	/* read target from make file and build dependency tree*/
	if (parseMakefile(fp, target, tarRoot) < 0 ) {
		/*doCleanup( fp, tarRoot);*/
		return -2;
	}

    printf(" ------- Tree Build -------- \n");
    buildDependency(tarRoot, target);

    printf(" ------- Tree Executed -------- \n");

	fclose(fp);	
}

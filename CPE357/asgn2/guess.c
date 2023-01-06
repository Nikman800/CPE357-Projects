#include <stdio.h>
/*#include <conio.h>*/
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*#pragma warning(disable : 4996)*/

#define MAXLEN 99
#define MARKER -1

/*struct for node*/
struct node {
    char *value;            /*all void* types replaced by char**/ 
    struct node *pLeft;
    struct node *pRight;
};

/*use typedef to make calling the compare function easier */
typedef int (*Compare)(const char *, const char *);
typedef struct node node;

/* Create a new node */
node* createNode( char* key )
{
    node* newNode = ( node*) malloc( sizeof(  node ) );
        newNode->value = malloc( strlen (key) +1 );     /* memory for key */
        strcpy (newNode->value, key);                   /* copy the key */
        newNode->pLeft = NULL;
        newNode->pRight = NULL;
    return newNode;    
}


/*inserts elements into the tree*/
void insert(char* key,  node** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = createNode( key);
    } else {
        res = cmp (key, (*leaf)->value);
        if( res < 0)
            insert( key, &(*leaf)->pLeft, cmp);
        else if( res > 0)
            insert( key, &(*leaf)->pRight, cmp);
        else                                            /* key already exists*/
            printf ("Key '%s' already in tree\n", key);
    }
}


/*char* input(void)
{
    static char line[MAXLEN+1];        //where to place key 
    printf("Please enter a string : ");
    fgets( line, sizeof line, stdin );
    return ( strtok(line, "\n" ));     //remove trailing newline 
}*/

/*recursive function to print out the tree preorder */
void pre_order( node *root)
{
    if( root != NULL ) {
        printf("   %s\n", root->value);     /* string type */
        pre_order(root->pLeft);        
        pre_order(root->pRight);
    }
}

/* Free up all allocated memoryand tree */
void deleteTree( node* n)
{
    if( n->pLeft == NULL && n->pRight == NULL )
    {
        free( n->value);
        free( n);
    }
    deleteTree(n->pLeft);
    deleteTree(n->pRight);
}

/* Get height of current node */
int getHeight( node* n )
{
    int leftHeight = NULL;
    int rightHeight = NULL;

    if (n == NULL)
        return 0;

    leftHeight = getHeight(n->pLeft); /*moved to the top of function*/
    rightHeight = getHeight(n->pRight);

    

    return ( (leftHeight > rightHeight)? leftHeight : rightHeight ) + 1;
}

/* This function stores a tree in a file pointed by fp */
void serialize(node* root, FILE* fp)
{
    /* If current node is NULL, store marker */
    if (root == NULL)
    {
        fprintf(fp, "%d\n", MARKER);
        return;
    }

    /* Else, store current nodeand recur for its children*/
    fprintf(fp, "%ld\n", strlen(root->value)); /*Attempting to typecast to int to bypass errors(changing to ld instead of d)*/
    fprintf(fp, "%s\n", root->value);
    serialize(root->pLeft, fp);
    serialize(root->pRight, fp);
}


int callSerialize( char* fileName, node* root )
{
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return -1;
    }

    serialize( root, fp);

    fclose( fp);
    return 0;

}


/* This function constructs a tree from a file pointed by 'fp'*/
void deSerialize(node** root, FILE* fp)
{
    /* Read next item from file.If there are no more items or next
    // item is marker, then return*/
    int val;
    /*char temp;*/
    char* stringVal = NULL; /*declaration moved up here*/
    node* n = NULL; /*declaration moved up here*/

    if (!fscanf(fp, "%d", &val))
        return;

    /*fscanf("%c", &temp); // temp statement to clear buffer*/

    if (val == MARKER)
        return;

    stringVal = (char*)malloc(val + 1);

    
    /* fscanf(fp, "%[^\n] ", stringVal);
    // fscanf(fp, "%[^\n] ", stringVal);*/
    fgets(stringVal, val + 1, fp);
    fgets(stringVal, val + 1, fp);

    /* Else create node with this itemand recur for children*/
    n = createNode(stringVal); /*declaration moved above*/
    *root = n;

    deSerialize(&((*root)->pLeft), fp);
    deSerialize(&((*root)->pRight), fp);

    free(stringVal);
}

int callDeserialize( char* fileName, node** root )
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        puts("Could not open file");
        return -1;
    }

    deSerialize(root, fp);
 
    fclose( fp);
    return 0;
}
 



/* User Guess*/
bool usersGuess()
{
    char startOfGuess;
    char str[MAXLEN];
    
    startOfGuess = getchar();
    /* throw away the rest*/
    fgets( str, MAXLEN, stdin );

    if(startOfGuess == 'y' || startOfGuess == 'Y' )
    {
        return true;
    }
    return false;
}

/* User Input*/
char* userInput()
{
    char* stringVal = (char*)malloc(MAXLEN+1 );
    fgets( stringVal, MAXLEN, stdin );
    return stringVal;
}
    
 
  

int main()
{
    
    /*TestSerialization();*/

    char* fileName = "qa.db";
        
    /* Case1: create new qa.db if it does not exist*/
    FILE *fp = fopen(fileName, "r");

    node* root = NULL; /*added from below to deal with errors*/

    node* root1 = NULL; /*added from below to deal with errors*/
    node* curNode = NULL;

    int curHeight = NULL; /*curHeight is now declared here*/

    char* animal = NULL; /*animal is now declared here*/

    char* question = NULL; /*question is now declared here*/

    char* curNodeValue = NULL; /*curNodeValue is now declared here*/

    char* object = NULL;

    if( fp == NULL)
    {
        /* Create first DB*/
        printf("qa.db: No such file or directory\n");
        printf("Unable to read database qa.db. Starting fresh.\n");
        printf("\nWhat is it (with article)?\n");
        object = userInput();
        root = createNode(object);
        /*root = createNode("a cat");*/
        

        /*node* root = createNode("Does it hunt mice?");
        root->pLeft = createNode("a dog");
        root->pRight = createNode("a cat");*/

        callSerialize( fileName, root);
        free(object);

        return 0;
    }

    /* Load the db to play the iteration of guessing game*/
    root1 = NULL; /*declaration put above*/
    curNode = NULL; /*declaration put above*/

    callDeserialize( fileName, &curNode);

    /* save root to finally save the update if needed*/
    root1 = curNode;
 
    /* printf("Inorder Traversal of the tree constructed from file:\n");
    // pre_order(curNode);*/

    curHeight = getHeight(curNode);  /*(curHeight was meant to be declared here)*/
    bool ifYesGuessed = false;

    while( curHeight > 1)
    {
        printf( "%s\n", curNode->value);
        ifYesGuessed = usersGuess();

        curNode = ifYesGuessed ? curNode->pRight : curNode->pLeft;
        curHeight--;
    }

    /* show results */
    printf( "Is it %s\n", curNode->value);
    ifYesGuessed = usersGuess();

    if( ifYesGuessed)
    {
        printf( "My, am I clever. :) Thanks for playing.\n");
        return 0;
    }
    
    printf( "How disappointing.\n");
    printf( "What is it ( with article )?\n");

    animal = userInput(); /*moving declaration up top*/

    printf( "What is a yes/no question that will distinguish %s from %s?\n", animal, curNode->value);
    question = userInput(); /*moving declaration up top*/

    printf( "What is the answer to the question for %s?\n", animal);
    bool isYesAnswer = false;

    isYesAnswer = usersGuess();
    curNodeValue = curNode->value; /*moving declaration up top*/

    curNode->value = question;
    if( isYesAnswer)
    {
        curNode->pRight = createNode( animal);
        curNode->pLeft = createNode(curNodeValue);
    }
    else{
        curNode->pRight = createNode(curNodeValue);        
        curNode->pLeft = createNode( animal);
    }

    /* Save the database */
    callSerialize( fileName, root1);

    printf( "I'll get it next time, I'm sure. Thanks for playing.\n");

    /* release all memory */
    deleteTree( root1);

    free(animal);
    free(question);
    free(curNodeValue);

    return 0;
        
}

#include <stdio.h>

typedef enum {
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    NO_VALID_PATH = 4,
    BAD_FILE_FORMAT = 5
} Error;

typedef struct n {
    int data;
    struct n **links;
} Node;

// initialisation des nodes de graph et liste chainées

typedef struct nde{
    int name;
    //array of node pointers
    struct nde **links;
}GNode;

typedef struct n1{
    int value;
    struct n1* next;
}NodeArray;

// Structure pour un élément de la file d'attente
typedef struct QueueNode {
    GNode *node;
    struct QueueNode *parent;
} QueueNode;

// Structure file 
typedef struct Queue {
    QueueNode **items;
    int front, rear, max_size;
} Queue;

// scans file and compares if it is mentioned in the #links
int* getNoLinks(FILE *file);

// compares routes size
int* sizeCompare(int** array);

// scans the graph by branching out on every links of the starting node
int** getPath(Node nde);

// counts the number of nodes mentionned in a file 
int getGraphSize(FILE *file);

// scans file ands gets start and end of path
int getStart(FILE *file);

// Trouve le dernier noeud
int getEnd(FILE *file);

// retourne un tableau de node contenant l’ensemble des nœuds du graphe
GNode** init_node( char *file);

// verifie si un noeud est dans une liste
int isInTab(GNode *table,GNode object);
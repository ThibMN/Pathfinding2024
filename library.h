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

// scans file and compares if it is mentioned in the #links
int* getNoLinks(FILE *file);

// compares routes size
int* sizeCompare(int** array);

// scans the graph by branching out on every links of the starting node
int** DepthScan(Node nde);

// counts the number of nodes mentionned in a file 
int getGraphSize(FILE *file);

// scans file ands gets start and end of path
int getStart(FILE *file);

// Trouve le dernier noeud
int getEnd(FILE *file);
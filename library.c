#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string.h>
#include <unistd.h>
#include "library.h"

// initialising graph nodes

typedef struct nde{
    int name;
    //array of node pointers
    struct nde **links;
}Nodes;

// scans file and compares if it is mentioned in the #links
int* getNoLinks(FILE *file);

// compares routes size
int* sizeCompare(int** array);

// scans the graph by branching out on every links of the starting node
int** DepthScan(Nodes nde);

int getStart(FILE *file){
    char buffer[256]; //Initialisation d'un buffer pour retourner la chaine de caractère voulue

    while (fgets(buffer, sizeof(buffer), file) != NULL){
        if (strcmp(buffer,"#start\n") == 0){
            if (fgets(buffer, sizeof(buffer), file) != NULL) { 
                return atoi(buffer);
            } else {
                return -1;
            }
        }
    }

    return -1;
}

int getEnd(FILE *file){
    char buffer[256]; //Initialisation d'un buffer pour retourner la chaine de caractère voulues

    while (fgets(buffer, sizeof(buffer), file) != NULL){
        if (strcmp(buffer,"#end\n") == 0){
            if (fgets(buffer, sizeof(buffer), file) != NULL) { 
                return atoi(buffer);
            } else {
                return -1;
            }
        }
    }

    return -1;
}

int getGraphSize(FILE *file){
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL){
        if (strcmp(buffer,"#links\n") == 0){
            if (fgets(buffer, sizeof(buffer), file) != NULL) { 
                int node_numbers = 1;
                for (int i = 0; buffer[i] != '\0';i++){
                    if (strcmp(&buffer[i], "-") == 0){
                        node_numbers++;
                    }
                }
                return node_numbers;
            } else {
                return 0;
            }
        }
    }

    return 0;
}
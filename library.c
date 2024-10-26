#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string.h>
#include <unistd.h>
#include "library.h"

#define MAX_NODES 100  // Limite du nombre de noeuds dans le fichier

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

// retourne un tableau de node contenant l’ensemble des nœuds du graphe
GNode** init_node( char *file){
    int **link=getLinks(file);
    GNode initialisedNode;
    GNode *nodeTable[];
    for (int i,i<strlen(link),i++){
        initialisedNode = GNode link[i][0];
        initialisedNode->links = realloc(initialisedNode->links,sizeof(GNode)*strlen(initialisedNode->links)+sizeof(GNode));
        initialisedNode->links[strlen(links)-1]= GNode link[i][0]
        if (isInTab(nodeTable,initialisedNode)==0){
            nodeIndex = strlen(nodeTable);
            nodeTable=realloc(nodeTable,sizeof(GNode)*strlen(nodeTable)+sizeof(GNode));
            nodeTable[nodeIndex]=initialisedNode;
            
        }

        initialisedNode = GNode link[i][1];
        initialisedNode->links = realloc(initialisedNode->links,sizeof(GNode)*strlen(initialisedNode->links)+sizeof(GNode));
        initialisedNode->links[strlen(links)-1]= GNode link[i][1]
        if (isInTab(nodeTable,initialisedNode)==0){
            nodeIndex = strlen(nodeTable);
            nodeTable=realloc(nodeTable,sizeof(GNode)*strlen(nodeTable)+sizeof(GNode));
            nodeTable[nodeIndex]=initialisedNode;
            
        }
    }
    free(linkList);
    return *nodeTable
}


// verifie si un noeud est dans une liste
int isInTab(GNode *table,GNode object){
    for(int i;i<strlen(table);i++){
        if (table[i]==object){
            return 1;
        }
    }
    return 0    
}

int* getLinks(FILE *file){
    char buffer[256]; //Initialisation d'un buffer pour retourner la chaine de caractère voulues
    int counter=1;
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        if (strcmp(buffer,"#links\n") == 0){
            while (fgets(buffer, sizeof(buffer), file) != NULL){
                int **linkList= realloc(linkList,counter*sizeof(int)*2);
                linkList[counter-1]=[buffer[0],buffer[2]];
                
                counter++;
            }
            return linkList;
        }
    }

    return -1;
}

// scans file and compares if it is mentioned in the #links
int* getNoLinks(FILE *file);

// compares routes size
int* sizeCompare(int** array);

// scans the graph by branching out on every links of the starting node
int** DepthScan(GNode nde);

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
    int nodes[MAX_NODES] = {0};
    int nodeCount = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strcmp(buffer, "#node\n") == 0) {
            if (fgets(buffer, sizeof(buffer), file) != NULL) {
                char *token = strtok(buffer, "-\n");

                while (token != NULL) {
                    int node = atoi(token);

                    if (node < MAX_NODES && nodes[node] == 0) {
                        nodes[node] = 1;
                        nodeCount++;
                    }
                    token = strtok(NULL, "-\n");
                }
                return nodeCount;
            } else {
                return 0;
            }
        }
    }

    return 0;
}
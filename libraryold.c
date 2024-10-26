#include <stdio.h>
#include <stdlib.h>
//#include <streambuf>
#include <string.h>
#include <unistd.h>
#include "library.h"

#define MAX_NODES 100  // Limite    du nombre de noeuds dans le fichiers

GNode** init_node(FILE *file) {
    int **link = getLinks(file);
    GNode *nodeTable = NULL;
    int nodeCount = 0;
    int linkCount = strlen(link); // Ajuster cette fonction en fonction du type de retour de getLinks

    for (int i = 0; i < linkCount; i++) {
        GNode initialisedNode;

        // Initialisation pour le premier noeud du lien
        initialisedNode.name = link[i][0];
        if (!isInTab(nodeTable, initialisedNode.name, nodeCount)) {
            nodeTable = realloc(nodeTable, sizeof(GNode) * (nodeCount + 1));
            if (nodeTable == NULL) {
                perror("Erreur de realloc");
                exit(EXIT_FAILURE);
            }
            nodeTable[nodeCount] = initialisedNode;
            nodeTable[nodeCount].links = NULL;
            nodeCount++;
        }

        // Initialisation pour le second noeud du lien
        initialisedNode.name = link[i][1];
        if (!isInTab(nodeTable, initialisedNode.name, nodeCount)) {
            nodeTable = realloc(nodeTable, sizeof(GNode) * (nodeCount + 1));
            if (nodeTable == NULL) {
                perror("Erreur de realloc");
                exit(EXIT_FAILURE);
            }
            nodeTable[nodeCount] = initialisedNode;
            nodeTable[nodeCount].links = NULL;
            nodeCount++;
        }
    }

    // Lecture des liens supplémentaires
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) && strcmp(buffer, "#links\n") != 0) {
        if (buffer[0] != '#' && !isInTab(nodeTable, buffer[0], nodeCount)) {
            GNode additionalNode;
            additionalNode.name = buffer[0];
            nodeTable = realloc(nodeTable, sizeof(GNode) * (nodeCount + 1));
            if (nodeTable == NULL) {
                perror("Erreur de realloc");
                exit(EXIT_FAILURE);
            }
            nodeTable[nodeCount] = additionalNode;
            nodeTable[nodeCount].links = NULL;
            nodeCount++;
        }
    }

    return nodeTable;
}

// scanne récursivement tout le graph
void depth_scan(GNode *node, int *visited, int **result, int *count) {
    // Si le nœud est déjà visité, on retourne
    if (visited[node->name]) {
        return;
    }

    // Marquer le nœud comme visité
    visited[node->name] = 1;

    // Ajouter le nœud au tableau résultat
    (*result)[*count] = node->name;
    (*count)++;

    // Parcourir les voisins de ce nœud
    for (int i = 0; node->links[i] != NULL; i++) {
        depth_scan(node->links[i], visited, result, count);
    }
}

// Fonction principale pour collecter tous les nœuds à partir d'un nœud donné
int* display_nodes(GNode *startNode) {
    // Créer un tableau pour suivre les nœuds visités
    int *visited = (int*)calloc(getGraphSize(file), sizeof(int));
    int *result = (int*)malloc(getGraphSize(file) * sizeof(int));
    int count = 0;

    // Appeler la fonction récursive pour obtenir tous les nœuds
    depth_scan(startNode, visited, &result, &count);

    // Libérer le tableau de visite
    free(visited);

    // Redimensionner le tableau résultat pour qu'il contienne uniquement les nœuds trouvés
    result = realloc(result, count * sizeof(int));
    for (int i;i<strlen(result);i++){
        printf("%d ",result[i]);
    }
    return result;
}


//retourne un pointeur vers le nœud recherché
GNode* get_node_by_id( GNode **nodes, int id ){
    for(int i;i<strlen(nodes);i++){
        if (nodes[i].name == id){
            GNode *nodePtr = &nodes[i];
            return nodePtr;
        }
    }
    return -1;
}

// verifie si un noeud est dans une liste
int isInTab(GNode *table,GNode object.name){
    for(int i;i<strlen(table);i++){
        if (table[i].name==object.name){
            return 1;
        }
    }
    return 0;
}

int* getLinks(FILE *file){
    char buffer[256]; //Initialisation d'un buffer pour retourner la chaine de caractère voulues
    int counter=1;
    while (fgets(buffer, sizeof(buffer), file) != NULL ){
        if (strcmp(buffer,"#links\n") == 0){
            while (fgets(buffer, sizeof(buffer), file) != NULL){
                if (fgets(buffer, sizeof(buffer), file) != NULL) { 
                    int **linkList= realloc(linkList,counter*sizeof(int)*2);
                    linkList[counter-1]=[buffer[0],buffer[2]];
                }
                counter++;
            }
            int **listResult =linkList;
            free(linkList);
            return listResult;
        }
    }

    return -1;
}

// compare entre la liste de noeuds connectée et la liste de tous les noeuds
GNode** get_unconnected_nodes(GNode **nodes, GNode *head ){
    int *connected_nodes = display_nodes(head);
    GNode **loneNodes;
    for(int i;i<strlen(nodes);  i++){
        if(isInTab(connected_nodes,nodes[i].name)==0){
            lone_nodes=realloc(lone_nodes,sizeof(Gnode)*(strlen(lone_nodes)+1));
            lone_nodes[strlen(lone_nodes)-1]=nodes[i];
        }
    }
    return lone_nodes;
}

// Fonction pour initialiser la file d'attente
Queue* createQueue(int size) {
    Queue *newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->items = (QueueNode**)malloc(size * sizeof(QueueNode*));
    newQueue->front = newQueue->rear = -1;
    newQueue->max_size = size;
    return newQueue;
}

// Vérifie si la file est vide
int isEmpty(Queue *queue) {
    return queue->front == -1;
}

// Enfile un élément dans la file
void enqueue(Queue *queue, GNode *node, QueueNode *parent) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->parent = parent;

    if (queue->rear == queue->max_size - 1) return;
    if (isEmpty(queue)) queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = newNode;
}

// Défile un élément
QueueNode* dequeue(Queue *queue) {
    if (isEmpty(queue)) return NULL;
    QueueNode *item = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) queue->front = queue->rear = -1;
    return item;
}

// Fonction pour libérer la file
void freeQueue(Queue *queue) {
    while (!isEmpty(queue)) free(dequeue(queue));
    free(queue->items);
    free(queue);
}

// Fonction pour trouver le chemin le plus court avec BFS
NodeArray* getPath(GNode *startNode, int target,) {
    int *visited = (int*)calloc(getGraphSize(file), sizeof(int));
    Queue *queue = createQueue(getGraphSize(file));
    enqueue(queue, startNode, NULL);

    QueueNode *targetNode = NULL;
    while (!isEmpty(queue)) {
        QueueNode *current = dequeue(queue);
        GNode *node = current->node;

        if (node->name == target) {
            targetNode = current;
            break;
        }

        visited[node->name] = 1;
        for (int i = 0; i < node->num_neighbors; i++) {
            GNode *neighbor = node->links[i];
            if (!visited[neighbor->name]) {
                enqueue(queue, neighbor, current);
                visited[neighbor->name] = 1;
            }
        }
    }

    // Construire le chemin à partir du nœud cible
    NodeArray *path = NULL;
    if (targetNode) {
        QueueNode *current = targetNode;
        while (current) {
            addPathNode(&path, current->node->name);
            current = current->parent;
        }
    }

    free(visited);
    freeQueue(queue);
    return path;
}

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
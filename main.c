#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string.h>
#include <unistd.h>
#include <"library.h">

int main(int a, char *filename[]){
    // Pointeur vers le fichier
    FILE* file;

    // Ouverture du fichier nodes qui contient le graphe
    file = fopen(filename[1],"r");

    // Teste si le fichier est bien ouvert
    if (file == NULL){
        printf("Erreur dans l'ouverture du fichier\n");
        return -1;
    }

    return 0;
}
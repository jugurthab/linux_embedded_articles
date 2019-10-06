#include "filemanager.h"

void getFileStats(const char* filePath){
    struct stat fileStat;
    int fileError = 0;
    
    fileError = stat(filePath, &fileStat);

    if(fileError < 0){
        perror("erreur fonction stat");
        return;
    }
    // Check if the provided file is a regular file
    if((fileStat.st_mode & S_IFMT) == S_IFREG)
        printf("Nom du Fichier %s => Taille : %ld bytes\n", filePath, fileStat.st_size);
    else
        printf("Le fichier n'est pas de type S_IFREG\n");
}

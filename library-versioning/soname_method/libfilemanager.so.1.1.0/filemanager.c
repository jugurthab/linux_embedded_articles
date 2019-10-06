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

void getFilesInFolder(const char* folderPath){
    DIR* folder = NULL;
    struct dirent* fileToRead = NULL;
    int fileCounter = 0;

    folder = opendir(folderPath); // open folder

    if (folder == NULL){
        perror("Fonction opendir");
        return;
    }
    
    while ((fileToRead = readdir(folder)) != NULL){
        fileCounter++;
        // display discovered files
        printf("%d - %s\n", fileCounter, fileToRead->d_name);
    }

    closedir(folder);
}

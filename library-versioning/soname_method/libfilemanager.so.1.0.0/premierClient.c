#include "filemanager.h"

int main(int argc, char *argv[]){
    
    if(argc <2){
        printf("Usage : ./%s <Nom_Fichier>\n", argv[0]);
        return 1;
    }
    // Get file statistics        
    getFileStats(argv[1]);

    return 0;
}


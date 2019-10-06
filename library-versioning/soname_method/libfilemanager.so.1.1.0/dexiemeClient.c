#include "filemanager.h"

int main(int argc, char *argv[]){
    
    if(argc <2){
        printf("Usage : %s <Nom_Dossier>\n", argv[0]);
        return 1;
    }
            
    getFilesInFolder(argv[1]);

    return 0;
}


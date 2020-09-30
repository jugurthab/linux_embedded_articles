#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/xattr.h>
#define MAX_ATTR_KEY_LENGTH 255 // Limitation imposée par le VFS.
#define MAX_ATTR_VALUE_LENGTH 50

void printUsage(){
	printf("Usage : $./attr FILENAME ATTR_KEY ATTR_VALUE\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
	char userKey[MAX_ATTR_KEY_LENGTH];
	char userValue[MAX_ATTR_VALUE_LENGTH];
	char retrievedValue[MAX_ATTR_VALUE_LENGTH];

	if(argc != 4)
		printUsage();
	
	// L'attribut sera sauvegardé dans le namespace "user".
	snprintf(userKey, MAX_ATTR_KEY_LENGTH,
			  "user.%s", argv[2]);
	snprintf(userValue, MAX_ATTR_VALUE_LENGTH,
			  argv[3]);	

	printf("User input extended attribute key = %s\n"
		"User input extended attribute value = %s\n",
		userKey, userValue);

	// Association des attributs étendus au fichier.
	if (setxattr(argv[1], userKey, userValue,
			strlen(userValue), 0) == -1)
		perror("setxattr");
	
	// Lecture des attributs étendus.
	if(getxattr(argv[1], userKey,
			     retrievedValue,
			     MAX_ATTR_VALUE_LENGTH) < 0){
		perror("getxattr");
		exit(EXIT_FAILURE);
	}

	printf("EA read from file : key %s = %s\n", userKey, retrievedValue);

	return EXIT_SUCCESS;
}


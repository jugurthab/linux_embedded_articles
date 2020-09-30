#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>
#include <fcntl.h>

#define MAX_CHARS_IN_ROW_INPUT_FILE 51
#define MAX_NUMBER_SCATTER_GATHER 3
#define CAESAR_SHIFT_KEY 3
#define XOR_ENCRYPTION_KEY "XknPBiwhKAeXzjhZRrYZWmUoPgpvunMeIUTQpVCXmhqvztnmQR"

/* Chiffrement de Caesar */
void applyCaesarCipher(char dataToEncrypt[]){
	for(int i = 0; i < MAX_CHARS_IN_ROW_INPUT_FILE - 1; i++)
		dataToEncrypt[i] += CAESAR_SHIFT_KEY;
}

/* Chiffrement XOR */
void applyXorCipher(char dataToEncrypt[]){
	for(int i = 0; i < MAX_CHARS_IN_ROW_INPUT_FILE - 1; i++)
		dataToEncrypt[i] ^= XOR_ENCRYPTION_KEY[i];
}

void loadFileContent(char noEnryptionBuf[],
					 char caesarEnryptionBuf[],
					 char xorEnryptionBuf[]){
	// Déclarer le nombre de scatter/gather.
	struct iovec iov[MAX_NUMBER_SCATTER_GATHER];
	ssize_t scatterGatherReturn;
	int fd;
	fd = open("data_input.txt", O_RDONLY);
	if(fd == -1){
		perror ("open");
		exit(EXIT_FAILURE);
	}
	/* configuration des structures iovec */
	iov[0].iov_base = noEnryptionBuf;
	iov[0].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE;
	iov[1].iov_base = caesarEnryptionBuf;
	iov[1].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE;
	iov[2].iov_base = xorEnryptionBuf;
	iov[2].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE;
	/* Lire le fichier avec 1 seul appel système */
	scatterGatherReturn = readv(fd, iov, MAX_NUMBER_SCATTER_GATHER);
	if (scatterGatherReturn == -1) {
		perror ("readv");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < MAX_NUMBER_SCATTER_GATHER; i++)
		printf ("%s\n", (char *) iov[i].iov_base);

	if (close (fd)) {
		perror ("close");
		exit(EXIT_FAILURE);
	}
}

void saveFileContent(char noEnryptionBuf[],
					 char caesarEnryptionBuf[],
					 char xorEnryptionBuf[]){
	struct iovec iov[MAX_NUMBER_SCATTER_GATHER];
	ssize_t scatterGatherReturn;
	int fd;
	fd = open("data_output.txt", O_WRONLY | O_CREAT | O_TRUNC,
								S_IWUSR | S_IRUSR | S_IWGRP |
								S_IRGRP | S_IROTH);

	if(fd == -1){
		perror ("open");
		exit(EXIT_FAILURE);
	}

	iov[0].iov_base = noEnryptionBuf;
	iov[0].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE+1;
	iov[1].iov_base = caesarEnryptionBuf;
	iov[1].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE+1;
	iov[2].iov_base = xorEnryptionBuf;
	iov[2].iov_len = MAX_CHARS_IN_ROW_INPUT_FILE+1;

	/* Ecriture du contenu avec 1 seul appel système */
	scatterGatherReturn = writev(fd, iov, MAX_NUMBER_SCATTER_GATHER);
	if (scatterGatherReturn == -1) {
		perror ("writev");
		exit(EXIT_FAILURE);
	}
	printf ("wrote %d bytes\n", scatterGatherReturn);
	if (close (fd)) {
		perror ("close");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){
	// Stocke la 1ère ligne du fichier.
	char noEnryptionBuf[MAX_CHARS_IN_ROW_INPUT_FILE+1];
	// Stocke la 2ème ligne du fichier.
	char caesarEnryptionBuf[MAX_CHARS_IN_ROW_INPUT_FILE+1];
	// Stocke la 3ème ligne du fichier.
	char xorEnryptionBuf[MAX_CHARS_IN_ROW_INPUT_FILE+1];

	
	memset(noEnryptionBuf, '\0', MAX_CHARS_IN_ROW_INPUT_FILE+1);
	memset(caesarEnryptionBuf, '\0', MAX_CHARS_IN_ROW_INPUT_FILE+1);
	memset(xorEnryptionBuf, '\0', MAX_CHARS_IN_ROW_INPUT_FILE+1);

	// Lecture du fichier et sauvegarde de chaque ligne dans un buffer.
	loadFileContent(noEnryptionBuf, caesarEnryptionBuf, xorEnryptionBuf);

	// Chiffrement de 2ème et 3ème ligne.
	applyCaesarCipher(caesarEnryptionBuf);
	applyXorCipher(xorEnryptionBuf);

	// Sauvegarde des données dans un autre fichier (data_output.txt).
	saveFileContent(noEnryptionBuf, caesarEnryptionBuf, xorEnryptionBuf);

	return EXIT_SUCCESS;
}


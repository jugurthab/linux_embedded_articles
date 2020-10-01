#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <aio.h>
#include <string.h>
#include <signal.h>

#define MAX_AIOCB_OPERATIONS 2 // Lecture + Ecriture.
#define MAX_USER_INPUT_STRING_LENGTH 50
#define FILENAME "aiocb.txt" // Fichier d'écriture.

struct aiocb cb[MAX_AIOCB_OPERATIONS];


char bufToWriteOut[MAX_USER_INPUT_STRING_LENGTH];
char bufToReadIn[MAX_USER_INPUT_STRING_LENGTH];

FILE * file;
volatile bool writeReadComplet = false;

void printUsage(){
	printf("Usage : $./aiocb INPUT_STRING\n");
	exit(EXIT_SUCCESS);
}

// Callback des opérations asynchrones lecture et écriture.
void aio_handler(int signal, siginfo_t *info, void*uap)
{
	int cbNumber = info->si_value.sival_int;
	if(cbNumber==0) { // Si l'écriture est achevée.
		printf("AIO wrote %s completed to file %s\n",
		       bufToWriteOut, FILENAME);
		aio_read(&cb[1]); // Lancer la lecture.
	}
	else{ // Si l'écriture est terminée.
		printf("AIO read %s from file %s\n",
		       bufToReadIn, FILENAME);
		fclose(file);
		writeReadComplet = true; // Arrêter le programme.
	}
}

int main(int argc, char *argv[]){
	struct sigaction action;

	if(argc != 2) {
		printUsage();
	}
	memset(bufToWriteOut, '\0', MAX_USER_INPUT_STRING_LENGTH);
	memset(bufToReadIn, '\0', MAX_USER_INPUT_STRING_LENGTH);

	// Récupérer la chaine de charactères utilisateur.
	snprintf(bufToWriteOut, MAX_USER_INPUT_STRING_LENGTH, argv[1]);
	file = fopen(FILENAME, "w+");

	// Configuration des IOs asynchrones.
	for(int i = 0; i < MAX_AIOCB_OPERATIONS; i++) {
		cb[i].aio_fildes = fileno(file);
		if(i==0) // Le cas d'une écriture
			cb[i].aio_buf = bufToWriteOut;
		else // Le cas d'une lecture
			cb[i].aio_buf = bufToReadIn;
		cb[i].aio_nbytes = MAX_USER_INPUT_STRING_LENGTH;
		action.sa_sigaction = aio_handler;
		action.sa_flags = SA_SIGINFO;
		sigemptyset(&action.sa_mask);
		cb[i].aio_sigevent.sigev_notify = SIGEV_SIGNAL;
		cb[i].aio_sigevent.sigev_signo = SIGIO;
		cb[i].aio_sigevent.sigev_value.sival_int = i;
	}

	sigaction(SIGIO, &action, NULL);

	aio_write(&cb[0]); // Lancer l'écriture

	// En production, la boucle doit être remplacée car le but
	// des IO asynchrones est de permettre au programme de continuer
	// son cycle de vie sans aucun bloquage.
	while(!writeReadComplet) {sleep(1);}

	return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>
#include <fcntl.h>

// Le nombre max d'événements inotify à récupérer en 1 seule lecture.
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(){
	int inotifyFd, currentDirectoryWatchId;
	char inotifyBufEvents[BUF_LEN];
	ssize_t nbReadEvents;
	char *eventRead;
	struct inotify_event *event;
	// inotify doit toujours être initialisé.
	inotifyFd = inotify_init();
	// Ajouter le dossier à liste des fichier à suivre	
	currentDirectoryWatchId = inotify_add_watch(inotifyFd,
				".", IN_ACCESS|IN_CLOSE_WRITE|IN_OPEN);
	printf("Current directory watch id %d\n", currentDirectoryWatchId);
	for (;;) {
		/* Récupérer les évenements inotify */
		nbReadEvents = read(inotifyFd, inotifyBufEvents, BUF_LEN);
		if (nbReadEvents == -1)
			printf("read");
		printf("%ld bytes read\n", (long) nbReadEvents);
		/* Parser et afficher chaque événement inotify */
		for (eventRead = inotifyBufEvents; eventRead < inotifyBufEvents + nbReadEvents; ) {
			event = (struct inotify_event *) eventRead;
			printf("watch id =%d; ", event->wd);
			if (event->mask & IN_ACCESS)
				printf("IN_ACCESS ");
			if (event->mask & IN_CLOSE_WRITE)
				printf("IN_CLOSE_WRITE ");
			if (event->mask & IN_OPEN)
				printf("IN_OPEN ");
			eventRead += sizeof(struct inotify_event) + event->len;
		}
	}

	return EXIT_SUCCESS;
}


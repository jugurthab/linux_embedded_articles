#include "contiki.h" // Il faut toujours inclure ce header

#include <stdio.h> // Pour utiser des printfs

// Création d'un block de contrôle de processus
PROCESS(display_hello_world, "display hello world");

// Lancer le processus dès le démarrage du capteur
AUTOSTART_PROCESSES(&display_hello_world);

// Prothread du processus (implémentation)
PROCESS_THREAD(display_hello_world, ev, data){
    PROCESS_BEGIN();

    printf("Hello world from Contiki-NG\n");

    PROCESS_END();
}

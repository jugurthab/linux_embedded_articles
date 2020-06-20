#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // inclure nice().
#include <errno.h>

int main(int argc, char *argv[]){
    int nice_value = -1;
    /*
    * nice altère la priorité dynamique d'un processus
    * à exécution temps partagés.
    * param : Nouvelle valeur de nice (0 pour récupérer
    *         la valeur en cours). 
    */
    nice_value = nice(0);

    printf ("--- Initial nice value %d ---\n", nice_value);

    errno = 0;
    // Incrémenter la valeur nice à 5 (baisser la priorité dynamique).
    nice_value = nice(5);
    
    /*
    * La vérification de errno est requise car nice = -1
    * représente aussi une valeur valide nice=[-20, 19].
    */
    if(nice_value == -1 && errno != 0){
        perror ("nice error");
    } else {
        printf ("--- New nice value is : %d --\n", nice_value);
    }
    return EXIT_SUCCESS;
}


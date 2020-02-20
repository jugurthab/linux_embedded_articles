#include "contiki.h"
#include "random.h" // Générateur de nombres pseudo-aléatoire

#include "sys/log.h" // Gestion de LOGS
#define LOG_MODULE "Test_timer" // Préfixe des logs (obligatoire)
#define LOG_LEVEL LOG_LEVEL_INFO // Niveau de criticité des LOG (obligatoire)

#define MAX_SOUND_INTENSITY 150
#define MIN_SOUND_INTENSITY 0

PROCESS(motor_rotation_sensing_process, "Motor rotation sensing process");
PROCESS(sound_sensing_process, "Sound sensing process");

/*
* AUTOSTART_PROCESSES lance les processus en paramètres après le démarrage
* de la carte
*/
AUTOSTART_PROCESSES(&sound_sensing_process, &motor_rotation_sensing_process);

static struct etimer etimer_timer_motor; // timer de type etimer
static struct ctimer ctimer_timer_sound; // timer de type ctimer

/*******************************************************
    Processus vérification de la rotation du moteur 
********************************************************/
// getMotorRorationStatus simule l'état de rotation d'un moteur 
unsigned short getMotorRorationStatus(){
    return (random_rand() & 1); // retourne 1 ou 0 (1 => moteur en rotation)
}

// Implémentation du processus motor_rotation_sensing_process
PROCESS_THREAD(motor_rotation_sensing_process, ev, data)
{
    PROCESS_BEGIN();
    LOG_INFO("------- Processus rotation moteur démarré ...\n");

    etimer_set(&etimer_timer_motor, 3 * CLOCK_SECOND);

    while(1)
    {
        // Libérer le processeur tant que le timer n'est pas expiré
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&etimer_timer_motor));
        LOG_INFO("L'état du moteur : %s\n", 
                getMotorRorationStatus()?"en rotation": "éteint");
        etimer_reset(&etimer_timer_motor); // réarmer le timer
    }
    PROCESS_END();
}

/*******************************************************
    Processus vérification du niveau sonore
********************************************************/
// getSoundIntensity simule la valeur du niveau sonore
void getSoundIntensityCallback(){
    int soundIntensity = random_rand() % (MAX_SOUND_INTENSITY + 1 - MIN_SOUND_INTENSITY) + MIN_SOUND_INTENSITY;
    LOG_INFO("Niveau sonore %d dB\n", soundIntensity);
    ctimer_reset(&ctimer_timer_sound);
}

// Implémentation du processus sound_sensing_process
PROCESS_THREAD(sound_sensing_process, ev, data)
{
    PROCESS_BEGIN();
    LOG_INFO("------- Processus mesure niveau sonore démarré \n");
   
    random_init(0); // Init du générateur pseudo-aléatoire    
    ctimer_set(&ctimer_timer_sound, 5 * CLOCK_SECOND, getSoundIntensityCallback, NULL);
    while(1)
    {
        // Plus besoin utiliser PROCESS_WAIT_EVENT_UNTIL car
        // le timer est déja configuré avec la callback qui sera appelé
        // automatiquement lors de l'expiration de l'expiration de ce dernier.
        
        PROCESS_YIELD(); // on libére le processeur (reprend l'exécution après expiration du timer)
    }
    PROCESS_END();
}

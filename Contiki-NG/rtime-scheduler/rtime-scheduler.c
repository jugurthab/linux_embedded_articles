#include "contiki.h"
#include "random.h"
#include "lib/list.h" // Liste qui contient nos tâches

#include "sys/log.h" // Gestion de LOGS
#define LOG_MODULE "RTimer" // Préfixe des logs (obligatoire)
#define LOG_LEVEL LOG_LEVEL_INFO // Niveau de criticité des LOG (obligatoire)

#define MAX_NB_SENSOR_TASKS_FIFO 3 // nombre de tâches

#define MAX_SOUND_INTENSITY 150
#define MIN_SOUND_INTENSITY 0

#define MAX_TEMPERATURE_VALUE 75
#define MIN_TEMPERATURE_VALUE 30

// Définition du type des tâches (peut être remplacé par un enum)
#define REQUESTED_READ_OPERATION_MOTOR_ROTATION  0
#define REQUESTED_READ_OPERATION_SOUND_INTENSITY 1
#define REQUESTED_READ_OPERATION_TEMPERATURE     2

// Déclaration et lancement du processus "rtime_sensor_reader_scheduler"
PROCESS(rtime_sensor_reader_scheduler, "FIFO real time sensor reader scheduler");
AUTOSTART_PROCESSES(&rtime_sensor_reader_scheduler);

static struct rtimer rtimer_timer; // Création d'un timer temps réel

/*
* Structure d'une tâche
*/
struct sensor_task {
    struct sensor_task *next_sensor; // Pointeur vers la prochaine tâche
    unsigned short requestReadOperation; // Indique le type de tâches (comme : REQUESTED_READ_OPERATION_MOTOR_ROTATION)
    int requestReadOperationValue; // Valeur de retourné par l'exécution de la tâche
};

static struct sensor_task *firstSensorStructHeader; // Renvoie la tâche à exécuter
volatile short isAllFifoTasksExecuted = 1;
  
// Déclaration d'une liste avec le type sensor_task;
// Le nom doit toujours être sous la forme "NOM_STRUCTURE + _list"
LIST(sensor_task_list);

// Fonction appelée par la taĉhe "Lecture Etat moteur"
void displayMotorRorationStatus(struct sensor_task *s){
    s->requestReadOperationValue = random_rand() & 1; // retourne 1 ou 0 (1 => moteur en rotation)
    LOG_INFO("L'état du moteur : %s\n", (s->requestReadOperationValue)?"on": "off");
}

// Fonction appelée par la taĉhe "Mesure niveau sonore"
void displaySoundIntensity(struct sensor_task *s){
    s->requestReadOperationValue = random_rand() % (MAX_SOUND_INTENSITY + 1 - MIN_SOUND_INTENSITY) + MIN_SOUND_INTENSITY;
    LOG_INFO("Niveau sonore %d dB\n", ((int) s->requestReadOperationValue));
}

// Fonction appelée par la taĉhe "Mesure de la température"
void displayTemeratureValue(struct sensor_task *s){
    s->requestReadOperationValue = random_rand() % (MAX_TEMPERATURE_VALUE + 1 - MIN_TEMPERATURE_VALUE) + MIN_TEMPERATURE_VALUE;
    LOG_INFO("Température %d °C\n", ((int) s->requestReadOperationValue));
}

void sensor_read_operation_callback(struct rtimer *t, void *ptr)
{
    struct sensor_task *sensors = ptr;

    switch(sensors->requestReadOperation){ // Décodage du type de la tâche
        case REQUESTED_READ_OPERATION_MOTOR_ROTATION:
            displayMotorRorationStatus(sensors);  
        break;

        case REQUESTED_READ_OPERATION_SOUND_INTENSITY:
            displaySoundIntensity(sensors);
        break;
        
        case REQUESTED_READ_OPERATION_TEMPERATURE:
            displayTemeratureValue(sensors);
        break;

        default:
        break;
    }

    firstSensorStructHeader = list_item_next(firstSensorStructHeader); // Lire la prochaine tâche
    if(firstSensorStructHeader != NULL){ // S'il reste encore des tâches dans la liste, on réarme le timer
        rtimer_set(&rtimer_timer, RTIMER_NOW() + (RTIMER_SECOND/2),
            1, sensor_read_operation_callback, firstSensorStructHeader);
    } else {
        isAllFifoTasksExecuted = 1;
        LOG_INFO("--------- (la pile est maintenant vide) -------------\n");
    }
}

PROCESS_THREAD(rtime_sensor_reader_scheduler, ev, data)
{
    PROCESS_BEGIN();
    int i = 0;    
    LOG_INFO("------- REAL TIME FIFO CONTIKI-NG SCHEDULER ----------\n");
    list_init(sensor_task_list); // Initialisation de la liste qui contiendra nos tâches
   
    struct sensor_task sensorTasks[MAX_NB_SENSOR_TASKS_FIFO]; // Contient les tâches à exécuter

    random_init(0); // Pour la génération pseudo-aléatoire des valeurs des capteurs

    LOG_INFO("Remplissage initale de la liste\n");

    for(i = 0; i < MAX_NB_SENSOR_TASKS_FIFO; i++){
        // Assignation du type de la tâche (comme : REQUESTED_READ_OPERATION_SOUND_INTENSITY)
        sensorTasks[i].requestReadOperation = i;
        // La tâche ne contiens aucune valeur initialement.
        sensorTasks[i].requestReadOperationValue = 0;
        list_add(sensor_task_list, &sensorTasks[i]); // Ajouter la tâche à la liste
    }

    for(;;) {
        // Si première exécution ou si toutes les tâches ont été accomplies, ré-executer les tâches
        //LOG_INFO("LENGTH => %d, isAllFifoTasksExecuted=%d\n", list_length(sensor_task_list), isAllFifoTasksExecuted);        
        if(isAllFifoTasksExecuted == 1){
            isAllFifoTasksExecuted = -1;
            // Recherche du premier élément de la liste
            //if(firstSensorStructHeader==NULL)            
            firstSensorStructHeader = list_head(sensor_task_list);
            
            /* Configuration d'un timer rtime et passage en paramètre de l'adresse
            * du premier élément de la liste.
            * le deuxième paramètre désigne le moment quand la tâche sera exécuté.
            * le troisième paramètre n'est pas utilisé pas Contiki-NG (en passe 1 en général).
            */
            rtimer_set(&rtimer_timer, RTIMER_NOW() + (RTIMER_SECOND/2), 1, sensor_read_operation_callback, firstSensorStructHeader);
        }
    }
    PROCESS_END();
}


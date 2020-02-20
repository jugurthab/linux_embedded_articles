#include "contiki.h"
#include "net/routing/routing.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-sr.h"

#include "webserver/httpd-simple.h"

#define MAX_SOUND_INTENSITY 150
#define MIN_SOUND_INTENSITY 0

#define MAX_TEMPERATURE_VALUE 75
#define MIN_TEMPERATURE_VALUE 30

/*---------------------------------------------------------------------------*/
PROCESS(webserver_nogui_process, "Web server AWS");

AUTOSTART_PROCESSES(&webserver_nogui_process);

int getMotorRorationStatus(){
    return (random_rand() & 1);
}

int getSoundIntensity(){
    return (random_rand() % (MAX_SOUND_INTENSITY + 1 - MIN_SOUND_INTENSITY) + MIN_SOUND_INTENSITY);
}

int getTemperatureValue(){
    return (random_rand() % (MAX_TEMPERATURE_VALUE + 1 - MIN_TEMPERATURE_VALUE) + MIN_TEMPERATURE_VALUE);
}

// Thread de lecture et renvoi des messages JSON
static PT_THREAD(generate_routes(struct httpd_state *s))
{
    char buff[80];
    PSOCK_BEGIN(&s->sout);

    sprintf(buff,"{\"temperature\":%d, \"sound_level\":%d, \"motor_rotation\":%d}",
                    getTemperatureValue(), getSoundIntensity(), getMotorRorationStatus());
    // LOG_INFO("Envoi du JSON\n");
    SEND_STRING(&s->sout, buff); // Retouner le json au middleware
    PSOCK_END(&s->sout);
}
/* Méthode requise par le serveur web */ 
httpd_simple_script_t httpd_simple_get_script(const char *name)
{
    return generate_routes;
}

PROCESS_THREAD(webserver_nogui_process, ev, data)
{
    PROCESS_BEGIN();

    httpd_init(); // Lancement du serveur web
    random_init(0);
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
        httpd_appcall(data);
    }

    PROCESS_END();
}

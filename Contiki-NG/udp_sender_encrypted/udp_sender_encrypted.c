#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/etimer.h"
#include <stdlib.h>

#define SEND_INTERVAL		  (5 * CLOCK_SECOND)

#define UDP_SERVER_PORT	5678
#define UDP_CLIENT_PORT	8765

#define MAX_TEMPERATURE_VALUE 75
#define MIN_TEMPERATURE_VALUE 30

char xor_encryption_key[20] = "tEsT_GHR5478_KHG52";

static struct simple_udp_connection udp_server_socket;
static struct simple_udp_connection udp_client_socket;

PROCESS(udp_server_process, "UDP server");
PROCESS(udp_client_process, "UDP client");

AUTOSTART_PROCESSES(&udp_server_process, &udp_client_process);
/*---------------------------------------------------------------------------*/

static void message_received_callback(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
    char decryptedData[20];
    int i =0;
    for(i=0; i<20; i++){
        decryptedData[i] = ((char)data[i]) ^ xor_encryption_key[i];
    } 
    printf("=> Received Encrypted '%s' => Decrypted : %s\n", (char *) data, decryptedData);
}

int displayTemeratureValue(){
    return (rand() % (MAX_TEMPERATURE_VALUE + 1 - MIN_TEMPERATURE_VALUE) + MIN_TEMPERATURE_VALUE);
}

PROCESS_THREAD(udp_server_process, ev, data)
{
    PROCESS_BEGIN();

    NETSTACK_ROUTING.root_start();

    simple_udp_register(&udp_server_socket, UDP_SERVER_PORT, NULL,
                        UDP_CLIENT_PORT, message_received_callback);

    PROCESS_END();
}

PROCESS_THREAD(udp_client_process, ev, data)
{
    static struct etimer periodic_timer;
    static char str[20];
    uip_ipaddr_t dest_ipaddr;
    int i = 0;
    PROCESS_BEGIN();

    simple_udp_register(&udp_client_socket, UDP_CLIENT_PORT, NULL,
                        UDP_SERVER_PORT, NULL);
    while(1) {
        etimer_set(&periodic_timer, SEND_INTERVAL);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        if(NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr)) {
            snprintf(str, sizeof(str), "Temperature = %d°C", displayTemeratureValue());
            for(i = 0; i < strlen(str); i++){
                str[i] ^= xor_encryption_key[i];
            }

            simple_udp_sendto(&udp_client_socket, str, strlen(str), &dest_ipaddr);
        } else {
            printf("Not reachable yet\n");
        }
    }

PROCESS_END();
}
/*---------------------------------------------------------------------------*/

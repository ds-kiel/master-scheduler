/**
 * \file
 *         Neighbor discovery
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 *
 */

// includes
  #include "contiki.h"
  #include "net/master-routing/master-routing.h"

  #include <string.h>

/* Log configuration */
  #include "sys/log.h"
  #define LOG_MODULE "App"
  #define LOG_LEVEL LOG_LEVEL_INFO


/*---------------------------------------------------------------------------*/
PROCESS(master_neighbor_discovery_process, "Master neighbor discovery example");
AUTOSTART_PROCESSES(&master_neighbor_discovery_process);

/*---------------------------------------------------------------------------*/
//void input_callback(const void *data, uint16_t len,
//  const linkaddr_t *src, const linkaddr_t *dest)
//{
//  if(len == sizeof(unsigned)) {
//    LOG_INFO("Received %u from ", *(unsigned *)data);
//    LOG_INFO_LLADDR(src);
//    LOG_INFO_("\n");
//  }
//}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(master_neighbor_discovery_process, ev, data)
{
  static struct etimer periodic_timer;
  //uint8_t success;

  PROCESS_BEGIN();

  /* Initialize Master */
  init_master_routing();
  //master_routing_set_input_callback(input_callback);

  etimer_set(&periodic_timer, CLOCK_SECOND);

  do {
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
      etimer_reset(&periodic_timer);
  } while(!master_routing_configured());

  if (node_is_sender()){
    while(1){
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
      //success = 
      master_routing_sendto(NULL, 0, 0); //TODO: nullpointer might break it
      //LOG_INFO("Success: %u", success);
      etimer_reset(&periodic_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
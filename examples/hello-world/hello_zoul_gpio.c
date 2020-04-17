/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
//#include "dev/leds.h"
//#include "arch/cpu/cc2538/dev/gpio.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "net/mac/tsch/tsch.h"

#include <stdio.h> /* For printf() */

#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
static linkaddr_t coordinator_addr =  {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
#endif /* MAC_CONF_WITH_TSCH */

#define SEND_INTERVAL (1 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer periodic_timer;
  static uint8_t count;
  PROCESS_BEGIN();

  GPIO_SET_OUTPUT(GPIO_D_BASE, 0x01);

#if MAC_CONF_WITH_TSCH
  tsch_set_coordinator(linkaddr_cmp(&coordinator_addr, &linkaddr_node_addr));
#endif /* MAC_CONF_WITH_TSCH */
  //leds_on(LEDS_GREEN);
  etimer_set(&periodic_timer, SEND_INTERVAL);

  while(1){//count <= 60){
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    if (count%2){
      GPIO_SET_PIN(GPIO_D_BASE, 0x01);
    } else {
      GPIO_CLR_PIN(GPIO_D_BASE, 0x01);
    }
    printf("%x:%x:%x:%x:%x:%x:%x:%x\n", linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1], linkaddr_node_addr.u8[2], linkaddr_node_addr.u8[3], linkaddr_node_addr.u8[4], linkaddr_node_addr.u8[5], linkaddr_node_addr.u8[6], linkaddr_node_addr.u8[7]);
    count++;
    etimer_reset(&periodic_timer);
  }

  //SKY only
  /*while(1){
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    
    printf("%u:%u:%u:%u:%u:%u:%u:%u\n", linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1], linkaddr_node_addr.u8[2], linkaddr_node_addr.u8[3], linkaddr_node_addr.u8[4], linkaddr_node_addr.u8[5], linkaddr_node_addr.u8[6], linkaddr_node_addr.u8[7]);
    count++;
    if (count > 60){
      _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
      NETSTACK_RADIO.off();
      NETSTACK_MAC.off();
      _BIC_SR(GIE); // disable interrupts
      // LPM4
      _BIS_SR(SCG1 | SCG0 | OSCOFF | CPUOFF);
    }
    etimer_reset(&periodic_timer);
  }*/

  //printf("Hello, world\n");
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

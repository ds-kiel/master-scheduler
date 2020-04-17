/*
 * Copyright (c) 2017, RISE SICS.
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
 *         NullNet, a minimal network layer.
 * \author
 *         Simon Duquennoy <simon.duquennoy@ri.se>
 *
 */

/**
 * \addtogroup nullnet
 * @{
 */

#include "contiki.h"
#include "dev/leds.h"
#include "net/packetbuf.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "NullNet"
#define LOG_LEVEL LOG_LEVEL_NULLNET

uint8_t *nullnet_buf;
uint16_t nullnet_len;
static nullnet_input_callback current_callback = NULL;
#if TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS)
static nullnet_config_callback config_callback = NULL;
#endif /* TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS) */
/*--------------------------------------------------------------------*/
static void
init(void)
{
  LOG_INFO("init\n");
  current_callback = NULL;
}
/*--------------------------------------------------------------------*/
static void
input(void)
{
  if(current_callback != NULL) {
    LOG_INFO("received %u bytes from ", packetbuf_datalen());
    LOG_INFO_LLADDR(packetbuf_addr(PACKETBUF_ADDR_SENDER));
    LOG_INFO_("\n");
    current_callback(packetbuf_dataptr(), packetbuf_datalen(),
      packetbuf_addr(PACKETBUF_ADDR_SENDER), packetbuf_addr(PACKETBUF_ADDR_RECEIVER));
  }
}
/*--------------------------------------------------------------------*/
void
nullnet_set_input_callback(nullnet_input_callback callback)
{
 current_callback = callback;
}
/*--------------------------------------------------------------------*/
#if TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS)
void
nullnet_set_config_callback(nullnet_config_callback callback)
{
 config_callback = callback;
}
#endif /* TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS) */
/*--------------------------------------------------------------------*/
static uint8_t
output(const linkaddr_t *dest)
{
  leds_on(LEDS_YELLOW);
# if TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS)
    packetbuf_config_t packet_configuration = config_callback();
    if (packet_configuration.relay){
      packetbuf_attr_clear();
    } else {
      packetbuf_clear();
      packetbuf_copyfrom(nullnet_buf, nullnet_len);
    }
# else
  packetbuf_clear();
  packetbuf_copyfrom(nullnet_buf, nullnet_len); //TODOLIV avoid included packetbuf_clear()!!!!
# endif /* TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS) */

# if TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS)
    //packetbuf_config_t packet_configuration = config_callback();
    //set max_transmissions
    packetbuf_set_attr(PACKETBUF_ATTR_MAX_MAC_TRANSMISSIONS, packet_configuration.max_tx);

#   if TSCH_FLOW_BASED_QUEUES
      //packetbuf set flow number
      packetbuf_set_attr(PACKETBUF_ATTR_FLOW_NUMBER, packet_configuration.flow_number);
#   endif /* TSCH_FLOW_BASED_QUEUES */

#   if TSCH_TTL_BASED_RETRANSMISSIONS
      //packetbuf set TTL
      packetbuf_set_attr(PACKETBUF_ATTR_TRANSMISSION_TTL, packet_configuration.ttl_slot_number);

      packetbuf_set_attr(PACKETBUF_ATTR_EARLIEST_TX_SLOT, packet_configuration.earliest_tx_slot);
#   endif /* TSCH_TTL_BASED_RETRANSMISSIONS */

# endif /* TSCH_WITH_CENTRAL_SCHEDULING && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS) */

  if(dest != NULL) {
    packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER, dest);
  } else {
    packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER, &linkaddr_null);
  }
  packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &linkaddr_node_addr);
  LOG_INFO("sending %u bytes to ", packetbuf_datalen());
  LOG_INFO_LLADDR(packetbuf_addr(PACKETBUF_ADDR_RECEIVER));
  LOG_INFO_("\n");
  leds_off(LEDS_YELLOW);
  NETSTACK_MAC.send(NULL, NULL);
  return 1;
}
/*--------------------------------------------------------------------*/
const struct network_driver nullnet_driver = {
  "nullnet",
  init,
  input,
  output
};
/*--------------------------------------------------------------------*/
/** @} */

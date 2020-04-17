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
 *         MasterNet, Master's minimal network layer, an adaptation of NullNet
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 *
 */

/**
 * \ingroup net-layer
 * \addtogroup masternet
A network layer that does nothing. Useful for lower-layer testing and
for non-IPv6 scenarios.
 * @{
 */

#ifndef MASTERNET_H_
#define MASTERNET_H_

#include "contiki.h"
#include "net/linkaddr.h"

//#if TSCH_WITH_CENTRAL_SCHEDULING // && (TSCH_FLOW_BASED_QUEUES || TSCH_TTL_BASED_RETRANSMISSIONS)
typedef struct master_packetbuf_config_t {
# if TSCH_TTL_BASED_RETRANSMISSIONS
    uint16_t ttl_slot_number;
    uint16_t earliest_tx_slot;
# endif /* TSCH_TTL_BASED_RETRANSMISSIONS */
# if TSCH_FLOW_BASED_QUEUES
  uint16_t flow_number;
# endif /* TSCH_FLOW_BASED_QUEUES */
  uint16_t max_tx;
} master_packetbuf_config_t;

/* Sicslowpan adaptation */
#ifdef MASTER_CONF_MAC_MAX_PAYLOAD
#define MAC_MAX_PAYLOAD MASTER_CONF_MAC_MAX_PAYLOAD
#else /* MASTER_CONF_MAC_MAX_PAYLOAD */
#define MAC_MAX_PAYLOAD (127 - 2)
#endif /* MASTER_CONF_MAC_MAX_PAYLOAD */

#define FIXED_HDRLEN 21 //might be too much

/**
 * Buffer used by the output function
*/
extern uint8_t *masternet_buf;
extern uint16_t masternet_len;

/**
 * Function prototype for MasterNet input callback
*/
typedef void (* masternet_input_callback)(const void *data, uint16_t len,
  const linkaddr_t *src, const linkaddr_t *dest);

/**
 * Set input callback for MasterNet
 *
 * \param callback The input callback
*/
void masternet_set_input_callback(masternet_input_callback callback);



/**
 * Function prototype for MasterNet configuration callback
*/
typedef master_packetbuf_config_t (* masternet_config_callback)(void);

/**
 * Set config callback for MasterNet
 *
 * \param callback The config callback
*/
void masternet_set_config_callback(masternet_config_callback callback);

#endif /* MASTERNET_H_ */
/** @} */

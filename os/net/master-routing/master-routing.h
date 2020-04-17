/*
 * Copyright (c) 2011, Swedish Institute of Computer Science.
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
 */

/** 
 * \file
 *         Header file for the Master Routing module.
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 *
 */

#ifndef MASTER_ROUTING_H
#define MASTER_ROUTING_H

#include "contiki.h"
#include "master-conf.h"
#include "net/linkaddr.h"

/**
 * Function prototype for MasterRouting input callback
*/
typedef void (* master_routing_input_callback)(const void *data, uint16_t len,
  uint8_t src, uint8_t dest);

/**
 * Set input callback for MasterRouting
 *
 * \param callback The input callback
*/
void master_routing_set_input_callback(master_routing_input_callback callback);

int node_is_sender(void);

int get_node_receiver(void);

int master_routing_configured(void);

//choose tx flow based on routing information
int master_routing_send(const void *data, uint16_t datalen);


int master_routing_sendto(const void *data, uint16_t datalen, uint8_t flow);

void init_master_routing(void);

#endif /* MASTER_ROUTING_H */

/** @} */
/** @} */

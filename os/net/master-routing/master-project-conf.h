/*
* Copyright (c) 2017, Inria.
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
 *         project_conf configuration for Master
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 */

/** \addtogroup net
 * @{ */

/** \addtogroup master
* @{ */

/* To be included by project_conf of application using MASTER */

#ifndef __MASTER_PROJECT_CONF_H__
#define __MASTER_PROJECT_CONF_H__


#ifndef TSCH_CONF_WITH_CENTRAL_SCHEDULING
#define TSCH_CONF_WITH_CENTRAL_SCHEDULING    1 //default setting
#endif
#ifndef TSCH_CONF_FLOW_BASED_QUEUES
#define TSCH_CONF_FLOW_BASED_QUEUES          1 //default setting
#endif
#ifndef TSCH_CONF_TTL_BASED_RETRANSMISSIONS
#define TSCH_CONF_TTL_BASED_RETRANSMISSIONS  1 //default setting
#endif

#ifndef MASTER_TSCH_COORDINATOR
#define MASTER_TSCH_COORDINATOR 0x01
#endif

#ifndef NUM_COOJA_NODES
#define NUM_COOJA_NODES 5
#endif

// neighbor discovery during runtime:
#undef  TSCH_CONF_PACKET_EB_WITH_NEIGHBOR_DISCOVERY
#define TSCH_CONF_PACKET_EB_WITH_NEIGHBOR_DISCOVERY 0

#ifndef MASTER_NUM_FLOWS
#define MASTER_NUM_FLOWS 8
#endif

#ifndef HASH_MAP_CONF_SIZE
#define HASH_MAP_CONF_SIZE MASTER_NUM_FLOWS
#endif

#undef TSCH_CONF_MAC_MAX_FRAME_RETRIES
#define TSCH_CONF_MAC_MAX_FRAME_RETRIES 0 //others: standard is 7 -> handled differently by Master

#undef IEEE802154_CONF_PANID
#define IEEE802154_CONF_PANID 0x4bb4

// free space
#undef SICSLOWPAN_CONF_FRAG
#define SICSLOWPAN_CONF_FRAG 0
#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE 0
#undef NETSTACK_MAX_ROUTE_ENTRIES
#define NETSTACK_MAX_ROUTE_ENTRIES 0


#define PACKETBUF_CONF_SIZE 96

#ifndef TSCH_CONF_DEFAULT_HOPPING_SEQUENCE
#define TSCH_CONF_DEFAULT_HOPPING_SEQUENCE TSCH_HOPPING_SEQUENCE_4_4
#endif

#ifndef TSCH_CONF_EB_PERIOD
#define TSCH_CONF_EB_PERIOD (4*CLOCK_SECOND)
#endif

#undef TSCH_SCHEDULE_CONF_MAX_SLOTFRAMES
#ifndef MASTER_CONF_SCHEDULE
#define TSCH_SCHEDULE_CONF_MAX_SLOTFRAMES 3
#else
#define TSCH_SCHEDULE_CONF_MAX_SLOTFRAMES MASTER_NUM_FLOWS+1
#endif

#undef TSCH_CONF_AUTOSELECT_TIME_SOURCE
#define TSCH_CONF_AUTOSELECT_TIME_SOURCE 0

#endif /* __MASTER_PROJECT_CONF_H__ */

/** @} */
/** @} */
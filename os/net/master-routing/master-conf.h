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
 *         Configuration for Master
 * \author
 *         Oliver Harms <oha@informatik.uni-kiel.de>
 */

/** \addtogroup net
 * @{ */

/** \addtogroup master
* @{ */

#ifndef __MASTER_CONF_H__
#define __MASTER_CONF_H__

# if defined(CONTIKI_TARGET_SKY) || defined(CONTIKI_TARGET_COOJA)
# define NODE_ID_INDEX 0
# else
# define NODE_ID_INDEX 7
# endif

#ifdef MASTER_CONF_SCHEDULE
#define MASTER_SCHEDULE MASTER_CONF_SCHEDULE
#endif

#ifdef MASTER_CONF_EBSF_PERIOD
#define MASTER_EBSF_PERIOD  MASTER_CONF_EBSF_PERIOD
#else
#define MASTER_EBSF_PERIOD  31 //for zoul, 11 for sky
#endif

#if !TSCH_CONF_TTL_BASED_RETRANSMISSIONS
#ifndef MAX_NUMBER_TRANSMISSIONS
#define MAX_NUMBER_TRANSMISSIONS   8    //maximum number transmissions possible for sender -> assuming sender of only one flow!
#endif
#endif /* !TSCH_CONF_TTL_BASED_RETRANSMISSIONS */

#ifndef MASTER_MSG_LENGTH
#define MASTER_MSG_LENGTH 64
#endif

#ifdef MASTER_CONF_INIT_PERIOD
#define MASTER_INIT_PERIOD MASTER_CONF_INIT_PERIOD
#else
#define MASTER_INIT_PERIOD 55 * CLOCK_SECOND
#endif

#endif /* __MASTER_CONF_H__ */

/** @} */
/** @} */
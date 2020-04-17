#ifndef TESTBED_H_
#define TESTBED_H_

#include "sys/testbed-conf.h"

//#ifdef TESTBED_CONF_TARGET_TYPE
//#define TESTBED_TARGET_TYPE TESTBED_CONF_TARGET_TYPE
//#else
//#define TESTBED_TARGET_TYPE TARGET_TYPE_UNDEFINED
//#endif

#if CONTIKI_TARGET_ZOUL
uint32_t get_ieee_addr_node_id(uint32_t hardware_node_id);
#endif

#endif /* TESTBED_H_ */
#include "contiki.h"
#include "sys/testbed.h"
//#include <stdio.h>

uint32_t get_ieee_addr_node_id(uint32_t hardware_node_id){
  //printf("old node id: %x\n", hardware_node_id);
  #ifdef TESTBED
    //printf("TESTBED\n");
    #if TESTBED == TESTBED_KIEL
      //printf("TESTBED == TESTBED_KIEL\n");
      switch(hardware_node_id) {
        case 0x18d6f3a4  : return 0x00000001;
        case 0x18d6f2fe  : return 0x00000002;
        case 0x18d6f3a2  : return 0x00000003;
        case 0x18d6f3c0  : return 0x00000004;
        case 0x18d6f3f4  : return 0x00000005;
        case 0x18d6f7a7  : return 0x00000006;
        case 0x18d6f7b9  : return 0x00000007;
        case 0x18d6f3e5  : return 0x00000008;
        case 0x18d6f7df  : return 0x00000009;
        case 0x18d6f204  : return 0x0000000a;
        
        case 0x18d6f38e  : return 0x0000000c;
        case 0x18d6f27d  : return 0x0000000d;
        case 0x18d6f3c4  : return 0x0000000e;
        case 0x18d6f3df  : return 0x0000000f;
        case 0x18d6f7cb  : return 0x00000010;
        case 0x18d6f261  : return 0x00000011;
        case 0x18d6f240  : return 0x00000012;
        case 0x18d6f3e9  : return 0x00000013;
        case 0x18d6f3e2  : return 0x00000014;
        case 0x18d6f3a6  : return 0x00000015;

        default : return hardware_node_id;
      }
    #elif TESTBED == TESTBED_DESK
      //printf("TESTBED == TESTBED_KIEL\n");
      switch(hardware_node_id) {
        case 0x194a5136  : return 0x00000001;
        case 0x194a5164  : return 0x00000002;
        case 0x14d52dee  : return 0x00000003;
        case 0x19332e5c  : return 0x00000004;
        case 0x1932e6b8  : return 0x00000005;

        default : return hardware_node_id;
      }
    #endif /* TESTBED == TESTBED_KIEL */
  #endif /* TESTBED */

  return hardware_node_id;
}
CONTIKI_PROJECT = master-unicast
all: $(CONTIKI_PROJECT)

CONTIKI = ../../..

MAKE_MAC = MAKE_MAC_TSCH
MAKE_NET = MAKE_NET_OTHER

MODULES += os/net/master-net
MODULES += os/net/master-routing

MODULES += os/services/simple-energest

include $(CONTIKI)/Makefile.include
CONTIKI_PROJECT = link_addr_identifier 
#hello_zoul_gpio
#link_addr_identifier 
all: $(CONTIKI_PROJECT)

MAKE_MAC = MAKE_MAC_TSCH
MAKE_NET = MAKE_NET_NULLNET
#TARGET=zoul
#BOARD=firefly

CFLAGS += -DTARGET=`echo \"$(TARGET)\"`

CONTIKI = ../..
include $(CONTIKI)/Makefile.include

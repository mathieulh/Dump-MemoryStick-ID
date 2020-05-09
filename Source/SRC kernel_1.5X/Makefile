TARGET = mstest
OBJS = main.o ms_drv.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = MSID Dumper 1.5X

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
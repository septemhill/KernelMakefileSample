PRJ_ROOT			= $(shell pwd)/..
KTARGET				= main
EMBEDDED			= n

CONFIG_PM_MOD			= y
CONFIG_DEV_MOD			= y
CONFIG_DRI_MOD			= y
CONFIG_SYSDEP_MOD		= y

obj-m				:= $(KTARGET).o
obj-y				:= pm/ dev/ dri/ sysdep/

$(KTARGET)-y			:= pm/main.o
$(KTARGET)-$(CONFIG_PM_MOD)	+= pm/built-in.o
$(KTARGET)-$(CONFIG_DEV_MOD)	+= dev/built-in.o
$(KTARGET)-$(CONFIG_DRI_MOD)	+= dri/built-in.o
$(KTARGET)-$(CONFIG_SYSDEP_MOD)	+= sysdep/built-in.o

ifeq ($(EMBEDDED), y)
else
KDIR				?= /lib/modules/$(shell uname -r)/build
endif

PWD				:= $(shell pwd)

ccflags-y			:= -I$(INCDEV) -I$(INCPM) -I$(INCSYSDEP) -I$(INCDRI)
subdir-ccflags-y		:= -I$(INCDEV) -I$(INCPM) -I$(INCSYSDEP) -I$(INCDRI)

.PHONY:	all clean

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) INCDEV=$(PWD)/inc/dev INCDRI=$(PWD)/inc/dri INCSYSDEP=$(PWD)/inc/sysdep INCPM=$(PWD)/inc/pm 

clean:
	@$(MAKE) -C $(KDIR) M=$(PWD) clean

install: all
	@$(MAKE) -C $(KDIR) M=$(PWD) INSTALL_MOD_PATH=$(PRJ_ROOT)/bin modules_install

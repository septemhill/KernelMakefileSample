TARGET				= main
EMBEDDED			= n

CONFIG_PM_MOD			= y
CONFIG_DEV_MOD			= y
CONFIG_DRI_MOD			= y
CONFIG_SYSDEP_MOD		= y

obj-m				:= $(TARGET).o
obj-y				:= pm/ dev/ dri/ sysdep/

$(TARGET)-y			:= pm/main.o
$(TARGET)-$(CONFIG_PM_MOD)	+= pm/pm.o
$(TARGET)-$(CONFIG_DEV_MOD)	+= dev/dev.o
$(TARGET)-$(CONFIG_DRI_MOD)	+= dri/dri.o
$(TARGET)-$(CONFIG_SYSDEP_MOD)	+= sysdep/sys.o

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
	@sudo insmod $(TARGET).ko
clean:
	@$(MAKE) -C $(KDIR) M=$(PWD) clean
	@sudo rmmod $(TARGET)

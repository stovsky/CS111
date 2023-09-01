ifneq ($(KERNELRELEASE),)
obj-m := proc_count.o
else
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD modules

modules_install:
	$(MAKE) -C $(KDIR) M=$$PWD modules_install

install:
	$(MAKE) -C $(KDIR) M=$$PWD install

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif

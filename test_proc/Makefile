#
# for Ambarella Driver Modules 
#

MODULE_NAME = test_proc.o

export ARCH = arm
export CROSS_COMPILE = arm-none-linux-gnueabi-
export CC = $(CROSS_COMPILE)gcc
KERNEL_PATH ?= /VMShare_Amb_fc15/Ambarella/a5s_linux_sdk3.2/a5s_linux_sdk/ambarella/kernel/linux/

ifneq ($(KERNELRELEASE),)
	obj-m :=  $(MODULE_NAME)
else
	KERNELDIR ?= $(KERNEL_PATH)
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(shell rm -f *.ko *.o *.bak *.mod.o *.mod.c *.symvers *.order)
endif
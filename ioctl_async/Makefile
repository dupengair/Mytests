# =============================================================================
# Center Makefile for Amba Factoryset Modules
# by dup
#
# Amba Factoryset modules 
# make MODULENAME : perform make in one module
# make           : make whole FactorySet module
# make install : copy *.ko to current  directory
# make clean  : clean each   module   directory
# =============================================================================
include Rules.mk


export CENTER_MAKEFILE = 1

export ARCH = $(MUDULE_ARCH)
export AMBABUILD_TOPDIR = $(AMBASDK_DIR)
export KERNEL_PATH = $(AMBABUILD_TOPDIR)/kernel/linux-2.6.38

LINUX_HEADER_INCLUDE = $(KERNEL_PATH)/include
LINUX_HEADER_ARCH = $(KERNEL_PATH)/arch/$(ARCH)/include
LINUX_HEADER_PLAT = $(KERNEL_PATH)/arch/arm/plat-ambarella/include
export AMBARELLA_INCLUDES = -I$(AMBABUILD_TOPDIR) -I$(LINUX_HEADER_INCLUDE) -I$(LINUX_HEADER_ARCH) -I$(LINUX_HEADER_PLAT) 

AMBARELLA_LD_FLAG = -lpthread
AMBARELLA_CFLAGS = -O2 -Wall -march=armv5te -mtune=arm9tdmi
export MODULE_LD_FLAG = $(AMBARELLA_LD_FLAG)
export MODULE_CFLAG = $(AMBARELLA_INCLUDES) $(AMBARELLA_CFLAGS)


export CC = $(LINUX_TOOLCHAIN_NAME)gcc
export TOOLCHAIN_PATH = $(ARM_LINUX_TOOLCHAIN_DIR)/bin
export PATH:=$(TOOLCHAIN_PATH):$(PATH)


SUBDIRS = $(sort $(dir $(wildcard */)))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))
INSTALLSUBDIRS = $(addsuffix .install, $(SUBDIRS))
SUBMODULE_OBJS = $(foreach DIR, $(SUBDIRS), $(wildcard $(DIR)*.o))


ROOTMODULE_SRCS = $(wildcard *.c)
ROOTMODULE_OBJS = $(ROOTMODULE_SRCS:%.c=%.o)
ROOTMODULE_NAMES = $(ROOTMODULE_SRCS:%.c=%)
MODULE_FILE = $(basename $@)
export MODULE_NAME = $(TARGET)

default: all 

.PHONY: clean ToolChain $(SUBMODULE_1) $(TARGET)  
all: ToolChain infosubdir $(SUBMODULE_1) inforootdir $(TARGET)

ToolChain:
	@echo
	@echo "============== Compiler ToolChain =============="
	@echo 
	@echo "PATH = $(PATH)"
	@echo "CC = $(CC)"
	@echo "AMBARELLA_INCLUDES = $(AMBARELLA_INCLUDES)"
	@echo "AMBARELLA_CFLAGS = $(AMBARELLA_CFLAGS)"
	@echo "SUBDIRS = $(SUBDIRS)"
	@echo

infosubdir:
	@echo
	@echo "============== Making all in subdirectory... =============="
	
$(SUBMODULE_1):
	@echo
#	ifeq($(SUBMODULE_1_DEBUG),y)
#	@echo "module 1 debug open"
#	endif
	@$(MAKE) -C $(SUBMODULE_1)
	@echo
	
inforootdir:	
	@echo "============== Making all in root dir... =============="
	@echo
	
$(TARGET):$(ROOTMODULE_OBJS)
	@echo
	@echo "============== generate [$(TARGET)] =============="
	@echo
	@echo "OBJS = $(ROOTMODULE_OBJS) $(SUBMODULE_OBJS)"
	@$(CC) $(MODULE_LD_FLAG) -o $(TARGET) $(SUBMODULE_OBJS) $(ROOTMODULE_OBJS)
	@echo
	@echo "============== make finished. =============="
	@echo
	@echo "TARGET = $(TARGET)"
	@echo

$(ROOTMODULE_OBJS):%.o:%.c
	@echo "compile $(TARGET) module : [$(MODULE_FILE)]"
	@$(CC) $(MODULE_CFLAG) -c -o $@ $<
	@echo "done."


install: $(INSTALLSUBDIRS)
	@echo
	@echo make install complete, find .ko in current directory
	@echo

$(INSTALLSUBDIRS):
	@echo
	@echo Executing make install in module $(basename $@)...
	@cd $(basename $@) ; $(MAKE) install


clean: $(CLEANSUBDIRS)
	@echo
	@echo "Executing make install in root dir ..."
	@echo "  Clean [$(ROOTMODULE_NAMES)]"
	@$(RM) -rf  $(ROOTMODULE_OBJS) $(TARGET) *.bak
	@echo
	@echo all generated files cleaned.	
	@echo

$(CLEANSUBDIRS):
	@echo
	@echo "Executing make clean in module $(basename $@)..."
	@cd $(basename $@) ; $(MAKE) clean


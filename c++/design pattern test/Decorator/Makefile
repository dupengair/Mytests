# =============================================================================
# Center Makefile for Common Use
# by dup
# 2012-05-12
# =============================================================================
######################  Makefile Includes #############################
include Config.mk
include Rules.mk 


###################### Check Includes #############################

ifneq ($(MAKEFILE_CONFIG_INCLUDE), y)
$(error Config.mk should be included)
endif

ifneq ($(MAKEFILE_RULES_INCLUDE), y)
$(error Rules.mk should be included)
endif


###################### Configure Compiler #############################
ifeq ($(CONFIG_SRC_C), y)
SRC_TYPE = c
else
SRC_TYPE = cpp
endif

ifeq ($(CONFIG_COMPILER_USE_GCC), y)
COMPILER = gcc
ifeq ($(CONFIG_SRC_CPP), y)
LD_FLAGS += -lstdc++
endif
else
COMPILER=g++
endif

ifeq ($(CONFIG_GDB_DEBUG), y)
C_FLAGS += -g
endif

CC = $(TOOLCHAIN_PREFIX)$(COMPILER) $(INCLUDES) $(C_FLAGS) 
AR = $(TOOLCHAIN_PREFIX)ar  
			
SOURCES = $(wildcard *.$(SRC_TYPE)) 
REL_OBJ = $(SOURCES:%.$(SRC_TYPE)=%.o)

ifeq ($(CONFIG_OBJ_EXEC), y)
GENERATE=$(TARGET)
TASK=$(CC) $(LD_FLAGS) -o $(GENERATE) $(OBJS_DIR)/*.o
endif
ifeq ($(CONFIG_OBJ_STATIC_LIB), y)
GENERATE = lib$(TARGET).a
TASK=$(AR) -rcs $(GENERATE) $(OBJS_DIR)/*.o
endif
ifeq ($(CONFIG_OBJ_DYNAMIC_LIB), y)
GENERATE = lib$(TARGET).so
TASK=$(CC) -shared  -o $(GENERATE) $(OBJS_DIR)/*.o
endif

###################### Configure Target #############################
all: check_env prepare $(GENERATE)

## Prepare Environment ##
check_env:
	$(MAKEFILE_V)echo "#------------------------------------------------------->"
	$(MAKEFILE_V)echo "check env :"
	$(MAKEFILE_V)echo "SOURCE FILE TYPE = $(SRC_TYPE)"
	$(MAKEFILE_V)echo "COMPILER = $(TOOLCHAIN_PREFIX)$(COMPILER)"
	$(MAKEFILE_V)echo "INCLUDES = $(INCLUDES)"
	$(MAKEFILE_V)echo "C_FLAGS = $(C_FLAGS)"
	$(MAKEFILE_V)echo "LD_FLAGS = $(LD_FLAGS)"

prepare:
	echo "OBJS_DIR = $(OBJS_DIR) "
ifneq ($(shell [ -d $(OBJS_DIR) ] && echo y), y)
	$(MAKEFILE_V)$(DEFAULTMKDIR) $(OBJS_DIR)/
	$(MAKEFILE_V)$(DEFAULTCHMOD) 777 $(OBJS_DIR)/
endif

## Generate Target ##
$(GENERATE):$(REL_OBJ) 
	$(MAKEFILE_V)echo 
	$(MAKEFILE_V)echo "generate : [$(GENERATE)] "
	$(MAKEFILE_V)echo "OBJS = $(REL_OBJ)"
	$(MAKEFILE_V)$(TASK)
	$(MAKEFILE_V)echo "done."

## Compile Objecs ##
$(REL_OBJ): %.o:%.$(SRC_TYPE)
	$(MAKEFILE_V)echo 
	$(MAKEFILE_V)echo "compile OBJ : [$(basename $@)]"
	$(MAKEFILE_V)$(CC) -c -o $(OBJS_DIR)/$@ $< 
	$(MAKEFILE_V)echo "done."

## Clean Target ##
clean:
	$(MAKEFILE_V)rm -rf $(GENERATE) $(OBJS_DIR) 



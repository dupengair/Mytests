# =============================================================================
# Configurations for Center Makefile
# by dup
# 2012-05-12
# =============================================================================
MAKEFILE_CONFIG_INCLUDE=y


###################### User Configurations #############################
####config source file type
CONFIG_SRC_C=y
#CONFIG_SRC_CPP=y

####config output type
CONFIG_OBJ_EXEC=y
#CONFIG_OBJ_STATIC_LIB=y
#CONFIG_OBJ_DYNAMIC_LIB=y

####config compiler type
#CONFIG_COMPILER_USE_GCC=y
CONFIG_COMPILER_USE_GPLUSPLUS=y

####GDB debug
CONFIG_GDB_DEBUG=y


###################### Configuration Check #############################
####Check source file type
ifeq ($(CONFIG_SRC_C), y)
ifeq ($(CONFIG_SRC_CPP), y)
$(error should not config CONFIG_SRC_C  and CONFIG_SRC_CPP at same time)
endif
else
ifeq ($(CONFIG_SRC_C), y)
$(error should not config CONFIG_SRC_C  and CONFIG_SRC_CPP at same time)
endif
endif

####Check output type
ifeq ($(CONFIG_OBJ_EXEC), y)
ifeq ($(CONFIG_OBJ_STATIC_LIB), y)
$(error output type should only be one)
endif
ifeq ($(CONFIG_OBJ_DYNAMIC_LIB), y)
$(error output type should only be one)
endif
else
ifeq ($(CONFIG_OBJ_STATIC_LIB), y)
ifeq ($(CONFIG_OBJ_DYNAMIC_LIB), y)
$(error output type should only be one)
endif
endif
endif

CONFIG_OBJ_EXEC=y
#CONFIG_OBJ_STATIC_LIB=y
#CONFIG_OBJ_DYNAMIC_LIB=y

####Check compiler type
ifeq ($(CONFIG_COMPILER_USE_GCC), y)
ifeq ($(CONFIG_COMPILER_USE_GPLUSPLUS), y)
$(error should not config CONFIG_COMPILER_USE_GCC  and CONFIG_COMPILER_USE_GPLUSPLUS at same time)
endif
else
ifeq ($(CONFIG_COMPILER_USE_GCC), y)
$(error should not config CONFIG_COMPILER_USE_GCC  and CONFIG_COMPILER_USE_GPLUSPLUS at same time)
endif
endif


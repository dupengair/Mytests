# =============================================================================
# Configurations for Center Makefile
# by dup
# 2012-05-12
# =============================================================================
MAKEFILE_CONFIG_INCLUDE=y


###################### User Configurations #############################
####config source file type
#CONFIG_SRC_C=y
CONFIG_SRC_CPP=y

####config output type
CONFIG_OBJ_EXEC=y
#CONFIG_OBJ_STATIC_LIB=y
#CONFIG_OBJ_DYNAMIC_LIB=y

####config compiler type
#CONFIG_COMPILER_USE_GCC=y
CONFIG_COMPILER_USE_GPLUSPLUS=y

####GDB debug
CONFIG_GDB_DEBUG=y

####CPP Standard
CONFIG_CPPSTD_C11=y
#CONFIG_CPPSTD_C0X=y
#CONFIG_CPPSTD_C98=y


###################### Configuration Check #############################
####Check source file type

ifneq ($(CONFIG_SRC_CPP)$(CONFIG_SRC_C), y)
$(error source file type should only be one)
endif

####Check output type
ifneq ($(CONFIG_OBJ_EXEC)$(CONFIG_OBJ_STATIC_LIB)$(CONFIG_OBJ_DYNAMIC_LIB), y)
$(error output type should only be one)
endif

####Check compiler type
ifneq ($(CONFIG_COMPILER_USE_GCC)$(CONFIG_COMPILER_USE_GPLUSPLUS), y)
$(error compiler type should only be one)
endif

####Check CPP Standard
ifneq ($(CONFIG_CPPSTD_C11)$(CONFIG_CPPSTD_C0X)$(CONFIG_CPPSTD_C98), y)
$(error CPP Standard should only be one)
endif


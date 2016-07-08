# =============================================================================
# Definitions for Center Makefile
# by dup
# 2012-05-12
# =============================================================================

###################### Check Includes #############################
MAKEFILE_RULES_INCLUDE=y

ifneq ($(MAKEFILE_CONFIG_INCLUDE), y)
$(error Config.mk should be included before Rules.mk)
endif


###################### Configure Definitions #############################
DEFAULTCD			:= cd
DEFAULTCP			:= cp -dpRf
DEFAULTRM			:= rm -rf
DEFAULTTAR		:= tar -zcf 
DEFAULTMV			:= mv 
DEFAULTLS			:= ls -hl 
DEFAULTMKDIR		:= mkdir -p
DEFAULTCHMOD	:= chmod -R
PWD             		:= $(shell pwd)

EMBED_PREFIX		:= arm_v5t_le-
EMBED_LDFLAGS	:= "-lpthread"
EMBED_HOST		:= arm


VERSION			= 1.0
MAKEFILE_V			= @
MAKE_PARA			= -s
MAKE_JOBS			= -j$(shell cat /proc/cpuinfo | grep processor | wc -l)


###################### Configure Definitions #############################
TARGET=test_13

INCLUDES = -I.
TOOLCHAIN_PREFIX = 
C_FLAGS =  -Wall -fdump-class-hierarchy
LD_FLAGS = 

OBJS_DIR			:= $(PWD)/objs

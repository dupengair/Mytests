PLATFORM = ARM
#PLATFORM = INTEL

ifeq ($(PLATFORM), INTEL)
ALSA_DIR = ../../../external/alsa-lib-1.0.24.1
ALSA_LIB_DIR = $(ALSA_DIR)libs/lib
else
ALSA_DIR = ../../../../../buildroot-2013.02/output/build/alsa-lib-1.0.26
ALSA_LIB_DIR = $(ALSA_DIR)/src/.libs
endif
ALSA_INC_DIR = $(ALSA_DIR)/include
ALSA_LIB = asound



PRJ_SRC_INC = -I$(ALSA_INC_DIR)
PRJ_LIBS_INC += -L$(ALSA_LIB_DIR)
PRJ_LIBS = -l$(ALSA_LIB)

ifeq ($(PLATFORM), INTEL)
PRJ_DEFINES += -DINTEL
endif


CFLAGS	+= $(PRJ_SRC_INC)
LDFLAGS	+= $(PRJ_LIBS_INC) $(PRJ_LIBS)
CROSS_COMPILE = arm-none-linux-gnueabi-
CC		= $(CROSS_COMPILE)g++ 

all: clean test_playraw test_playwave test_capture	

test_playraw:
	@echo "Building APP $@"
	@$(CC) $(CFLAGS) $(PRJ_DEFINES) $@.cpp -o $@ $(LDFLAGS)
	@echo "done"
	@echo
	
test_playwave:
	@echo "Building APP $@"
	@$(CC) $(CFLAGS) $(PRJ_DEFINES) $@.cpp -o $@ $(LDFLAGS)
	@echo "done"
	@echo
	
test_capture:
	@echo "Build: APP $@"
	@$(CC) $(CFLAGS) $(PRJ_DEFINES) $@.cpp -o $@ $(LDFLAGS)
	@echo "done"
	@echo
	
clean:
	@rm -f test_playraw test_capture test_playwave
	
	
	
	
	
	
	
	
	
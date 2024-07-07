SILENCE = @

#The stuff is mostly copypaste from good tutorials by James Grenning, see LICENSE for more details


COMPONENT_NAME = NoiseSynth

PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
$(error The environment variable CPPUTEST_HOME is not set. \
Set it to where cpputest is installed)
endif

TEST_SRC_DIRS += tests

MOCKS_SRC_DIRS += mocks

SRC_FILES += src/ReadMatrix.c
SRC_DIRS += src

CPPUTEST_USE_EXTENSIONS = Y

INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(CPPUTEST_HOME)/include/Platforms/Gcc
INCLUDE_DIRS += include


CPPUTEST_OBJS_DIR = test-obj

CPPUTEST_LIB_DIR = test-lib

ifeq ($(shell $(CC) -v 2>&1 | grep -c "clang"), 1)
CPPUTEST_WARNINGFLAGS += -Wno-unknown-warning-option
CPPUTEST_WARNINGFLAGS += -Wno-covered-switch-default
CPPUTEST_WARNINGFLAGS += -Wno-reserved-id-macro
CPPUTEST_WARNINGFLAGS += -Wno-keyword-macro
CPPUTEST_WARNINGFLAGS += -Wno-documentation
CPPUTEST_WARNINGFLAGS += -Wno-missing-noreturn
endif

CPPUTEST_WARNINGFLAGS += -Wall
CPPUTEST_WARNINGFLAGS += -Werror
CPPUTEST_WARNINGFLAGS += -Wfatal-errors
CPPUTEST_WARNINGFLAGS += -Wswitch-default
CPPUTEST_WARNINGFLAGS += -Wno-format-nonliteral
CPPUTEST_WARNINGFLAGS += -Wno-sign-conversion
CPPUTEST_WARNINGFLAGS += -Wno-pedantic
CPPUTEST_WARNINGFLAGS += -Wno-shadow
CPPUTEST_WARNINGFLAGS += -Wno-missing-field-initializers
CPPUTEST_WARNINGFLAGS += -Wno-unused-parameter
CPPUTEST_CFLAGS += -pedantic
CPPUTEST_CFLAGS += -Wno-missing-prototypes
CPPUTEST_CFLAGS += -Wno-strict-prototypes
CPPUTEST_CXXFLAGS += -Wno-c++14-compat
CPPUTEST_CXXFLAGS += --std=c++11
CPPUTEST_CXXFLAGS += -Wno-c++98-compat-pedantic
CPPUTEST_CXXFLAGS += -Wno-c++98-compat

# Coloroze output
CPPUTEST_EXE_FLAGS += -c

# --- LD_LIBRARIES -- Additional needed libraries can be added here.
# commented out example specifies math library
#LD_LIBRARIES += -lm


include $(CPPUTEST_HOME)/build/MakefileWorker.mk


clean: 
	
	if [ -f NoiseSynth_tests ]; then rm Noisesynth_tests; fi;

	if [ -d ./test-lib/ ]; then rm -r ./test-lib/; fi;
	
	if [ -d ./test-obj/ ]; then rm -r ./test-obj/; fi;
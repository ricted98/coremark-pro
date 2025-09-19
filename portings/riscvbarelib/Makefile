COREMARK_HOME=$(abspath ../..)
MITH_DIR=$(COREMARK_HOME)/mith
PORT_DIR=$(abspath .)
AL_DIR=$(PORT_DIR)/al
WL_DIR=$(PORT_DIR)/workloads

XLEN ?= 64

RISCV     ?= $(error missing RISCV)
RVB_HOME  ?= $(error missing RVB_HOME)
RVB_BUILD ?= $(RVB_HOME)/build
TARGET    ?= $(error missing TARGET)

OBJS += $(patsubst %.c,%.o,$(wildcard $(MITH_DIR)/src/*.c))
OBJS += $(patsubst %.c,%.o,$(wildcard $(AL_DIR)/src/*.c))

EXTRA_INCLUDES += -I$(MITH_DIR)/include
EXTRA_INCLUDES += -I$(AL_DIR)/include
EXTRA_INCLUDES += -I$(RVB_HOME)/drivers/uart16550/include
EXTRA_INCLUDES += -I$(RVB_HOME)/drivers/clint/include
EXTRA_INCLUDES += -I$(RVB_HOME)/drivers/uart16750/include
EXTRA_INCLUDES += -I$(RVB_HOME)/drivers/plic/include
EXTRA_INCLUDES += -I$(RVB_HOME)/drivers/clint_cheshire/include

CFLAGS += -DFAKE_FILEIO
CFLAGS += -DHOST_EXAMPLE_CODE=1
CFLAGS += -DUSE_CLOCK=1
CFLAGS += -DUSE_TH_PRINTF
# CFLAGS += -DTHDEBUG=5

CFLAGS += -iquote -O2 -Wall

ifeq ($(XLEN),64)
	CFLAGS += -DEE_SIZEOF_LONG=8
	CFLAGS += -DEE_SIZEOF_PTR=8
	CFLAGS += -DEE_PTR_ALIGN=8
else
	CFLAGS += -DEE_SIZEOF_LONG=4
	CFLAGS += -DEE_SIZEOF_PTR=4
	CFLAGS += -DEE_PTR_ALIGN=4
endif

include $(PORT_DIR)/xcmd.mk

include $(WL_DIR)/$(TARGET)/$(TARGET).mk

include $(RVB_BUILD)/makefile.include

ifeq ($(BSP_NCPUS), 1)
	CFLAGS += -DUSE_SINGLE_CONTEXT=1
else
	CFLAGS += -DAL_THREAD_RISCVBARELIB=1
endif

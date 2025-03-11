OBJS += $(COREMARK_HOME)/workloads/core/core.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/core/core_*.c))

ifeq ($(XLEN),64)
	CFLAGS += -DUSE_FP64
else
	CFLAGS += -DUSE_FP32
endif

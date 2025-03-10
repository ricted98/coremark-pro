OBJS += $(COREMARK_HOME)/workloads/core/core.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/core/core_*.c))

CFLAGS += -DUSE_FP64

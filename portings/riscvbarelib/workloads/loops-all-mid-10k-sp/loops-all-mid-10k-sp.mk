OBJS += $(COREMARK_HOME)/workloads/loops-all-mid-10k-sp/loops-all-mid-10k-sp.o
OBJS += $(COREMARK_HOME)/benchmarks/fp/loops/loops.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/fp/loops/ref-sp/*.c))

EXTRA_INCLUDES += -I$(COREMARK_HOME)/benchmarks/fp/loops

CFLAGS += -DUSE_MATH_H=1
CFLAGS += -DUSE_FP32=1
# CFLAGS += -DVERBOSE

EXTRA_LIBS += -lm

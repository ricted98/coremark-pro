OBJS += $(COREMARK_HOME)/workloads/sha-test/sha-test.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/darkmark/sha/*.c))

EXTRA_INCLUDES += -I$(COREMARK_HOME)/benchmarks/darkmark/sha

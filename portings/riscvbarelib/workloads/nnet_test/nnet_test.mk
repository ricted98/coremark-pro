OBJS += $(COREMARK_HOME)/workloads/nnet_test/nnet_test.o
OBJS += $(COREMARK_HOME)/benchmarks/fp/nnet/nnet.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/fp/nnet/ref/*.c))

EXTRA_INCLUDES += -I$(COREMARK_HOME)/benchmarks/fp/nnet

CFLAGS += -DUSE_MATH_H=1
CFLAGS += -DUSE_FP64=1

EXTRA_LIBS += -lm

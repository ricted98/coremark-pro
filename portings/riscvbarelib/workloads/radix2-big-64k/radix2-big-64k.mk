OBJS += $(COREMARK_HOME)/workloads/radix2-big-64k/radix2-big-64k.o
OBJS += $(COREMARK_HOME)/benchmarks/fp/fft_radix2/fft_radix2.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/fp/fft_radix2/ref/*.c))

EXTRA_INCLUDES += -I$(COREMARK_HOME)/benchmarks/fp/fft_radix2

CFLAGS += -DUSE_MATH_H=1
CFLAGS += -DUSE_FP64=1

EXTRA_LIBS += -lm

OBJS += $(COREMARK_HOME)/workloads/linear_alg-mid-100x100-sp/linear_alg-mid-100x100-sp.o
OBJS += $(COREMARK_HOME)/benchmarks/fp/linpack/linpack.o $(COREMARK_HOME)/benchmarks/fp/linpack/ref/inputs_f32.o

CFLAGS += -DUSE_MATH_H=1
CFLAGS += -DUSE_FP32=1

EXTRA_LIBS += -lm

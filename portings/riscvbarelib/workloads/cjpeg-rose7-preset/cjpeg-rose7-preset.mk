OBJS += $(COREMARK_HOME)/workloads/cjpeg-rose7-preset/cjpeg-rose7-preset.o
OBJS += $(COREMARK_HOME)/benchmarks/consumer_v2/cjpeg/data/Rose256_bmp.o
OBJS += $(patsubst %.c,%.o,$(wildcard $(COREMARK_HOME)/benchmarks/consumer_v2/cjpeg/*.c))

EXTRA_INCLUDES += -I$(COREMARK_HOME)/benchmarks/consumer_v2/cjpeg/data

ifeq ($(XLEN),64)
	CFLAGS += -DUSE_FP64=1
else
	CFLAGS += -DUSE_FP32=1
endif

CFLAGS += -DSELECT_PRESET_ID=1
CFLAGS += -DUSE_PRESET

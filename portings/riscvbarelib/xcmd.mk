# add support for argc/argv override using cli-like options
# e.g. make XCMD='-v1 -c4'
# --- config ---
XCMD         ?=

# --- helpers ---
empty   :=
space   := $(empty) $(empty)
comma   := ,

ifneq ($(strip $(XCMD)),)
  OV_LIST := $(TARGET) $(XCMD)
  OV_ARGC := $(words $(OV_LIST))
  OV_ARGV := {$(subst $(space),$(comma),$(foreach a,$(OV_LIST),"$(a)")) , NULL}

  CFLAGS  += -DARGS_OVERRIDE \
             -DARGC_OVERRIDE=$(OV_ARGC) \
             -D'ARGV_OVERRIDE=$(OV_ARGV)'
endif

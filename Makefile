###############################################################################
# EDIT
###############################################################################

CEU_DIR  ?= $(error set absolute path to "<ceu>" repository)
ARCH_SUB ?= poll

###############################################################################
# DO NOT EDIT
###############################################################################

ARD_DIR  = .
ARCH_DIR = $(ARD_DIR)/arch/$(ARCH_SUB)

include $(CEU_DIR)/Makefile

ifneq ($(MAKECMDGOALS),link)
ifeq ("$(wildcard $(ARD_DIR)/arch/up)","")
$(error run "make link")
endif
endif

link:
	rm -f $(ARD_DIR)/arch/up
	ln -s `readlink -f $(CEU_DIR)/arch` $(ARD_DIR)/arch/up
	rm -f samples
	ln -s samples-$(ARCH_SUB) samples

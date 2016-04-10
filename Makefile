###############################################################################
# EDIT
###############################################################################

CEU_DIR  ?= $(error set path to "<ceu>" repository)

###############################################################################
# DO NOT EDIT
###############################################################################

ARCH_SUB = poll
ARCH_DIR = arch/$(ARCH_SUB)

include $(CEU_DIR)/Makefile

link:
	rm -f arch/up
	ln -s `readlink -f $(CEU_DIR)/arch` arch/up
	rm -f samples
	ln -s samples-$(ARCH_SUB) samples

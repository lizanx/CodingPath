####################################
# Define common macros and functions
####################################
# This file should be the first included makefile in common.mk.

# Print this file name with full path
$(info +   Included  : $(realpath $(lastword $(MAKEFILE_LIST))))

# -----------------------------
# macros (don't take arguments)
# -----------------------------
# -------------------
# print-last-makefile
# -------------------
# Print the MOST RECENTLY included makefile with full path.
# For debugging, use this function at the top of each makefile, before any other includes, to see the current file name.
# (See: https://www.gnu.org/software/make/manual/html_node/Special-Variables.html)
# (See: http://timmurphy.org/2015/09/27/how-to-get-a-makefile-directory-path)
define print-last-makefile
  $(info +   Included  : $(realpath $(lastword $(MAKEFILE_LIST))))
endef

# -----------------
# print-description
# -----------------
# Print description text for the MOST RECENTLY included object or program makefile.
define print-description
  $(info ... $(description))
endef

# ----------------------------
# functions (take argument(s))
# ----------------------------
# ------------
# include-once
# ------------
# Include any makefile just once.
# Already included makefiles are in MAKEFILE_LIST, thus don't include if makefile matches any in that list.
# usage: $(eval $(call include-once, makefile))
define include-once
  ifeq (, $(filter $1,$(MAKEFILE_LIST)))
    include $1
  endif
endef

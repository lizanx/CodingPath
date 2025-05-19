# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)


# Subdirectories, in random order
# dir	:= $(d)/test
# include		$(dir)/Rules.mk


# Local variables

OBJS_$(d)	:= $(d)/car.o $(d)/car_impl.o
DEPS_$(d)	:= $(OBJS_$(d):%=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) \
		   $(d)/car.a


# Local rules

# $(OBJS_$(d)):	CF_TGT := -I$(d)

$(d)/car.a:	$(OBJS_$(d)) $(d)/Rules.mk
	ar rcs $@ $^


# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))


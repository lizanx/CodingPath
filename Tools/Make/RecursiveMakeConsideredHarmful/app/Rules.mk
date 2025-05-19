# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)


# Local rules and targets

TGTS_$(d)	:= $(d)/main
DEPS_$(d)	:= $(TGTS_$(d):%=%.d)

TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))
CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(DEPS_$(d))

$(TGTS_$(d)):	$(d)/Rules.mk

# $(TGTS_$(d)):	CF_TGT := -Icommon -DRADDB=\"$(DIR_ETC)\"
$(TGTS_$(d)):	LL_TGT := car/car.a
$(TGTS_$(d)):	$(d)/main.c car/car.a
		$(COMPLINK)


# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))


.PHONY: test_expansion assign_if_not_defined override_cmd_args \
	target_specific_var TargetOne TargetTwo \
	conditional


ImmediatelyExpanded := Hello $(Name)
LaterExpanded = Hello $(Name)
Name = Christine
test_expansion:
	@echo "===== test_expansion ====="
	@echo "Immediately expanded var:(no name included)"
	@echo $(ImmediatelyExpanded)
	@echo "Later expanded var:(name included)"
	@echo $(LaterExpanded)


VarOne = Defined
VarOne ?= Redfined
VarTwo ?= Redefined
assign_if_not_defined:
	@echo "===== assign_if_not_defined ====="
	@echo "VarOne = "$(VarOne)
	@echo "VarTwo = "$(VarTwo)


override OptionOne = "This is always the same overridden value!"
OptionTwo = "This may differ when passing from command line!"
# make override_cmd_args OptionOne=abc OptionTwo=def
override_cmd_args:
	@echo "===== override_cmd_args ====="
	@echo "OptionOne = "$(OptionOne)
	@echo "OptionTwo = "$(OptionTwo)


TargetOne:
	@echo "[TargetOne]Target specific var = "$(TargetSpecificVar)
TargetTwo:
	@echo "[TargetTwo]Target specific var = "$(TargetSpecificVar)
TargetTwo: TargetSpecificVar = This var only has value for TargetTwo
target_specific_var: TargetOne TargetTwo


foo =
bar = bar
space =$(foo) # a trailing space
conditional:
	@echo "===== conditional ====="
ifeq ($(foo),)
	@echo "foo is empty"
else
	@echo "foo not empty"
endif
ifeq ($(space),)
	@echo "space is empty"
else
	@echo "space not empty"
endif
ifdef bar
	@echo "bar defined"
else
	@echo "bar not defined"
endif
ifdef foo
	@echo "foo defined"
else
	@echo "foo not defined"
endif
ifdef space
	@echo "space defined"
else
	@echo "space not defined"
endif

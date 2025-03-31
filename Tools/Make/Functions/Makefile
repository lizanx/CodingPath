.PHONY: subst_fn patsubst_fn foreach_fn if_fn call_fn filter_fn

AllFiles := a.h a.c b.h b.c a.result b.result
SrcFiles := a.h b.h a.c b.c
ObjectFiles := a.o b.o

subst_fn:
	@echo "Src files of ObjectFiles: "$(subst .o,.c,$(ObjectFiles))

patsubst_fn:
	@echo "Src files of ObjectFiles: "$(patsubst %.o,%.c,$(ObjectFiles))
	@echo "Src files of ObjectFiles(shorthand): "$(ObjectFiles:%.o=%.c)
	@echo "Src header files of ObjectFiles: "$(patsubst %.o,%.h,$(ObjectFiles))

foreach_fn:
	@echo "Append prefix to SrcFiles: "$(foreach word,$(SrcFiles),Prefix-$(word))

foo =#empty
bar = not empty
var_a := $(if $(foo),Var a not empty,Var a empty)
var_b := $(if $(bar),Var b not empty,Var b empty)
if_fn:
	@echo "var_a = "$(var_a)
	@echo "var_b = "$(var_b)

BuildDirFn = src/$(1)/$(2)/$(3)
call_fn:
	@echo "Build dir for include,demo,simple.h: "$(call BuildDirFn,include,demo,simple.h)

filter_fn:
	@echo "Headers in AllFiles: "$(filter %.h,$(AllFiles))
	@echo "C files in AllFiles: "$(filter %.c,$(AllFiles))
	@echo "Results in AllFiles: "$(filter %.result,$(AllFiles))
	@echo "Non-result files in AllFiles: "$(filter-out %.result,$(AllFiles))

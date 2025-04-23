macro(MyMacro myArg)
    message("1. myArg = ${myArg}")
    set(myArg "second value") # macro is simple text substitution, this will affect outer definition of "myVar"
    message("2. myArg = ${myArg}") # due to simple text substitution, this won't print "second value"
endmacro()


set(VAR "first value")
message("Before: VAR = ${VAR}")
MyMacro(${VAR})
message("After: VAR = ${VAR}")

message("\nTest with same var name:")
set(myArg "first value")
message("Before: myArg = ${myArg}")
MyMacro(${myArg})
message("After: myArg = ${myArg}")

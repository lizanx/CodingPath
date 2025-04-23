function(MyFunc FirstArg SecondArg)
    message("Function: ${CMAKE_CURRENT_FUNCTION}")
    message("File: ${CMAKE_CURRENT_FUNCTION_LIST_FILE}")
    message("First argument: ${FirstArg}")
    message("Second argument: ${SecondArg}")
    set(FirstArg "new value") # function creates new scope, this won't affect outer scope vars
    set(SecondArg "new value") # function creates new scope, this won't affect outer scope vars
    message("First argument: ${FirstArg}")
    message("Second argument: ${SecondArg}")

    message("Arguments count: ${ARGC}")
    message("All arguments: ${ARGV0} ${ARGV1} ${ARGV2}")
endfunction(MyFunc FirstArg SecondArg)

set(FirstArg "hello")
set(SecondArg "world")
MyFunc(${FirstArg} ${SecondArg} "C++")
message("(Global)First argument: ${FirstArg}")
message("(Global)Second argument: ${SecondArg}")

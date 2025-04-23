# message(WARNING "This is a warning message!")
# message(FATAL_ERROR "This fatal error will stop further execution.")
# message("This message won't show if above fatal error message exists.")

function(my_func)
    list(APPEND CMAKE_MESSAGE_CONTEXT "my_func")
    message("Message inside function 'my_func'")
endfunction()

list(APPEND CMAKE_MESSAGE_INDENT "  ")
list(APPEND CMAKE_MESSAGE_CONTEXT "global")
message("Message in global scope.")
my_func()
message("Message in global scope(after calling 'my_func').")

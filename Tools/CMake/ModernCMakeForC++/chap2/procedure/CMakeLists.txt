cmake_minimum_required(VERSION 3.20.0)
project(Procedure)

macro(main)
    set_up_target()
    add_dependencies()
    post_process()
endmacro()

function(set_up_target)
    message("Setting target...")
endfunction()

function(add_dependencies)
    message("Adding dependencies...")
endfunction()

function(post_process)
    message("Doing some post processing...")
endfunction()

main()

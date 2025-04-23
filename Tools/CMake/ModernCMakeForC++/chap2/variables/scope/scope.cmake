cmake_minimum_required(VERSION 3.20.0)

set(V 1)
message("Global(before): V = " ${V})
block() # outer block
    message("> Outer block: V = " ${V})
    set(V 2)
    block() # inner block
        message(">> Inner block: V = " ${V})
        set(V 3)
        message("<< Inner block: V = " ${V})
    endblock()
    message("< Outer block: V = " ${V})
endblock()
message("Global(after): V = " ${V})

message("\n\nPropagate V to outer scope:")
set(V 1)
message("Global(before): V = " ${V})
block(PROPAGATE V) # outer block
    message("> Outer block: V = " ${V})
    set(V 2)
    block() # inner block
        message(">> Inner block: V = " ${V})
        set(V 3)
        message("<< Inner block: V = " ${V})
    endblock()
    message("< Outer block: V = " ${V})
endblock()
message("Global(after): V = " ${V})

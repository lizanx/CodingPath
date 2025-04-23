# These list definitions are the same
set(LIST_1 a list of 5 elements)
set(LIST_2 "a;list;of;5;elements")
set(LIST_3 a list "of;5;elements")

message("LIST_1: " ${LIST_1})
message("LIST_2: " ${LIST_2})
message("LIST_3: " ${LIST_3})

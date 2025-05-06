# add_library(calc_test calc_test.cpp)
# target_link_libraries(calc_test PRIVATE program)

# add_library(program_test program_test.cpp)
# target_link_libraries(calc_test PRIVATE program)

add_executable(unit_test unit_test.cpp program_test.cpp calc_test.cpp)
target_link_libraries(unit_test PRIVATE program)

add_test(NAME CalcSumTwoInts COMMAND unit_test 1)
add_test(NAME CalcMultiplyTwoInts COMMAND unit_test 2)
add_test(NAME CompleteProgram COMMAND unit_test 3)

# include(Valgrind)
# AddValgrind(unit_test)

include(MemCheck)
AddMemCheck(unit_test)

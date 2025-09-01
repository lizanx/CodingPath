touch mtrace.log
export MALLOC_TRACE=mtrace.log
../build/program
mtrace ../build/program mtrace.log

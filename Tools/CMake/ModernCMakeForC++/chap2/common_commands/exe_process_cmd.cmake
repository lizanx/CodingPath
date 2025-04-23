execute_process(COMMAND "ls" "-alh" RESULT_VARIABLE CMD_RESULT OUTPUT_VARIABLE CMD_OUTPUT)
message("Exit code: ${CMD_RESULT}")
message("\n--> Command output:\n${CMD_OUTPUT}")

add_executable(vehicle_test vehicle_test.cpp)
target_link_libraries(vehicle_test PRIVATE vehicle_static)
AddTest(vehicle_test)

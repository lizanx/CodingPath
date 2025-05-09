add_library(vehicle_obj OBJECT Audi.cpp Volvo.cpp)
target_include_directories(vehicle_obj PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
set_target_properties(vehicle_obj PROPERTIES POSITION_INDEPENDENT_CODE 1)
set(VEHICLE_HEADERS include/vehicle/Vehicle.hpp include/vehicle/car/Audi.hpp include/vehicle/car/Volvo.hpp)
target_sources(vehicle_obj PUBLIC
    FILE_SET HEADERS
    TYPE HEADERS
    BASE_DIRS include
    FILES ${VEHICLE_HEADERS})

InstrumentForCoverage(vehicle_obj)

add_library(vehicle_static STATIC)
target_link_libraries(vehicle_static PUBLIC vehicle_obj)
add_library(vehicle_shared SHARED)
target_link_libraries(vehicle_shared PUBLIC vehicle_obj)

CleanCoverage(vehicle_static)
Format(vehicle_static .)
AddCppCheck(vehicle_obj)
Doxygen(vehicle src/vehicle)

# Main program, for debug only
add_library(main_obj OBJECT main.cpp bootstrap.cpp)
target_include_directories(main_obj PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
add_executable(main_static)
target_link_libraries(main_static PRIVATE main_obj vehicle_static)
add_executable(main_shared)
target_link_libraries(main_shared PRIVATE main_obj vehicle_shared)

# Installation
include(GNUInstallDirs)

install(TARGETS vehicle_obj vehicle_static vehicle_shared
    EXPORT VehicleLibrary
    ARCHIVE COMPONENT development
    LIBRARY COMPONENT runtime
    FILE_SET HEADERS COMPONENT runtime)

if(UNIX)
    install(CODE "execute_process(COMMAND ldconfig)")
endif()

install(EXPORT VehicleLibrary
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/vehicle/cmake
    NAMESPACE Vehicle::
    COMPONENT runtime)

install(FILES VehicleConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/vehicle/cmake)

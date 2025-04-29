# Define the IMPORTED target.
function(define_imported_target lib_path header_path)
    add_library(PQXX::PQXX UNKNOWN IMPORTED)
    set_target_properties(PQXX::PQXX
        PROPERTIES
            IMPORTED_LOCATION ${lib_path}
            INTERFACE_INCLUDE_DIRECTORIES ${header_path})
    set(PQXX_FOUND 1 CACHE INTERNAL "PQXX found" FORCE)
    set(PQXX_LIBRARIES ${lib_path} CACHE STRING "Path to pqxx library" FORCE)
    set(PQXX_INCLUDES ${header_path} CACHE STRING "Path to pqxx headers" FORCE)
    mark_as_advanced(FORCE PQXX_LIBRARIES)
    mark_as_advanced(FORCE PQXX_INCLUDES)
endfunction()

# If the configured before and lib/header path are cached, use them directly.
if(PQXX_LIBRARIES AND PQXX_INCLUDES)
    message("PQXX already cached: lib path[${PQXX_LIBRARIES}], header path[${PQXX_INCLUDES}]")
    define_imported_target(${PQXX_LIBRARIES} ${PQXX_INCLUDES})
    return()
endif()

# Search for nested dependency - PostgreSQL
# Pass "REQUIRED" from PQXX to PostgreSQL
set(REQUIRED_ARG)
if(PQXX_FIND_REQUIRED)
    set(REQUIRED_ARG REQUIRED)
endif()
# Pass "QUIET" from PQXX to PostgreSQL
set(QUIET_ARG)
if(PQXX_FIND_QUIETLY)
    set(QUIET_ARG QUIET)
endif()
# Find dependent package
find_package(PostgreSQL ${REQUIRED_ARG} ${QUIET_ARG})

# Search for PQXX lib path
file(TO_CMAKE_PATH "$ENV{PQXX_DIR}" _PQXX_DIR) # Generally, pqxx lib path is stored in env var "PQXX_DIR"
# "find_library" command will automatically add OS-determined lib file extensions.
find_library(PQXX_LIB_PATH
    NAMES libpqxx pqxx
    PATHS
        ${_PQXX_DIR}/lib/${CMAKE_LIBRARY_ARCHITECTURE}
        /usr/lib
    NO_DEFAULT_PATH)

# Search for PQXX header files
find_path(PQXX_HEADER_PATH
    NAMES pqxx/pqxx # this is header, for use like "#include <pqxx/pqxx>"
    PATHS
        ${_PQXX_DIR}/include
        /usr/include
    NO_DEFAULT_PATH)

# Return the final results
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    PQXX DEFAULT_MSG PQXX_LIB_PATH PQXX_HEADER_PATH
)
if(PQXX_FOUND)
    define_imported_target(
        "${PQXX_LIB_PATH};${POSTGRES_LIBRARIES}"
        "${PQXX_HEADER_PATH};${POSTGRES_INCLUDE_DIRECTORIES}"
    )
elseif(PQXX_FIND_REQUIRED)
    message(FATAL_ERROR "Required library PQXX not found!")
endif()

add_library(calc STATIC calc.cpp)

target_sources(calc
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src/include
        FILES ${PROJECT_SOURCE_DIR}/src/include/calc.hpp
)

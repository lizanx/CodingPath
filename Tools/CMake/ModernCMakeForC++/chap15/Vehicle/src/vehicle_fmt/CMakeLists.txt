include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281 # 10.2.1
)
FetchContent_MakeAvailable(fmt)

add_executable(main_fmt main.cpp bootstrap.cpp)
target_link_libraries(main_fmt PRIVATE vehicle_obj fmt::fmt)

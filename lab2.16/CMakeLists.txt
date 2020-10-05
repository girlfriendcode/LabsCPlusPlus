set(core_SRCS main.cpp)
add_library(core ${core_SRCS})
add_executable(exe main.cpp lab2.16.cpp lab2.16.h)
target_link_libraries(exe core)
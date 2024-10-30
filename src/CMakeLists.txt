file(GLOB_RECURSE SRC "*.cpp")

message(${SRC})

add_executable(test ${SRC})
cmake_minimum_required(VERSION 3.28)
project(tjs2)


set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
add_definitions(-DUNICODE -DTJS_NO_REGEXP)

set(KRKRZ_INC /)
file(GLOB KRKRZ_SRC "*.cpp")

include_directories(${KRKRZ_INC})

add_executable(tjs2 ${KRKRZ_SRC})



cmake_minimum_required(VERSION 3.1)

project(msu2020progs)

set(PROG_SRC Source.c prog.c)
set(PROG_HDR prog.h)

add_executable(${PROJECT_NAME} ${PROG_SRC} ${PROG_HDR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

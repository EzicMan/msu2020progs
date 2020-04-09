cmake_minimum_required(VERSION 3.1)

project(msu2020progs)

set(REMOVE_SMILES_SRC Source.c prog.c)
set(REMOVE_SMILES_HDR prog.h)

add_executable(${PROJECT_NAME} ${REMOVE_SMILES_SRC} ${REMOVE_SMILES_HDR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
cmake_minimum_required(VERSION 3.26)
project(Compile)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compile old/main.cpp)
add_executable(compile old/main.cpp
        old/syntax.h)

add_executable(own old/own.cpp)
add_executable(own2 old/own2.cpp)
add_executable(own3 old/own3.cpp)
add_executable(syntax old/syntax.cpp)
add_executable(exp2 old/exp2.cpp
        old/syntax.h)
add_executable(own4 old/own4.cpp)
add_executable(exp2pro old/exp2pro.cpp)
add_executable(SemanticMeaning old/SemanticMeaning.cpp)
add_executable(FF1 old/FF1.cpp)
add_executable(midcode old/midcode.c)
add_executable(FF1Pre old/FF1Pre.cpp)


add_executable(start main.cpp E1/E1.cpp E1/E1.h E3/Simulator.h E3/Simulator.cpp E3/E3.cpp E3/E3.h)
add_executable(Simulator E3/Simulator.h E3/Simulator.cpp)
add_executable(E1 E1/E1.cpp E1/E1.h)
add_executable(E3 E3/E3.cpp E3/E3.h)
add_executable(E2 E2/E2.cpp)
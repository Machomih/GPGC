cmake_minimum_required(VERSION 3.27)
project(GPGC)

set(CMAKE_CXX_STANDARD 17)

add_executable(T1 Lab1/Lab1.cpp)
add_executable(T2 Lab2/Lab2.cpp)
add_executable(T3 "Lab3/t301 FilimonMihail Condurat Victor.cpp")
add_executable(T32 "Lab3/t302 Filimon Mihail Condurat Victor.cpp")
add_executable(T4 Lab4/Lab4.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(T1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(T1 ${GLUT_LIB})
target_link_libraries(T2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(T2 ${GLUT_LIB})
target_link_libraries(T3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(T3 ${GLUT_LIB})
target_link_libraries(T32 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(T32 ${GLUT_LIB})
target_link_libraries(T4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(T4 ${GLUT_LIB})



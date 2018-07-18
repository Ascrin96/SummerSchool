cmake_minimum_required(VERSION 3.1)

project(GateDetector)

set(CMAKE_CXX_STANDARD 14 -std=c++11)
set(NAME_SRC
	main.cpp 
    utills.cpp
    gate.cpp 
    detectiongate.cpp
    imageworker.cpp
    detectionmarkup.cpp
    markup.cpp
)

set(NAME_HEADRES
    detection.h
    gobject.h
    utills.h
    gate.h 
    detectiongate.h 
    context.h 
    imageworker.h
    detectionmarkup.h 
    markup.h
)

find_package(Threads)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GateDetect ${NAME_SRC} ${NAME_HEADERS}})

target_link_libraries( GateDetector
#	${CMAKE_THREAD_LIBS_INIT}
	${OpenCV_LIBS}
)
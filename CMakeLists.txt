cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        bmp.cpp
        bmp.h
        image.cpp
        image.h
        filters.cpp filters.h test.cpp test.h parser.cpp parser.h Filter_factory.cpp Filter_factory.h)

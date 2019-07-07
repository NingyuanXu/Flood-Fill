cmake_minimum_required(VERSION 3.13)
project(pa2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs221util)
include_directories(cs221util/lodepng)

add_executable(pa2
        cs221util/lodepng/lodepng.cpp
        cs221util/lodepng/lodepng.h
        cs221util/catch.hpp
        cs221util/HSLAPixel.cpp
        cs221util/HSLAPixel.h
        cs221util/json.hpp
        cs221util/PNG.cpp
        cs221util/PNG.h
        cs221util/RGB_HSL.h
        animation.cpp
        animation.h
        borderColorPicker.cpp
        borderColorPicker.h
        colorPicker.h
        deque.cpp
        deque.h
        filler.cpp
        filler.h
        ordering_structure.h
        queue.cpp
        queue.h
        rainbowColorPicker.cpp
        rainbowColorPicker.h
        stack.cpp
        stack.h
        stripeColorPicker.cpp
        stripeColorPicker.h
        testFills.cpp
        testStackQueue.cpp)
